#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "account.h"

void save_accounts(const Account accounts[], int account_count, const char *filename);
void load_accounts(Account accounts[], int *account_count, const char *filename);

#endif 
