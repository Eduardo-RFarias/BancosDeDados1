#include "authService.h"

int login(char *cnh)
{
    FILE *loginFile = overrideOrCreateFileForWriting(LOGIN_FILE_PATH);
    FILE *userTable = openFileForReading(USER_TABLE_PATH);

    User user;

    while (fread(&user, sizeof(User), 1, userTable) == TRUE)
    {
        if (strcmp(user.cnh, cnh) == 0)
        {
            fwrite(user.cnh, sizeof(char) * USER_CNH_MAXSIZE, 1, loginFile);
            fclose(loginFile);
            fclose(userTable);
            return TRUE;
        }
    }

    fclose(loginFile);
    fclose(userTable);
    return FALSE;
}

void logout()
{
    FILE *loginFile = overrideOrCreateFileForWriting(LOGIN_FILE_PATH);
    fclose(loginFile);
}

User *getLoggedInUser()
{
    FILE *loginFile = openFileOrCreateForReading(LOGIN_FILE_PATH);

    char userCnh[USER_CNH_MAXSIZE];

    int success = fread(userCnh, sizeof(char) * USER_CNH_MAXSIZE, 1, loginFile);

    fclose(loginFile);

    if (success != TRUE)
    {
        return NULL;
    }

    User *user = findUserByCnh(userCnh);

    return user;
}

int isLoggedIn()
{
    FILE *loginFile = openFileOrCreateForReading(LOGIN_FILE_PATH);

    char userCnh[USER_CNH_MAXSIZE];

    if (fread(userCnh, sizeof(char) * USER_CNH_MAXSIZE, 1, loginFile) == TRUE)
    {
        fclose(loginFile);
        return TRUE;
    }

    fclose(loginFile);
    return FALSE;
}