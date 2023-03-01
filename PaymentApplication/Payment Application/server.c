
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Server.h"


extern cardData_t *card_Data;
extern ST_terminalData_t *term_Data;
ST_transaction *trans_Data;


int ind = -1;

int transactions_index = 0;

EN_transStat_t transstat;


ST_transaction transaction [255] = {0};

ST_transaction * transaction_ref ;

ST_accountsDB_t accountsDB[255]= {  {4500.0, RUNNING, "123456789012345678"},
									{5000.0, BLOCKED, "876543210987654321"},
									{6000.0, BLOCKED, "098765432112345678"},
									{7000.0, RUNNING, "098765432187654321"},
									{7500.0, BLOCKED, "123456789087654321"},
									{8000.0, RUNNING, "876543211234567890"},
									{1000.0, RUNNING, "123456781234567890"},
									{500.0 , RUNNING, "123456780987654321"}};
ST_accountsDB_t *accptr =&accountsDB;


EN_transStat_t recieveTransactionData(cardData_t *cardData,ST_terminalData_t *termData,ST_transaction *transData){
    EN_transStat_t Local_enuServerError ;


    EN_serverError_t is_Valid = isValidAccount(cardData,&accountsDB);
    EN_serverError_t isBlocked= isBlockedAccount(&accountsDB);
	EN_serverError_t isAmount_Availabil = isAmountAvailable(termData, &accountsDB);


	if (is_Valid == ACCOUNT_NOT_FOUND){
		transstat = FRAUD_CARD;

		Local_enuServerError= FRAUD_CARD;
	}
	else if(isBlocked == BLOCKED_ACCOUNT){
		transstat = DECLINED_STOLEN_CARD;

		Local_enuServerError = DECLINED_STOLEN_CARD;



	}
	else if (isAmount_Availabil == LOW_BALANCE){
		transstat = DECLINED_INSUFFECIENT_FUND;
		Local_enuServerError = DECLINED_INSUFFECIENT_FUND;
	}

	else {
		transstat = APPROVED;
		Local_enuServerError = APPROVED;

		//(accountsDB+ind)->balance -= transData->terminalData.transAmount;
        saveTransaction(transData);
	}

    return Local_enuServerError;
}
void recieveTransactionDataTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: recieveTransactionData.\n");

    EN_serverError_t testrecive = recieveTransactionData(&card_Data,&term_Data,&trans_Data);
    switch(testrecive){
    case SERVER_OK:
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: SERVER_OK\n");
        printf("*****************************\n");
        break;
    case FRAUD_CARD :
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: FRAUD_CARD \n");
        printf("*****************************\n");
        break;
    case DECLINED_INSUFFECIENT_FUND :
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: DECLINED_INSUFFECIENT_FUND \n");
        printf("*****************************\n");
        break;
    case DECLINED_STOLEN_CARD :
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: DECLINED_STOLEN_CARD \n");
        printf("*****************************\n");
        break;

    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }

}
/***************************************************/


EN_serverError_t isValidAccount(cardData_t* cardData, ST_accountsDB_t* accountRefrence){
    accountRefrence = &accountsDB;
    int counter;
    uint32_t found= 1,PAN_com;


    if (cardData->primaryAccountNumber== NULL){
            return ACCOUNT_NOT_FOUND;
    }
    for (counter = 0; counter<8;counter++){
            PAN_com = strcmp(cardData->primaryAccountNumber , accountRefrence[counter].primaryAccountNumber);
            if (PAN_com == 0){
                found =0;
                ind = counter;
                printf("%d",ind);
                break;
            }
    }
    if (found==0){
        strcmp(transaction->cardHolderData.primaryAccountNumber,cardData->primaryAccountNumber);
        return SERVER_OK;
    }
    else {

            return ACCOUNT_NOT_FOUND;
    }
}
/*
EN_serverError_t isValidAccount(cardData_t *cardData, ST_accountsDB_t *accountRefrence){

	uint32_t Counter;
	EN_serverError_t LocalServerError = SERVER_OK;
	printf("cardData->primaryAccountNumber: %s",cardData->primaryAccountNumber);

	for(Counter=0;Counter<=8;Counter++) {
		if ( (strcmp(cardData->primaryAccountNumber , accountRefrence[Counter].primaryAccountNumber)) == 0)
		{
			accountRefrence= accountsDB;
            LocalServerError = SERVER_OK;
            break;
		}
		else {
			accountRefrence = NULL;
			LocalServerError = ACCOUNT_NOT_FOUND;
		}
		return LocalServerError;
	}
}*/
/**************************************************8*/

void isValidAccountTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: isValidAccount.\n");
    ST_accountsDB_t accoauntsDB;

    EN_serverError_t testValidAcount = isValidAccount(&card_Data,&accoauntsDB);
    switch(testValidAcount){
    case SERVER_OK:
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: SERVER_OK\n");
        printf("*****************************\n");
        break;
    case ACCOUNT_NOT_FOUND :
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: ACCOUNT_NOT_FOUND \n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }
}
/*****************************************************************/

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence){
    accountRefrence = &accountsDB;



    if ((accountRefrence+ind)->state == BLOCKED ){
        return BLOCKED_ACCOUNT;
    }
    else {

        return SERVER_OK;
    }

}
void isBlockedAccountTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: isBlockedAccount.\n");

    EN_serverError_t testBlockAcount = isBlockedAccount(&accountsDB);
    switch(testBlockAcount){
    case SERVER_OK:
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: SERVER_OK\n");
        printf("*****************************\n");
        break;
    case BLOCKED_ACCOUNT :
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: BLOCKED_ACCOUNT \n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }


}
/*********************************/



EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t* accountRefrence){

    accountRefrence = &accountsDB;


    if ((accountRefrence+ind)->balance < termData->transAmount){
        return LOW_BALANCE;
    }
    else {
        transaction->terminalData.transAmount = termData->transAmount;
        return SERVER_OK;
    }

}
void isAmountAvailableTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: isAmountAvailable.\n");

    EN_serverError_t testAm_Ava = isAmountAvailable(&term_Data,&accountsDB);
    switch(testAm_Ava){
    case SERVER_OK:
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: SERVER_OK\n");
        printf("*****************************\n");
        break;
    case LOW_BALANCE :
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: LOW_BALANCE \n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }

}
/*********************************************/

/*
EN_serverError_t saveTransaction(cardData_t *cardData,ST_terminalData_t *termData,ST_transaction *transData){
	transData->transactionSequenceNumber +=  transactions_index ;


    printf("please enter your name: ");
    scanf("%s",transData->cardHolderData.cardHolderName);


    printf("please enter EXP date: ");
    scanf("%s",transData->cardHolderData.cardExpirationDate);



    printf("please enter PAN: ");
    scanf("%s",transData->cardHolderData.primaryAccountNumber);



    printf("please enter TransAmount: ");
    scanf("%f",transData->terminalData.transAmount);
    printf("%f\n",transData->terminalData.transAmount);


    transData->terminalData.maxTransAmount = 10000;

    time_t t;
    uint32_t day,mon,year,counter;
    t = time(NULL);// returns the current calendar time (seconds since Jan 1, 1970)
    struct tm tm= *localtime(&t);
    day = tm.tm_mday;
    mon = tm.tm_mon+1;
    year = tm.tm_year+1900;
    transData->terminalData.transactionDate[0] = day/10 +'0';
    transData->terminalData.transactionDate[1] = day%10 +'0';
    transData->terminalData.transactionDate[2] = '/';
    transData->terminalData.transactionDate[3] = mon/10+'0';
    transData->terminalData.transactionDate[4] = mon%10 +'0';
    transData->terminalData.transactionDate[5] = '/';
    transData->terminalData.transactionDate[6] = year /1000 +'0';
    transData->terminalData.transactionDate[7] = (year/100) %10 +'0';
    transData->terminalData.transactionDate[8] = (year/10) %10 +'0';
    transData->terminalData.transactionDate[9] = year%10+'0';
    transData->terminalData.transactionDate[10] = '\0';

    if (transstat== APPROVED){
        return SERVER_OK;
    }
    else if(transstat ==FRAUD_CARD ){
        return SAVING_FAILED;
}
 else if(transstat ==DECLINED_INSUFFECIENT_FUND ){
        return SAVING_FAILED;
}
else if(transstat == DECLINED_STOLEN_CARD){
    return SAVING_FAILED;
}


    if (transaction->transactionSequenceNumber >255){
        return SAVING_FAILED;
    }
    else{
        transaction[transData->transactionSequenceNumber].cardHolderData= transData->cardHolderData;
        transaction[transData->transactionSequenceNumber].terminalData= transData->terminalData;
        transaction[transData->transactionSequenceNumber].transactionSequenceNumber= transData->transactionSequenceNumber;
        transactions_index++;
        return SERVER_OK;

    }





    //    transaction_ref->cardHolderData.cardHolderName = transData->cardHolderData.cardExpirationDate;

    printf("a%f\n",term_Data->transAmount);
    if(transData->transactionSequenceNumber>255){
        return SAVING_FAILED;
    }
    else{
        transaction[transData->transactionSequenceNumber].cardHolderData= transData->cardHolderData;
        transaction[transData->transactionSequenceNumber].terminalData= transData->terminalData;
        transaction[transData->transactionSequenceNumber].transactionSequenceNumber= transData->transactionSequenceNumber;
        transactions_index++;
        return SERVER_OK;



    }

	//strcpy(transData->cardHolderData.cardHolderName,card_Data->cardHolderName );
	strcpy(transData->cardHolderData.cardExpirationDate, card_Data->cardExpirationDate);
	strcpy(transData->cardHolderData.primaryAccountNumber, card_Data->primaryAccountNumber);
	strcpy(transData->terminalData.transactionDate, term_Data->transactionDate);


	transData->transState = transstat;
	transData->terminalData.transAmount = term_Data->transAmount;
	transData->terminalData.maxTransAmount = term_Data->maxTransAmount;
	transData->transactionSequenceNumber = 1+transactions_index;


    transactions_index++;
    listSavedTransactions(&trans_Data);




    //listSavedTransactions();

    return SERVER_OK;



}*/

