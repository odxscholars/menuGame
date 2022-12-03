#include<stdio.h>
#include<stdbool.h>

//ASSUMPTIONS:
//1. EACH COMPLETED ORDER IS ASSUMED TO BE FROM A DIFFERENT CUSTOMER
//2. EACH CUSTOMER IS ASSUMED TO HAVE ONLY ONE ORDER
#define MAXROW 10
int customerMenu(){
    int choice;
    bool goBack = false;
    while(goBack == false){
        printf("Welcome to the customer menu. Please select an option: ");
        printf("\n1. Order\n");
        printf("2. Pay\n");
        printf("3. Display status\n");
        printf("4. Exit\n");
        scanf("%d", &choice);
        if (choice < 0 || choice > 5){
            printf("Invalid choice. Please try again.\n");
        }else{
            goBack = true;
        }

    }
    
    return choice;

}

int managerMenu(){
    int choice;
    bool goBack = false;
    while(goBack == false){
        printf("Welcome to the manager menu. Please select an option: ");
        printf("\n1. Display the menu for today.\n");
        printf("2. Send order to chef.\n");
        printf("3. List Pending order\n");
        printf("4. List Current customers and ordered food.\n");
        printf("5. Send Driver.\n");
        printf("6. Display income for the day.\n");
        printf("7. Display dishes served for the day.\n");
        printf("8. Close Restaurant.\n");
        printf("9. Exit\n");
        scanf("%d", &choice);
        if (choice < 1 || choice > 9){
            printf("Invalid choice. Please try again.\n");
        }else{
            goBack = true;
        }  

    }
    return choice;
}


int menu(){
    int choice;
    do{
        printf("1. Customer/s\n");
        printf("2. Manager\n");
        printf("3. Chef\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice < 1 || choice >4){
            printf("Choice is invalid. Out of bounds.\n");
        }

    }while(choice < 1 || choice > 4);
    return choice;
    

}
void initializeOrderArr(int arr[MAXROW][14]){
    //this function sets everything in the array to -1
    for(int i = 0; i < MAXROW; i++){
        for(int j = 0; j < 14; j++){
            arr[i][j] = -1;
            
        }
    }


}



void displayMenu(char foodMenu[5][15], int prices[]){
    printf("Food Menu:\n");
    for(int i = 0; i < 5; i++){
        printf("%d. %s: %d\n", i+1, foodMenu[i], prices[i]);
    }
    char temp;
    printf("Press anything to exit ");
    scanf(" %c", &temp);

}

int countOrders(int orderArr[MAXROW][14]){
    int count = 0;
    //counts how many orders there are
    for(int i = 0; i < MAXROW; i++){
        if (orderArr[i][0] != -1){
            count++;
        }
    }
    return count;

}

void customerPayForOrder(char foodMenu[5][15], int prices[], int orderArr[MAXROW][14]){
    int orderCount = countOrders(orderArr);
    if (orderCount != 0){
        for(int i = 0; i < MAXROW; i++){
            if (orderArr[i][1] == 0){  
                printf("- Customer %d's order:\n", orderArr[i][0]);
            }
            
        }
        int customerNum;
        printf("For who are you paying for? ");
        scanf("%d", &customerNum);
        if (customerNum > 0 && customerNum <= orderCount && orderArr[customerNum-1][1] == 0){
            int total = 0;
            printf("Here is your receipt:\n");
            printf("\n\n---RECEIPT---\n");
            printf("Customer #: %d\n", orderArr[customerNum-1][0]);
            printf("# of items: %d\n", orderArr[customerNum-1][2]);
            printf("Items: \n");
            int count = 1;
            
            for(int i = 3; i <= orderArr[customerNum-1][2] * 3; i+=3){
                printf("%d. %d-%s: %d\n",count,orderArr[customerNum-1][i],foodMenu[orderArr[customerNum-1][i]], prices[orderArr[customerNum-1][i]]);
                total += prices[orderArr[customerNum-1][i]];
                count++;
            }
            printf("\n--------------\n");
            printf("Total: %d\n", total);
            printf("--------------\n");
            char temp;
            printf("Press y to pay using e-wallet ");
            scanf(" %c", &temp);
            if (temp == 'y'){
                orderArr[customerNum-1][1] = 1;
                printf("Payment successful!\n");
                printf("Thank you for your purchase!\n");
                printf("Press anything to exit ");
                scanf(" %c", &temp);
            }
        }
    }else{
        printf("There are no orders to pay for.\n");
        char temp;
        printf("Press anything to exit ");
        scanf(" %c", &temp);
    }   

}

