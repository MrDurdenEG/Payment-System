

#ifndef LIST_H
#define LIST_H
AccountNode* reverseList(AccountNode* head);
void addAccountNode(ST_accountsDB_t account);
AccountNode* findAccountByPAN(const char* pan);
void deleteAccountNode(const char* pan);
void freeLinkedList(void);

#endif // LIST_H

