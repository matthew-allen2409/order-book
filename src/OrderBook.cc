#include <mutex>
#include <set>
#include <iostream>
#include "OrderBook.h"
#include "Order.h"

void OrderBook::placeOrder(Order order) {
    std::lock_guard<std::mutex> lock(mtx);

    order.getType() == Order::OrderType::Buy ? buy_orders.insert(order) : sell_orders.insert(order);
}

void OrderBook::removeOrder(int orderId) {}

void OrderBook::modifyOrder(int orderId, double newPrice, int newQuantity) {}

void OrderBook::modifyOrder(int orderId, double newPrice) {}

void OrderBook::modifyOrder(int orderId, int newQuantity) {}

Order OrderBook::getOrderById(int orderId) const { return Order(Order::OrderType::Buy, 420.69, 100); }

void OrderBook::printOrders() {
    for (auto& order:buy_orders) {
        std::cout << order << std::endl;
    }
    for (auto& order:sell_orders) {
        std::cout << order << std::endl;
    }
}

