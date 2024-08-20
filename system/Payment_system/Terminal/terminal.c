#include "../../Libraries/Libraries.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    uint8_t LocalTransDate[11]={0};
    printf("\n Enter the transaction date: ");
    fgets(LocalTransDate,11,stdin);
    if( (NULL == LocalTransDate) || (LocalTransDate != 10) || (LocalTransDate[2] != '/' || LocalTransDate[5] != '/') ){
        return WRONG_DATE;
    }else{
        strcpy(termData->transactionDate ,LocalTransDate);
    }
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){

  uint8_t ExpMonth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
  uint8_t TransMonth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
  uint8_t ExpYear  = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');
  uint8_t TransYear  = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');
  if(ExpYear<TransYear){
    return EXPIRED_CARD;
  }else if((ExpYear==TransYear) || (ExpYear>TransYear)){
      if((ExpMonth<TransMonth) || (ExpMonth==TransMonth)){
            return EXPIRED_CARD;
      }
  }
  return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float localTransAmount=0;
    printf("\n Enter transaction amount: ");
    scanf("%f", &localTransAmount);
    if(localTransAmount<=0){
        return INVALID_AMOUNT;
    }else{
        termData->transAmount = localTransAmount;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData,float maxAmount){
    float LocalMaxAmount =0;
  //  printf("\n Enter transaction maximum amount: ");
   // scanf("%f", &LocalMaxAmount);
    if(LocalMaxAmount<=0){
        return INVALID_AMOUNT;
    }else{
        termData->maxTransAmount = maxAmount;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

    int lenght = strlen(cardData->primaryAccountNumber);
    int sum = 0;
    int isSecond = 0;
    for (int i = lenght - 1; i >= 0; i--) {
        int digit = cardData->primaryAccountNumber[i] - '0';
        if (!isdigit(cardData->primaryAccountNumber[i])) {
            return 0;
        }
        if (isSecond) {
            digit = digit * 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        isSecond = !isSecond;
    }
    if((sum % 10) == 0){
        return INVALID_CARD;
    }
    return TERMINAL_OK;
}
