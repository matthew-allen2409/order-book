#ifndef ORDER_H
#define ORDER_H

#include <ostream>

class Order {
public:
    enum class OrderType {
        Buy,
        Sell
    };

    Order(
        OrderType type,
        double price,
        int quantity
    ) noexcept;

    unsigned int getId() const noexcept;
    double getPrice() const noexcept;
    int getQuantity() const noexcept;
    OrderType getType() const noexcept;

    bool operator<(const Order& other) const noexcept;
    bool operator>(const Order& other) const noexcept;
    bool operator<=(const Order& other) const noexcept;
    bool operator>=(const Order& other) const noexcept;

private:
    unsigned int order_id;
    double price;
    int quantity;
    OrderType type;

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
    friend std::ostream& operator<<(std::ostream& os, const OrderType& orderType);
};

#endif
