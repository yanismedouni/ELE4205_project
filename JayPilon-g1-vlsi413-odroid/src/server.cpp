#include "server.h"



// Fonction de démarrage du serveur
int Server::StartServer(int port) {
    const auto server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Échec de la création du socket");
        return -1;
    }

    const auto opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Échec du bind");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("Échec de l'écoute");
        close(server_fd);
        return -1;
    }

    std::cout << "Serveur en écoute sur le port " << port << std::endl;
    return server_fd;
}

// Fonction d'acceptation d'un client
int Server::AcceptClient(int server_fd) {
    sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(client_address);

    const auto client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_addr_len);
    if (client_fd < 0) {
        perror("Échec de l'acceptation du client");
        return -1;
    }

    std::cout << "Client connecté." << std::endl;
    return client_fd;
}

//  Fonction pour capturer une image de la caméra
bool Server::CaptureImage(cv::VideoCapture &cap, cv::Mat &image) {
    if (!cap.isOpened()) {
        std::cerr << "Erreur : Impossible d'ouvrir la caméra" << std::endl;
        return false;
    }

    cap >> image;  // Capture une seule image
    return !image.empty();
}

//  Fonction pour envoyer une image au client
void Server::SendImage(int client_fd, const cv::Mat &image) {
    // Convertir l'image en un flux de données binaires
    std::vector<uchar> buffer;
    cv::imencode(".jpg", image, buffer);  // Encode l'image en JPG
    const auto imgSize = static_cast<int> (buffer.size());

    // Envoyer d'abord la taille de l'image
    send(client_fd, &imgSize, sizeof(imgSize), 0);

    // Envoyer ensuite les données de l'image
    send(client_fd, buffer.data(), buffer.size(), 0);
    //std::cout << "Image envoyée au client" << std::endl;
}

//  Fonction pour recevoir une commande du client
char Server::ReceiveCommand(int client_fd) {
    char command;
    recv(client_fd, &command, sizeof(command), 0);
    return command;
}

// Fonction pour fermer les connexions du serveur et du client
void Server::CloseConnection(int server_fd, int client_fd) {
    // shutdown(server_fd, SHUT_RD);
    if (client_fd >= 0) close(client_fd);
    if (server_fd >= 0) close(server_fd);
}

std::pair<int, int> Server::ReceiveResolution(int client_fd) {
    int capture_width;
    int capture_height;
    recv(client_fd, &capture_width, sizeof(capture_width), 0);   // Recevoir la largeur
    recv(client_fd, &capture_height, sizeof(capture_height), 0); // Recevoir la hauteur
    std::pair<int, int> resolution = {capture_width, capture_height};
    std::cout << resolution.first << std::endl;
    return resolution;
}

void Server::SendChar(int client_fd, char message) {
    const auto bytesSent = send(client_fd, &message, sizeof(message), 0);  // Envoyer un seul caractère
    if (bytesSent <= 0) {
        std::cerr << "Erreur : échec de l'envoi du caractère." << std::endl;
    }
}


////////////////////////////// LIVRABLE 6 //////////////////////////////////  

std::string Server::ReceiveFilteredDataFromClient() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);                 // Create a socket
    if (server_fd < 0) {
        perror("Second socket creation failed");
        return "";
    }
    else{
        std::cout << "Second socket created" << std::endl;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  // Allow port reuse

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;                            // Bind to any network interface
    address.sin_port = htons(4098);                                  // Use port 4098

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));   // Bind the socket to the address
    listen(server_fd, 3);                                            // Start listening for connections

    int client_fd = accept(server_fd, nullptr, nullptr);             // Accept a client connection
    if (client_fd < 0) {
        perror("Second client connection failed");
        close(server_fd);
        return "";
    }else{
        std::cout << "Second client connection established succesfully" << std::endl;
    }
    
    int msgSize;
    recv(client_fd, &msgSize, sizeof(msgSize), 0);
    std::cout << msgSize << std::endl;
    std::vector<char> buffer(msgSize);
    recv(client_fd, buffer.data(), msgSize, MSG_WAITALL);  // Receive data into buffer
    
    
    close(client_fd);                                                // Close the client connection
    close(server_fd);                                                // Close the server socket
    
    std::string receivedMessage(buffer.begin(), buffer.end());
    return receivedMessage;                           // Return the received data
}

