#pragma once

#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include "Order.h"

struct OrderIndex{
    std::list<Order>::iterator it;

};

class OrderBook {

public:
    void addOrder(Order& ord);
    //void addOrder(Order order);

    void cancelOrder(uint64_t id);
    void modifyOrder();

    size_t getBidSizeAmount() const {return bids.size(); }
    size_t getAskSizeAmount() const {return asks.size(); }

private:
    bool validId(uint64_t id) const {return indexMap.find(id) != indexMap.end();};
    void matchBuy(Order& buyOrd);
    void matchSell(Order& sellOrd);
    void saveOrder(Order& ord);

    std::map<uint64_t, std::list<Order>, std::greater<uint64_t>> bids; //buy orders
    std::map<uint64_t, std::list<Order>> asks; //sell orders

    std::unordered_map<int, OrderIndex> indexMap; //Keep track of order memory location in order to cancel them efficiently
};