#include<iostream>
#include<atomic>
#include "Order.h"

std::atomic<unsigned int> id(0);

Order::Order(
    OrderType type,
    double price,
    int quantity
) noexcept : order_id(id++), price(price), quantity(quantity),
type(type) {}

unsigned int Order::getId() const noexcept {
    return this->order_id;
}

double Order::getPrice() const noexcept {
    return this->price;
}

int Order::getQuantity() const noexcept {
    return this->quantity;
}

Order::OrderType Order::getType() const noexcept {
    return this->type;
}

bool Order::operator<(const Order& other) const noexcept {
    if (this->price == other.price) {
        return this->order_id < other.order_id;
    }
    return this->price < other.price;
}

bool Order::operator>(const Order& other) const noexcept {
    if (this->price == other.price) {
        return this->order_id > other.order_id;
    }
    return this->price > other.price;
}

bool Order::operator<=(const Order& other) const noexcept {
    if (this->price == other.price) {
        return this->order_id <= other.order_id;
    }
    return this->price <= other.price;
}

bool Order::operator>=(const Order& other) const noexcept {
    if (this->price == other.price) {
        return this->order_id >= other.order_id;
    }
    return this->price >= other.price;
}

std::ostream& operator<<(std::ostream& os, const Order::OrderType& orderType) {
    switch (orderType) {
        case Order::OrderType::Buy:
            os << "Buy";
            break;
        case Order::OrderType::Sell:
            os << "Sell";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Id: " << order.getId() << " Type: " << order.getType() << " Price: " << order.getPrice() << " Quantity: " << order.getQuantity();
    return os;
}
