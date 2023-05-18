/*
 * @file dbms.c 
 * @brief DBMS (Database Management System) is an implementation of a basic database system.
 *             this file contains basic functions to save, read, delete and edit database recordes.
 * @author Eng-Mohamed Arafa.
 * @version 1.0
 * @date May-2023 
*/

#include "dbms.h"

// array of pointers of all the functions of the system.
int (*task_arr[])(void* ptrParameters)=
{
    iDbmsPrint_all,
    iDbmsPrint_name,
    iDbmsPrint_payment,
    iDbmsPrint_complaint,  
    iDbmsDelet_record,
    iDbmsSave_record,
    iDbmsEdit_ID,
    iDbmsEdit_amount_payment,
    iDbmsEdit_name,
    iDbmsEdit_complaint,
    iDbmsHelp
};

/**
 * @name [iDbmsHelp] function
 * @brief prints all the available functions and queries.
 * 
 * @param ptrParameters 
 * @return nothing
 */
int iDbmsHelp(void* ptrParameters)
{
    int choice=print_menue(NULL);
    run_task_choice(&choice);
}


/****************************************************************
 * @brief Function for initializing the database or adding new records.
 * @param ptrParameter pointer to the customer data structure that contains data for the customer.
 * @return 0 on success, -1 on failure with error message.
 */
int iDbmsSave_record(void *ptrParameter)
{
    customer xCustomer;
    char str[30];
    FILE *xFile = fopen("database.txt", "a"); // open the database file for appending.
    char cContinue = 'y';
    int len=0;
    do
    { 
        // read the name, ID, payment and complaint from the used and write them to the file.
        printf("name: ");
        //getline(&xCustomer->name,&len,stdin); // read the name
        gets(str);
        gets(xCustomer.name);
        printf("ID: ");
        scanf("%i", &xCustomer.ID);
        printf("payment amount: ");
        scanf("%i", &xCustomer.amount);
        printf("complaint: ");
        gets(xCustomer.complaint);
        gets(xCustomer.complaint);

        // write the record to the file.
        fprintf(xFile, "%i,%s,%i,%s\n", xCustomer.ID, xCustomer.name, xCustomer.amount, xCustomer.complaint);
        printf("customer saved successfully\n\n");

        printf("do you want to continue? (y/n)"); // ask the user to add another record or cancel.
        scanf("%c", &cContinue);
    } while (cContinue == 'y');
    fclose(xFile); // close the file.
    return 0;
}

/****************************************************************
 * @brief Function for getting all records from the database and printing them to stdout.
 * @param ptrParameter pointer to nothing and should be set to NULL.
 * @return 0 if all records are prented successfully, and returns 1 otherwise.
 */
int iDbmsPrint_all(void *ptrParameter)
{
    FILE *xFile;
    xFile = fopen("database.txt", "r");         // open the database file for reading.
    char *sTemp_str;                            // temp strings.
    char *sTemp_str2;
    char *sID, *sName;
    char *sPayment_amount, *sComplaint;
    char sLine[50];                             // buffer to read each line in it.

    printf("ID  | name          | amount | complaint          \n\n"); // for creating a table.
    while (fgets(sLine, 50, xFile) != NULL)
    { 
        /*
         * read each line in the database file into a string then trim it into substrings.
         * substrings(tokens) are ID, name, amount and complaint.
         */ 
        sTemp_str2 = sLine;
        sID = strtok_r(sTemp_str2, ",", &sTemp_str); // trim the string to its substrings(tokens).
        sName = strtok_r(sTemp_str, ",", &sTemp_str2);
        sPayment_amount = strtok_r(sTemp_str2, ",", &sTemp_str);
        sComplaint = strtok_r(sTemp_str, "\n", &sTemp_str2);
        // print the customer ID,name, amount and complaint to the console.
        if(atoi(sID))
            printf("%-4s|%-15s|%-8s|%-20s\n", sID, sName, sPayment_amount, sComplaint);
    }
    fclose(xFile);                               // close the file.
    return 0;
}

/****************************************************************
 *@brief this function delets the specified record from the database with its associated ID.
 *@param ptrParameter pointer to the record ID to be deleted from the database.
 *@return 0 on success and -1 on failure.
 */
