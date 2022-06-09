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

#define USER_CPF_MAXSIZE 15
#define USER_NAME_MAXSIZE 100

#define CAR_CHASSIS_MAXSIZE 20
#define CAR_PLATE_MAXSIZE 15
#define CAR_BRAND_MAXSIZE 100
#define CAR_MODEL_MAXSIZE 100

#define TRUE 1
#define FALSE 0

typedef struct User_struct
{
    char cpf[USER_CPF_MAXSIZE];
    char name[USER_NAME_MAXSIZE];
} User;

typedef struct Car_struct
{
    char chassis[CAR_CHASSIS_MAXSIZE];
    char plate[CAR_PLATE_MAXSIZE];
    char brand[CAR_BRAND_MAXSIZE];
    char model[CAR_MODEL_MAXSIZE];
    char userCpf[USER_CPF_MAXSIZE];
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

User *findUserByCpf(char *cpf)
{
    FILE *userTable = openFileOrCreateForReading(USER_TABLE_PATH);
    User *user = malloc(sizeof(User));

    while (fread(user, sizeof(User), 1, userTable) == TRUE)
    {
        if (strcmp(user->cpf, cpf) == 0)
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

Car *findCarByChassis(char *chassis)
{
    FILE *carTable = openFileOrCreateForReading(CAR_TABLE_PATH);
    Car *car = malloc(sizeof(Car));

    while (fread(car, sizeof(Car), 1, carTable) == TRUE)
    {
        if (strcmp(car->chassis, chassis) == 0)
        {
            fclose(carTable);
            return car;
        }
    }

    fclose(carTable);
    return NULL;
}

User *createUser(char *name, char *cpf)
{
    User *user = (User *)malloc(sizeof(User));
    strcpy(user->name, name);
    strcpy(user->cpf, cpf);
    return user;
}

Car *createCar(char *chassis, char *plate, char *brand, char *model, char *userCpf)
{
    Car *car = (Car *)malloc(sizeof(Car));
    strcpy(car->chassis, chassis);
    strcpy(car->plate, plate);
    strcpy(car->brand, brand);
    strcpy(car->model, model);
    strcpy(car->userCpf, userCpf);
    return car;
}

void saveUser(User *user)
{
    FILE *userTable = appendOrCreateFileForWriting(USER_TABLE_PATH);

    User *userWithSameCpf = findUserByCpf(user->cpf);

    if (userWithSameCpf != NULL)
    {
        printf("User with same CPF already exists.\n");
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
    Car *carWithSameChassis = findCarByChassis(car->chassis);

    if (carWithSamePlate != NULL || carWithSameChassis != NULL)
    {
        printf("Car with same plate or chassis already exists.\n");
        printf("Press ENTER to continue...\n");
        getchar();
        return;
    }

    fwrite(car, sizeof(Car), 1, carTable);
    fclose(carTable);
}

CarNode *findAllCarsByUserCpf(char *userCpf)
{
    FILE *carTable = openFileOrCreateForReading(CAR_TABLE_PATH);

    Car car;
    CarNode *root = NULL;
    CarNode *current = NULL;

    int cont = 0;

    while (fread(&car, sizeof(Car), 1, carTable) == TRUE)
    {
        if (strcmp(car.userCpf, userCpf) == 0)
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

void loginPrompt()
{
    printf("\n\nLogin\n\n");

    char cpf[USER_CPF_MAXSIZE];

    printf("Enter your CPF: \n");
    readString(cpf, USER_CPF_MAXSIZE);

    int success = login(cpf);

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
    char cpf[USER_CPF_MAXSIZE];

    printf("Enter your name: \n");
    readString(name, USER_NAME_MAXSIZE);

    printf("Enter your CPF: \n");
    readString(cpf, USER_CPF_MAXSIZE);

    User *newUser = createUser(name, cpf);

    saveUser(newUser);

    free(newUser);
}

void registerCarPrompt(char *loggedInUserCpf)
{
    printf("\n\nRegistering new car\n\n");

    char brand[CAR_BRAND_MAXSIZE];
    char model[CAR_MODEL_MAXSIZE];
    char chassis[CAR_CHASSIS_MAXSIZE];
    char plate[CAR_PLATE_MAXSIZE];

    printf("Enter the brand: \n");
    readString(brand, CAR_BRAND_MAXSIZE);

    printf("Enter the model: \n");
    readString(model, CAR_MODEL_MAXSIZE);

    printf("Enter the chassis: \n");
    readString(chassis, CAR_CHASSIS_MAXSIZE);

    printf("Enter the plate: \n");
    readString(plate, CAR_PLATE_MAXSIZE);

    Car *newCar = createCar(chassis, plate, brand, model, loggedInUserCpf);

    saveCar(newCar);

    free(newCar);
}

void showAllCarsFromUser(char *loggedInUserCpf)
{
    printf("\n\nCurrent user's cars.\n\n");

    CarNode *root = findAllCarsByUserCpf(loggedInUserCpf);
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
            printf("%d - [Model = %s, Brand = %s, Chassis = %s, Plate = %s]\n", cont, car.model, car.brand, car.chassis, car.plate);
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
            registerCarPrompt(loggedInUser->cpf);
            break;
        case '2':
            showAllCarsFromUser(loggedInUser->cpf);
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
