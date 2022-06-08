/*
Author : Eduardo Rodrigues de Farias
June 8th, 2022

Universidade de Brasília, UNB

FGA0137 - SISTEMAS DE BANCO DE DADOS 1 - T01 - 2022/1
Aula 1 - Exercício 1
*/

#include "stdio.h"
#include "stdlib.h"

#include "lib/dbClient.h"
#include "lib/menus.h"

// * Testing functions
char *randstring(size_t length)
{

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomString = NULL;

    if (length)
    {
        randomString = malloc(sizeof(char) * (length + 1));

        if (randomString)
        {
            for (int n = 0; n < length; n++)
            {
                int key = rand() % (int)(sizeof(charset) - 1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

void preRegister(char *userTablePath)
{
    for (int i = 0; i < 3; i++)
    {
        char *name = randstring(10);
        char *cnh = randstring(11);

        User *user = createUser(name, cnh);

        saveUser(user);

        free(name);
        free(user);

        char *plate = randstring(8);
        char *brand = randstring(10);
        char *model = randstring(10);

        Car *car = createCar(plate, brand, model, 2020, cnh);

        saveCar(car);

        free(plate);
        free(brand);
        free(model);
        free(cnh);
        free(car);
    }
}

void showUsers(char *userTablePath)
{
    FILE *userTable = openFileForReading(userTablePath);
    User user;

    while (fread(&user, sizeof(User), 1, userTable) == TRUE)
    {
        printf("User[name = %s, cnh = %s]\n", user.name, user.cnh);
    }

    fclose(userTable);
}

void showCars(char *carTablePath)
{
    FILE *carTable = openFileForReading(carTablePath);
    Car car;

    while (fread(&car, sizeof(Car), 1, carTable) == TRUE)
    {
        printf("Car[plate = %s; brand= %s; model= %s; year= %d; userCnh= %s]\n", car.plate, car.brand, car.model, car.year, car.userCnh);
    }

    fclose(carTable);
}
// * End of testing functions

int main()
{
    mainMenu();

    return 0;
}
