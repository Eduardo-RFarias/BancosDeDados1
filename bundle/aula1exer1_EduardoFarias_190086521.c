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

/**
 * The user struct stores the user cpf and name.
 * The cpf is unique among the users.
 */
typedef struct User_struct
{
    char cpf[USER_CPF_MAXSIZE];
    char name[USER_NAME_MAXSIZE];
} User;

/**
 * The car struct stores the car chassis, plate, brand and model.
 * The car chassis and plate are unique among the cars.
 */
typedef struct Car_struct
{
    char chassis[CAR_CHASSIS_MAXSIZE];
    char plate[CAR_PLATE_MAXSIZE];
    char brand[CAR_BRAND_MAXSIZE];
    char model[CAR_MODEL_MAXSIZE];
    char userCpf[USER_CPF_MAXSIZE];
} Car;

/**
 * The CarNode struct represents a node in a linked list of cars.
 * The car field stores the car data, the next field stores the pointer to the next item.
 */
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

    // Remove the newline character from the string
    destiny[strlen(destiny) - 1] = '\0';
}

/**
 * Query for an user with the given cpf.
 *
 * @param cpf
 * @return A pointer to an User (Do not forget to free it)
 */
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

/**
 * Query for a car with the given plate.
 *
 * @param plate
 * @return A pointer to a Car (Do not forget to free it)
 */
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

/**
 * Query for a car with the given chassis.
 *
 * @param chassis
 * @return A pointer to a Car (Do not forget to free it)
 */
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

    // Query for an user with the same CPF
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

    // Query for a car with the same plate
    Car *carWithSamePlate = findCarByPlate(car->plate);
    // Query for a car with the same chassis
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

/**
 * Query for the cars which belongs to an user with the given CPF.
 * The cars are stored in a linked list,
 * so you can iterate through them using the next field.
 * The last element of the list will have a NULL next field.
 * Do not forget to free the list using the freeCarsLinkedList function.
 *
 * @param userCpf
 * @return A pointer to the root of the linked list of cars
 */
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

/**
 * Log in the user with the given CPF.
 * Login works by writing the user's cpf in a session file.
 * If the file is empty, the user is logged out.
 *
 * @param cpf
 * @return int (1 if the login was successful, 0 otherwise)
 */
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

/**
 * Logout works by emptying the session file.
 */
void logout()
{
    FILE *loginFile = overrideOrCreateFileForWriting(LOGIN_FILE_PATH);
    fclose(loginFile);
}

/**
 * Get the Logged In User by reading the session file.
 * If the file is empty, the function will return NULL.
 *
 * @return A pointer to User (Do not forget to free it)
 */
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

/**
 * Check if the user is logged in by reading the session file.
 * If the file is empty, the user is not logged in.
 *
 * @return int (1 if the user is logged in, 0 otherwise)
 */
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
