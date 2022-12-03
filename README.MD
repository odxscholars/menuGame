# Anatomy of an order array
## index 0: Customer number
### limitations: 1-10

## index 1: Order status
### states:
* #### 0 - booking which means not yet paid but an order has been made
* #### 1 - paid but not yet delivered
* #### 2 - delivered

## index 2: number of dishes that were ordered
### limitation: MAX 3 orders
### there are 9 empty spaces that are free to contain the 3 pieces of information for __EACH__ dish. Hence, if there are 3 dishes ordered, all 9 spaces will be occupied. Likewise, if there is only 1 dish, index 6 to index 11 are empty
* #### first space - dish number or its number on the menu
* #### second space - price
* #### third space - status. 0 if it is uncooked, 1 = cooked, 2 = packed

## index 12: total price of all dishes

## index 13: status if it has been sent to the kitchen or not. 
* ### 1 = sent to the chef by the manager but not yet accepted by chef. 
* ### 2 = Chef receives the order
