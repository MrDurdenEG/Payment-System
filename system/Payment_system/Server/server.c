#include "../../Libraries/Libraries.h"



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

    while (fscanf(file, "%f %s %s", &amount, pan, state) == 3)
    {
        const char* accountStateStrings[] = { "RUNNING", "BLOCKED" };
        ST_accountsDB_t account;
        account.balance = amount;
        strncpy(account.primaryAccountNumber, pan, sizeof(account.primaryAccountNumber));
        account.state = (strcmp(state, "RUNNING") == 0) ? RUNNING : BLOCKED;
        addAccountNode(account);

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
    head = reverseList(head);
    AccountNode* current = head;
    while (current != NULL)
    {
        const char* accountStateStrings[] = { "RUNNING", "BLOCKED" };
        fprintf(file, "%f %s %s\n", current->account.balance, current->account.primaryAccountNumber, accountStateStrings[current->account.state]);
        current = current->next;
    }
    fclose(file);
    head = reverseList(head);
}




EN_transState_t recieveTransactionData(ST_transaction_t *transData,ST_cardData_t *cardData,ST_terminalData_t *termData)
{
    if(ACCOUNT_NOT_FOUND == isValidAccount(cardData))
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(LOW_BALANCE == isAmountAvailable(termData,cardData))
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    if(BLOCKED_ACCOUNT == isBlockedAccount(cardData))
    {
        transData->transState = BLOCKED_ACCOUNT_ERROR;
        return BLOCKED_ACCOUNT_ERROR ;
    }
    else
    {
        transData->transState = APPROVED;
        AccountNode* node = findAccountByPAN(cardData->primaryAccountNumber);
        if (node != NULL)
        {
            node->account.balance -= termData->transAmount;
        }

    }

    return APPROVED;
}


EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    AccountNode* node = findAccountByPAN(cardData->primaryAccountNumber);
    if (node == NULL)
    {
        return ACCOUNT_NOT_FOUND;
    }
    //index = node;
    return SERVER_OK;
}
EN_serverError_t isBlockedAccount(ST_cardData_t *cardData)
{
    AccountNode* node = findAccountByPAN(cardData->primaryAccountNumber);
    if (node != NULL && node->account.state == BLOCKED)
    {
        return BLOCKED_ACCOUNT;
    }
    return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_cardData_t *cardData)
{
    AccountNode* node = findAccountByPAN(cardData->primaryAccountNumber);
    if (node != NULL && termData->transAmount > node->account.balance)
    {
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
    switch (transData->transState)
    {
    case APPROVED:
        fprintf(file2, "APPROVED\n");
        break;
    case DECLINED_INSUFFECIENT_FUND:
        fprintf(file2, "DECLINED_INSUFFECIENT_FUND\n");
        break;
    case DECLINED_STOLEN_CARD:
        fprintf(file2, "DECLINED_STOLEN_CARD\n");
        break;
    case BLOCKED_ACCOUNT_ERROR:
        fprintf(file2, "BLOCKED_ACCOUNT_ERROR\n");
        break;
    default:
        fprintf(file2, "UNKNOWN\n");
        break;
    }
    fprintf(file2,"\tTerminal Max Amount: %f\n",termData->maxTransAmount);
    fprintf(file2,"\tCard holder Name: %s\n",cardData->CardHolderName);
    fprintf(file2,"\tPAN: %s\n",cardData->primaryAccountNumber);
    fprintf(file2,"\tCard Expiration Date: %s\n",cardData->cardExpirationDate);

    printf("Transactions:-\n");
    printf("\tTransaction Sequence Number: \033[1;36m%d\033[0m\n", transData->transactionSequenceNumber);
    printf("\tTransaction Date: \033[1;36m%s\033[0m\n",termData->transactionDate);
    printf("\tTransaction Amount: \033[1;36m%f\033[0m\n",termData->transAmount);
    printf("\tTransactions State: ");
    switch (transData->transState)
    {
    case APPROVED:
        printf("APPROVED\n");
        break;
    case DECLINED_INSUFFECIENT_FUND:
        printf("DECLINED_INSUFFECIENT_FUND\n");
        break;
    case DECLINED_STOLEN_CARD:
        printf("DECLINED_STOLEN_CARD\n");
        break;
    case BLOCKED_ACCOUNT_ERROR:
        printf("BLOCKED_ACCOUNT_ERROR\n");
        break;
    default:
        printf("UNKNOWN\n");
        break;
    }
    printf("\tTerminal Max Amount: \033[1;36m%f\033[0m\n",termData->maxTransAmount);
    printf("\tCard holder Name: \033[1;36m%s\033[0m\n",cardData->CardHolderName);
    printf("\tPAN: \033[1;36m%s\033[0m\n",cardData->primaryAccountNumber);
    printf("\tCard Expiration Date: \033[1;36m%s\033[0m\n\n",cardData->cardExpirationDate);


    return SERVER_OK;
}


