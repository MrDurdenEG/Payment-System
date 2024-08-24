
#include "../../Libraries/Libraries.h"

 AccountNode* head = NULL;
void addAccountNode(ST_accountsDB_t account) {
    AccountNode* newNode = (AccountNode*)malloc(sizeof(AccountNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->account = account;
    newNode->next = head;
    head = newNode;
}

AccountNode* findAccountByPAN(const char* pan) {
    AccountNode* current = head;
    while (current != NULL) {
        if (strcmp(current->account.primaryAccountNumber, pan) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteAccountNode(const char* pan) {
    AccountNode* current = head;
    AccountNode* previous = NULL;
    while (current != NULL && strcmp(current->account.primaryAccountNumber, pan) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) return;
    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}

void freeLinkedList() {
    AccountNode* current = head;
    while (current != NULL) {
        AccountNode* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

AccountNode* reverseList(AccountNode* head) {
    AccountNode* prev = NULL;
    AccountNode* current = head;
    AccountNode* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
