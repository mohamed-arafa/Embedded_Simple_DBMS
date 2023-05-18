/*
 * @file dbms.h 
 * @brief Header file for dbms.c which is a basic implementation of a database management system
 *                                     that provides add, update, delete and query operations.
 * @author Eng-Mohamed Arafa
 * @version 1.0
 * @date May-2023
*/

#ifndef _DBMS_H
    #define _DBMS_H

/********* Include section Begins ******************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/********* Include section Ends ********************/
/********* Macros Definitions Begins ***************/ 

/********* Macros Definitions Ends *******************/
/********* User defined section Begins ***************/
typedef struct
{
    int ID;
    int amount;
    char name[30];
    char complaint[100];
}customer;

typedef struct  
{
    int args_num;
    char** args;
}args_t;
/******** User defined section Ends *********************/

/********* Function prototype section Begins ************/
/********************************************************
 * @name [iDbmsHelp] function
 * @brief prints all the available functions and queries.
 * 
 * @param ptrParameters 
 * @return int
 */
int iDbmsHelp(void* ptrParameters);

/*********************************************************
 * @name [ print all ]
 * @brief Function for getting all records from the database and printing them to stdout.
 * @param ptrParameter pointer to nothing and should be set to NULL.
 * @return 0 if all records are prented successfully, and returns 1 otherwise.
 */
int iDbmsPrint_all(void *ptrParameter);

/*********************************************************
 * @name [save record]
 * @brief Function for initializing the database or adding new records.
 * @param ptrParameter pointer to the customer data structure that contains data for the customer.
 * @return 0 on success, -1 on failure with error message.
 ***************************************************************/
int iDbmsSave_record(void *ptrParameter);

/****************************************************************
 * @name [ delete records]
 * @brief this function delets the specified record from the database with its associated ID.
 * @param ptrParameter pointer to the record ID to be deleted from the database.
 * @return 0 on success and -1 on failure.
 ***************************************************************/
int iDbmsDelet_record(void *ptrParameter);


/****************************************************************
 * @name [ print menue ]
 * @brief this function is called to tell the user the available functions and their number.
 * @param ptrParameter should be null.
 * @return a value of the function that represents the query index.
 */
static int print_menue(void *ptrParameter);


/****************************************************************
 * @name [ excute an indexed task ]
 * @brief Excute the requested function using its number.
 * @param ptrParameter a pointer to the number of the function.
 * @return non.
 */
static int run_task_choice(void *ptrParameter);

/***************************************************************
 * @name [ print complaint ]
 * @brief This function prints the complaint of a customer with the given ID number.
 * @param ptrParameter a pointer to the customer ID number.
 * @return 0 on success and -1 on failure.
 *
 ***************************************************************/
int iDbmsPrint_complaint(void* ptrParameter);


/****************************************************************
 * @name [ print name ]
 * @brief This function prints the name of a customer with the given ID number.
 * @param ptrParameter a pointer to the customer ID number.
 * @return 0 on success and -1 on failure.
 *
 **************************************************************/
int iDbmsPrint_name(void* ptrParameter);

/****************************************************************
 * @name [ print payment ]
 * @brief This function prints the payment of a customer with the given ID number.
 * @param ptrParameter a pointer to the customer ID number.
 * @return 0 on success and -1 on failure.
 *
 ***************************************************************/
int iDbmsPrint_payment(void *ptrParameter);

/****************************************************************
 * @name [ edit ID ]
 * @brief this function edit customer ID.
 * @param ptrParameter should be null or a pointer to a customer old ID.
 * @return 0 on success and -1 on failure.
 */
int iDbmsEdit_ID(void *ptrParameter);

/****************************************************************
 * @brief this function edit customer amount of payment.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success and 1 on failure.
 */
int iDbmsEdit_name(void *ptrParameter);

/****************************************************************
 * @brief this function edit customer amount of payment.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success and 1 on failure.
 */
int iDbmsEdit_complaint(void *ptrParameter);

/****************************************************************
 * @brief this function edit customer amount of payment.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success and 1 on failure.
 */
int iDbmsEdit_amount_payment(void *ptrParameter);


/********* Function prototype section Ends *************/

/********* Log history Begins **************************/
/*
 * 17 May 2023, file created, Mohamed Arafa
 * 18 May 2023, file modified, Mohamed Arafa
 */
/********* Log history Ends ****************************/
#endif /* _DBMS_H */