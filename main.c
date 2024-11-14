#include <stdio.h>
#include "account.h"
#include <string.h>
#include "file_operations.h"
#include "utils.h"

int main() {
    Account accounts[MAX_ACCOUNTS];
    int account_count = 0;
    char filename[] = "accounts.txt";

    load_accounts(accounts, &account_count, filename);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Créer un compte\n");
        printf("2. Afficher un compte\n");
        printf("3. Déposer de l'argent\n");
        printf("4. Retirer de l'argent\n");
        printf("5. Transférer de l'argent\n");
        printf("6. Afficher l'historique des opérations\n");
        printf("7. Supprimer un compte\n");
        printf("8. Sauvegarder les comptes\n");
        printf("9. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: {
                int account_number;
                char owner_name[MAX_NAME_LENGTH];
                printf("Numéro de compte: ");
                scanf("%d", &account_number);
                clear_input_buffer();
                printf("Nom du propriétaire: ");
                fgets(owner_name, sizeof(owner_name), stdin);
                owner_name[strcspn(owner_name, "\n")] = 0; 
                create_account(&accounts[account_count], account_number, owner_name);
                account_count++;
                break;
            }
            case 2: {
                int account_number;
                printf("Numéro de compte à afficher: ");
                scanf("%d", &account_number);
                for (int i = 0; i < account_count; i++) {
                    if (accounts[i].account_number == account_number) {
                        display_account(&accounts[i]);
                        break;
                    }
                }
                break;
            }
            case 3: {
                int account_number;
                double amount;
                printf("Numéro de compte: ");
                scanf("%d", &account_number);
                printf("Montant à déposer: ");
                scanf("%lf", &amount);
                for (int i = 0; i < account_count; i++) {
                    if (accounts[i].account_number == account_number) {
                        deposit(&accounts[i], amount);
                        break;
                    }
                }
                break;
            }
            case 4: {
                int account_number;
                double amount;
                printf("Numéro de compte: ");
                scanf("%d", &account_number);
                printf("Montant à retirer: ");
                scanf("%lf", &amount);
                for (int i = 0; i < account_count; i++) {
                    if (accounts[i].account_number == account_number) {
                        withdraw(&accounts[i], amount);
                        break;
                    }
                }
                break;
            }
            case 5: {
                int from_account_number, to_account_number;
                double amount;
                printf("Numéro de compte d'origine: ");
                scanf("%d", &from_account_number);
                printf("Numéro de compte de destination: ");
                scanf("%d", &to_account_number);
                printf("Montant à transférer: ");
                scanf("%lf", &amount);
                Account *from_account = NULL;
                Account *to_account = NULL;
                for (int i = 0; i < account_count; i++) {
                    if (accounts[i].account_number == from_account_number) {
                        from_account = &accounts[i];
                    }
                    if (accounts[i].account_number == to_account_number) {
                        to_account = &accounts[i];
                    }
                }
                if (from_account && to_account) {
                    transfer(from_account, to_account, amount);
                } else {
                    printf("Un des comptes est introuvable.\n");
                }
                break;
            }
            case 6: {
                int account_number;
                printf("Numéro de compte pour afficher l'historique: ");
                scanf("%d", &account_number);
                for (int i = 0; i < account_count; i++) {
                    if (accounts[i].account_number == account_number) {
                                                display_history(&accounts[i]);
                        break;
                    }
                }
                break;
            }
            case 7: {
                int account_number;
                printf("Numéro de compte à supprimer: ");
                scanf("%d", &account_number);
                delete_account(accounts, &account_count, account_number);
                break;
            }
            case 8: {
                save_accounts(accounts, account_count, filename);
                printf("Comptes sauvegardés dans %s.\n", filename);
                break;
            }
            case 9:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 9);

    return 0;
}
