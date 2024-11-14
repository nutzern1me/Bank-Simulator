#include <stdio.h>
#include "transaction.h"

void transfer(Account *from_account, Account *to_account, double amount) {
    if (amount > 0 && amount <= from_account->balance) {
        from_account->balance -= amount;
        to_account->balance += amount;
        snprintf(from_account->history[from_account->history_count].operation, sizeof(from_account->history[from_account->history_count].operation), "Transfert vers %d", to_account->account_number);
        from_account->history[from_account->history_count].amount = amount;
        from_account->history_count++;
        
        snprintf(to_account->history[to_account->history_count].operation, sizeof(to_account->history[to_account->history_count].operation), "Transfert de %d", from_account->account_number);
        to_account->history[to_account->history_count].amount = amount;
        to_account->history_count++;

        printf("Transfert de %.2f de compte #%d à compte #%d effectué.\n", amount, from_account->account_number, to_account->account_number);
    } else {
        printf("Montant invalide pour le transfert.\n");
    }
}