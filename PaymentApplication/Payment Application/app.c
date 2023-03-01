#include <stdio.h>
#include <stdlib.h>
#include"app.h"
/*
void main (){
	int flag =1;
	do{
		printf("Welcome to Payment Application\n");

		appStart();
		char state;
		printf("do you want to continue ? (y,n)");
		scanf("%c ", &state);
		if (state == 'y'){
			flag =1;

		}
		else if (state == 'n')

		{
			flag = 0;
		}
		else {
			printf("you enter invalid value !!");


		}

	}while (flag);
}
*/



cardData_t cardData;
ST_terminalData_t termData;
ST_transaction transData;
//extern ST_transaction transaction [255] = {0};

void appStart(void){



		printf("Welcome to Payment Application\n\n");

        cardError_t testC_H_N = getCardHolderName(&cardData);
		if (testC_H_N != CARD_OK) {
		    printf("Wrong Name.\n");
            return;

		}
        cardError_t readPIN = getCardPAN(&cardData);
		if (readPIN != CARD_OK) {
		    printf("Wrong PAN.\n");
            return;

		}
        cardError_t readEXP = getCardExpiryDate(&cardData);
		if (readEXP != CARD_OK) {
		    printf("Wrong EXP.\n");
            return;

		}
		printf("Holder Name: %s\nExpiry date: %s\nPrimary Account Number: %s\n",
		cardData.cardHolderName,
		cardData.cardExpirationDate,
		cardData.primaryAccountNumber);

		EN_terminalError_t readTransDate= getTransactionDate(&termData);
        if (readTransDate != TERMINAL_OK) {
		    printf("Transaction Date is Wrong.\n");
            return;

		}
		EN_terminalError_t readCardEXP=isCardExpired(&cardData, &termData);
		if (readCardEXP != TERMINAL_OK) {
		    printf("Your Card is Expired.\n");
            return;

		}
		ST_accountsDB_t *accountsdbb;
		EN_serverError_t readIsValid=isValidAccount(&cardData, &accountsdbb);
		if (readIsValid != SERVER_OK) {
		    printf("Account Not Found.\n");
            return;

		}

		EN_serverError_t readIsBlocked=isBlockedAccount(&accountsdbb);

		if (readIsBlocked != SERVER_OK) {
		    printf("Account is Blocked.\n");
            return;

		}
        EN_terminalError_t readTransAmount= getTransactionAmount(&termData);
		if (readTransAmount != TERMINAL_OK) {
		    printf("INVALID AMOUNT.\n");
            return;

		}

        EN_terminalError_t readMAX = setMaxAmount(&termData, 10000);
        if (readMAX != TERMINAL_OK) {
		    printf("INVALID MAX AMOUNT.\n");
            return;

		}

		EN_terminalError_t checkBelMAx =isBelowMaxAmount(&termData);
		if (checkBelMAx != SERVER_OK) {
		    printf("EXCEED MAX AMOUNT.\n");
            return;
		}

		EN_serverError_t checkAm_Ava = isAmountAvailable(&termData,&accountsdbb);
		if (checkAm_Ava != SERVER_OK) {
		    printf("Amount Not Available\n");
            return;
		}
		EN_transStat_t transState = recieveTransactionData(&cardData,&termData,&transData);
        if(transState == DECLINED_STOLEN_CARD){
            printf("DECLINED STOLEN CARD! \n");

        }
        else if(transState == DECLINED_INSUFFECIENT_FUND){
            printf("DECLINED_INSUFFECIENT_FUND! \n");

        }
        else if(transState == APPROVED){
            printf("APPROVED\n");

        }/*
        EN_serverError_t SaveTrans = saveTransaction(&transData);
        if (SaveTrans !=SERVER_OK){
            printf("Failed to save.\n");
        }
        listSavedTransactions(&transData);*/
       listSavedTransactions(&cardData, &termData,&transData);




	}


    /*
    getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();

    getTransactionDateTest();
    isCardExpriedTest();

    isValidAccountTest();
    isBlockedAccountTest();

    getTransactionAmountTest();
    setMaxAmountTest();
    isBelowMaxAmountTest();


   isAmountAvailableTest();
   recieveTransactionDataTest();
    EN_serverError_t ST = saveTransactionTest();
    EN_serverError_t LST = listSavedTransactionsTest();

    */

    /*
    cardError_t readName = getCardHolderName(&cardData);
    while (readName == WRONG_NAME){
        printf("WRONGE NAME ,Please try again,\n");
         readName = getCardHolderName(&cardData);

    }*/


   /* do{
    card_Error_t readName =getCardHolderName(&cardData);
    if (readName == WRONG_NAME){
        printf("WRONGE NAME "\n");
    }
    else {
        printf("Welcom Mr: %S\n",cardData->cardHolderName)

    }while (readName == WRONG_NAME);


    cardError_t readEXP = getCardExpiryDate(&cardData);
    while (readEXP == WRONG_EXP_DATE){
        printf("WRONG EXP DATE ,Please try again,\n");
         readEXP = getCardExpiryDate(&cardData);

    }

    cardError_t readPIN = getCardPAN(&cardData);
    while (readPIN == WRONG_PAN){
        printf("WRONG PAN ,Please try again,\n");
         readPIN = getCardPAN(&cardData);

    }

   EN_terminalError_t readMAX= setMaxAmount(&termData, 5000);
   while (readMAX==INVALID_MAX_AMOUNT){
        printf("Invalid Amount! ,Please try again.\n");
         readMAX= setMaxAmount(&termData, 5000);


   }


    EN_terminalError_t readTransDate= getTransactionDate(&termData);
   while (readTransDate==WRONG_DATE){
        printf("WRONG DATE! ,Please try again.\n");
        readTransDate= getTransactionDate(&termData);
   }

    EN_terminalError_t readCardEXP=isCardExpired(&cardData, &termData);
   if (readCardEXP==EXPIRED_CARD){
        printf("EXPIRED CARD! ,Please try again.\n");
        return;

   }



     EN_terminalError_t readTransAmount= getTransactionAmount(&termData);
   while (readTransAmount==INVALID_AMOUNT){
        printf("INVALID_AMOUNT! ,Please try again.\n");
        readTransAmount= getTransactionAmount(&termData);
   }
   EN_terminalError_t checkBelMAx =isBelowMaxAmount(&termData);
   if(checkBelMAx == EXCEED_MAX_AMOUNT){
    printf("EXCEED MAX AMOUNT! ,Please try again.\n");
     return;

   }

    transData.cardHolderData = cardData;
	transData.terminalData = termData;


    EN_transStat_t transState = recieveTransactionData(&transData);
    if(transState == DECLINED_STOLEN_CARD){
        printf("DECLINED STOLEN CARD! \n");

    }
    else if(transState == DECLINED_INSUFFECIENT_FUND){
        printf("DECLINED_INSUFFECIENT_FUND! \n");

    }
    else if(transState == APPROVED){
        printf("APPROVED\n");
        saveTransaction(&transData);

    }*/




