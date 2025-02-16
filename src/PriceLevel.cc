#include "PriceLevel.h"
#include<algorithm>
#include<memory>
#include<mutex>
#include<iostream>

void PriceLevel::addOrder(std::shared_ptr<Order> order) {
    std::lock_guard lock(level_mutex);
    orders.push_back(order);
}

void PriceLevel::removeOrder(std::shared_ptr<Order> order) {
    std::lock_guard lock(level_mutex);
    orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
}

void PriceLevel::print_orders() {
    std::lock_guard lock(level_mutex);
    for (const auto& order:orders) {
        std::cout << *order << std::endl;
    }
}

bool PriceLevel::empty() {
    std::lock_guard lock(level_mutex);
    return orders.empty();
}
