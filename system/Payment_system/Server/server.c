#include "../../Libraries/Libraries.h"


//extern int
index = -1 ;
static ST_accountsDB_t Account[255];

void readAccountDB(void)
{
    file= fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\AccountsDB.txt", "r");
    if (!file)
    {
        printf("(AccountsDB.txt) File Not Found \n");
        return;
    }
    uint8_t pan[20];
    float amount;
    char state[10];
    int i = 0,j;
        while (fscanf(file, "%f %s %s", &amount, pan, state) == 3)
    {

        Account[i].balance = amount;
        strncpy(Account[i].primaryAccountNumber, pan, sizeof(Account[i].primaryAccountNumber));
        if (strcmp(state, "RUNNING") == 0)
        {
            Account[i].state = RUNNING;
        }
        else if (strcmp(state, "BLOCKED") == 0)
        {
            Account[i].state = BLOCKED;
        }printf("Account %d:\n", i + 1);
        printf("Balance: %.6f\n", Account[i].balance);
        printf("PAN: %s\n", Account[i].primaryAccountNumber);
        printf("state: %d\n\n", Account[i].state);
        i++;
    }
      if (feof(file))
    {
        printf("End of file reached.\n");
    }
    else if (ferror(file))
    {
        printf("Error reading file.\n");
    }

    fclose(file);
}

void updateAccountDB(void)
{
    file= fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\AccountsDB.txt", "w");
    if (!file)
    {
        printf("(AccountsDB.txt) File Not Found \n");
        return;
    }
    for (int i = 0; i < 255; i++)
    {
        if (Account[i].primaryAccountNumber[0] == '\0')
        {
            break;
        }
        const char *accountStateStrings[] = {
          "RUNNING",
          "BLOCKED"
        };
        fprintf(file, "%f %s %s\n", Account[i].balance, Account[i].primaryAccountNumber,accountStateStrings[Account[i].state]);
        printf("Updated Account %d: PAN = %s, Balance = %.2f\n", i, Account[i].primaryAccountNumber, Account[i].balance);
    }
}


EN_transState_t recieveTransactionData(ST_transaction_t *transData,ST_cardData_t *cardData,ST_terminalData_t *termData)
{
    if(ACCOUNT_NOT_FOUND == isValidAccount(cardData))
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(LOW_BALANCE == isAmountAvailable(termData))
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    if(BLOCKED_ACCOUNT == isBlockedAccount(Account))
    {
        transData->transState = BLOCKED_ACCOUNT_ERROR;
        return BLOCKED_ACCOUNT_ERROR ;
    }
    else
    {
         transData->transState = APPROVED;
        printf("before : %f  %f \n",Account[index].balance,termData->transAmount);
        Account[index].balance -= termData->transAmount;
        printf("after : %f  %f \n",Account[index].balance,termData->transAmount);
    }

    return APPROVED;
}


EN_serverError_t isValidAccount(ST_cardData_t *cardData) {
    for (int i = 0; i < 255; i++) {
        if (Account[i].primaryAccountNumber[0] == '\0') {
            printf("There are no more accounts in the database.\n\n\n");
            break; // No more accounts in the database
        }
        if (strcmp(cardData->primaryAccountNumber, Account[i].primaryAccountNumber) == 0) {
            index = i;;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(Account[index].state == BLOCKED){
        return BLOCKED_ACCOUNT;
    }
    return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if(termData->transAmount > Account[index].balance){
        return LOW_BALANCE;
    }
    return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData,ST_terminalData_t *termData,ST_cardData_t *cardData)
{
    file2 = fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\TransNumber.txt", "r");
    if (!file2)
    {
        return SAVING_FAILED;
    }
    int NumberOfTrans=0;
    fscanf(file2, "%d", &NumberOfTrans);
    fclose(file2);
    file2 = fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\TransNumber.txt", "w");
    fprintf(file2, "%d", ++NumberOfTrans);
    fclose(file2);
    transData->transactionSequenceNumber = NumberOfTrans;
    file2 = fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\TransInfo.txt", "a");
    if (!file2)
    {
        return SAVING_FAILED;
    }

    fprintf(file2,"Transactions:-\n");
    fprintf(file2,"\tTransaction Sequence Number: %d\n", transData->transactionSequenceNumber);
    fprintf(file2,"\tTransaction Date: %s\n",termData->transactionDate);
    fprintf(file2,"\tTransaction Amount: %f\n",termData->transAmount);
    fprintf(file2,"\tTransactions State: ");
    switch (transData->transState) {
        case APPROVED:
            fprintf(file1, "APPROVED\n");
            break;
        case DECLINED_INSUFFECIENT_FUND:
            fprintf(file1, "DECLINED_INSUFFECIENT_FUND\n");
            break;
        case DECLINED_STOLEN_CARD:
            fprintf(file1, "DECLINED_STOLEN_CARD\n");
            break;
        case BLOCKED_ACCOUNT_ERROR:
            fprintf(file1, "BLOCKED_ACCOUNT_ERROR\n");
            break;
        default:
            fprintf(file1, "UNKNOWN\n");
            break;
    }
    fprintf(file2,"\tTerminal Max Amount: %f\n",termData->maxTransAmount);
    fprintf(file2,"\tCard holder Name: %s\n",cardData->CardHolderName);
    fprintf(file2,"\tPAN: %s\n",cardData->primaryAccountNumber);
    fprintf(file2,"\tCard Expiration Date: %s\n",cardData->cardExpirationDate);


    return SERVER_OK;
}


