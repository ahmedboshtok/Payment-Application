#include<time.h>
#include "terminal.h"

#define MAXAMOUNT   10000


ST_terminalData_t *term_Data;
extern cardData_t *card_Data;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){

    time_t t;
    uint32_t day,mon,year,counter;
    printf("Getting Date From System... \n");
    t = time(NULL);// returns the current calendar time (seconds since Jan 1, 1970)

    struct tm tm= *localtime(&t);
    day = tm.tm_mday;
    mon = tm.tm_mon+1;
    year = tm.tm_year+1900;
    termData->transactionDate[0] = day/10 +'0';
    termData->transactionDate[1] = day%10 +'0';
    termData->transactionDate[2] = '/';
    termData->transactionDate[3] = mon/10+'0';
    termData->transactionDate[4] = mon%10 +'0';
    termData->transactionDate[5] = '/';
    termData->transactionDate[6] = year /1000 +'0';
    termData->transactionDate[7] = (year/100) %10 +'0';
    termData->transactionDate[8] = (year/10) %10 +'0';
    termData->transactionDate[9] = year%10+'0';
    termData->transactionDate[10] = '\0';

    printf("Transaction Date is: %s\n",termData->transactionDate);


    for (counter =0;counter <10;counter++){
        if ((termData->transactionDate[counter] < '0' || termData->transactionDate[counter] >'9') &&counter!=2 &&counter!=5){
            return WRONG_DATE;
        }

    }

     if (sizeof(termData->transactionDate)-1!=10){
           return WRONG_DATE;
    }
    else{
        return TERMINAL_OK;
    }



}

void getTransactionDateTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: getTransactionDate.\n");
    EN_terminalError_t testTransDate = getTransactionDate(&term_Data);
    switch(testTransDate){
    case WRONG_DATE:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: WRONG_DATE\n");
        printf("*****************************\n");
        break;
    case TERMINAL_OK:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: TERMINAL_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }
}
/*******************************************************************/

EN_terminalError_t isCardExpired(cardData_t *cardData, ST_terminalData_t *termData){
    EN_terminalError_t Local_enuTerminalError;

    uint32_t Card_mon = ((cardData->cardExpirationDate[0]  -  '0') * 10) + (cardData->cardExpirationDate[1]-'0');
    uint32_t Card_year = (cardData->cardExpirationDate[3]  -  '0') * 10 + cardData->cardExpirationDate[4] - '0'+2000;//to get mm/20yy
    uint32_t Terminal_mon = (termData->transactionDate[3]  -  '0') * 10 + termData->transactionDate[4] - '0';
    uint32_t Terminal_year = (termData->transactionDate[6] - '0' ) * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10 +termData->transactionDate[9] - '0';
    printf("System Date is : %d/%d\n",Terminal_mon,Terminal_year);

    if (Terminal_year >Card_year){
            Local_enuTerminalError= EXPIRED_CARD;

    }
    else if (Terminal_year == Card_year && Terminal_mon > Card_mon){
            Local_enuTerminalError= EXPIRED_CARD;

    }
    else {

        Local_enuTerminalError= TERMINAL_OK;
    }
    return Local_enuTerminalError;


}

void isCardExpriedTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: isCardExpried.\n");

    EN_terminalError_t testC_EXp = isCardExpired(&card_Data,&term_Data);
    switch(testC_EXp){
    case EXPIRED_CARD:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: EXPIRED_CARD\n");
        printf("*****************************\n");
        break;
    case TERMINAL_OK:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: TERMINAL_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }

}
/***************************************************/

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float amount;
    int x;
    printf("Please enter transaction amount : ");
    x=scanf("%f", &amount );
    if (x!=1){
        return INVALID_AMOUNT;
    }

    if (amount <=  0)
    {

        return INVALID_AMOUNT;
    }

    else {
        termData->transAmount= amount;
        return TERMINAL_OK;
    }

}

void getTransactionAmountTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: getTransactionAmount.\n");

    EN_terminalError_t testTransAm = getTransactionAmount(&term_Data);
    switch(testTransAm){
    case INVALID_AMOUNT:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: INVALID_AMOUNT\n");
        printf("*****************************\n");
        break;
    case TERMINAL_OK:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: TERMINAL_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }
}

/***********************************************/

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
    EN_terminalError_t localerrorState ;
    //I will set Max a mount as a constant
    printf("Maximum amount for transaction is: :%f\n",maxAmount);
    if (maxAmount <= 0){


       localerrorState =INVALID_MAX_AMOUNT;
    }
    else {
        termData->maxTransAmount = maxAmount;
        localerrorState= TERMINAL_OK;
    }
    return localerrorState;


}
void setMaxAmountTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: setMaxAmount.\n");

    EN_terminalError_t testMaxAm = setMaxAmount(&term_Data,MAXAMOUNT);
    switch(testMaxAm){
    case INVALID_MAX_AMOUNT:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: INVALID_MAX_AMOUNT\n");
        printf("*****************************\n");
        break;
    case TERMINAL_OK:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: TERMINAL_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
    }
}
/*********************************************************/


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if (termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }
    else {
        return TERMINAL_OK;
    }
}
void isBelowMaxAmountTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: isBelowMaxAmount.\n");

    EN_terminalError_t testMaxAm = isBelowMaxAmount(&term_Data);
    switch(testMaxAm){
    case EXCEED_MAX_AMOUNT:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: EXCEED_MAX_AMOUNT\n");
        printf("*****************************\n");
        break;
    case TERMINAL_OK:
        printf("Expected Result: TERMINAL_OK\n");
        printf("Actual Result: TERMINAL_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************\n");
    }

}
/********************************************************/

