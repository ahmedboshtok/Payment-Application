#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED


#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25];
     uint8_t primaryAccountNumber[20];
     uint8_t cardExpirationDate[6];
}cardData_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}cardError_t;

cardError_t getCardHolderName(cardData_t *cardData);
cardError_t getCardExpiryDate(cardData_t *cardData);
cardError_t getCardPAN(cardData_t *cardData);
/********************************************/
void getCardHolderNameTest(void);
void getCardExpiryDateTest (void);
void getCardPANTest (void);

#endif // CARD_H_INCLUDED
