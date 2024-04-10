#ifndef ACCOUNT_MANAGER_HEADER
#define ACCOUNT_MANAGER_HEADER

#include "Structs.h"

char create_account(Account *acc, char *datapath);
char login(Account *acc, char *datapath);

#endif