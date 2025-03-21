#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <thread>
#include <functional>
#include <cstring>

#include "Server.h"
#include "OrderBook.h"
#include "FIX_message.h"

Server::Server(int manager_socket, std::shared_ptr<OrderBook> book) : manager_socket(manager_socket) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::string("Socket creation failed");
    }

    struct sockaddr_in address;
    address.sin_family      = AF_INET;
    address.sin_port        = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address))) {
        close(sockfd);
        throw std::string("failed to bind socket");
    }

    if (listen(sockfd, 5)) {
        close(sockfd);
        throw std::string("failed to listen");
    }

    this->server_socket = sockfd;
    this->book = book;
}

Server::~Server() {
    this->running = false;
    close(server_socket);
}

void stripWhitespace(char buffer[]) {
    int length = strlen(buffer);
    int start = 0, end = length - 1;

    while(start <= end && std::isspace(buffer[start])) {
        start++;
    }

    while(end >= start && std::isspace(buffer[end])) {
        end--;
    }

    if (end < start) {
        buffer[0] = '\0';
        return;
    }

    for (int i = start; i <= end; i++) {
        buffer[i - start] = buffer[i];
    }

    buffer[end - start + 1] = '\0';
}

void Server::handle_client(int client_socket) {
    char buffer[1024] = {0};

    std::string orderString = book->serialize_orders();
    send(client_socket, orderString.c_str(), orderString.size(), 0);

    while (int bytesRead = recv(client_socket, buffer, sizeof(buffer), 0)) {
        stripWhitespace(buffer);
        std::string message = std::string(buffer);
            memset(buffer, 0, sizeof(buffer));

        if (message == "PRINT") {
            std::string orderString = book->serialize_orders();
            send(client_socket, orderString.c_str(), orderString.size(), 0);
            continue;
        }

        if (is_valid_FIX_message(message)) {
            if (send(manager_socket, message.c_str(), message.size(), 0) < 0) {
                perror("failed to send FIX message");
                continue;
            }
            std::string orderString = book->serialize_orders();
            send(client_socket, orderString.c_str(), orderString.size(), 0);
        }
    }

    close(client_socket);
}


void Server::begin() {
    while (this->running) {
        int clientSocket = accept(this->server_socket, nullptr, nullptr);
        if (clientSocket < 0) {
            perror("failed to accept connection");
            continue;
        }

        std::thread thread(std::bind(&Server::handle_client, this, clientSocket));
        thread.detach();
        std::lock_guard<std::mutex> lock(this->clients_mutex);
        this->clients.push_back(clientSocket);
    }
}

