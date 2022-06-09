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

#define LOGIN_FILE_PATH "sessionTable.bin"
#define USER_TABLE_PATH "userTable.bin"
#define CAR_TABLE_PATH "carTable.bin"

#define USER_CNH_MAXSIZE 15
#define USER_NAME_MAXSIZE 100

#define CAR_PLATE_MAXSIZE 15
#define CAR_BRAND_MAXSIZE 100
#define CAR_MODEL_MAXSIZE 100

#define TRUE 1
#define FALSE 0

typedef struct User_struct
{
    char cnh[USER_CNH_MAXSIZE];
    char name[USER_NAME_MAXSIZE];
} User;

typedef struct Car_struct
{
    char plate[CAR_PLATE_MAXSIZE];
    char brand[CAR_BRAND_MAXSIZE];
    char model[CAR_MODEL_MAXSIZE];
    int year;
    char userCnh[USER_CNH_MAXSIZE];
} Car;

typedef struct CarNode_struct
{
    Car car;
    struct CarNode_struct *next;
} CarNode;

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

FILE *openFileOrCreateForReading(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "rb");

    if (file != NULL)
    {
        return file;
    }

    file = fopen(fileName, "wb");

    if (file == NULL)
    {
        printf("Error creating file!\n");
        exit(1);
    }

    fclose(file);

    file = fopen(fileName, "rb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

FILE *overrideOrCreateFileForWriting(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "wb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

void clearTerminal()
{
#if defined(_linux) || defined(unix) || defined(APPLE_)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void readString(char *destiny, int MAXSIZE)
{
    fgets(destiny, MAXSIZE, stdin);
    destiny[strlen(destiny) - 1] = '\0';
}

User *findUserByCnh(char *cnh)
{
    FILE *userTable = openFileOrCreateForReading(USER_TABLE_PATH);
    User *user = malloc(sizeof(User));

    while (fread(user, sizeof(User), 1, userTable) == TRUE)
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
    FILE *carTable = openFileOrCreateForReading(CAR_TABLE_PATH);
    Car *car = malloc(sizeof(Car));

    while (fread(car, sizeof(Car), 1, carTable) == TRUE)
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

void saveUser(User *user)
{
    FILE *userTable = appendOrCreateFileForWriting(USER_TABLE_PATH);

    User *userWithSameCnh = findUserByCnh(user->cnh);

    if (userWithSameCnh != NULL)
    {
        printf("User with same CNH already exists.\n");
        printf("Press ENTER to continue...\n");
        getchar();
        return;
    }

    fwrite(user, sizeof(User), 1, userTable);
    fclose(userTable);
}

void saveCar(Car *car)
{
    FILE *carTable = appendOrCreateFileForWriting(CAR_TABLE_PATH);

    Car *carWithSamePlate = findCarByPlate(car->plate);

    if (carWithSamePlate != NULL)
    {
        printf("Car with same plate already exists.\n");
        printf("Press ENTER to continue...\n");
        getchar();
        return;
    }

    fwrite(car, sizeof(Car), 1, carTable);
    fclose(carTable);
}

CarNode *findAllCarsByUserCnh(char *userCnh)
{
    FILE *carTable = openFileOrCreateForReading(CAR_TABLE_PATH);

    Car car;
    CarNode *root = NULL;
    CarNode *current = NULL;

    int cont = 0;

    while (fread(&car, sizeof(Car), 1, carTable) == TRUE)
    {
        if (strcmp(car.userCnh, userCnh) == 0)
        {
            if (cont == 0)
            {
                root = (CarNode *)malloc(sizeof(CarNode));
                root->car = car;
                root->next = NULL;
                current = root;
            }
            else
            {
                current->next = (CarNode *)malloc(sizeof(CarNode));
                current->next->car = car;
                current->next->next = NULL;
                current = current->next;
            }

            cont++;
        }
    }

    fclose(carTable);

    return root;
}

void freeCarsLinkedList(CarNode *root)
{
    CarNode *current = root;
    CarNode *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int login(char *cnh)
{
    FILE *loginFile = overrideOrCreateFileForWriting(LOGIN_FILE_PATH);
    FILE *userTable = openFileOrCreateForReading(USER_TABLE_PATH);

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

void loginPrompt()
{
    printf("\n\nLogin\n\n");

    char cnh[USER_CNH_MAXSIZE];

    printf("Enter your CNH: \n");
    readString(cnh, USER_CNH_MAXSIZE);

    int success = login(cnh);

    if (success == FALSE)
    {
        printf("\n\nLogin failed! Try again later.\n");
        printf("Press ENTER to continue...\n");
        getchar();
    }
}

void registerUserPrompt()
{
    printf("\n\nRegistering a new user\n\n");

    char name[USER_NAME_MAXSIZE];
    char cnh[USER_CNH_MAXSIZE];

    printf("Enter your name: \n");
    readString(name, USER_NAME_MAXSIZE);

    printf("Enter your CNH: \n");
    readString(cnh, USER_CNH_MAXSIZE);

    User *newUser = createUser(name, cnh);

    saveUser(newUser);

    free(newUser);
}

void registerCarPrompt(char *loggedInUserCnh)
{
    printf("\n\nRegistering new car\n\n");

    char plate[CAR_PLATE_MAXSIZE];
    char brand[CAR_BRAND_MAXSIZE];
    char model[CAR_MODEL_MAXSIZE];
    int year;

    printf("Enter the brand: \n");
    readString(brand, CAR_BRAND_MAXSIZE);

    printf("Enter the model: \n");
    readString(model, CAR_MODEL_MAXSIZE);

    printf("Enter the year: \n");
    scanf("%d", &year);
    getchar();

    printf("Enter the plate: \n");
    readString(plate, CAR_PLATE_MAXSIZE);

    Car *newCar = createCar(plate, brand, model, year, loggedInUserCnh);

    saveCar(newCar);

    free(newCar);
}

void showAllCarsFromUser(char *loggedInUserCnh)
{
    printf("\n\nCurrent user's cars.\n\n");

    CarNode *root = findAllCarsByUserCnh(loggedInUserCnh);
    CarNode *current = root;

    int cont = 1;

    if (current == NULL)
    {
        printf("You don't have any cars registered!\n");
    }
    else
    {
        while (current != NULL)
        {
            Car car = current->car;
            printf("%d - [Model = %s, Brand = %s, Year = %d, Plate = %s]\n", cont, car.model, car.brand, car.year, car.plate);
            current = current->next;

            cont++;
        }
    }

    freeCarsLinkedList(root);

    printf("\n\nPress ENTER to continue...\n");
    getchar();
}

int notLoggedInMenu()
{
    char choice;

    do
    {
        clearTerminal();

        printf("Main Menu\n\n");
        printf("You are not logged in! Please log-in or register a new user.\n\n");
        printf("1. Login\n");
        printf("2. Sign-up\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: \n");
        scanf("%c", &choice);
        getchar();

        switch (choice)
        {
        case '1':
            loginPrompt();
            return FALSE;
        case '2':
            registerUserPrompt();
            break;
        case '0':
            return TRUE;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (TRUE);
}

int loggedInMenu()
{
    char choice;
    User *loggedInUser = getLoggedInUser();

    do
    {
        clearTerminal();

        printf("Main Menu\n\n");
        printf("Welcome %s!\n\n", loggedInUser->name);
        printf("1. Register new Car\n");
        printf("2. View Cars\n");
        printf("3. Log out\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: \n");
        scanf("%c", &choice);
        getchar();

        switch (choice)
        {
        case '1':
            registerCarPrompt(loggedInUser->cnh);
            break;
        case '2':
            showAllCarsFromUser(loggedInUser->cnh);
            break;
        case '3':
            logout();
            free(loggedInUser);
            return FALSE;
        case '0':
            free(loggedInUser);
            return TRUE;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (TRUE);
}

void mainMenu()
{
    int exit;

    do
    {
        if (isLoggedIn() == FALSE)
        {
            exit = notLoggedInMenu();
        }
        else
        {
            exit = loggedInMenu();
        }
    } while (exit == FALSE);
}

int main()
{
    mainMenu();
    return 0;
}
