
#include "../Libraries/Libraries.h"

void appStart(void)
{
    //to color the console "\033[1;36m%s\033[0m\n"
    printf("====================================\n");
    printf("  Reading Accounts Data Base\n");
    printf("====================================\n\n");
    readAccountDB();
    printf("====================================\n");
    printf("  Successfully loaded Accounts Data Base\n");
    printf("====================================\n\n");

    ST_cardData_t *cardData = (ST_cardData_t *)malloc(sizeof(ST_cardData_t));
    if (cardData == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    ST_terminalData_t *termData = (ST_terminalData_t *)malloc(sizeof(ST_terminalData_t));
    if (termData == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    ST_transaction_t *transData = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
    if (transData == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }


    EN_cardError_t RetCard = getCardHolderName(cardData);
    while (RetCard != CARD_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   WRONG NAME ENTERED!\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetCard = getCardHolderName(cardData);
    }
    printf("====================================\n");
    printf("  Card Holder Name Accepted:\n");
    printf("  %s\n", cardData->CardHolderName);
    printf("====================================\n");




    RetCard = getCardExpiryDate(cardData);
    while (RetCard != CARD_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   WRONG EXP DATE ENTERED!\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetCard = getCardExpiryDate(cardData);
    }
    printf("====================================\n");
    printf("  Card EXP DATE Accepted:\n");
    printf("  %s\n", cardData->cardExpirationDate);
    printf("====================================\n");
    getchar();
 RetCard = getCardPAN(cardData);
    while (RetCard != CARD_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   WRONG PAN ENTERED!\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetCard = getCardPAN(cardData);
    }
    printf("====================================\n");
    printf("  Card PAN Accepted:\n");
    printf("  %s\n", cardData->primaryAccountNumber);
    printf("====================================\n");

    EN_terminalError_t RetTerm = isValidCardPAN(cardData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   INVALID PAN ENTERED!\n");
        printf("*****************************\n\n");
        return 0;
    }
    printf("====================================\n");
    printf("  PAN Accepted:\n");
    printf("  %s\n", cardData->primaryAccountNumber);
    printf("====================================\n");

    RetTerm = getTransactionDate(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   WRONG DATE ENTERED!\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetTerm = getTransactionDate(termData);
    }
    printf("====================================\n");
    printf("  Transaction DATE Accepted:\n");
    printf("  %s\n", termData->transactionDate);
    printf("====================================\n");

    RetTerm = isCardExpired(cardData,termData);
    while (RetTerm != TERMINAL_OK )
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   WRONG DATE ENTERED!\n");
        printf("   Your card is expired\n");
        return 0;
    }
  RetTerm = setMaxAmount(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   INVALID Amount ENTERED!\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetTerm = setMaxAmount(termData);
    }
    printf("====================================\n");
    printf("  MAX Amount Accepted:\n");
    printf("  %f\n", termData->maxTransAmount);
    printf("====================================\n");

    RetTerm = getTransactionAmount(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   INVALID Amount ENTERED!\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetTerm = getTransactionAmount(termData);
    }
    printf("====================================\n");
    printf("  Amount Accepted:\n");
    printf("  %f\n", termData->transAmount);
    printf("====================================\n");

    RetTerm = isBelowMaxAmount(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          ERROR\n");
        printf("*****************************\n");
        printf("   AMOUNT BELOW MAX ENTERED!\n");
        printf("*****************************\n\n");
        return 0;
    }
    printf("====================================\n");
    printf("  Amount Accepted:\n");
    printf("====================================\n");



    EN_transState_t RetStat = recieveTransactionData(transData,cardData,termData);
    if (RetStat == DECLINED_STOLEN_CARD) {
		printf("\n\tDECLINED STOLEN CARD/INVALID ACCOUNT\n");
	}
	else if (RetStat== DECLINED_INSUFFECIENT_FUND) {
		printf("\n\tDECLINED_INSUFFECIENT_FUND\n");
	}
	else if (RetStat== BLOCKED_ACCOUNT_ERROR) {
		printf("\n\BLOCKED_ACCOUNT_ERROR\n");
	}
	else if (RetStat == APPROVED) {
		printf("\n\tAPPROVED\n");
		printf("\tUPDATING ACCOUNTS DB\n");
		updateAccountDB();
	EN_serverError_t RetServ = saveTransaction(transData,termData);
		if(RetServ == SERVER_OK){
            printf("\tSAVING TRANSACTION\n");
		}
	}

}




