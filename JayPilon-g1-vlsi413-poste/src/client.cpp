#include "client.h"      // Includes client-side functions for TCP/IP communication
#include "constants.h"   // Includes project-specific constants

// Function to establish a connection to the server
int Client::ConnectToServer(const std::string &server_ip, int port) {
    const auto sock = socket(AF_INET, SOCK_STREAM, 0);               // Create a socket for communication
    if (sock < 0) {                                                 // Check if the socket creation failed
        perror("Erreur de création du socket");                     // Print an error message if socket creation failed
        return -1;                                                  // Return -1 to indicate failure
    }

    sockaddr_in serv_addr;                                          // Structure to hold server address information
    serv_addr.sin_family = AF_INET;                                 // Specify IPv4 address family
    serv_addr.sin_port = htons(port);                               // Convert port number to network byte order

    if (inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr) <= 0) {  // Convert IP address to binary format
        perror("Adresse invalide / non supportée");                 // Print error for invalid IP address
        close(sock);                                                // Close the socket
        return -1;                                                  // Return -1 to indicate failure
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {  // Attempt to connect to the server
        perror("Connexion échouée");                                           // Print error if connection failed
        close(sock);                                                           // Close the socket
        return -1;                                                             // Return -1 to indicate failure
    }

    std::cout << "Connecté au serveur." << std::endl;                          // Print a success message
    return sock;                                                               // Return the socket descriptor (positive if the sock is successfully created)
}

// Function to receive an image from the server
cv::Mat Client::ReceiveImage(int sock) {
    int imgSize;                                                               // Variable to hold the size of the image
    recv(sock, &imgSize, sizeof(imgSize), 0);                                  // Receive the image size from the server

    std::vector<uchar> buffer(imgSize);                                        // Buffer to hold the image data
    recv(sock, buffer.data(), imgSize, MSG_WAITALL);                           // Receive the complete image data

    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);                    // Decode the image from the buffer
    return image;                                                              // Return the decoded image
}

// Function to send a command to the server
void Client::SendCommand(int sock, char command) {
    send(sock, &command, sizeof(command), 0);                                  // Send a single character command to the server
}

// Function to close the client connection
void Client::CloseClient(int sock) {
    if (sock >= 0)                                                             // Check if the socket is valid (positive if the sock is successfully created)
        close(sock);                                                           // Close the socket
}

// Function to allow the user to select a resolution
std::pair<int, int> Client::SelectResolution() {
    std::cout << "Sélectionnez une résolution :" << std::endl;                 // Prompt user to select a resolution
    for (size_t i = 0; i < RESOLUTIONS.size(); ++i) {                          // Loop through available resolutions
        std::cout << i + 1 << ". " << RESOLUTIONS[i].first << " x "            // Display the resolution index and values
                  << RESOLUTIONS[i].second << std::endl;
    }
    int choice;                                                                // Variable to store user's choice of res
    std::cout << "Choisissez un numéro : ";
    std::cin >> choice;                                                        // Get user's choise of res
    while (std::cin.fail() || choice < 1 || choice > RESOLUTIONS.size()) {     // Validate the user's choice
        std::cin.clear();                                                      // Clear the fail state of std::cin (won't process further input otherwise)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    // Discard invalid input
        std::cout << "Choix invalide. Réessayez : ";                           // Prompt for invalid input
        std::cin >> choice;                                                    // Get user's input again
    }
    return RESOLUTIONS[choice - 1];                                            // Return the selected resolution
}

// Function to send the selected resolution to the server
void Client::SendResolution(int sock, const std::pair<int, int> &resolution) {
    const auto width = resolution.first;                                       // Extract the width from the resolution pair
    const auto height = resolution.second;                                     // Extract the height from the resolution pair
    send(sock, &width, sizeof(width), 0);                                      // Send the width to the server
    send(sock, &height, sizeof(height), 0);                                    // Send the height to the server
}

// Function to receive a command from the server
char Client::ReceiveCommand(int sock) {
    char command;                                                              // Variable to store the command
    recv(sock, &command, sizeof(command), 0);                                  // Receive the command from the server
    return command;                                                            // Return the received command
}

///////////////////////////////////// LIVRABLE 6 //////////////////////////////////////////  

void Client::SendFilteredDataToServer(int sock, const std::string &filteredData) {
    const auto msgSize = static_cast<int> (filteredData.size());
    std::cout << msgSize << std::endl;
    send(sock, &msgSize, sizeof(msgSize), 0);
    send(sock, filteredData.c_str(), msgSize, 0);                                                     // Close the connection
}