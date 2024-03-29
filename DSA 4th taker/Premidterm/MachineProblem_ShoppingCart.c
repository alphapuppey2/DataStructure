#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
#define PMSIZE 3

typedef struct{
	char promoCode[17];
	float discount;
}PromoCode;

typedef struct{
	char prodID[9];
	char prodName[33];
	float unitPrice;
	int qty;
}Product;

typedef struct{
	Product prodList[50];
	int lastProd; /* When ProdList is empty, lastProd is -1 */
}ProdList;

typedef struct nodeItem{
	Product item;
	struct nodeItem* nextItem;
}nodeItem, *SList;

typedef struct{
	float VAT;	/*12% of totalPrice */
	float discount; /* Value is equal to 0.00 if no Promo code has been used */
	float totalPrice;
}Invoice;

typedef struct{
	SList sCart;
	int numItems;
	char promoCode[17]; /* default value is "" (empty string) */
	Invoice receipt;
}Cart;

void pause(void);

/* Problem 1 */
/* Instructions: 
	1) displayProdList() - Partial Code is provided. The function will display the details of ALL the products in the 
						   passed ProductList.
	2) initProdList() - The function will initialize the passed ProductList.
	3) populateProdList() - Partial Code is provided. The function will populate the passed ProductList with ALL the
							products in the array of products defined within the function.
*/
void displayProdList(ProdList);
void initProdList(ProdList*);
void populateProdList(ProdList*);

/* Problem 2 */
/* Instructions:
	1) initCart() - The function will initialize the passed Cart to be empty.
	2) genReceipt() - The function will calculate for the values of the receipt for the passed Cart.
	3) displayCart() - Partial Code is provided. The function will display all the details of the Cart based on the format
					   given in the output screenshot. Note: The function will call genReceipt to calculate the Receipt details
					   of the given Cart before these details are displayed.
	4) addToCart() - The function will check if the passed productID exists in the ProdList and if there is enough stocks 
					 in the ProdList to accomodate your purchase. If both of these conditions are met, it will insert
					 the item into the FIRST node of your sCart. Update the necessary fields upon insertion. 
					 Note: Machine Problems will not normally say what the necessary fields are. But you can ask me if
					 	   you give up. :)
*/
Cart initCart(void);
void genReceipt(Cart*, PromoCode[], char[]);
void displayCart(Cart*);
void addToCart(Cart*, ProdList*, char[], int);

/* Problem 3 */
/* Instructions:
	1) returnItem() - The function will check if the passed productID exists in the passed Cart. If it does, also check if
					  the qty to be returned does not exceed the quantity you've purchased based on you Cart info. If both
					  these conditions are met, subtract the quantity for that item in your Cart. Also, if the quantity
					  for that item reaches ZERO, delete the item from your cart. Update the necessary fields upon successful
					  item return.
					  Note: Machine Problems will not normally say what the necessary fields are. But you can ask me if
					 	    you give up. :)
*/
void returnItem(Cart*, ProdList*, char[], int);

