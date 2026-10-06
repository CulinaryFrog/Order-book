#pragma once

enum class OrderSide {
    BUY,
    SELL,
    UNKNOWN
};

enum class OrderType {

};

struct Order {
    uint64_t id_ = 0;
    uint64_t prc_ = 0;
    uint64_t qty_ = 0;
    OrderSide side_ = OrderSide::UNKNOWN;
    
    Order(uint64_t id,  uint64_t prc, int qty, OrderSide side)
    : id_(id), prc_(prc), qty_(qty), side_(side) {} // Constructor initialization list
    
};
