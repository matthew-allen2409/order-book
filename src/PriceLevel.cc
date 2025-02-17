#include "PriceLevel.h"
#include<algorithm>
#include<memory>
#include<iostream>

void PriceLevel::addOrder(std::shared_ptr<Order> order) {
    orders.push_back(order);
}

void PriceLevel::removeOrder(std::shared_ptr<Order> order) {
    orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
}

void PriceLevel::print_orders() {
    for (const auto& order:orders) {
        std::cout << *order << std::endl;
    }
}

bool PriceLevel::empty() {
    return orders.empty();
}
