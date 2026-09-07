#pragma once

#include <string>
using namespace std;

enum class OrderType {

};

struct Order {
    int id_;
    double prc_;
    uint64_t qty_;
    bool isBuy_;
    
    Order(int id,  double prc, int qty, bool isBuy)
    : id_(id), prc_(prc), qty_(qty) {}
    
};
