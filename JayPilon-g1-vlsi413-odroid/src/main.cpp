#include "server.h"       // Handles server-side TCP/IP communication
#include "camera.h"       // Manages camera operations
#include "gpio.h"         // Handles GPIO interactions (button, light sensor)
#include "button.h"          // C
#include "constants.h"    // Contains predefined constants for states
#include "morse.h"        // Manages Morse code functionality (writing and playing)

void LoadBuzzerModules() {
    // Load the pwm-meson module
    if (system("modprobe pwm-meson") != 0) {
        std::cerr << "Error: Failed to load pwm-meson module." << std::endl;
    } else {
        std::cout << "pwm-meson module loaded successfully." << std::endl;
    }

    // Load the pwm-ctrl module
    if (system("modprobe pwm-ctrl") != 0) {
        std::cerr << "Error: Failed to load pwm-ctrl module." << std::endl;
    } else {
        std::cout << "pwm-ctrl module loaded successfully." << std::endl;
    }
}

// Main function to manage server operations
int main() {
    LoadBuzzerModules();
    Button button("/sys/class/gpio/gpio228/value");
    // Start the server on port 4099 and get the server file descriptor
    const auto server_fd = Server::StartServer(4099);  // Start the server
    if (server_fd >= 0) {                              // If server starts successfully
        const auto client_fd = Server::AcceptClient(server_fd);  // Accept a client connection
        if (client_fd >= 0) {                                   // If client connects successfully
            int width;                                          // Image width for camera
            int height;                                         // Image height for camera
            cv::VideoCapture cap;                              // OpenCV VideoCapture object for camera
            recv(client_fd, &width, sizeof(width), 0);          // Receive width from the client
            recv(client_fd, &height, sizeof(height), 0);        // Receive height from the client
            cap = Cam::CreateCamera(width, height);             // Initialize camera with given resolution
            auto serverState = READY;                           // Initialize server state as READY

            // Main server loop
            while (true) {
                serverState = GPIO::GetServerState(button);           // Get the current server state from GPIO
                Server::SendChar(client_fd, serverState);       // Notify the client of the current server state
                if (Server::ReceiveCommand(client_fd) != 'g')   // If client does not send 'g', exit the loop
                    break;

                // Handle NO_LIGHT state
                if (serverState == NO_LIGHT) {
                    Server::SendChar(client_fd, serverState);   // Inform the client of the NO_LIGHT state
                }
                // Handle other states (e.g., READY or BUTTON_PUSHED)
                else {
                    cv::Mat image;                              // Image container for captured frame
                    if (!Server::CaptureImage(cap, image))      // Capture an image from the camera
                        break;                                  // Exit if image capture fails
                    Server::SendImage(client_fd, image);        // Send the captured image to the client

                    // Handle BUTTON_PUSHED state
                    if (serverState == BUTTON_PUSHED) {
                        pid_t pid = fork();                     // Fork a new process for QR code processing
                        if (pid == 0) {                         // Child process
                            std::string filteredMessage = 
                                Server::ReceiveFilteredDataFromClient();  // Receive filtered data (QR code text)
                            std::cout << "Filtered message: " 
                                      << filteredMessage << std::endl;    // Print the received message

                            if (filteredMessage != "-1") {      // If a valid message is received
                                WriteMorseToFile(filteredMessage);      // Write the message in Morse code format
                                auto parser = Morse();                 // Create a Morse parser instance
                                parser.ParseSongFile(MESSAGE_FILENAME); // Parse the Morse code file
                                parser.PlaySong();                     // Play the Morse code as sound
                            }
                            exit(0);                            // Exit the child process
                        }
                    }
                }

                // Handle client commands (e.g., 'q' to quit or 'm' to change resolution)
                auto command = Server::ReceiveCommand(client_fd); // Receive a command from the client
                if (command == 'q')                               // If 'q', quit the loop
                    break;
                else if (command == 'm') {                        // If 'm', change camera resolution
                    cap.release();                                // Release the current camera
                    recv(client_fd, &width, sizeof(width), 0);    // Receive new width from the client
                    recv(client_fd, &height, sizeof(height), 0);  // Receive new height from the client
                    cap = Cam::CreateCamera(width, height);       // Reinitialize the camera with new resolution
                }
            }

            cap.release();                                        // Release the camera before exiting
        }
        Server::CloseConnection(server_fd, client_fd);            // Close server and client connections
    }
    return 0;                                                     // Exit the program
}