int main(void)
{
	ProdList groceryStore;
	Cart myCart;
	char prod1[] = "FR000001";
	char prod2[] = "FR000010";
	char prod3[] = "VG000001";

	puts("PROBLEM 1");
	/* Instructions:
		1) Initialize variable groceryStore. 
		2) Populate groceryStore with products.
		3) Display the products in the groceryStore.
		4) Call the pause() function.
	*/
		initProdList(&groceryStore);
		populateProdList(&groceryStore);
		displayProdList(groceryStore);
		pause();


	/*1) Initialize variable myCart.
		2) Call function addToCart passing prod1 as the string parameter, and 55 as the int parameter.
		3) Call function addToCart passing prod1 as the string parameter, and 10 as the int parameter.
		4) Call function addToCart passing prod2 as the string parameter, and 50 as the int parameter.
		5) Call function addToCart passing prod3 as the string parameter, and 10 as the int parameter.
		6) Display the contents of myCart.
		7) Display the products in the groceryStore.
		8) Call the pause() function.
	*/
	myCart = initCart();
	addToCart(&myCart , &groceryStore, prod1, 30);
	addToCart(&myCart , &groceryStore, prod1, 10);
	addToCart(&myCart , &groceryStore, prod2, 50);
	addToCart(&myCart , &groceryStore, prod3, 10);

	displayCart(&myCart);
	displayProdList(groceryStore);
	pause();

	
	puts("PROBLEM 3");
	/* Instructions:
		1) Call function returnItem passing prod1 as the string parameter, and 20 as the int parameter.
		2) Call function returnItem passing prod1 as the string parameter, and 40 as the int parameter.
		3) Call function returnItem passing prod2 as the string parameter, and 10 as the int parameter.
		4) Call function returnItem passing prod3 as the string parameter, and 10 as the int parameter.
		5) Display the contents of myCart.
		6) Display the products in the groceryStore.
		7) Call the pause() function.
	*/

	returnItem(&myCart,&groceryStore,prod1,20);
	returnItem(&myCart,&groceryStore,prod1,40);
	returnItem(&myCart,&groceryStore,prod2,10);
	returnItem(&myCart,&groceryStore,prod3,10);

	displayCart(&myCart);
	displayProdList(groceryStore);
	pause();



	
	return 0;
}

void pause(void)
{
	printf("\n\nPress any key to continue...");
	getch(stdin);
	system("CLS");
}
 
void displayProdList(ProdList PL)
{
	printf("\n\n<-- Product List -->\n");
	printf("%-10s", "ProdID");
	printf("%-15s", "ProdName");
	printf("%-10s", "Price");
	printf("%-10s", "Stocks");

	int x;
	for (x = 0; x <= PL.lastProd ; x++)
	{
		printf("\n%-10s",PL.prodList[x].prodID);
		printf("%-15s",PL.prodList[x].prodName);
		printf("%-10f",PL.prodList[x].unitPrice);
		printf("%-10d",PL.prodList[x].qty);
	}
	
}

void initProdList(ProdList* PL)
{
	PL->lastProd = -1;
}

void populateProdList(ProdList* PL)
{
	int i;
	Product items[] = {{"FR000001", "Apple", 32.00, 60},
					   {"FR000002", "Orange", 25.00, 50},
					   {"FR000003", "Pineapple", 66.00, 30},
					   {"FR000004", "Durian", 45.00, 25},
					   {"FR000005", "Squash", 54.00, 40},
					   {"FR000006", "Grapes", 12.00, 150},
					   {"FR000007", "Mango", 33.00, 80},
					   {"FR000008", "Cherries", 7.00, 150},
					   {"VG000001", "Cabbage", 24.00, 40},
					   {"VG000002", "Broccoli", 18.00, 60},
					  };

	for ( i = 0; i < SIZE; i++)
	{
		PL->prodList[i] = items[i];
	}
	PL->lastProd = i - 1;
}

Cart initCart(void)
{
	Cart Shopee;

	Shopee.sCart = NULL;
	Shopee.numItems = 0;
	strcpy(Shopee.promoCode,"");
	Shopee.receipt.VAT = 0;
	Shopee.receipt.discount = 0;
	Shopee.receipt.totalPrice = 0;

	return Shopee;
}

void genReceipt(Cart* C, PromoCode promoList[], char promoCode[])
{
	int total,x;
	SList trav;

	if(strcmp(promoCode , "") != 0){
		for(x = 0; x < PMSIZE && strcmp(promoList[x].promoCode ,promoCode) != 0;x++)
		{	
		}

		if(x < PMSIZE){
			if(strcmp(promoList[x].promoCode , "NEWCUSTOMER") == 0)
			{
				C->receipt.discount = C->receipt.totalPrice * 0.33;
			}
			else if(strcmp(promoList[x].promoCode , "FRIYAY") == 0)
			{
				C->receipt.discount = C->receipt.totalPrice * 0.15;
			}
			else if(strcmp(promoList[x].promoCode , "HURRAYFORPAYDAY") == 0)
			{
				C->receipt.discount = C->receipt.totalPrice * 0.20;
			}
		}
	}
	else{
		C->receipt.discount = 0;
	}
	strcpy(C->promoCode, promoList[x].promoCode);
	C->receipt.totalPrice = C->receipt.totalPrice - C->receipt.discount; 
	C->receipt.VAT = C->receipt.totalPrice * 0.12;
	
}

