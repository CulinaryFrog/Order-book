#include "OrderBook.h"
void OrderBook::addOrder(Order ord){
    if (!validNewOrder(ord))
        return;
    if (ord.side_ == OrderSide::BUY){
        matchBuy(ord);

        if (ord.qty_ > 0)
            saveOrder(ord);
    }
    else if (ord.side_ == OrderSide::SELL){
        matchSell(ord);

        if (ord.qty_ > 0)
            saveOrder(ord);
    }

}

void OrderBook::saveOrder(Order& ord){
    if (idInBook(ord.id_))
        return;

    if (ord.side_ == OrderSide::BUY){
        auto& list = bids[ord.prc_];
        auto it = list.insert(list.end(), ord); //We copy by value as original from addOrder is local
        indexMap[ord.id_] = {it, OrderSide::BUY, ord.prc_};
    }
    else if (ord.side_ == OrderSide::SELL)
    {
        auto& list = asks[ord.prc_];
        auto it = list.insert(list.end(), ord); //We copy by value as original from addOrder is local
        indexMap[ord.id_] = {it, OrderSide::SELL, ord.prc_};
    }
}

bool OrderBook::validNewOrder(const Order& ord) const{
    return !idInBook(ord.id_) && ord.side_ != OrderSide::UNKNOWN;
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
                indexMap.erase(sellOrd.id_); //For maps can pass key
                askList.pop_front(); //We are matching most recent order
            }
        }
        
        if (askList.empty())
            asks.erase(askIt); //For lists need to pass iterator

    }
}

void OrderBook::matchSell(Order& sellOrd){
    while (sellOrd.qty_> 0 && !bids.empty()){ //If there are no buy orders, no need to match
        auto bidIt = bids.begin(); //.begin() returns a prvalue

        if (bidIt->first < sellOrd.prc_)
            break; //All buy orders are out of range of sell order
        
        auto& bidList = bidIt->second;
        while (sellOrd.qty_> 0 && !bidList.empty()) //Just need to iterate most recent buy order until we exhaust sell order qty
        {
            Order& buyOrd = bidList.front();
            uint64_t exchQty = std::min(sellOrd.qty_, buyOrd.qty_); 
            sellOrd.qty_ -= exchQty;
            buyOrd.qty_ -= exchQty;

            if (buyOrd.qty_ == 0){
                indexMap.erase(buyOrd.id_); //For maps can pass key
                bidList.pop_front(); //We are matching most recent order
            }
        }
        
        if (bidList.empty()) 
            bids.erase(bidIt); //For lists need to pass iterator

    }
}

void OrderBook::cancelOrder(uint64_t id){
    if (!idInBook(id)) //If id isn't in indexMap, not a valid cancel id
        return;
    
    OrderIndex ordInd = indexMap[id];

    if (ordInd.side == OrderSide::BUY)
    {
        bids[ordInd.price].erase(ordInd.it);
        if (bids[ordInd.price].empty())
            bids.erase(ordInd.price);
    }
    else if (ordInd.side == OrderSide::SELL)
    {
        asks[ordInd.price].erase(ordInd.it);
        if (asks[ordInd.price].empty())
            asks.erase(ordInd.price);
    }
    
    indexMap.erase(id);
    

}