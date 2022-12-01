#include<stdio.h>
#include<stdbool.h>

//ASSUMPTIONS:
//1. EACH COMPLETED ORDER IS ASSUMED TO BE FROM A DIFFERENT CUSTOMER
//2. EACH CUSTOMER IS ASSUMED TO HAVE ONLY ONE ORDER

int customerMenu(){
    int choice;
    bool goBack = false;
    while(goBack == false){
        printf("Welcome to the customer menu. Please select an option: ");
        printf("\n1. Order\n");
        printf("2. Pay\n");
        printf("3. Display Customer Number\n");
        printf("4. Display status\n");
        printf("5. Exit\n");
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
        if (choice < 0 || choice > 3){
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
void initializeOrderArr(int arr[5][13]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 13; j++){
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
void customerMakeOrder(char foodMenu[5][15], int prices[], int orderArr[5][13], int * dishesServedForTheDay){
    //look for empty slot in orderArr
    int index = -1;
    for(int i = 0; i < 5; i++){
        if(orderArr[i][0] == -1){
            index = i;
            i = 5;
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
                        //print all
                        
                        *dishesServedForTheDay++;

                    }
                }
                printf("---RECEIPT---");
                printf("Order number: %d\n", orderArr[index][0]);
                printf("Order status: %d\n", orderArr[index][1]);
                printf("Order quantity: %d\n", orderArr[index][2]);
                for(int i = 0; i < orderQty; i++){
                    printf("Order %d: %s\n", i+1, foodMenu[orderArr[index][3*i + 3]]);
                    printf("Price: %d\n", orderArr[index][3*i + 4]);
                    printf("Status: %d\n", orderArr[index][3*i + 5]);
                }

                printf("Your order has been placed.\n");
                printf("To begin with the process of making your food, you must pay for it first.\n");
                validOrder = true;
                    
            }
            


        }
        

    }


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
    //third will be dish status
    //last column will be total price of all dishes
    int listOfOrders[5][13];
    initializeOrderArr(listOfOrders);

    while(startGame){
        int choice = menu();
        bool goBackToMenu = false;
        while(goBackToMenu == false){


            //CUSTOMER
            if (choice == 1){
                int customerChoice = customerMenu();
                if (customerChoice == 1){
                    customerMakeOrder(food, foodPrice, listOfOrders, &dishesServedForTheDay);

                }




            //MANAGER
            }else if(choice == 2){
                int managerChoice = managerMenu();
                if (managerChoice == 1){
                    displayMenu(food, foodPrice);
                }

            }

        }
        

    }



}