#include <shared_mutex>
#include <map>
#include <iostream>
#include <cmath>
#include <memory>
#include "OrderBook.h"
#include "Order.h"

void OrderBook::placeOrder(std::unique_ptr<Order> order) {
    std::shared_ptr<Order> orderPtr = std::move(order);
    orderPtr->getType() == Order::OrderType::Buy ? buy_orders.insert_order(orderPtr) : sell_orders.insert_order(orderPtr);
}

void OrderBook::removeOrder(int orderId) {}

void OrderBook::modifyOrder(int orderId, int newPrice, int newQuantity) {}

Order OrderBook::getOrderById(int orderId) const { return Order(Order::OrderType::Buy, 420, 100); }

void OrderBook::printOrders() {
    buy_orders.print_map();
    sell_orders.print_map();
}