void displayCart(Cart* C)
{
	PromoCode promos[PMSIZE] = {{"NEWCUSTOMER", 0.33},
						  {"FRIYAY", 0.15},
						  {"HURRAYFORPAYDAY", 0.20}
						 };
	
	printf("\n\n<-- Your Cart -->\n");
	printf("%-10s", "ProdID");
	printf("%-15s", "ProdName");
	printf("%-10s", "Price");
	printf("%-10s", "Qty");
	printf("%-15s", "Line Item Price");	/* Line item Price is the product of qty and price */

	SList trav = C->sCart;
	for(;trav != NULL ; trav= trav->nextItem){
		printf("\n%-10s%-15s%-10.2f%-10d%-15.2f", trav->item.prodID , trav->item.prodName , trav->item.unitPrice, trav->item.qty , trav->item.unitPrice * trav->item.qty);
	}
	
	genReceipt(C , promos,"NEWCUSTOMER");
	printf("\n\nNumber of items: %d\n\nPromo Code: %s\nVAT: %.2f\nDiscount: %.2f\nTotal Price: %.2f\n",C->numItems , C->promoCode , C->receipt.VAT , C->receipt.discount ,C->receipt.totalPrice);



}

void addToCart(Cart* C, ProdList* PL, char prodID[], int itemQty) 
{
	SList shopCart = C->sCart;

	int x;
	SList *trav , temp; 
	/*check from the ProductList is available*/
	for(x = 0; x <= PL->lastProd && strcmp(PL->prodList[x].prodID , prodID) != 0; x++){}

	if(x <= PL->lastProd){
		/* if found Check itemQty is Less than the Stocks */
		if(PL->prodList[x].qty > itemQty){
			for(trav = &C->sCart ; *trav != NULL && strcmp((*trav)->item.prodID , prodID) != 0;trav = &(*trav)->nextItem){}
			if(*trav == NULL){
				temp = (SList)malloc(sizeof(nodeItem));
				if(temp != NULL){
					temp->item = PL->prodList[x];
					temp->item.qty = itemQty;

					PL->prodList[x].qty = PL->prodList[x].qty - itemQty;
					C->numItems++;
					C->receipt.totalPrice = C->receipt.totalPrice + (temp->item.qty * temp->item.unitPrice);

					temp->nextItem = C->sCart;
					C->sCart = temp; 

				}
			}
		}else{
			printf("Not Enough stocks to complete the transaction\n");
		}
	}
	else{ 
		printf("Product ID [%s] not Found\n", prodID);
	}
}

void returnItem(Cart* C, ProdList* PL, char prodID[], int qty)
{
	SList *trav,temp;

	int x,total;
	for(trav = &C->sCart ; *trav != NULL && strcmp((*trav)->item.prodID , prodID) != 0; trav = &(*trav)->nextItem){}

	if(*trav != NULL){
		for(x = 0; x <= PL->lastProd && strcmp(PL->prodList[x].prodID,prodID) != 0; x++){}

		if(x <= PL->lastProd){
			if(qty <= (*trav)->item.qty){
				temp = *trav;
				PL->prodList[x].qty = PL->prodList[x].qty + qty;
				temp->item.qty = temp->item.qty - qty;

				C->receipt.totalPrice = C->receipt.totalPrice - (temp->item.qty * temp->item.unitPrice); 


				if(temp->item.qty == 0){
					*trav = temp->nextItem;
					C->numItems--;
					free(temp);
				}
				
				for(temp = C->sCart ,total = 0; temp != NULL;temp = temp->nextItem){
					total = total + (temp->item.qty * temp->item.unitPrice);
				} 
				C->receipt.totalPrice = total;
			}
			else{
				printf("you cannot return greater than your purchased\n\n");
			}
		}
		else{
			printf("Invalid Sales\n\n");
		}
	}
	else{
		printf("You are returning an item that isn't in your cart\n\n");
	}

}
