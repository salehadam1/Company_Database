// Advanced Procedural Programming Assignment 
// name : saleh adam
// ID   : G00372853
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

// struct login hold the user logIn data
typedef struct logIn {
	//Data
	//log_in
	char userName[30];
	char password[30];
	//Next
	struct logIn* NEXT;
}log_in;


// struct for the company data stock
typedef struct node {
	//Data
	//company_Database
	float itemNumber;
	char itemName[30];
	char itemSupplierName[30];
	float itemSupplierNumber;
	float re_Order;
	float NumberOfUnit;
	float costPerUnit;
	char lastOrderDate[30];
	char itemStored[30];
	char itemDepartment[30];
	char itemRe_orderMonth[30];
	char purchasePeople[30];
	//Next
	struct node* NEXT;
}company_Database;

// function 
int ask_ForOption();
int logIn(struct logIn** top);
void Add_Stock_fromfile(struct node** top);
int check_ItemNumber(struct node *top, float numer);
void Add_NewStock_Item(struct node** top, float num);
void Display_allitem(struct node* top);
void Display_specificstock(struct node* top);
void Update_StockIte(struct node* top);
void Delete_StockItem(struct node* top);
void Generate_statistic(struct node* top);
void Print_reportfile(struct node* top);
void List_allstock(struct node* top);
void updata_file(struct node* top);

