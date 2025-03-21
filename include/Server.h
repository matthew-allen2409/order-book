#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <mutex>
#include <vector>

#include "OrderBook.h"

class Server {
    public:
        Server(int manager_socket,std::shared_ptr<OrderBook> book);
        ~Server();

        int server_socket;
        int manager_socket;

        void begin();

    private:
        std::mutex clients_mutex;
        std::vector<int> clients;
        std::shared_ptr<OrderBook> book;
        bool running = true;

        void handle_client(int client_socket);
};

#endif
