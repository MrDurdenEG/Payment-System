#include "../../Libraries/Libraries.h"


int index = -1;
ST_accountsDB_t Account[255];

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
    int i = 0,j;
    while (fscanf(file, "%f %s", &amount, pan))
    {
        if (i > 0 && Account[i - 1].balance == amount && Account[i - 1].primaryAccountNumber[6] == pan[6])
        {
            break;
        }
        Account[i].balance = amount;
        for (j = 0; j < 20; j++)
        {
            Account[i].primaryAccountNumber[j] = pan[j];
        }
        i++;
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
        fprintf(file, "%f %s\n", Account[i].balance, Account[i].primaryAccountNumber);
    }
}


EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if(ACCOUNT_NOT_FOUND == isValidAccount(&(transData->cardHolderData)))
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(LOW_BALANCE == isAmountAvailable(&(transData->terminalData)))
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    if(BLOCKED_ACCOUNT == isBlockedAccount(Account))
    {
        transData->transState = BLOCKED_ACCOUNT_ERROR;
        return BLOCKED_ACCOUNT_ERROR ;
    }
    if( (SAVING_FAILED == saveTransaction(transData)) )
    {
        return INTERNAL_SERVER_ERROR;
    }
    else
    {
        transData->transState = APPROVED;
        Account[index].balance -= transData->terminalData.transAmount;
    }

    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData){

    if( (0 == strcmp(cardData->primaryAccountNumber, Account->primaryAccountNumber)) )
        {
            return SERVER_OK;
        }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(accountRefrence->state == BLOCKED){
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

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    file2 = fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\TransNumber.txt", "r");
    if (!file2)
    {
        return SAVING_FAILED;
    }
    int NumberOfTrans;
    fscanf(file2, "%d", &NumberOfTrans);
    fclose(file2);

    file2 = fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\TransNumber.txt", "w");
    fprintf(file2, "%d", NumberOfTrans+1);
    fclose(file2);
    transData->transactionSequenceNumber = NumberOfTrans+1;
    file1 = fopen("C:\\Users\\HTech\\Desktop\\system\\Data_Bases\\Data\\TransInfo.txt", "a");
    if (!file1)
    {
        return SAVING_FAILED;
    }
    fprintf(file1,"Transactions:-\n");
    fprintf(file1,"\tTransaction Sequence Number: %d\n", transData->transactionSequenceNumber);
    fprintf(file1,"\tTransaction Date: %s\n",transData->terminalData.transactionDate);
    fprintf(file1,"\tTransaction Amount: %s\n",transData->terminalData.transAmount);
    fprintf(file1,"\tTransactions State: ");
    if (transData->transState == APPROVED)
    {
        fprintf(file1, "APPROVED\n");
    }
    else if (transData->transState == DECLINED_INSUFFECIENT_FUND)
    {
        fprintf(file1, "DECLINED_INSUFFECIENT_FUND\n");
    }
    else if (transData->transState == DECLINED_STOLEN_CARD)
    {
        fprintf(file1, "DECLINED_STOLEN_CARD\n");
    }
    else if (transData->transState == BLOCKED_ACCOUNT_ERROR)
    {
        fprintf(file1, "BLOCKED_ACCOUNT_ERROR\n");
    }
    fprintf(file1,"\tTerminal Max Amount:%f\n", transData->terminalData.maxTransAmount);
    fprintf(file1,"\tCard Holder Name: %s\n",transData->cardHolderData.CardHolderName);
    fprintf(file1,"\tPAN: %s\n",transData->cardHolderData.primaryAccountNumber);
    fprintf(file1,"\tCard Expiration Date: %s\n",transData->cardHolderData.cardExpirationDate);
    fprintf(file1,"##################################\n");
    fclose(file1);

    return SERVER_OK;
}

void listSavedTransactions(void)
{


}

