#pragma once

#include <string>

enum class OrderSide {
    BUY,
    SELL,
};

enum class OrderType {

};

struct Order {
    int id_;
    uint64_t prc_;
    uint64_t qty_;
    OrderSide side_;
    
    Order(int id,  uint64_t prc, int qty, OrderSide side)
    : id_(id), prc_(prc), qty_(qty), side_(side) {} // Constructor initialization list
    
};
