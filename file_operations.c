#include <stdio.h>
#include <string.h>
#include "file_operations.h"

void save_accounts(const Account accounts[], int account_count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < account_count; i++) {
            fprintf(file, "%d\n%s\n%.2f\n%d\n", accounts[i].account_number, accounts[i].owner_name, accounts[i].balance, accounts[i].history_count);
            for (int j = 0; j < accounts[i].history_count; j++) {
                fprintf(file, "%s\n%.2f\n", accounts[i].history[j].operation, accounts[i].history[j].amount);
            }
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde.\n");
    }
}

void load_accounts(Account accounts[], int *account_count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        while (fscanf(file, "%d\n", &accounts[*account_count].account_number) != EOF) {
            fgets(accounts[*account_count].owner_name, sizeof(accounts[*account_count].owner_name), file);
            accounts[*account_count].owner_name[strcspn(accounts[*account_count].owner_name, "\n")] = 0;
            fscanf(file, "%lf\n%d\n", &accounts[*account_count].balance, &accounts[*account_count].history_count);
            for (int j = 0; j < accounts[*account_count].history_count; j++) {
                fgets(accounts[*account_count].history[j].operation, sizeof(accounts[*account_count].history[j].operation), file);
                fscanf(file, "%lf\n", &accounts[*account_count].history[j].amount);
            }
            (*account_count)++;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier pour chargement.\n");
    }
}
