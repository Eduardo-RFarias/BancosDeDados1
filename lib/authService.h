#ifndef AUTH_SERVICE_H_INCLUDED
#define AUTH_SERVICE_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"

#define LOGIN_FILE_PATH "sessionTable.bin"

#include "dbClient.h"

int login(char *cpf);

void logout();

User *getLoggedInUser();

int isLoggedIn();

#endif
