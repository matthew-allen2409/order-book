#include <iostream>
#include <random>
#include <memory>
#include <vector>
#include <chrono>
#include "Order.h"
#include "OrderBook.h"
#include "ThreadPool.h"

int main() {
    OrderBook book;
    ThreadPool pool(16);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> edis(0, 1);
    std::uniform_int_distribution<> dis(1, 1000);
    std::uniform_real_distribution<> pdis(0.0, 1000.0);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        pool.enqueue_task(
            [&] {
                book.placeOrder(
                    std::make_unique<Order>(
                        static_cast<Order::OrderType>(edis(gen)),
                        dis(gen),
                        dis(gen)
                    )
                );
            }
        );
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    book.printOrders();

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
}
