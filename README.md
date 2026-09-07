# Order-book


Order book features:
takes in orders with info: 
price
buy/sell

Can input orders, can modify orders, can remove orders.

Architecture and code reasoning:
Avoid double and float for money amount types to avoid rounding.

Use uint_64 and int_64 to avoid difference between windows and linux.