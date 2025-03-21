#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <iostream>
#include <thread>

#include "OrderBook.h"
#include "Server.h"
#include "FIX_message.h"
#include "Order.h"

int main() {
    std::shared_ptr<OrderBook> book = std::make_shared<OrderBook>();

    std::cout << "listening" << std::endl;

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Failed to create socket");
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8081);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Failed to connect");
        close(clientSocket);
        return 1;
    }

    Server server(clientSocket, book);
    std::thread(&Server::begin, &server).detach();

    char buffer[1024] = {0};

    while (recv(clientSocket, buffer, sizeof(buffer), 0)) {
        FIXMessage message = (std::string(buffer));
        Order::OrderType type = message.tag_map["40"] == "1" ? Order::OrderType::BID : Order::OrderType::ASK;
        int price = std::stoi(message.tag_map["44"]);
        int quantity = std::stoi(message.tag_map["38"]);

        book->placeOrder(
            std::make_unique<Order>(
                type,
                price,
                quantity
            )
        );

        book->printOrders();
    }
}

