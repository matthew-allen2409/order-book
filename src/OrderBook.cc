#include <mutex>
#include <iostream>
#include <memory>
#include "OrderBook.h"
#include "Order.h"

void OrderBook::placeOrder(std::unique_ptr<Order> order) {
    std::shared_ptr<Order> orderPtr = std::move(order);
    orderPtr->getType() == Order::OrderType::Buy ? buy_orders.insert_order(orderPtr) : sell_orders.insert_order(orderPtr);
    std::lock_guard<std::mutex> lock(mtx);
    order_map[orderPtr->getId()] = orderPtr;
}

void OrderBook::removeOrder(unsigned int orderId) {
    std::shared_ptr<Order> orderPtr;
    {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = order_map.find(orderId);
        if (it == order_map.end()) { return; }
        std::cout << "here" << std::endl;
        orderPtr = (*it).second;
        order_map.erase(it);
    }
    OrderMap* mapPtr;
    if (orderPtr->getType() == Order::OrderType::Buy) {
        mapPtr = &buy_orders;
    } else {
        mapPtr = &sell_orders;
    }

    mapPtr->remove_order(orderPtr);
}

void OrderBook::modifyOrder(int orderId, int newPrice, int newQuantity) {}

Order OrderBook::getOrderById(int orderId) const { return Order(Order::OrderType::Buy, 420, 100); }

void OrderBook::printOrders() {
    buy_orders.print_map();
    sell_orders.print_map();
}

