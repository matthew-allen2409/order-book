#include "OrderMap.h"
#include <shared_mutex>
#include <memory>
#include <iostream>


void OrderMap::insert_order(std::shared_ptr<Order> order) {
    std::shared_lock<std::shared_mutex> shared_lock(mtx);
    auto priceLevel = orders.find(order->getPrice());

    if (priceLevel == orders.end()) {
        shared_lock.unlock();
        std::unique_lock<std::shared_mutex> unique_lock(mtx);
        orders[order->getPrice()].addOrder(order);
    } else {
        (*priceLevel).second.addOrder(order);
    }
}

void OrderMap::print_map() {
    std::shared_lock shared_lock(mtx);
    for (auto& [price, priceLevel]:orders) {
        priceLevel.print_orders();
    }

}
