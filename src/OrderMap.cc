#include "OrderMap.h"
#include <memory>
#include <iostream>


void OrderMap::insert_order(std::shared_ptr<Order> order) {
    orders[order->getPrice()].addOrder(order);
}

void OrderMap::remove_order(std::shared_ptr<Order> order) {
    auto it = orders.find(order->getPrice());
    if (it != orders.end()) {
        auto& [price, priceLevel] = *it;
        priceLevel.removeOrder(order);
        if (priceLevel.empty()) {
            orders.erase(it);
        }
    }
}

void OrderMap::print_map() {
    for (auto& [price, priceLevel]:orders) {
        priceLevel.print_orders();
    }

}
