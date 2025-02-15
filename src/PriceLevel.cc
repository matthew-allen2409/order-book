#include "PriceLevel.h"
#include<memory>
#include<mutex>
#include<iostream>

void PriceLevel::addOrder(std::shared_ptr<Order> order) {
    std::lock_guard lock(level_mutex);
    orders.push_back(order);
}

void PriceLevel::removeOrder(const unsigned int orderId) {}

void PriceLevel::print_orders() {
    std::lock_guard lock(level_mutex);
    for (const auto& order:orders) {
        std::cout << *order << std::endl;
    }
}
