#include<mutex>
#include<condition_variable>
#include<deque>
#include<memory>
#include "Order.h"

// TODO: FAIR LOCKING

#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

class PriceLevel {
public:
    void addOrder(Order& order);
    void removeOrder(const unsigned int orderId);
    void print_orders();

private:
    std::mutex level_mutex;
    std::deque<Order> orders;
};

#endif
