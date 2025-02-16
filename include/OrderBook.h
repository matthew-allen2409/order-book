#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Order.h"
#include "PriceLevel.h"
#include "OrderMap.h"
#include <map>
#include <functional>
#include <memory>
#include <mutex>

class OrderBook {
public:
    void placeOrder(std::unique_ptr<Order> order);
    void removeOrder(unsigned int orderId);
    void modifyOrder(int orderId, int newPrice, int newQuantity);
    Order getOrderById(int orderId) const;
    void printOrders();

private:
    std::mutex mtx;
    OrderMap buy_orders;
    OrderMap sell_orders;
    std::unordered_map<unsigned int, std::shared_ptr<Order>> order_map;
};

#endif