void customerMakeOrder(char foodMenu[5][15], int prices[], int orderArr[MAXROW][14]){
    //look for empty slot in orderArr
    int index = -1;
    for(int i = 0; i < MAXROW; i++){
        if(orderArr[i][0] == -1){
            index = i;
            i = MAXROW;
        }
    }

    
    //display menu
    if (index != -1){
        bool validOrder = false;
        while(validOrder == false){
            printf("Menu: \n");
            int orderQty = 0;
            for(int i = 0; i < 5; i++){
                printf("%d. %s: %d\n", i, foodMenu[i], prices[i]);
            }
            printf("Enter the quantity of the food you want to order: ");
            scanf("%d", &orderQty);
            if (orderQty < 0 || orderQty > 3){
                printf("Invalid choice. Please try again.\n");
                printf("Orders must be greater than 0 and less than 4.\n");
            }else{
                int totalPrice = 0;
                orderArr[index][0] = index + 1;
                orderArr[index][1] = 0;
                orderArr[index][2] = orderQty;
                for(int i = 0; i < orderQty; i++){
                    int orderNumber;
                    printf("Enter the menu number of the food you want to order: ");
                    scanf("%d", &orderNumber);
                    if (orderNumber < 0 || orderNumber > 4){
                        printf("Invalid choice. Please try again.\n");
                        printf("Orders must be greater than 0 and less than 4.\n");
                        i--;
                    }else{
                        orderArr[index][3*i + 3] = orderNumber;
                        orderArr[index][3*i + 4] = prices[orderNumber];
                        orderArr[index][3*i + 5] = 0;
                        totalPrice += prices[orderNumber];
                        //print all
                        
                        

                    }
                }
                orderArr[index][12] = totalPrice;
                orderArr[index][13] = 0;
                
                printf("---RECEIPT---\n");
                printf("Order number: %d\n", orderArr[index][0]);
                printf("Order status: %d\n", orderArr[index][1]);
                printf("Order quantity: %d\n", orderArr[index][2]);
                for(int i = 0; i < orderQty; i++){
                    printf("Order %d: %s\n", i+1, foodMenu[orderArr[index][3*i + 3]]);
                    printf("Price: %d\n", orderArr[index][3*i + 4]);
                    printf("Status: %d\n", orderArr[index][3*i + 5]);
                }
                printf("Total Price: %d\n", orderArr[index][12]);

                printf("Your order has been placed.\n");
                printf("To begin with the process of making your food, you must pay for it first.\n");
                validOrder = true;
                    
            }
            


        }
        

    }else{
        printf("There are no more empty slots for orders.\n");
    }


}

void customerDisplayStatus( int orderArr[MAXROW][14]){
    int nOrder = countOrders(orderArr);
    if(nOrder > 0){
        for(int i = 0; i < MAXROW; i++){
            if(orderArr[i][0] != -1){
                //TERNARY OPERATOR
                printf("Customer %d's order status: %s\n", orderArr[i][0], orderArr[i][1] == 0 ? "Booking" : orderArr[i][1] == 1 ? "Waiting" : "Received order");
            }
            
        
        }
        char temp;
        printf("Press anything to exit ");
        scanf(" %c", &temp);
    }else{
        printf("There are no orders to display.\n");
        char temp;
        printf("Press anything to exit ");
        scanf(" %c", &temp);
    }

}


