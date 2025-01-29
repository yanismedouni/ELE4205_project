#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>     // Pour close()
#include <cstring>      // Pour memset() et strlen()
#include <sys/socket.h> // Pour les sockets
#include <netinet/in.h> // Pour sockaddr_in
#include <opencv2/opencv.hpp> // NEW: Pour la capture d'images avec OpenCV

namespace Server {
    /// @brief Initializes and starts a server on the specified port.
    /// @param port The port number on which the server will listen for incoming connections.
    /// @return The server file descriptor if successful, or -1 if an error occurs.
    int StartServer(int port);

    /// @brief Accepts a client connection on the server socket.
    /// @param server_fd The file descriptor of the server socket.
    /// @return The client file descriptor if successful, or -1 if an error occurs.
    int AcceptClient(int server_fd);

    /// @brief Captures an image from the specified camera.
    /// @param capture Reference to an open cv::VideoCapture object for the camera.
    /// @param image Output parameter to store the captured image as a cv::Mat object.
    /// @return True if the image is captured successfully, false otherwise.
    bool CaptureImage(cv::VideoCapture &capture, cv::Mat &image);

    /// @brief Sends an image to the connected client over a socket.
    /// @param client_fd The file descriptor of the client socket.
    /// @param image The image to send, provided as a constant cv::Mat reference.
    void SendImage(int client_fd, const cv::Mat &image);

    /// @brief Receives a command character from the client over a socket.
    /// @param client_fd The file descriptor of the client socket.
    /// @return The received command character, or '\0' if an error occurs.
    char ReceiveCommand(int client_fd);

    /// @brief Closes the server and client connections.
    /// @param server_fd The file descriptor of the server socket.
    /// @param client_fd The file descriptor of the client socket.
    void CloseConnection(int server_fd, int client_fd);

    /// @brief Receives the resolution dimensions (width and height) from the client.
    /// @param client_fd The file descriptor for the client socket.
    /// @return A std::pair<int, int> containing the width and height of the resolution.
    std::pair<int, int> ReceiveResolution(int client_fd);

    /// @brief Sends a single character to the client.
    /// @param client_fd The file descriptor for the client socket.
    /// @param message The character to be sent to the client.
    void SendChar(int client_fd, char message);

    /// @brief 
    /// @return 
    std::string ReceiveFilteredDataFromClient();
}

#endif
