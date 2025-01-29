#ifndef CLIENT_H
#define CLIENT_H

#include <string>         // Pour utiliser std::string
#include <netinet/in.h>   // Pour sockaddr_in
#include <opencv2/opencv.hpp> // Pour le type cv::Mat
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

namespace Client {
    /// @brief Connects to a server using the specified IP address and port.
    /// @param server_ip The IP address of the server to connect to.
    /// @param port The port number on the server to connect to.
    /// @return The socket file descriptor if successful, or -1 if the connection fails.
    int ConnectToServer(const std::string &server_ip, int port);

    /// @brief Receives an image from the server over a socket.
    /// @param sock The socket file descriptor for the connection to the server.
    /// @return The received image as a cv::Mat object. Returns an empty cv::Mat if an error occurs.
    cv::Mat ReceiveImage(int sock);

    /// @brief Sends a command character to the server over a socket.
    /// @param sock The socket file descriptor for the connection to the server.
    /// @param command The command character to send.
    void SendCommand(int sock, char command);

    /// @brief Closes the client connection by closing the socket.
    /// @param sock The socket file descriptor of the client connection.
    void CloseClient(int sock);

    /// @brief Allows the user to select a resolution from predefined options.
    /// @return A std::pair<int, int> representing the selected resolution:
    ///         - `first`: The width of the resolution.
    ///         - `second`: The height of the resolution.
    std::pair<int, int> SelectResolution();

    /// @brief Sends the selected resolution to the server.
    /// @param sock The socket file descriptor used for communication.
    /// @param resolution A std::pair<int, int> containing:
    ///         - `first`: The width of the resolution.
    ///         - `second`: The height of the resolution. 
    void SendResolution(int sock, const std::pair<int, int>& resolution);

    /// @brief Receives a command from the server.
    /// @param sock The socket file descriptor used for communication.
    /// @return A char representing the command received from the server.
    char ReceiveCommand(int sock);

    ///  @brief 
    ///  
    ///  @param sock 
    ///  @param filteredData 
    void SendFilteredDataToServer(int sock, const std::string &filteredData);
}
#endif // CLIENT_H
