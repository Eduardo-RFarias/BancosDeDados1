#include "authService.h"

int login(unsigned long long cpf)
{
    FILE *loginFile = overrideOrCreateFileForWriting(LOGIN_FILE_PATH);
    FILE *userTable = openFileOrCreateForReading(USER_TABLE_PATH);

    User user;

    while (fread(&user, sizeof(User), 1, userTable) == TRUE)
    {
        if (user.cpf == cpf)
        {
            fwrite(&(user.cpf), sizeof(unsigned long long), 1, loginFile);
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

    unsigned long long userCpf;

    int success = fread(&userCpf, sizeof(unsigned long long), 1, loginFile);

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

    unsigned long long userCpf;

    if (fread(&userCpf, sizeof(unsigned long long), 1, loginFile) == TRUE)
    {
        fclose(loginFile);
        return TRUE;
    }

    fclose(loginFile);
    return FALSE;
}