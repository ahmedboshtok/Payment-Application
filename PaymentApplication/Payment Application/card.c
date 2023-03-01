#include<stdio.h>
#include<string.h>
#include "card.h"


cardData_t *card_Data;

cardError_t getCardHolderName(cardData_t *cardData){
   cardError_t Local_enuCardError;

    char C_HoldName [100];
    uint32_t counter;
    for (counter =0; counter<100;counter++){
        C_HoldName[counter]='\0';
    }
    printf("Please enter your card holder name [20-24 characters]: ");
    scanf("%[^\n]s", C_HoldName);
    if (C_HoldName[19]=='\0' || C_HoldName[24]!= '\0'){
        return WRONG_NAME;
    }
    else if (C_HoldName == NULL){
        return WRONG_NAME;
    }
    else{
    for(counter =0;counter<25;counter++){
		cardData->cardHolderName[counter] = C_HoldName[counter];
	}

	Local_enuCardError = CARD_OK;
    }

    return Local_enuCardError;

}



void getCardHolderNameTest(void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: getCardHolderName.\n");
    cardError_t testC_H_N = getCardHolderName(&card_Data);
    switch(testC_H_N){
        case WRONG_NAME:
            printf("Expected Result: CARD_OK\n");
            printf("Actual Result: WRONG_NAME\n");
            printf("*****************************\n");
            break;
        case CARD_OK:
            printf("Expected Result: CARD_OK\n");
            printf("Actual Result: CARD_OK\n");
            printf("*****************************\n");
            break;
        default:
            printf("Unexpected Result.");
            printf("*****************************\n");
    }
}

/*********************************************************/


cardError_t getCardExpiryDate(cardData_t *cardData){
    cardError_t Local_enuCardError ;
    uint32_t counter;
    char CardExp[6];


    printf("Please Enter expiry data [mm/yy] ");
    scanf("%s", CardExp);//EX:01/24

    if (sizeof(CardExp)!=5){
        Local_enuCardError = WRONG_EXP_DATE;
    }
    for (counter =0;counter <6;counter++){
        if ((CardExp[counter] < '0' || CardExp[counter] >'9')  &&counter!=2 &&counter!=5){
            Local_enuCardError = WRONG_EXP_DATE;
        }
    }
    if ( (  (CardExp[0]-'0')*10) + (CardExp[1]-'0')<=31 && CardExp[2]=='/'){
         for (counter =0; counter < 6 ;counter++)
           {
            cardData->cardExpirationDate[counter]=CardExp[counter];
           }
           Local_enuCardError= CARD_OK;
        }
    return Local_enuCardError;

}
void getCardExpiryDateTest (void){
    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: getCardExpiryDate.\n");

    cardError_t testC_E_D = getCardExpiryDate(&card_Data);
    switch(testC_E_D){
    case WRONG_EXP_DATE:
        printf("Expected Result: CARD_OK\n");
        printf("Actual Result: WRONGE_EXP_DATE\n");
        printf("*****************************\n");
        break;
    case CARD_OK:
        printf("Expected Result: CARD_OK\n");
        printf("Actual Result: CARD_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
        printf("*****************************");
    }
    }
/**********************************************/


cardError_t getCardPAN(cardData_t *cardData){

    uint8_t  PAN[20];
    uint32_t counter;
    printf("Please Enter PAN : ");
    scanf("%s", PAN);
     for (counter=0; counter <sizeof(PAN);counter++){
        if (PAN[counter]>'9' || PAN[counter]<'0'){
            if(PAN[counter] == '\0'){
                continue;
            }
        else{
            return WRONG_PAN;
            }
        }
    }
    if (sizeof(PAN)<16 || sizeof(PAN)>20){
        return WRONG_PAN;
    }
    else {
        for (counter=0; counter <20;counter++){
            cardData->primaryAccountNumber[counter]=PAN[counter];
        }
        return CARD_OK;
    }

}
void getCardPANTest (void){

    printf("Tester Name: Ahmed Mahmoud,\n");
    printf("Function Name: getCardPAN.\n");

    cardError_t testCPIN = getCardPAN(&card_Data);
    switch(testCPIN){
    case WRONG_PAN:
        printf("Expected Result: CARD_OK\n");
        printf("Actual Result: WRONGE_PAN\n");
        printf("*****************************\n");
        break;
    case CARD_OK:
        printf("Expected Result: CARD_OK\n");
        printf("Actual Result: CARD_OK\n");
        printf("*****************************\n");
        break;
    default:
        printf("Unexpected Result.");
    }
    }
    /*****************************************/


