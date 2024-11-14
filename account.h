#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 100
#define MAX_HISTORY_LENGTH 100

typedef struct {
    char operation[50];
    double amount;
} Transaction;

typedef struct {
    int account_number;
    char owner_name[MAX_NAME_LENGTH];
    double balance;
    Transaction history[MAX_HISTORY_LENGTH];
    int history_count;
} Account;

void create_account(Account *account, int account_number, const char *owner_name);
void delete_account(Account accounts[], int *account_count, int account_number);
void deposit(Account *account, double amount);
void withdraw(Account *account, double amount);
void transfer(Account *from_account, Account *to_account, double amount);
void display_account(const Account *account);
void display_history(const Account *account);

#endif 
