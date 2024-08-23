#include "../../Libraries/Libraries.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
    uint8_t LocalName[25] = {0};
    printf("\nPlease enter the card holder name (20-24 characters): ");

    fgets(LocalName, 25, stdin);
    //to prevent the buffer overflow
    uint8_t length = strlen(LocalName);

    if (length > 0 && LocalName[length - 1] == '\n') {
            LocalName[length - 1] = '\0';
            length--;
        }

    if (length < 20 || length > 24) {
        return WRONG_NAME;
    }else
    {
        strcpy(cardData->CardHolderName,LocalName);
    }

    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8_t LocalExpirationDate[6] = {0};

    printf("\nPlease enter the card expiry date (MM/YY): ");
    fgets(LocalExpirationDate, 6, stdin);

    uint16_t length = strlen(LocalExpirationDate);
    if (length > 0 && LocalExpirationDate[length - 1] == '\n')
    {
        LocalExpirationDate[length - 1] = '\0';
        length--;
    }
    if (length != 5 || (LocalExpirationDate[2] != '/'))
    {
        return WRONG_EXP_DATE;
    }
    else
    {
        strcpy(cardData->cardExpirationDate, LocalExpirationDate);
    }
    int month = (cardData->cardExpirationDate[0] - '0') * 10 +  (cardData->cardExpirationDate[1] - '0');
    if(month< 1 || month >12)
    {
        return WRONG_EXP_DATE;
    }
    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    uint8_t LocalCardPAN[20] = {0};
    printf("\n Enter the card primary account number: ");
    fgets(LocalCardPAN, 20, stdin);
    uint8_t length = strlen(LocalCardPAN);

    if((NULL == LocalCardPAN) || (length < 16) || (length > 20))
    {
        return WRONG_PAN;
    }
    else
    {

        strcpy(cardData->primaryAccountNumber, LocalCardPAN);
    }
    return CARD_OK;
}