int iDbmsDelet_record(void *ptrParameter)
{
    char sTemp_str3[50];
    char *sTemp_str2;
    char sLine[50];

    // Main file is the database file.
    FILE *xMain_f;
    if(!(xMain_f = fopen("database.txt", "r")))     
    {
        printf("error opening database file\n");
        return -1;
    }

    // Temp file is for writing the records except the record with the specified ID.
    FILE *xTemp_f;
    if(!(xTemp_f = fopen("temp.txt", "w")))
    {
        printf("error opening database file\n");
        return -1;
    }
    int iID;
    // if the ID parameter is passed, use it. otherwise ask the user for the ID number.
    if (ptrParameter != NULL) 
    {
        iID = *(int *)ptrParameter;
    }
    else
    {
        printf("enter ID num: ");
        scanf("%i", &iID);
    }
    while (fgets(sLine, 50, xMain_f) != NULL)       // traverse through  all the records.
    {
        strcpy(sTemp_str3, sLine);
        char *sID = strtok_r(sTemp_str3, ",", &sTemp_str2); // trim the string to its substrings(tokens).
        if (iID != atoi(sID))                       // if the ID doesn't matches with a record ID, copy it to temp file, otherwise delete the record.
        {
            fputs(sLine, xTemp_f);                  // write the record to the temp file.
        }
    }

    fclose(xMain_f);
    fclose(xTemp_f);

    // remover the old file and rename the temp file to be the new one.
    remove("database.txt");
    rename("temp.txt", "database.txt");
    return 0;
}

/********************************
 * @brief This function prints the payment of a customer with the given ID number.
 * @param ptrParameter a pointer to the customer ID number.
 * @return 0 on success and -1 on failure.
 *
 *******************************/
int iDbmsPrint_payment(void *ptrParameter)
{
    FILE *xFile;
    if(!(xFile = fopen("database.txt", "r")))       // open database file for reading.
    {
        printf("error opening database file\n");
        return -1;
    }
    char *sTemp_str;                                // Strings used as temporary strings.
    char *sTemp_str2;
    char *sID, *sName;
    char *amount_s, *complaint_s;
    char sLine[50];                                 // sLine is a buffer to store the records.
    int iID;
    if (ptrParameter != NULL)                       // if the ID parameter is passed, use it. otherwise ask the user for the ID number.
    {
        iID = *(int *)ptrParameter;                 //get customer ID number.
    }
    else
    {
        printf("enter ID num: ");
        scanf("%i", &iID);
    }
    // traverse the database records and print amount of payment
    while (fgets(sLine, 50, xFile) != NULL)
    {
        sTemp_str2 = sLine;
        sID = strtok_r(sTemp_str2, ",", &sTemp_str); // trim the string to its substrings(tokens).
        if (iID != atoi(sID))
        {
            continue;
        }
        sName = strtok_r(sTemp_str, ",", &sTemp_str2);
        amount_s = strtok_r(sTemp_str2, ",", &sTemp_str);
        complaint_s = strtok_r(sTemp_str, "\n", &sTemp_str2);
        break;
    }
    printf("the amount of payment is: %s\n", amount_s);
    fclose(xFile);
    return atoi(amount_s);
}

/********************************
 * @brief This function prints the name of a customer with the given ID number.
 * @param ptrParameter a pointer to the customer ID number.
 * @return 0 on success and -1 on failure.
 *
 */
int iDbmsPrint_name(void *ptrParameter)
{
    FILE *xFile;
    if(!(xFile = fopen("database.txt", "r")))          // open database file for reading.
    {
        printf("error opening database file\n");
        return -1;
    }
    char *sTemp_str;
    char *sTemp_str2;
    char *sID, *sName;
    char *sPayment_amount, *sComplaint;
    char sLine[50];
    int iID;
    if (ptrParameter != NULL)
    {
        iID = *(int *)ptrParameter;                    // get the customer ID.
    }
    else
    {
        printf("enter ID num: ");
        scanf("%i", &iID);
    }

    while (fgets(sLine, 50, xFile) != NULL)
    {
        sTemp_str2 = sLine;
        // printf("aaaa");
        sID = strtok_r(sTemp_str2, ",", &sTemp_str);     // trim the string to its substrings(tokens).
        if (iID != atoi(sID))
        {
            // skip over if it is not the customer ID.
            continue;       
        }
        sName = strtok_r(sTemp_str, ",", &sTemp_str2);
        sPayment_amount = strtok_r(sTemp_str2, ",", &sTemp_str);
        sComplaint = strtok_r(sTemp_str, "\n", &sTemp_str2);
        break;  
        // we are done, if it is the customer ID.
    }
    printf("the name is: %s\n", sName);
    fclose(xFile);
    return 0;
}