void sendOrderToChef(int orderArr[MAXROW][14]){
    int indexOfOrdersNotSent[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int count = 0;
    for(int i = 0; i < MAXROW; i++){
        if(orderArr[i][0] != -1 && orderArr[i][13] == 0 && orderArr[i][1] == 1){
            indexOfOrdersNotSent[i] = 0;
            count++;
        }else if(orderArr[i][0] != -1 && orderArr[i][13] == 1 && orderArr[i][1] == 1){
            indexOfOrdersNotSent[i] = 1;
        }else{
            
            indexOfOrdersNotSent[i] = -1;
        }
    }
    if (count != 0){
         printf("Orders to send to chef: \n");
        for(int i = 0; i < MAXROW; i++){
            if (indexOfOrdersNotSent[i] == 0){
                printf("%d. Customer %d's order \n", i+1, orderArr[i][0]);
            }
        }
        int sendToChef;
        printf("Enter the number of the order you want to send to the chef: ");
        scanf("%d", &sendToChef);
        if (sendToChef <= 0 || sendToChef > 5){
            printf("Invalid choice. Please try again.\n");
            printf("Orders must be greater than 0 and less than 5.\n");
        }
        else if(orderArr[sendToChef-1][13] == 0 && orderArr[sendToChef-1][1] == 1){
            orderArr[sendToChef-1][13] = 1;
            printf("Order sent to chef!\n");
            char temp;
            printf("Press anything to exit ");
            scanf(" %c", &temp);
        }else if (orderArr[sendToChef-1][13] == 1 && orderArr[sendToChef-1][1] != 2){
            printf("Order has already been sent to chef!\n");
            char temp;
            printf("Press anything to exit ");
            scanf(" %c", &temp);
        }
        printf("%d %d\n", orderArr[sendToChef-1][13],orderArr[sendToChef-1][1]);


    }else{
        printf("There are no orders to send to the chef.\n");
        char temp;
        printf("Press anything to exit ");
        scanf(" %c", &temp);
    }
   
    

}
void managerListPendingOrder(char food[5][15], int orderArr[MAXROW][14], int foodPrices[] ){
    printf("Orders that are yet to be cooked by the chef: \n");
    for(int i = 0; i < MAXROW; i++){
        if(orderArr[i][0] != -1 && orderArr[i][1] == 1 && orderArr[i][13] == 2){
            printf("Customer %d's order: \n", orderArr[i][0]);
            for(int j = 3; j <= orderArr[i][2] * 3; j+=3){
                if (orderArr[i][j+2] == 0 || orderArr[i][j+2] == 1){
                    printf("- %d %s \n", orderArr[i][j], food[orderArr[i][j]]);
                }
            }

        }
    }
    char temp;
    printf("Press anything to exit ");
    scanf(" %c", &temp);

}

void listCustomersAndOrderedFood(int orderArr[MAXROW][14], int foodPrices[], char food[5][15]){
    for(int i = 0; i < MAXROW; i++){
        if (orderArr[i][0] != -1 && orderArr[i][1] != 2){
            printf("Customer %d's order: \n", orderArr[i][0]);
            for(int j = 3; j <= orderArr[i][2] * 3; j+=3){
                printf("- %d %s \n", orderArr[i][j], food[orderArr[i][j]]);
            }
        }
    }

}
int chefMenu(){
    int choice;
    do{

        printf("Welcome to the chef menu: \n");
        printf("1. Receive order from manager\n");
        printf("2. Cook N Dishes\n");
        printf("3. Pack Food\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 4){
            printf("Invalid choice. Please try again.\n");
        }
    }while(choice < 1 || choice > 4);

}
void receiveOrder(int orderArr[MAXROW][14]){
    int count = 0;
    printf("Orders yet to receive by chef\n");
    for(int i = 0; i < MAXROW; i++){
        if(orderArr[i][0] != -1 && orderArr[i][13] == 1 && orderArr[i][13] != 2 && orderArr[i][1] == 1){
            printf("Customer %d's order: \n", orderArr[i][0]);
            count++;
        }
    }
    if(count != 0){
        int receiveOrder;
        printf("Enter the number of the order you want to receive: ");
        scanf("%d", &receiveOrder);
        if (orderArr[receiveOrder-1][1] == 2 || orderArr[receiveOrder-1][13] == 2){
            printf("Invalid choice. Please try again.\n");
        }
        else if(orderArr[receiveOrder-1][13] == 1 && orderArr[receiveOrder-1][1] != 2){
            orderArr[receiveOrder-1][13] = 2;
            printf("Order received!\n");
            char temp;
            printf("Press anything to exit ");
            scanf(" %c", &temp);
        }
    }else{
        printf("There are no orders to receive.\n");
        char temp;
        printf("Press anything to exit ");
        scanf(" %c", &temp);
    }
}

void cookNDishes(int orderArr[MAXROW][14], int n, int foodPrices[], char food[5][15]){
    printf("Cook %d dishes?\n", n);
    char temp;
    printf("Press anything to start cooking ");
    scanf(" %c", &temp);
    for(int i = 0; i < MAXROW && n > 0; i++){
        if(orderArr[i][0] != -1 && orderArr[i][13] == 2 && orderArr[i][1] == 1){
            for(int j = 3; j <= orderArr[i][2] * 3 && n > 0; j+=3){
                
                if (orderArr[i][j+2] == 0){
                    
                    orderArr[i][j+2] = 1;
                    printf("Cooked %s with code: %d\n", food[orderArr[i][j]], orderArr[i][j]);
                    n--;
                }
            }
        }
    }

}


void packFood(int orderArr[MAXROW][14], int foodPrices[], char food[5][15]){
    printf("These are the dishes to be packed: \n");
    int indexes[MAXROW][2];
    int count = 1;
    for(int i = 0; i < MAXROW; i++){
        if(orderArr[i][0] != -1 && orderArr[i][13] == 2 && orderArr[i][1] == 1){
            for(int j = 3; j <= orderArr[i][2] * 3; j+=3){
                if (orderArr[i][j+2] == 1){
                    printf("%d. %d %s \n",count, orderArr[i][j], food[orderArr[i][j]]);
                    count++;
                    indexes[count-1][0] = i;
                    indexes[count-1][1] = j;
                }
            }
        }
    }
    printf("Enter the number of the dish you want to pack: ");
    int pack;
    scanf("%d", &pack);
    if (orderArr[indexes[pack][0]][indexes[pack][1]+2] == 2){
        printf("Invalid choice. Please try again.\n");
    }
    else if(orderArr[indexes[pack][0]][indexes[pack][1]+2] == 1){
        orderArr[indexes[pack][0]][indexes[pack][1]+2] = 2;
        printf("Packed %s with code: %d\n", food[orderArr[indexes[pack][0]][indexes[pack][1]]], orderArr[indexes[pack][0]][indexes[pack][1]]);
        char temp;
        printf("Press anything to exit ");
        scanf(" %c", &temp);
    }
}

void listCurrentCustomers(int orderArr[MAXROW][14], char food[5][15], int foodPrice[5]){
    for(int i = 0; i < MAXROW; i++){
        if (orderArr[i][1] == 1){
            printf("Customer %d's order: \n", orderArr[i][0]);
            for(int j = 3; j <= orderArr[i][2] * 3; j+=3){
                printf("- %d %s \n", orderArr[i][j], food[orderArr[i][j]]);
            }
        }
    }
    char temp;
    printf("Press anything to exit ");
    scanf(" %c", &temp);

}


int main(){
    //FOOD
    char food[5][15] = {
        "Chicken",
        "Beef",
        "Fish",
        "Pork",
        "Veggie"
    };
    int foodPrice[5] = {
        10,
        15,
        20,
        25,
        30
    };
    



    int nDishes = 0;
    bool startGame = true;
    int currentCustomersBeingServed = 0;
    int dishesServedForTheDay = 0; //max is 20
    int customersServedForTheDay = 0; //max is 10
    //rows = max number of customers = 5 at any given time
    //first column = customer number : 1-n -> limitation: 5 customers at any given time
    //second column = status of order : 0 = booking, 1 = waiting, or 2 =received order
    //third column = number of dishes : 1-n -> limitation: 3 orders per customer
    //given the number in the third columns
    //first will be dish number
    //second will be dish price
    //third will be dish status 0 = uncooked,1 = cooked, 2 = packed
    //second to the last column will be total price of all dishes
    //last column will be status if sent to the kitchen or not
    int listOfOrders[MAXROW][14];
    initializeOrderArr(listOfOrders);
    do{
        printf("What will N be? ");
        scanf("%d", &nDishes);
        if (nDishes < 1 || nDishes > 3){
            printf("Invalid choice. Please try again.\n");
            printf("N must be greater than 0 and less than 4.\n");
        }

    }while(nDishes > 3 || nDishes < 1);
    while(startGame){
        int choice = menu();
        bool goBackToMenu = false;
        while(goBackToMenu == false){


            //CUSTOMER
            if (choice == 1){
                int customerChoice = customerMenu();
                if (customerChoice == 1){
                    printf("Went in 1\n");
                    customerMakeOrder(food, foodPrice, listOfOrders);
                }else if(customerChoice == 2){
                    customerPayForOrder(food, foodPrice, listOfOrders);
                }else if(customerChoice == 3){
                    customerDisplayStatus(listOfOrders);
                }else if (customerChoice == 4){
                    goBackToMenu = true;
                }
            




            //MANAGER
            }else if(choice == 2){
                int managerChoice = managerMenu();
                if (managerChoice == 1){
                    displayMenu(food, foodPrice);
                }else if(managerChoice == 2){
                    sendOrderToChef(listOfOrders);
                }else if(managerChoice == 3){
                    managerListPendingOrder(food, listOfOrders, foodPrice);
                }else if(managerChoice == 4){
                    listCurrentCustomers(listOfOrders, food, foodPrice);
                    
                }else if(managerChoice == 9){
                    goBackToMenu = true;
                }

            }else if(choice ==3){
                int chefChoice = chefMenu();
                if (chefChoice == 1){
                    receiveOrder(listOfOrders);
                }else if(chefChoice == 2){
                    cookNDishes(listOfOrders, nDishes, foodPrice, food);
                }else if(chefChoice == 3){
                    packFood(listOfOrders, foodPrice, food);
                }else if(chefChoice == 4){
                    goBackToMenu = true;
                }
            }

        }
        

    }



}