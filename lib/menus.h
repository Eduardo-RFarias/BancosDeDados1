#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"

#include "utils.h"
#include "authService.h"
#include "dbClient.h"

void mainMenu();

int notLoggedInMenu();

int loggedInMenu();

void loginPrompt();

void registerUserPrompt();

void registerCarPrompt();

#endif