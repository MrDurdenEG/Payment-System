

#include "../Libraries/Libraries.h"

void appStart(void)
{
    printf("====================================\n");
    printf("  \033[1;36mReading Accounts Data Base\033[0m\n");
    printf("====================================\n\n");

    readAccountDB();

    printf("====================================\n");
    printf(" \033[1;36mSuccessfully loaded Accounts Data Base\033[0m\n");
    printf("====================================\n\n");

    ST_cardData_t *cardData = (ST_cardData_t *)malloc(sizeof(ST_cardData_t));
    if (cardData == NULL) { printf("Memory allocation failed\n"); return; }

    ST_terminalData_t *termData = (ST_terminalData_t *)malloc(sizeof(ST_terminalData_t));
    if (termData == NULL) { printf("Memory allocation failed\n"); return; }

    ST_transaction_t *transData = (ST_transaction_t *)malloc(sizeof(ST_transaction_t));
    if (transData == NULL) { printf("Memory allocation failed\n"); return; }

    EN_cardError_t RetCard = getCardHolderName(cardData);
    while (RetCard != CARD_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mWRONG NAME ENTERED!\033[0m\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetCard = getCardHolderName(cardData);
    }

    RetCard = getCardExpiryDate(cardData);
    while (RetCard != CARD_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mWRONG EXP DATE ENTERED!\033[0m\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetCard = getCardExpiryDate(cardData);
    }
    getchar();

    RetCard = getCardPAN(cardData);
    while (RetCard != CARD_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mWRONG PAN ENTERED!\033[0m\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetCard = getCardPAN(cardData);
    }

    EN_terminalError_t RetTerm = isValidCardPAN(cardData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mINVALID PAN ENTERED!\033[0m\n");
        printf("*****************************\n\n");
        return;
    }


    RetTerm = getTransactionDate(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mWRONG DATE ENTERED!\033[0m\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetTerm = getTransactionDate(termData);
    }


    RetTerm = isCardExpired(cardData, termData);
    if (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mCARD IS EXPIRED!\033[0m\n");
        printf("*****************************\n\n");
        return;
    }

    RetTerm = setMaxAmount(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mINVALID AMOUNT ENTERED!\033[0m\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetTerm = setMaxAmount(termData);
    }


    RetTerm = getTransactionAmount(termData);
    while (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mINVALID AMOUNT ENTERED!\033[0m\n");
        printf("   Please try again.\n");
        printf("*****************************\n\n");
        RetTerm = getTransactionAmount(termData);
    }

    RetTerm = isBelowMaxAmount(termData);
    if (RetTerm != TERMINAL_OK)
    {
        printf("\n*****************************\n");
        printf("          \033[1;31mERROR\033[0m\n");
        printf("  \033[1;31mAMOUNT EXCEEDS MAXIMUM ALLOWED!\033[0m\n");
        printf("*****************************\n\n");
        return;
    }

    EN_transState_t RetStat = recieveTransactionData(transData, cardData, termData);
    if (RetStat == DECLINED_STOLEN_CARD) {
        printf("\n\t\033[1;31mDECLINED: STOLEN CARD / INVALID ACCOUNT!\033[0m\n");
    } else if (RetStat == DECLINED_INSUFFECIENT_FUND) {
        printf("\n\t\033[1;31mDECLINED: INSUFFICIENT FUNDS!\033[0m\n");
    } else if (RetStat == BLOCKED_ACCOUNT_ERROR) {
        printf("\n\t\033[1;31mDECLINED: ACCOUNT BLOCKED!\033[0m\n");
    } else if (RetStat == APPROVED) {
        printf("\n\033[1;32mTRANSACTION APPROVED!\033[0m\n");
        printf("\n\033[1;36mUPDATING ACCOUNTS DATABASE...\033[0m\n\n");
        updateAccountDB();

        EN_serverError_t RetServ = saveTransaction(transData, termData, cardData);
        if (RetServ == SAVING_FAILED) {
            printf("\033[1;31mFailed to save transaction data!\033[0m\n\n");
        } else {
            printf("\033[1;32mTransaction data saved successfully!\033[0m\n\n");
        }
    }

    free(cardData);
    free(termData);
    free(transData);
}