EN_serverError_t saveTransaction(ST_transaction *transData){


	if (transactions_index > 255){
		return SAVING_FAILED;
		//		printf("Saving failed");
	}
	else {
		transaction[transactions_index].cardHolderData = transData->cardHolderData;
		transaction[transactions_index].terminalData = transData->terminalData;
		transaction[transactions_index].transState = transData->transState;
		transaction[transactions_index].transactionSequenceNumber = transData->transactionSequenceNumber;
        transactions_index++;

        printf("Saving Ok");

		return SERVER_OK;
	}

}

void saveTransactionTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: saveTransactionTest.\n");

    EN_serverError_t testsaveTrans = saveTransaction(&trans_Data);
    if(testsaveTrans== SERVER_OK){
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: SERVER_OK\n");
        printf("*****************************\n");

    }
    else{
        printf("Expected Result: SERVER_OK\n");
        printf("Actual Result: SAVE_FAILD\n");
        printf("*****************************\n");

    }


}
/**********************************************/





EN_serverError_t listSavedTransactions(cardData_t *cardData,ST_terminalData_t *termData,ST_transaction *transData){


	printf("Transaction sequence number is :%d\n", transactions_index);
	printf("Transaction date is : %s\n",termData->transactionDate);
	printf("transaction amounts : %f\n",termData->transAmount);
	transData->transState =transstat;
	if (transData->transState== APPROVED){

		printf("Transaction Approved.\n");
		float balance =(accountsDB+ind)->balance -= termData->transAmount ;
        printf("Your New Balance is: %f\n", balance );




	}
	else if (transData->transState== DECLINED_STOLEN_CARD){
		printf("Transaction Declined, Blocked Account\n");



	}
	else if (transData->transState== DECLINED_INSUFFECIENT_FUND){
			printf("Transaction Declined, Insufficient Fund\n");


		}
	else if (transData->transState== FRAUD_CARD){
			printf("Transaction Declined, Fraud Card\n");


		}

	printf("Card Holder Name is: %s\n", cardData->cardHolderName);
	printf("PAN is: %s\n", cardData->primaryAccountNumber);
	printf("Card Expiration Date is : %s\n", cardData->cardExpirationDate);
   return SERVER_OK;


}
/*
void listSavedTransactionsTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: listSavedTransactions.\n");

    EN_serverError_t testLsaveTrans = listSavedTransactions(&transaction);
    switch(testLsaveTrans){
    case APPROVED:
        printf("Expected Result: APPROVED\n");
        printf("Actual Result: APPROVED\n");
        printf("*****************************\n");
        break;
    case SAVING_FAILED :
        printf("Expected Result: APPROVED\n");
        printf("Actual Result: SAVING_FAILED \n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }


}


*/
