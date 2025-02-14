#include "Order.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(OderGetters, GetID) {
    int id = 123;
    Order order(id, 420.69, 100, Order::OrderType::Buy);

    std::cout << "hello" << std::endl;

    EXPECT_EQ(order.getId(), id);
}
