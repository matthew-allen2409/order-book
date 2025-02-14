#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include "Order.h"
#include "OrderBook.h"
#include "ThreadPool.h"

int main() {
    ThreadPool pool(16);
    OrderBook book;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> edis(0, 1);
    std::uniform_int_distribution<> dis(1, 1000);
    std::uniform_real_distribution<> pdis(0.0, 1000.0);

    std::vector<Order> orders;

    for (int i = 0; i < 100000; i++) {
        orders.emplace_back(
            static_cast<Order::OrderType>(edis(gen)),
            pdis(gen),
            dis(gen)
        );
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (Order& order:orders) {
        pool.enqueue_task([&book, &order] {
            book.placeOrder(order);
        });
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    book.printOrders();

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}
