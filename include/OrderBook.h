#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Order.h"
#include <map>
#include <unordered_map>
#include <deque>
#include <memory>

using order_ptr_t = std::shared_ptr<Order>;

template<typename Comparator>
using OrderMap = std::map<int, std::deque<order_ptr_t>, Comparator>;

class OrderBook {
public:
    void placeOrder(std::unique_ptr<Order> order);
    void removeOrder(const unsigned int orderId);
    void modifyOrder(int orderId, int newPrice, int newQuantity);
    void printOrders();

private:
    inline void match_orders(order_ptr_t order);
    inline void match_order(order_ptr_t buyOrder, order_ptr_t sellOrder);
    OrderMap<std::greater<int>> buy_orders;
    OrderMap<std::less<int>> sell_orders;
    std::unordered_map<unsigned int, order_ptr_t> lookup_map;
};

#endif

