#include "../../Libraries/Libraries.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
    printf("Please enter the cardholder name (20-24 characters): ");
    fgets((char *)cardData->cardHolderName, 25, stdin);

    size_t length = strlen((char *)cardData->cardHolderName);
    if (length > 0 && cardData->cardHolderName[length - 1] == '\n') {
        cardData->cardHolderName[length - 1] = '\0';
        length--;
    }

    if (length < 20 || length > 24) {
        return WRONG_NAME;
    }

    for (size_t i = 0; i < length; i++) {
        if (!isalpha(cardData->cardHolderName[i]) && cardData->cardHolderName[i] != ' ') {
            return WRONG_NAME;
        }
    }

    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    printf("Please enter the card expiry date (MM/YY): ");
    fgets((char *)cardData->cardExpirationDate, 6, stdin);

    size_t length = strlen((char *)cardData->cardExpirationDate);
    if (length > 0 && cardData->cardExpirationDate[length - 1] == '\n') {
        cardData->cardExpirationDate[length - 1] = '\0';
        length--;
    }

    if (length != 5 ) {
        return WRONG_EXP_DATE;
    }

    if (!isdigit(cardData->cardExpirationDate[0]) || !isdigit(cardData->cardExpirationDate[1]) ||
        cardData->cardExpirationDate[2] != '/' ||
        !isdigit(cardData->cardExpirationDate[3]) || !isdigit(cardData->cardExpirationDate[4])) {
        return WRONG_EXP_DATE;
    }

    int month = (cardData->cardExpirationDate[0] - '0') * 10 +  (cardData->cardExpirationDate[1] - '0');
    if(month< 1 || month >12){
        return WRONG_EXP_DATE;
    }
    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){

}
