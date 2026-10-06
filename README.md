# Order-book


Order book features:
takes in orders with info: 
price
buy/sell

Can input orders, can modify orders, can remove orders.

Architecture and code reasoning:
Avoid double and float for money amount types to avoid rounding.

Use uint_64 and int_64 to avoid difference between windows and linux.


To do:
- Cancel order
- Modify order
-  Record trades
- Implement alternate order types including limit trades 
- Create testing

- Original plan to use map<price, list> data structure to hold orders. This is suboptimal for low latency. Adding alternative vector structure to keep access in consistent memory space vs node based structure.