void main()
{
	// calling both struct
	struct node* informtion = NULL;
	struct logIn* userInf = NULL;

	//function read file int linked list 
	// but it dosnot work its just read 1th line in the file 
	//
	Add_Stock_fromfile(&informtion);

	//variables 
	int reEnter;
	int option;
	float itemnumber;
	int itemPostion;
	// calling logIn function allowed user to logIn
	reEnter = logIn(&userInf);
	//while the return 2 kepp asking user to re-LogIn
	while (reEnter == 2)
	{
		reEnter = logIn(&userInf);
	}
	// login if the return 1
	if (reEnter == 1)
	{
		//calling an menu to allowed the user choose
		option = ask_ForOption();
		while (option != 0)
		{
			//option 1 allowed user to input new item into stock
			if (option == 1)
			{
				printf("pleas enter the Stock Item Number (Assume an integer – must be unique)\n");
				scanf("%f", &itemnumber);

				//calling function for check the item number as must be unique
				itemPostion = check_ItemNumber(informtion, itemnumber);
				//if it return 0 that mean the item number did not match and go in and add the new item
				if (itemPostion == 0)
				{
					// calling function to add the new item stock
					Add_NewStock_Item(&informtion, itemnumber);
				}
			}
			// option 2 for display all the stock items
			else if (option == 2)
			{
				// calling function for display 
				Display_allitem(informtion);
			}
			//option 3 for display specific stock item 
			else if (option == 3)
			{
				// calling function for the display
				Display_specificstock(informtion);
			}
			//option for update an item 
			else if (option == 4)
			{
				// calling the update function
				Update_StockIte(informtion);
			}
			// option for deleten an item
			else if (option == 5)
			{
				// calling the deleten function
				Delete_StockItem(informtion);
			}
			// option for Generate by item department
			else if (option == 6)
			{
				// calling the Generate function
				Generate_statistic(informtion);
			}
			// option for Print out the report
			else if (option == 7)
			{
				//calling the report function
				Print_reportfile(informtion);
			}
			else if (option == 8)
			{
				List_allstock(informtion);
			}
			//calling function to updata the file
			updata_file(informtion);
			//calling an menu to allowed the user choose
			option = ask_ForOption();
		}

	}
	//else if the user logout or the logIn did not go right 
	else
	{
		printf("you been logout\n");
	}

	getch();
}
// function ask give an option to user for choose one of the main
int ask_ForOption()
{
	int asking;
	printf("Enter 1 to  Add Stock Item (Note: Stock Item Number must be unique)\n");
	printf("Enter 2 to  Display all stock item details to scree\n");
	printf("Enter 3 to  Display specific stock item details\n");
	printf("Enter 4 to  Update a stock item details \n");
	printf("Enter 5 to  Delete a stock ite\n");
	printf("Enter 6 to  Generate statistics (a – c) based on the user selecting a certain department\n");
	printf("Enter 7 to  Print all stock items details into a report file\n");
	printf("Enter 8 to  List all the stock items in order of their total monetary valu\n");
	printf("Enter 0 to  logout\n");
	scanf("%d", &asking);
	while (asking < 0 && asking > 8)
	{
		printf("pleas choos one of the options\n");
		printf("Enter 1 to  Add Stock Item (Note: Stock Item Number must be unique)\n");
		printf("Enter 2 to  Display all stock item details to scree\n");
		printf("Enter 3 to  Display specific stock item details\n");
		printf("Enter 4 to  Update a stock item details \n");
		printf("Enter 5 to  Delete a stock ite\n");
		printf("Enter 6 to  Generate statistics (a – c) based on the user selecting a certain department\n");
		printf("Enter 7 to  Print all stock items details into a report file\n");
		printf("Enter 8 to  List all the stock items in order of their total monetary valu\n");
		printf("Enter 0 to  logout\n");
		scanf("%d", &asking);
	}
	return asking;
}
// function for allowed  the user to logIn
int logIn(struct logIn** top)
{
	// call the struct 
	struct logIn* newNode;
	// open file
	FILE*userInput;
	//call file to read from the file into logIn linked list
	userInput = fopen("loginstructure.txt", "r");

	//variables 
	int check = 0;
	char name[30];
	char passowrd[30];
	int ask;
	int i = 0;
	// asking user to input ther info
	printf("pleas Enter the user name\n");
	scanf("%s", name);
	printf("pleas Enter the passowrd\n");
	// while the user input the passowrd show output **
	do {
		passowrd[i] = getch();

		if (passowrd[i] != '\r')
		{
			printf("*");
		}
		i++;


	} while (i <= 7);
	passowrd[i - 1] = '\0';
	printf("\n");
	// check the file 
	if (userInput == NULL)
	{
		printf("Sorry the file could not be opened\n");
	}
	else
	{
		// keep reading the file and add them to the link list
		while (!feof(userInput))
		{
			newNode = (struct logIn*)malloc(sizeof(struct logIn));

			fscanf(userInput, "%s %s \n", newNode->userName, newNode->password);

			// while its reading from file into list check the user info
			// if it match or not
			if (strcmp(newNode->userName, name) == 0)
			{
				if (strcmp(newNode->password, passowrd) == 0)
				{
					// variables  for checking if it match or not
					check++;
				}
			}
			newNode->NEXT = *top;
			*top = newNode;
		}

	}
	fclose(userInput);
	i = 0;
	// if the check great than 0 that mean the user input match and login and return 1
	if (check > 0)
	{
		printf("welcom %s\n", name);
		printf("pleas choose one of the option\n");
		return 1;
	}
	// if the check = 0 that mean the user input did not match 
	//then giver user the option down
	else if (check == 0)
	{
		printf("user name or the passowrd not found please choose one\n");
		printf("Ener 1 for re-login\n");
		printf("Ener 2 for sign up\n");
		printf("Ener 3 for exit\n");
		scanf("%d", &ask);

		// while the user did not choos one of the list
		while (ask != 3 && ask != 1 && ask != 2)
		{
			printf("pleas chosse one of the optin\n");
			printf("user name or the passowrd not found please choose one\n");
			printf("Ener 1 for re-login\n");
			printf("Ener 2 for sign up\n");
			printf("Ener 3 for exit\n");
			scanf("%d", &ask);

		}
	}
	// user choose 1 the drive user to re-login by return 2
	if (ask == 1)
	{
		return 2;
	}
	// user choose  2  that mean wann sign up and then return 1
	// and add the new user logIn info into the loginstructure.txt file
	else if (ask == 2)
	{
		newNode = (struct logIn*)malloc(sizeof(struct logIn));

		userInput = fopen("loginstructure.txt", "a");
		printf("pleas Enter the user name\n");
		scanf("%s", newNode->userName);
		printf("pleas Enter the passowrd\n");
		do {
			newNode->password[i] = getch();

			if (newNode->password[i] != '\r')
			{
				printf("*");
			}
			i++;


		} while (i <= 7);
		newNode->password[i - 1] = '\0';

		printf("\n");
		fprintf(userInput, "%s %s\n", newNode->userName, newNode->password);

		fclose(userInput);
		printf("welcom %s\n", newNode->userName);
		printf("pleas choose one of the option\n");

		newNode->NEXT = *top;
		*top = newNode;
		return 1;
	}
	// else for exiting the logIn

	else
	{
		return 3;
	}

}
// function read from file into  company stock linked list
void Add_Stock_fromfile(struct node** top)
{
	// calling the struct and the File
	struct node* newNode;
	FILE* data;
	// open the file 
	data = fopen("database.txt", "r");
	if (data == NULL)
	{
		printf("Sorry the file could not be opened\n");
	}
	else
	{
		while (!feof(data))
		{
			//add from file into linked list
			newNode = (struct node*)malloc(sizeof(struct node) * 1);
			fscanf(data, "%f %s %s %f %f %f %f %s %s %s %s %s\n", &newNode->itemNumber, newNode->itemName, newNode->itemSupplierName, &newNode->itemSupplierNumber, &newNode->re_Order, &newNode->NumberOfUnit, &newNode->costPerUnit, newNode->lastOrderDate, newNode->itemStored, newNode->itemDepartment, newNode->itemRe_orderMonth, newNode->purchasePeople);

			//printf("%f %s %s %f %f %f %f %s %s %s %s %s\n", newNode->itemNumber, newNode->itemName, newNode->itemSupplierName, newNode->itemSupplierNumber, newNode->re_Order, newNode->NumberOfUnit, newNode->costPerUnit, newNode->lastOrderDate, newNode->itemStored, newNode->itemDepartment, newNode->itemRe_orderMonth, newNode->purchasePeople);

				//printf("hello\n");


			newNode->NEXT = *top;
			*top = newNode;
		}
	}
	fclose(data);

}
// function for check the item Number as  must be unique
// by passing the user input item number 
int check_ItemNumber(struct node* top, float numer)
{
	// calling linked list
	struct node* temp;
	temp = top;
	int i = 0;
	int ask;
	// while the list is not != null then keep checking all the item number
	// in the list
	while (temp != NULL)
	{

		if (numer == temp->itemNumber)
		{
			// if the item number been match give the user an option to updata the item stock 
			printf("item number have been found in the stock\n");
			printf("choos one of the option\n");
			printf("enter 1 to updata item stoct\n");
			printf("enter 2 to exit\n");
			scanf("%d", &ask);
			while (ask != 1 && ask != 2)
			{
				printf("****************************************\n");
				printf("item number have been found in the stock\n");
				printf("choos one of the option\n");
				printf("enter 1 to updata item stoct\n");
				printf("enter 2 to exit\n");
				scanf("%d", &ask);
			}
			if (ask == 1)
			{
				printf("enter new Stock Item Supplier Name\n");
				scanf("%s", temp->itemSupplierName);
				printf("enter new Stock Item Supplier Contact Number\n");
				scanf("%f", &temp->itemSupplierNumber);
				printf("enter new Re-order threshold limit \n");
				scanf("%f", &temp->re_Order);
			}
			printf("\n");
			// i variable for check 
			i++;
		}
		temp = temp->NEXT;
	}
	//return the i value
	return i;
}
// function for add the new stock item into list 
// after checking the item Number 
void Add_NewStock_Item(struct node** top, float num)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	FILE* data;
	int j;
	// open the file to add the new item list

	data = fopen("database.txt", "a");

	newNode->itemNumber = num;
	printf("pleas enter the Stock Item Name\n");
	scanf("%s", newNode->itemName);
	printf("pleas enter the Stock Item Supplier Name\n");
	scanf("%s", newNode->itemSupplierName);
	printf("pleas enter the Stock Item Supplier Contact Numbe\n");
	scanf("%f", &newNode->itemSupplierNumber);
	printf("pleas enter the Re-order threshold limit\n");
	scanf("%f", &newNode->re_Order);
	printf("pleas enter the Number of Units \n");
	scanf("%f", &newNode->NumberOfUnit);
	printf("pleas enter the Cost per Unit  \n");
	scanf("%f", &newNode->costPerUnit);
	printf("pleas enter the Last Order Date\n");
	scanf("%s", newNode->lastOrderDate);
	printf("Does this item need to be stored in a hazardous chemical store ?\n");
	printf("enter 1 for YES\n");
	printf("enter 2 for NO\n");
	scanf("%d", &j);
	while (j != 1 && j != 2)
	{
		printf("pleas enter 1 or 2\n");
		printf("Does this item need to be stored in a hazardous chemical store ?\n");
		printf("enter 1 for YES\n");
		printf("enter 2 for NO\n");
		scanf("%d", &j);

	}
	if (j == 1)
	{
		strcpy(newNode->itemStored, "YES");
	}
	else if (j == 2)
	{
		strcpy(newNode->itemStored, "NO");
	}
	printf("Which Department does this stock item belong to ?\n");
	printf("enter 1 for Office \n");
	printf("enter 2 for Maintenance \n");
	scanf("%d", &j);
	while (j != 1 && j != 2)
	{
		printf("pleas enter 1 or 2\n");
		printf("Which Department does this stock item belong to ?\n");
		printf("enter 1 for Office \n");
		printf("enter 2 for Maintenance \n");
		scanf("%d", &j);
	}
	if (j == 1)
	{
		strcpy(newNode->itemDepartment, "Office");
	}
	else if (j == 2)
	{
		strcpy(newNode->itemDepartment, "Maintenance");
	}
	printf("Which of the following months do items need to re-order ?\n");
	printf("enter 1 for No Specified Month \n");
	printf("enter 2 for Feb  \n");
	printf("enter 3 for August   \n");
	scanf("%d", &j);
	while (j != 1 && j != 2 && j != 3)
	{
		printf("pleas enter 1 or 2 or 3\n");
		printf("Which of the following months do items need to re-order ?\n");
		printf("enter 1 for No Specified Month \n");
		printf("enter 2 for Feb  \n");
		printf("enter 3 for August   \n");
		scanf("%d", &j);

	}
	if (j == 1)
	{
		strcpy(newNode->itemRe_orderMonth, "No Specified Month");
	}
	else if (j == 2)
	{
		strcpy(newNode->itemRe_orderMonth, "Feb");
	}
	else if (j == 3)
	{
		strcpy(newNode->itemRe_orderMonth, "August");
	}
	printf("Which of the following people need to authorise the purchase?\n");
	printf("enter 1 for Managing Director  \n");
	printf("enter 2 for Financial Controller   \n");
	printf("enter 3 for Department Manager    \n");
	scanf("%d", &j);
	while (j != 1 && j != 2 && j != 3)
	{
		printf("pleas enter 1 or 2 or 3\n");
		printf("Which of the following people need to authorise the purchase?\n");
		printf("enter 1 for Managing Director  \n");
		printf("enter 2 for Financial Controller   \n");
		printf("enter 3 for Department Manager    \n");
		scanf("%d", &j);

	}
	if (j == 1)
	{
		strcpy(newNode->purchasePeople, "Managing Director");
	}
	else if (j == 2)
	{
		strcpy(newNode->purchasePeople, "Financial Controller");
	}
	else if (j == 3)
	{
		strcpy(newNode->purchasePeople, "Department Manager");
	}

	fprintf(data, "%f %s %s %f %f %f %f %s %s %s %s %s\n", newNode->itemNumber, newNode->itemName, newNode->itemSupplierName, newNode->itemSupplierNumber, newNode->re_Order, newNode->NumberOfUnit, newNode->costPerUnit, newNode->lastOrderDate, newNode->itemStored, newNode->itemDepartment, newNode->itemRe_orderMonth, newNode->purchasePeople);
	fclose(data);
	newNode->NEXT = *top;
	*top = newNode;
}
//function for diplay the stock item into list 
void Display_allitem(struct node* top)
{
	struct node* temp;
	temp = top;
	int i = 0;

	while (temp != NULL)
	{
		// i variable for checking if there is item list in the link
		i++;

		printf("itemnumber          :%f *itemname            :%s *itemSupplierName    :%s\nitemSupplierNumber  :%f *re_Order            :%f *NumberOfUnit        :%f\ncostPerUnit         :%f *lastOrderDate       :%s *itemStored          :%s\nitemDepartment      :%s *itemRe_orderMonth   :%s *purchasePeople      :%s\n", temp->itemNumber, temp->itemName, temp->itemSupplierName, temp->itemSupplierNumber, temp->re_Order, temp->NumberOfUnit, temp->costPerUnit, temp->lastOrderDate, temp->itemStored, temp->itemDepartment, temp->itemRe_orderMonth, temp->purchasePeople);
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		temp = temp->NEXT;
	}// i i = 0 that mean there is no item in the list
	if (i == 0)
	{
		printf("*************************************\n\n");
		printf("sorry theres no any item in the story\n\n");
		printf("*************************************\n\n");
	}

}
//function for display the specific stock item details  
void Display_specificstock(struct node* top)
{
	struct node* temp;
	temp = top;
	int i = 0;
	int ask;
	float itNmuner;
	char name[30];
	//asking user to shoose how they want to display the item
	// by item number ot item name
	printf("Display a specific stock item details \n");
	printf("enter 1 by Display by Stock Item name\n");
	printf("enter 2 by Display by Stock Item number\n");
	scanf("%d", &ask);
	while (ask != 1 && ask != 2)
	{
		printf("pleas enter chose one of the option\n");
		printf("Display a specific stock item details \n");
		printf("enter 1 by Display by Stock Item name\n");
		printf("enter 2 by Display by Stock Item number\n");
		scanf("%d", &ask);
	}
	if (ask == 1)
	{
		printf("enter Stock Item name\n");
		scanf("%f", &itNmuner);
	}
	if (ask == 2)
	{
		printf("enter Stock Item number\n");
		scanf("%s", name);
	}

	// check the list for what the user has\have input
	while (temp != NULL)
	{

		if (ask == temp->itemNumber || strcmp(name, temp->itemName) == 0)
		{
			i++;
			printf("itemnumber          :%f\nitemname            :%s\nitemSupplierName    :%s\nitemSupplierNumber  :%f\nre_Order            :%f\nNumberOfUnit        :%f\ncostPerUnit         :%f\nlastOrderDate       :%s\nitemStored          :%s\nitemDepartment      :%s\nitemRe_orderMonth   :%s\npurchasePeople      :%s\n", temp->itemNumber, temp->itemName, temp->itemSupplierName, temp->itemSupplierNumber, temp->re_Order, temp->NumberOfUnit, temp->costPerUnit, temp->lastOrderDate, temp->itemStored, temp->itemDepartment, temp->itemRe_orderMonth, temp->purchasePeople);
		}
		temp = temp->NEXT;
	}
	if (i == 0)
	{
		printf("*************************************\n\n");
		printf("sorry theres no any item in the story\n\n");
		printf("*************************************\n\n");
	}

}
//function for update the specific stock item details
void Update_StockIte(struct node* top)
{
	struct node* temp;
	temp = top;
	int i = 0;
	int ask;
	float itNmuner;
	char name[30];
	//asking user to shoose how they want to display the item
	// by item number ot item name
	printf("Update a specific stock item details \n");
	printf("enter 1 to Update by Stock Item name\n");
	printf("enter 2 to Update by Stock Item number\n");
	scanf("%d", &ask);
	while (ask != 1 && ask != 2)
	{
		printf("pleas enter chose one of the option\n");
		printf("Update a specific stock item details \n");
		printf("enter 1 to Update by Stock Item name\n");
		printf("enter 2 to Update by Stock Item number\n");
		scanf("%d", &ask);
	}
	if (ask == 1)
	{
		printf("enter Stock Item name\n");
		scanf("%f", &itNmuner);
	}
	if (ask == 2)
	{
		printf("enter Stock Item number\n");
		scanf("%s", name);
	}


	while (temp != NULL)
	{

		if (ask == temp->itemNumber || strcmp(name, temp->itemName) == 0)
		{
			printf("*************************************\n\n");
			printf("enter new Stock Item Supplier Name\n");
			scanf("%s", temp->itemSupplierName);
			printf("enter new Stock Item Supplier Contact Number\n");
			scanf("%f", &temp->itemSupplierNumber);
			printf("enter new Re-order threshold limit \n");
			scanf("%f", &temp->re_Order);
			printf("*************************************\n\n");
			i++;
		}
		temp = temp->NEXT;
	}
	if (i == 0)
	{
		printf("*************************************\n\n");
		printf("sorry theres no any item in the story\n\n");
		printf("*************************************\n\n");
	}
	else
	{
		printf("*************************************\n\n");
		printf("item been successful updata \n\n");
		printf("*************************************\n\n");
	}

}
//function for delete the specific stock item details
void Delete_StockItem(struct node* top)
{
	struct node* temp = top;
	struct node* prev_temp;
	int i = 0;
	int ask;
	float itNmuner;
	char name[30];

	printf("Delete Stock Item \n");
	printf("enter 1 to Delete by Stock Item name\n");
	printf("enter 2 to Delete by Stock Item number\n");
	scanf("%d", &ask);
	while (ask != 1 && ask != 2)
	{
		printf("pleas enter chose one of the option\n");
		printf("Delete Stock Item \n");
		printf("enter 1 to Delete by Stock Item name\n");
		printf("enter 2 to Delete by Stock Item number\n");
		scanf("%d", &ask);
	}
	if (ask == 1)
	{
		printf("enter Stock Item name\n");
		scanf("%f", &itNmuner);
	}
	if (ask == 2)
	{
		printf("enter Stock Item number\n");
		scanf("%s", name);
	}


	while (temp != NULL)
	{

		if (ask == temp->itemNumber || strcmp(name, temp->itemName) == 0)
		{
			i++;

		}
		temp = temp->NEXT;
	}

	for (int j = 0; j < i - 1; j++)
	{
		prev_temp = temp;
		temp = temp->NEXT;
	}
	prev_temp->NEXT = temp->NEXT;
	free(temp);
	if (i == 0)
	{
		printf("*************************************\n\n");
		printf("sorry theres no any item in the story\n\n");
		printf("*************************************\n\n");
	}
	else
	{
		printf("*************************************\n\n");
		printf("item  been successful delete \n\n");
		printf("*************************************\n\n");
	}
}
//function for print report for all the item 
void Print_reportfile(struct node* top)
{
	struct node* temp = top;
	FILE* report;
	int i = 0;
	// 1th clear the file report
	report = fopen("reportFile.txt", "w+");
	// add the new report in to file
	report = fopen("reportFile.txt", "a");
	if (report == NULL)
	{

	}
	else
	{
		while (temp != NULL)
		{
			i++;
			fprintf(report, "itemnumber          :%f *itemname            :%s *itemSupplierName    :%s\nitemSupplierNumber  :%f *re_Order            :%f *NumberOfUnit        :%f\ncostPerUnit         :%f *lastOrderDate       :%s *itemStored          :%s\nitemDepartment      :%s *itemRe_orderMonth   :%s *purchasePeople      :%s\n", temp->itemNumber, temp->itemName, temp->itemSupplierName, temp->itemSupplierNumber, temp->re_Order, temp->NumberOfUnit, temp->costPerUnit, temp->lastOrderDate, temp->itemStored, temp->itemDepartment, temp->itemRe_orderMonth, temp->purchasePeople);
			fprintf(report, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			temp = temp->NEXT;
		}
	}
	fclose(report);
	if (i == 0)
	{
		printf("*************************************\n\n");
		printf("sorry theres no any item in the story\n\n");
		printf("*************************************\n\n");
	}
	else
	{
		printf("*************************************\n\n");
		printf("report file been successful\n\n");
		printf("*************************************\n\n");
	}
}
//function for generate report by the department 
void Generate_statistic(struct node* top)
{
	struct node* temp = top;
	char dep[30];
	int depart;
	int option;
	char slect[5];
	char prs[5];
	strcpy(prs, "%");

	//asking the user to choose the department 
	printf("pleas choose the department\n");
	printf("enter 1 for Office \n");
	printf("enter 2 for Maintenance \n");
	scanf("%d", &depart);
	while (depart != 1 && depart != 2)
	{
		printf("pleas choose the department\n");
		printf("enter 1 for Office \n");
		printf("enter 2 for Maintenance \n");
		scanf("%d", &depart);
	}
	if (depart == 1)
	{
		strcpy(dep, "Office");

	}
	else if (depart == 2)
	{
		strcpy(dep, "Maintenance");
	}
	printf("pleas choose one of the option\n");
	printf("Enter A for %s of stock items below the re-order threshold limit \n", prs);
	printf("Enter B for %s of stock items below twice the re-order threshold limit \n", prs);
	printf("Enter C for %s of stock items above twice the re-order threshold limit\n", prs);
	scanf("%s", slect);
	while ((strcmp(slect, "a") != 0) && (strcmp(slect, "A") != 0) && (strcmp(slect, "b") != 0) && (strcmp(slect, "B") != 0) && (strcmp(slect, "c") != 0) && (strcmp(slect, "C") != 0))
	{
		printf("******************************\n");
		printf("pleas choose one of the option\n");
		printf("Enter A for %s of stock items below the re-order threshold limit \n", prs);
		printf("Enter B for %s of stock items below twice the re-order threshold limit \n", prs);
		printf("Enter C for %s of stock items above twice the re-order threshold limit\n", prs);
		scanf("%s", slect);
	}
	while (temp != NULL)
	{
		if ((strcmp(slect, "a") == 0) || (strcmp(slect, "A") == 0))
		{
			if ((strcmp(dep, temp->itemDepartment) == 0))
			{
				printf("********************************************************\n");
				printf("till here and i dont real know what i have do for %s\n", dep);
				printf("slect option %s\n", slect);
				printf("********************************************************\n");
			}
		}

		if ((strcmp(slect, "b") == 0) || (strcmp(slect, "B") == 0))
		{
			if ((strcmp(dep, temp->itemDepartment) == 0))
			{
				printf("********************************************************\n");
				printf("till here and i dont real know what i have do for %s\n", dep);
				printf("slect option %s\n", slect);
				printf("********************************************************\n");
			}
		}

		if ((strcmp(slect, "C") == 0) || (strcmp(slect, "c") == 0))
		{
			if ((strcmp(dep, temp->itemDepartment) == 0))
			{
				printf("********************************************************\n");
				printf("till here and i dont real know what i have do for %s\n", dep);
				printf("slect option %s\n", slect);
				printf("********************************************************\n");
			}
		}

		temp = temp->NEXT;
	}
}
//function for list all the stock item by department
void List_allstock(struct node* top)
{
	printf("*************************************\n\n");
	printf("sorry did not get what i have to do \n\n");
	printf("*************************************\n\n");
}
//function for updata the file
void updata_file(struct node* top)
{
	struct node* newNode;
	newNode = top;
	FILE* delet;
	//making the file blank.
	delet = fopen("database.txt", "w+");
	delet = fopen("database.txt", "a");
	if (delet == NULL)
	{
		printf("Sorry the file could not be opened\n");
	}
	else
	{
		while (newNode != NULL)
		{
			//appending the new list into file
			fprintf(delet, "%f %s %s %f %f %f %f %s %s %s %s %s\n", newNode->itemNumber, newNode->itemName, newNode->itemSupplierName, newNode->itemSupplierNumber, newNode->re_Order, newNode->NumberOfUnit, newNode->costPerUnit, newNode->lastOrderDate, newNode->itemStored, newNode->itemDepartment, newNode->itemRe_orderMonth, newNode->purchasePeople);

			newNode = newNode->NEXT;
		}

	}
	fclose(delet);
}