#pragma once

#include <map>
#include <list>
#include <string>
#include "Order.h"

class OrderBook {

public:
    void addOrder(Order order);
    void cancelOrder();
    void modifyOrder();

    size_t getBidSizeAmount() const {return bids.size(); }
    size_t getAskSizeAmount() const {return asks.size(); }

private:
    map<uint64_t, std::list<Order, std::greater<double>>> asks;
    map<uint64_t, std::list<Order>> bids;
};