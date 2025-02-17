#include <deque>
#include <iostream>
#include <algorithm>
#include <memory>
#include "OrderBook.h"
#include "Order.h"

using OrderType = Order::OrderType;

void OrderBook::placeOrder(std::unique_ptr<Order> order) {
    std::shared_ptr<Order> orderPtr = std::move(order);
    match_orders(orderPtr);
}

inline void OrderBook::match_orders(order_ptr_t order) {
    if (order->getType() == OrderType::Buy) {
        auto it = sell_orders.begin();
        while (it != sell_orders.end() && it->first <= order->getPrice() && order->getQuantity() > 0) {
            auto& sellOrder = it->second.front();
            match_order(order, sellOrder);
            if (sellOrder->getQuantity() == 0) { it->second.pop_front(); }
            if (it->second.empty()) { sell_orders.erase(it++); }
        }
        if (order->getQuantity() > 0) {
            buy_orders[order->getPrice()].push_back(order);
            lookup_map[order->getId()] = order;
        }
    } else {
        auto it = buy_orders.begin();
        while (it != buy_orders.end() && it->first >= order->getPrice() && order->getQuantity() > 0) {
            auto& buyOrder = it->second.front();
            match_order(buyOrder, order);
            if (buyOrder->getQuantity() == 0) { it->second.pop_front(); }
            if (it->second.empty()) { buy_orders.erase(it++); }
        }
        if (order->getQuantity() > 0) {
            sell_orders[order->getPrice()].push_back(order);
            lookup_map[order->getId()] = order;
        }
    }
}

inline void OrderBook::match_order(order_ptr_t buyOrder, order_ptr_t sellOrder) {
    int buyOrderQuantity = buyOrder->getQuantity();
    int sellOrderQuantity = sellOrder->getQuantity();
    int tradeQuantity = std::min(buyOrderQuantity, sellOrderQuantity);

    buyOrder->setQuantity(buyOrderQuantity - tradeQuantity);
    sellOrder->setQuantity(sellOrderQuantity - tradeQuantity);
}

void OrderBook::removeOrder(unsigned int orderId) {
    auto it = lookup_map.find(orderId);
    if (it != lookup_map.end()) {
        auto orderPtr = it->second;

        if (orderPtr->getType() == OrderType::Buy) {
            auto& orders = buy_orders[orderPtr->getPrice()];
            orders.erase(std::find(orders.begin(), orders.end(), orderPtr));
            if (orders.empty()) {
                buy_orders.erase(orderPtr->getPrice());
            }
        } else {
            auto& orders = sell_orders[orderPtr->getPrice()];
            orders.erase(std::find(orders.begin(), orders.end(), orderPtr));
            if (orders.empty()) {
                sell_orders.erase(orderPtr->getPrice());
            }
        }

        lookup_map.erase(it);
    }
}

void OrderBook::modifyOrder(int orderId, int newPrice, int newQuantity) {}

Order OrderBook::getOrderById(int orderId) const { return Order(Order::OrderType::Buy, 420, 100); }

void OrderBook::printOrders() {
    for (auto& [price, orders]:buy_orders) {
        for (auto& order:orders) {
            std::cout << *order << std::endl;
        }
    }
    for (auto& [price, orders]:sell_orders) {
        for (auto& order:orders) {
            std::cout << *order << std::endl;
        }
    }
}
