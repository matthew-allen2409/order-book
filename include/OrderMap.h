#ifndef ORDER_MAP_H
#define ORDER_MAP_H

#include "PriceLevel.h"
#include "Order.h"
#include <shared_mutex>
#include <memory>
#include <map>

class OrderMap {
public:
    void insert_order(std::shared_ptr<Order> order);
    void remove_order(std::shared_ptr<Order> order);
    void print_map();


private:
    std::map<int, PriceLevel> orders;
    std::shared_mutex mtx;
};

#endif
