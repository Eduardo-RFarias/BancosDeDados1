/*
Author : Eduardo Rodrigues de Farias
June 8th, 2022

Universidade de Brasília, UNB

FGA0137 - SISTEMAS DE BANCO DE DADOS 1 - T01 - 2022/1
Aula 1 - Exercício 1
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define USER_TABLE_PATH "userTable.bin"
#define CAR_TABLE_PATH "carTable.bin"

// ! Structs
typedef struct User_struct
{
    char cnh[12];
    char name[100];
} User;

typedef struct Car_struct
{
    char plate[9];
    char brand[100];
    char model[100];
    int year;
    char userCnh[12];
} Car;

typedef struct CarList_struct
{
    Car *cars;
    int size;
} CarList;
// ! End of Structs

// ? Auxiliary Functions
FILE *appendOrCreateFileForWriting(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "ab");

    if (file != NULL)
    {
        return file;
    }

    file = fopen(fileName, "wb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

FILE *openFileForReading(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "rb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}
// ? End of Auxiliary Functions

// ! CRUD Functions
// Models
User *createUser(char *name, char *cnh)
{
    User *user = (User *)malloc(sizeof(User));
    strcpy(user->name, name);
    strcpy(user->cnh, cnh);
    return user;
}

Car *createCar(char *plate, char *brand, char *model, int year, char *userCnh)
{
    Car *car = (Car *)malloc(sizeof(Car));
    strcpy(car->plate, plate);
    strcpy(car->brand, brand);
    strcpy(car->model, model);
    car->year = year;
    strcpy(car->userCnh, userCnh);
    return car;
}

// Inserts
// TODO: Implement unique constraint in CNH
void saveUser(User *user)
{
    FILE *userTable = appendOrCreateFileForWriting(USER_TABLE_PATH);
    fwrite(user, sizeof(User), 1, userTable);
    fclose(userTable);
}

// TODO: Implement unique constraint in PLATE
void saveCar(Car *car)
{
    FILE *carTable = appendOrCreateFileForWriting(CAR_TABLE_PATH);
    fwrite(car, sizeof(Car), 1, carTable);
    fclose(carTable);
}

// Searches
User *findUserByCnh(char *cnh)
{
    FILE *userTable = openFileForReading(USER_TABLE_PATH);
    User *user = malloc(sizeof(User));

    while (fread(user, 1, sizeof(User), userTable) == sizeof(User))
    {
        if (strcmp(user->cnh, cnh) == 0)
        {
            fclose(userTable);
            return user;
        }
    }

    fclose(userTable);
    return NULL;
}

Car *findCarByPlate(char *plate)
{
    FILE *carTable = openFileForReading(CAR_TABLE_PATH);
    Car *car = malloc(sizeof(Car));

    while (fread(car, 1, sizeof(Car), carTable) == sizeof(Car))
    {
        if (strcmp(car->plate, plate) == 0)
        {
            fclose(carTable);
            return car;
        }
    }

    fclose(carTable);
    return NULL;
}

Car *findFirstCarByUserCnh(char *userCnh)
{
    FILE *carTable = openFileForReading(CAR_TABLE_PATH);
    Car *car = malloc(sizeof(Car));

    while (fread(car, 1, sizeof(Car), carTable) == sizeof(Car))
    {
        if (strcmp(car->userCnh, userCnh) == 0)
        {
            fclose(carTable);
            return car;
        }
    }

    fclose(carTable);
    return NULL;
}

CarList *findAllCarsByUserCnh(char *userCnh)
{
    FILE *carTable = openFileForReading(CAR_TABLE_PATH);
    Car car;
    Car *carList; // TODO: Implement linked list
    int i = 0;

    while (fread(&car, 1, sizeof(Car), carTable) == sizeof(Car))
    {
        if (strcmp(car.userCnh, userCnh) == 0)
        {
            carList[i] = car;
            i++;
        }
    }

    fclose(carTable);

    CarList *carListStruct = malloc(sizeof(CarList));
    carListStruct->cars = carList;
    carListStruct->size = i;

    return carListStruct;
}
// ! End of CRUD Functions

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

void preRegister(char *userTablePath, char *carTablePath)
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

    while (fread(&user, 1, sizeof(User), userTable) == sizeof(User))
    {
        printf("User[name = %s, cnh = %s]\n", user.name, user.cnh);
    }

    fclose(userTable);
}

void showCars(char *carTablePath)
{
    FILE *carTable = openFileForReading(carTablePath);
    Car car;

    while (fread(&car, 1, sizeof(Car), carTable) == sizeof(Car))
    {
        printf("Car[plate = %s; brand= %s; model= %s; year= %d; userCnh= %s]\n", car.plate, car.brand, car.model, car.year, car.userCnh);
    }

    fclose(carTable);
}
// * End of testing functions

int main()
{
    //
    char userTablePath[14];
    char carTablePath[13];
    strcpy(userTablePath, USER_TABLE_PATH);
    strcpy(carTablePath, CAR_TABLE_PATH);

    //
    User *user = createUser("Joao", "12345678901");
    saveUser(user);
    free(user);

    user = findUserByCnh("12345678901");

    if (user != NULL)
    {
        printf("User[name = %s, cnh = %s]\n", user->name, user->cnh);
    }

    free(user);

    printf("\n");

    //
    Car *car = createCar("ABC-1234", "Ford", "Fiesta", 2020, "12345678901");
    saveCar(car);
    free(car);

    car = findCarByPlate("ABC-1234");

    if (user != NULL)
    {
        printf("Car[plate = %s; brand= %s; model= %s; year= %d; userCnh= %s]\n", car->plate, car->brand, car->model, car->year, car->userCnh);
    }

    free(car);

    printf("\n");

    //

    showCars(carTablePath);
    return 0;
}
