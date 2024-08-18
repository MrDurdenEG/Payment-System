#include "Libraries/Libraries.h"
int main() {
    ST_cardData_t cardData;
    EN_cardError_t result = getCardHolderName(&cardData);

    if (result == CARD_OK) {
        printf("cardHolder Name: %s\n", cardData.cardHolderName);
    } else {
        printf("Error: Invalid cardHolder name.\n");
    }

    result = getCardExpiryDate(&cardData);

    if (result == CARD_OK) {
        printf("Card Expiry Date: %s\n", cardData.cardExpirationDate);
    } else {
        printf("Error: Invalid card expiry date.\n");
    }

    return 0;
}
