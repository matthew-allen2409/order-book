#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Order.h"
#include <set>
#include <map>
#include <functional>
#include <memory>
#include <mutex>

class OrderBook {
public:
    void placeOrder(Order order);
    void removeOrder(int orderId);
    void modifyOrder(int orderId, double newPrice, int newQuantity);
    void modifyOrder(int orderId, double newPrice);
    void modifyOrder(int orderId, int newQuantity);
    Order getOrderById(int orderId) const;
    void printOrders();

private:
    std::mutex mtx;
    std::set<Order> buy_orders;
    std::set<Order> sell_orders;
    std::unordered_map<unsigned int, std::shared_ptr<Order>> order_map;
};

#endif

