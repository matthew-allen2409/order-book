#include <shared_mutex>
#include <map>
#include <iostream>
#include <memory>
#include <cmath>
#include "OrderBook.h"
#include "Order.h"

void OrderBook::placeOrder(Order& order) {
    order.getType() == Order::OrderType::Buy ? buy_orders.insert_order(order) : sell_orders.insert_order(order);
}

void OrderBook::removeOrder(int orderId) {}

void OrderBook::modifyOrder(int orderId, int newPrice, int newQuantity) {}

Order OrderBook::getOrderById(int orderId) const { return Order(Order::OrderType::Buy, 420, 100); }

void OrderBook::printOrders() {
    buy_orders.print_map();
    sell_orders.print_map();
}

