#include "dbClient.h"

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
    FILE *carTable = openFileForReading(CAR_TABLE_PATH);
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

Car *findFirstCarByUserCnh(char *userCnh)
{
    FILE *carTable = openFileForReading(CAR_TABLE_PATH);
    Car *car = malloc(sizeof(Car));

    while (fread(car, sizeof(Car), 1, carTable) == TRUE)
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

CarNode *findAllCarsByUserCnh(char *userCnh)
{
    FILE *carTable = openFileForReading(CAR_TABLE_PATH);

    Car car;
    CarNode *root;
    CarNode *current;

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