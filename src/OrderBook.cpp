#include "OrderBook.h"
void OrderBook::addOrder(Order& ord){
    if (!validId(ord.id_))
        return;
    if (ord.side_ == OrderSide::BUY){
        matchBuy(ord);

        if (ord.qty_ >= 0)
            saveOrder(ord);
    }
    else if (ord.side_ == OrderSide::SELL){
        matchSell(ord);

        if (ord.qty_ >= 0)
            saveOrder(ord);
    }

}

void OrderBook::saveOrder(Order& ord){
    if (!validId(ord.id_)) //Lets not allow 0 qty orders to be recorded
        return;

    if (ord.side_ == OrderSide::BUY){
        auto& list = bids[ord.prc_];
        auto it = list.insert(list.end(), ord);
        indexMap[ord.id_] = {it};
    }
    else if (ord.side_ == OrderSide::SELL)
    {
        auto& list = asks[ord.prc_];
        auto it = list.insert(list.end(), ord);
        indexMap[ord.id_] = {it};
    }
}


void OrderBook::matchBuy(Order& buyOrd){
    while (buyOrd.qty_> 0 && !asks.empty()){ //If there are no sell orders, no need to match
        auto askIt = asks.begin(); //.begin() returns a prvalue

        if (askIt->first > buyOrd.prc_)
            break; //All sell orders are out of range of buy order
        
        auto& askList = askIt->second;
        while (buyOrd.qty_> 0 && !askList.empty()) //Just need to iterate most recent sell order until we exhaust buy order qty
        {
            Order& sellOrd = askList.front();
            uint64_t exchQty = std::min(buyOrd.qty_, sellOrd.qty_); 
            buyOrd.qty_ -= exchQty;
            sellOrd.qty_ -= exchQty;

            if (sellOrd.qty_ == 0){
                indexMap.erase(sellOrd.id_);
                askList.pop_front(); //We are matching most recent order
            }
        }
        
        if (askList.empty())
            asks.erase(askIt);

    }
}

void OrderBook::matchSell(Order& sellOrd){
    while (sellOrd.qty_> 0 && !bids.empty()){ //If there are no buy orders, no need to match
        auto bidIt = bids.begin(); //.begin() returns a prvalue

        if (bidIt->first < sellOrd.prc_)
            break; //All buy orders are out of range of sell order
        
        auto& bidList = bidIt->second;
        while (sellOrd.qty_> 0 && !bidList.empty()) //Just need to iterate most recent sell order until we exhaust buy order qty
        {
            Order& buyOrd = bidList.front();
            uint64_t exchQty = std::min(buyOrd.qty_, sellOrd.qty_); 
            sellOrd.qty_ -= exchQty;
            buyOrd.qty_ -= exchQty;

            if (buyOrd.qty_ == 0){
                indexMap.erase(sellOrd.id_);
                bidList.pop_front(); //We are matching most recent order
            }
        }
        
        if (bidList.empty())
            bids.erase(bidIt);

    }
}

void cancelOrder(uint64_t id){

}