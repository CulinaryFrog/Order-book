#include <iostream>
#include "OrderBook.h"

int main() {
    OrderBook book;
    Order test(1,5,1,OrderSide::BUY);
    Order test2(2,5,4, OrderSide::SELL);
    book.addOrder(test);
    book.addOrder(test2);
    book.addOrder({3,5,1, OrderSide::BUY});
    book.cancelOrder(1);
    std::cout << "hello";
}

