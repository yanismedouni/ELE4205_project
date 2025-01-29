#include "client.h"         // Includes client functions for TCP/IP communication
#include "constants.h"      // Includes project-specific constants (e.g., READY, NO_LIGHT)
#include "qrreader.h"       // Includes QR code detection and decoding functionality

int main() {
    const auto sock = Client::ConnectToServer("192.168.7.2", 4099);  // Attempt to connect to the server on port 4099
    if (sock >= 0) {                                                 // If sock >= 0, the connection is established
        auto resolution = Client::SelectResolution();                // Allow user to select image resolution
        Client::SendResolution(sock, resolution);                    // Send the selected resolution to the server
        auto serverState = READY;                                    // Initialize server state as READY
        auto imageCounter = 0;                                       // Counter to name saved images sequentially
        cv::Mat image;                                               // OpenCV matrix to hold the received image

        while (true) {                                               // Infinite loop to process incoming data
            serverState = Client::ReceiveCommand(sock);              // Receive server state (READY, NO_LIGHT, or BUTTON_PUSHED)
            Client::SendCommand(sock, 'g');                          // Send acknowledgment to the server
            if (serverState == NO_LIGHT) {                           // If no light is detected (dark room)
                Client::ReceiveCommand(sock);                        // Wait for the next server command
            } else {                                                 // Otherwise, receive the image
                image = Client::ReceiveImage(sock);                  // Retrieve image from server
                if (image.empty()) break;                            // Exit loop if no image is received
            }

            if (serverState == 'B') {                                // If the button was pressed
                pid_t pid = fork();                                  // Fork a new process for QR code processing
                if (pid == 0) {                                      // In the child process
                    std::string fileName = "output/image" + std::to_string(imageCounter) + ".png";  // Construct the filename for the original image
                    cv::imwrite(fileName, image);                                                   // Save the original image to disk

                    std::string decodedText;                                            // Variable to store decoded QR text
                    std::vector<cv::Point> boundingBox;                                 // Vector to hold the QR code bounding box
                    if (QR::DetectAndDecodeQRCode(image, decodedText, boundingBox)) {   // Attempt to detect and decode QR code
                        std::cout << "QR Code Detected: " << decodedText << std::endl;  // If detected, print the QR code text
                        std::string fileNameModified =
                            "output/image" + std::to_string(imageCounter) + "_qr.png";  // Construct filename for the modified image

                        QR::DrawBoundingBox(image, boundingBox);                        // Draw bounding box on the image
                        cv::imwrite(fileNameModified, image);                           // Save modified image with bounding box

                        std::string filteredData = QR::FilterQRCodeData(decodedText);   // Filter the decoded QR code data //new
                        std::cout << "Filtered Data: " << filteredData << std::endl;    // Print the filtered data to test the function //new

                        const auto sock2 = Client::ConnectToServer("192.168.7.2", 4098);  // Attempt to connect to the server on port 4099
                        if (sock2 >= 0) {                                                 // If sock >= 0, the connection is established
                            std::cout<< "Second connexion established succesfully !" << std::endl;
                            Client::SendFilteredDataToServer(sock2, filteredData);
                        }
                        Client::CloseClient(sock2);                                                       // Close the TCP connection    
                    } else {
                        std::string errorMessage = "-1";
                        std::cout << "No QR Code detected." << errorMessage << std::endl;
                        const auto sock2 = Client::ConnectToServer("192.168.7.2", 4098);  // Attempt to connect to the server on port 4099
                        if (sock2 >= 0) {                                                 // If sock >= 0, the connection is established
                            std::cout<< "Second connexion established succesfully !" << std::endl;
                            Client::SendFilteredDataToServer(sock2, errorMessage);
                        }
                        Client::CloseClient(sock2);              // If no QR code is detected, print a message
                    }
                    exit(0);                                                            // Exit the child process
                }
                ++imageCounter;                                                         // Increment the image counter for the next image
            }

            cv::imshow("Image recue", image);                                         // Display the received image
            auto key = cv::waitKey(30);                                               // Wait for a key press for 30 ms

            if (key == 27) {                                                          // If ESC key is pressed
                Client::SendCommand(sock, 'q');                                       // Notify server to terminate the session
                cv::destroyWindow("Image recue");                                     // Close the OpenCV display window
                break;                                                                // Exit the loop
            } else if (key == 'm') {                                                  // If 'm' key is pressed
                Client::SendCommand(sock, 'm');                                       // Notify server to change resolution
                auto resolution = Client::SelectResolution();                         // Allow user to select a new resolution
                Client::SendResolution(sock, resolution);                             // Send the updated resolution to the server
            } else {                                                                  // For any other key press
                Client::SendCommand(sock, 'c');                                       // Notify server to continue
            }
        }
    }
    Client::CloseClient(sock);                                                       // Close the TCP connection
    return 0;                                                                        // Exit the program
}
