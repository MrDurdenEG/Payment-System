#ifndef _SERVER_H_
#define _SERVER_H_

#include "../Terminal/terminal.h"
#include "../Card/card.h"



typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLEN_CARD,
    FRAUD_CARD,
    INTERNAL_SERVER_ERROR,
    BLOCKED_ACCOUNT_ERROR
} EN_transState_t;

typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
} EN_accountState_t;

typedef enum EN_serverError_t
{
    SERVER_OK,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE,
    BLOCKED_ACCOUNT
} EN_serverError_t ;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
} ST_transaction_t;

typedef struct ST_accountsDB_t
{
    double balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
} ST_accountsDB_t;

typedef struct AccountNode {
    ST_accountsDB_t account;
    struct AccountNode* next;
} AccountNode;

extern AccountNode* head ;

extern int index ;

EN_transState_t recieveTransactionData(ST_transaction_t *transData,ST_cardData_t *cardData,ST_terminalData_t *termData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isBlockedAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_cardData_t *cardData);
EN_serverError_t saveTransaction(ST_transaction_t *transData,ST_terminalData_t *termData,ST_cardData_t *cardData);
void listSavedTransactions(void);


#endif // _SERVER_H_
