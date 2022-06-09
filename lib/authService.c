#include "authService.h"

int login(char *cpf)
{
    FILE *loginFile = overrideOrCreateFileForWriting(LOGIN_FILE_PATH);
    FILE *userTable = openFileOrCreateForReading(USER_TABLE_PATH);

    User user;

    while (fread(&user, sizeof(User), 1, userTable) == TRUE)
    {
        if (strcmp(user.cpf, cpf) == 0)
        {
            fwrite(user.cpf, sizeof(char) * USER_CPF_MAXSIZE, 1, loginFile);
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

    char userCpf[USER_CPF_MAXSIZE];

    int success = fread(userCpf, sizeof(char) * USER_CPF_MAXSIZE, 1, loginFile);

    fclose(loginFile);

    if (success != TRUE)
    {
        return NULL;
    }

    User *user = findUserByCpf(userCpf);

    return user;
}

int isLoggedIn()
{
    FILE *loginFile = openFileOrCreateForReading(LOGIN_FILE_PATH);

    char userCpf[USER_CPF_MAXSIZE];

    if (fread(userCpf, sizeof(char) * USER_CPF_MAXSIZE, 1, loginFile) == TRUE)
    {
        fclose(loginFile);
        return TRUE;
    }

    fclose(loginFile);
    return FALSE;
}