/********************************
 * @brief This function prints the complaint of a customer with the given ID number.
 * @param ptrParameter a pointer to the customer ID number.
 * @return 0 on success and -1 on failure.
 *
 */
int iDbmsPrint_complaint(void *ptrParameter)
{
    FILE *xFile;
    if(!(xFile = fopen("database.txt", "r")))           // open database file for reading.
    {
        printf("error opening database file\n");
        return -1;
    }
    char *sTemp_str;                                    // used as temporary strings.
    char *sTemp_str2;
    char *sID, *sName;
    char *sPayment_amount, *sComplaint;
    char sLine[50];                                     //sLine is a buffer for saving the records' lines
    int iID;
    if (ptrParameter != NULL){                          // if the ID parameter is passed use it, otherwise ask the user for the ID number.
        iID = *(int *)ptrParameter;
    }
    else{
        printf("enter ID num: ");
        scanf("%i", &iID);
    }
    while (fgets(sLine, 50, xFile) != NULL){
        sTemp_str2 = sLine;
        // printf("aaaa");
        sID = strtok_r(sTemp_str2, ",", &sTemp_str);   // trim the string to its substrings(tokens).
        if (iID != atoi(sID))
        {
            continue;
        }
        sName = strtok_r(sTemp_str, ",", &sTemp_str2);
        sPayment_amount = strtok_r(sTemp_str2, ",", &sTemp_str);
        sComplaint = strtok_r(sTemp_str, "\n", &sTemp_str2);
        break;
    }
    printf("the complaint is: %s\n", sComplaint);   // print out the complaint.
    fclose(xFile);
    return 0;
}

/****************************************************************
 * @brief Excute the requested function using its number.
 * @param ptrParameter a pointer to the number of the function.
 * @return non.
 */
static int run_task_choice(void *ptrParameter)
{
    int iFun_index = *(int *)ptrParameter;
    task_arr[iFun_index](NULL); // call the function with the needed function pointer.
}

/****************************************************************
 * @brief this function is called to tell the user the available functions and their number.
 * @param ptrParameter should be null.
 * @return a value of the function that represents the query index.
 */
static int print_menue(void *ptrParameter)
{
    printf("choose your order:\n");
    printf("(0) for print all records\n");
    printf("(1) for print name\n");
    printf("(2) for print a payment\n");
    printf("(3) for print a complaint\n");
    printf("(4) for deleting a record\n");
    printf("(5) for adding a new record\n");
    printf("(6) for editing IDs\n");
    printf("(7) for editing payments\n");
    printf("(8) for editing Names\n");
    printf("(9) for editing complaints\n");
    printf("(10) for help\n");
    
    

    //asks the user to select the index of the requested function.
    
    int iFun_index;    
    printf("query index: ");
    scanf("%i", &iFun_index);
    
    return iFun_index;
}

/****************************************************************
 * @brief this function edit customer ID.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success, -1 on failure.
 */
int iDbmsEdit_ID(void *ptrParameter)
{
    
    char sTemp_str3[50];
    char *sTemp_str2;
    char *sTemp_str;
    
    char sLine[50];

    char *sID;
    char *sComplaint;
    char *sPayment_amount;
    char *sName;

    char sComplaintarr[30];
    char sPayment_amountarr[30];
    char sNamearr[30];
    // Main file is the database file.
    FILE *xMain_f;
    if(!(xMain_f = fopen("database.txt", "r")))     
    {
        printf("error opening database file\n");
        return -1;
    }

    // Temp file is for writing the records except the record with the specified ID.
    FILE *xTemp_f;
    if(!(xTemp_f = fopen("temp.txt", "w")))
    {
        printf("error opening database file\n");
        return -1;
    }
    int iOld_ID;
    // if the ID parameter is passed, use it. otherwise ask the user for the ID number.
    if (ptrParameter != NULL) 
    {
        iOld_ID = *(int *)ptrParameter;
    }
    else
    {
        printf("enter ID num: ");
        scanf("%i", &iOld_ID);
    }
    while (fgets(sLine, 50, xMain_f) != NULL)       // traverse through  all the records.
    {
        strcpy(sTemp_str3, sLine);
        sID = strtok_r(sTemp_str3, ",", &sTemp_str2); // trim the string to its substrings(tokens).
        
        if (iOld_ID != atoi(sID))                       // if the ID doesn't matches with a record ID, copy it to temp file, otherwise delete the record.
        {
            fputs(sLine, xTemp_f);                  // write the record to the temp file.
        }
        else
        {
            sName = strtok_r(sTemp_str2, ",", &sTemp_str);
            strcpy(sNamearr, sName);
            sPayment_amount = strtok_r(sTemp_str, ",", &sTemp_str2);
            strcpy(sPayment_amountarr, sPayment_amount);  
            sComplaint = strtok_r(sTemp_str2, "\n", &sTemp_str);
            strcpy(sComplaintarr, sComplaint);
        }
    }
    int iNew_ID;
    printf("enter new ID num: ");
    scanf("%i", &iNew_ID);
    fprintf(xTemp_f, "%i,%s,%s,%s\n", iNew_ID, sNamearr,sPayment_amountarr,sComplaintarr);
        printf("customer saved successfully\n\n");
    fclose(xMain_f);
    fclose(xTemp_f);

    // remover the old file and rename the temp file to be the new one.
    remove("database.txt");
    rename("temp.txt", "database.txt");
    return 0;

}

