#include <stdio.h>
#include <string.h>
#include "account.h"

void create_account(Account *account, int account_number, const char *owner_name) {
    account->account_number = account_number;
    snprintf(account->owner_name, sizeof(account->owner_name), "%s", owner_name);
    account->balance = 0.0;
    account->history_count = 0;
}

void delete_account(Account accounts[], int *account_count, int account_number) {
    for (int i = 0; i < *account_count; i++) {
        if (accounts[i].account_number == account_number) {
            for (int j = i; j < *account_count - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            (*account_count)--;
            printf("Compte #%d supprimé.\n", account_number);
            return;
        }
    }
    printf("Compte #%d non trouvé.\n", account_number);
}

void deposit(Account *account, double amount) {
    if (amount > 0) {
        account->balance += amount;
        snprintf(account->history[account->history_count].operation, sizeof(account->history[account->history_count].operation), "Dépôt");
        account->history[account->history_count].amount = amount;
        account->history_count++;
        printf("Dépôt de %.2f effectué. Nouveau solde: %.2f\n", amount, account->balance);
    } else {
        printf("Le montant du dépôt doit être positif.\n");
    }
}

void withdraw(Account *account, double amount) {
    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        snprintf(account->history[account->history_count].operation, sizeof(account->history[account->history_count].operation), "Retrait");
        account->history[account->history_count].amount = amount;
        account->history_count++;
        printf("Retrait de %.2f effectué. Nouveau solde: %.2f\n", amount, account->balance);
    } else {
        printf("Montant invalide pour le retrait.\n");
    }
}

void display_account(const Account *account) {
    printf("Compte #%d\nPropriétaire: %s\nSolde: %.2f\n", account->account_number, account->owner_name, account->balance);
}

void display_history(const Account *account) {
    printf("Historique des opérations pour le compte #%d:\n", account->account_number);
    for (int i = 0; i < account->history_count; i++) {
        printf("%s: %.2f\n", account->history[i].operation, account->history[i].amount);
    }
}