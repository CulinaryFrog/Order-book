#include <iostream>
#include "OrderBook.h"

int main() {
    OrderBook book;
    Order test(1,5,1,OrderSide::BUY);
    book.addOrder(test);

    std::cout << "hello";
}