/****************************************************************
 * @brief this function edit customer amount of payment.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success and 1 on failure.
 */
int iDbmsEdit_amount_payment(void *ptrParameter)
{
    
    char sTemp_str3[50];
    char *sTemp_str2;
    char *sTemp_str;
    
    char sLine[50];

    char *sID;
    char *sComplaint;
    char *sPayment_amount;
    char *sName;

    char sComplaintarr[30];
    char sPayment_amountarr[30];
    char sNamearr[30];

    // Main file is the database file.
    FILE *xMain_f;
    if(!(xMain_f = fopen("database.txt", "r")))     
    {
        printf("error opening database file\n");
        return -1;
    }

    // Temp file is for writing the records except the record with the specified ID.
    FILE *xTemp_f;
    if(!(xTemp_f = fopen("temp.txt", "w")))
    {
        printf("error opening database file\n");
        return -1;
    }
    int iID;
    // if the ID parameter is passed, use it. otherwise ask the user for the ID number.
    if (ptrParameter != NULL) 
    {
        iID = *(int *)ptrParameter;
    }
    else
    {
        printf("enter ID num: ");
        scanf("%i", &iID);
    }
    while (fgets(sLine, 50, xMain_f) != NULL)       // traverse through  all the records.
    {
        strcpy(sTemp_str3, sLine);
        sID = strtok_r(sTemp_str3, ",", &sTemp_str2); // trim the string to its substrings(tokens).
        
        if (iID != atoi(sID))                       // if the ID doesn't matches with a record ID, copy it to temp file, otherwise delete the record.
        {
            fputs(sLine, xTemp_f);                  // write the record to the temp file.
        }
        else
        {
            sName = strtok_r(sTemp_str2, ",", &sTemp_str);
            strcpy(sNamearr, sName);
            sPayment_amount = strtok_r(sTemp_str, ",", &sTemp_str2);
            strcpy(sPayment_amountarr, sPayment_amount);  
            sComplaint = strtok_r(sTemp_str2, "\n", &sTemp_str);
            strcpy(sComplaintarr, sComplaint);
        }
    }
    int iPayment_amount;
    printf("enter ID num: ");
    scanf("%i", &iPayment_amount);
    fprintf(xTemp_f, "%i,%s,%i,%s\n", iID, sNamearr, iPayment_amount, sComplaintarr);
        printf("customer saved successfully\n\n");
    fclose(xMain_f);
    fclose(xTemp_f);

    // remover the old file and rename the temp file to be the new one.
    remove("database.txt");
    rename("temp.txt", "database.txt");
    return 0;

}


/****************************************************************
 * @brief this function edit customer amount of payment.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success and 1 on failure.
 */
