#include<mutex>
#include<deque>
#include<memory>
#include "Order.h"

// TODO: FAIR LOCKING

#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

class PriceLevel {
public:
    void addOrder(std::shared_ptr<Order> order);
    void removeOrder(const unsigned int orderId);
    void print_orders();

private:
    std::mutex level_mutex;
    std::deque<std::shared_ptr<Order>> orders;
};

#endif