int iDbmsEdit_complaint(void *ptrParameter)
{
    
    char sTemp_str3[50];
    char *sTemp_str2;
    char *sTemp_str;
    
    char sLine[50];

    char *sID;
    char *sComplaint;
    char *sPayment_amount;
    char *sName;

    char sComplaintarr[30];
    char sPayment_amountarr[30];
    char sNamearr[30];

    // Main file is the database file.
    FILE *xMain_f;
    if(!(xMain_f = fopen("database.txt", "r")))     
    {
        printf("error opening database file\n");
        return -1;
    }

    // Temp file is for writing the records except the record with the specified ID.
    FILE *xTemp_f;
    if(!(xTemp_f = fopen("temp.txt", "w"))){
        printf("error opening database file\n");
        return -1;
    }
    int iID;
    // if the ID parameter is passed, use it. otherwise ask the user for the ID number.
    if (ptrParameter != NULL) {
        iID = *(int *)ptrParameter;
    }
    else{
        printf("enter ID num: ");
        scanf("%i", &iID);
    }

    while (fgets(sLine, 50, xMain_f) != NULL)       // traverse through  all the records.
    {
        strcpy(sTemp_str3, sLine);
        sID = strtok_r(sTemp_str3, ",", &sTemp_str2); // trim the string to its substrings(tokens).
    
        if (iID != atoi(sID))                       // if the ID doesn't matches with a record ID, copy it to temp file, otherwise delete the record.
        {
            fputs(sLine, xTemp_f);                  // write the record to the temp file.
        }
        else
        {
            sName = strtok_r(sTemp_str2, ",", &sTemp_str);
            strcpy(sNamearr, sName);
            sPayment_amount = strtok_r(sTemp_str, ",", &sTemp_str2);
            strcpy(sPayment_amountarr, sPayment_amount);  
            sComplaint = strtok_r(sTemp_str2, "\n", &sTemp_str);
            strcpy(sComplaintarr, sComplaint);
        }
    }
    char sNewComplaint[50];
    printf("enter new Complaint: ");
    gets(sNewComplaint);
    gets(sNewComplaint);
    fprintf(xTemp_f, "%i,%s,%s,%s\n", iID, sNamearr, sPayment_amountarr, sNewComplaint);
        printf("customer saved successfully\n\n");
    fclose(xMain_f);
    fclose(xTemp_f);

    // remover the old file and rename the temp file to be the new one.
    remove("database.txt");
    rename("temp.txt", "database.txt");
    return 0;

}


/****************************************************************
 * @brief this function edit customer amount of payment.
 * @param ptrParameter should be null or customer ID address.
 * @return 0 on success and 1 on failure.
 */
int iDbmsEdit_name(void *ptrParameter)
{
    
    char sTemp_str3[100];
    char *sTemp_str2;
    char *sTemp_str;
    char sLine[100];

    char *sID;
    char *sComplaint;
    char *sPayment_amount;
    char *sName;

    char sComplaintarr[30];
    char sPayment_amountarr[30];
    char sNamearr[30];
    
    // Main file is the database file.
    FILE *xMain_f;
    if(!(xMain_f = fopen("database.txt", "r")))     
    {
        printf("error opening database file\n");
        return -1;
    }

    // Temp file is for writing the records except the record with the specified ID.
    FILE *xTemp_f;
    if(!(xTemp_f = fopen("temp.txt", "w")))
    {
        printf("error opening database file\n");
        return -1;
    }
    int iID;
    // if the ID parameter is passed, use it. otherwise ask the user for the ID number.
    if (ptrParameter != NULL) 
    {
        iID = *(int *)ptrParameter;
    }
    else
    {
        printf("Enter ID num: ");
        scanf("%i", &iID);
    }
    while (fgets(sLine, 50, xMain_f) != NULL)       // traverse through  all the records.
    {
        strcpy(sTemp_str3, sLine);
        sID = strtok_r(sTemp_str3, ",", &sTemp_str2); // trim the string to its substrings(tokens).
        
        
        if (iID != atoi(sID))                       // if the ID doesn't matches with a record ID, copy it to temp file, otherwise delete the record.
        {
            fputs(sLine, xTemp_f);                  // write the record to the temp file.
        }
        else
        {
            sName = strtok_r(sTemp_str2, ",", &sTemp_str);
            strcpy(sNamearr, sName);
            sPayment_amount = strtok_r(sTemp_str, ",", &sTemp_str2);
            strcpy(sPayment_amountarr, sPayment_amount);  
            sComplaint = strtok_r(sTemp_str2, "\n", &sTemp_str);
            strcpy(sComplaintarr, sComplaint);
        }
        
    }
    char sNewName[30];
    printf("enter new name: ");
    
    gets(sNewName);
    gets(sNewName);
    fprintf(xTemp_f, "%i,%s,%s,%s\n", iID, sNewName, sPayment_amountarr, sComplaintarr);
        printf("customer saved successfully\n\n");
    fclose(xMain_f);
    fclose(xTemp_f);

    // remover the old file and rename the temp file to be the new one.
    remove("database.txt");
    rename("temp.txt", "database.txt");
    return 0;

}
