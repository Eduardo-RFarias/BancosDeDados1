#include "dbClient.h"

User *createUser(char *name, unsigned long long cpf)
{
    User *user = (User *)malloc(sizeof(User));
    strcpy(user->name, name);
    user->cpf = cpf;
    return user;
}

Car *createCar(char *chassis, char *plate, char *brand, char *model, unsigned long long userCpf)
{
    Car *car = (Car *)malloc(sizeof(Car));
    strcpy(car->chassis, chassis);
    strcpy(car->plate, plate);
    strcpy(car->brand, brand);
    strcpy(car->model, model);
    car->userCpf = userCpf;
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

User *findUserByCpf(unsigned long long cpf)
{
    FILE *userTable = openFileOrCreateForReading(USER_TABLE_PATH);
    User *user = malloc(sizeof(User));

    while (fread(user, sizeof(User), 1, userTable) == TRUE)
    {
        if (user->cpf == cpf)
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

CarNode *findAllCarsByUserCpf(unsigned long long userCpf)
{
    FILE *carTable = openFileOrCreateForReading(CAR_TABLE_PATH);

    Car car;
    CarNode *root = NULL;
    CarNode *current = NULL;

    int cont = 0;

    while (fread(&car, sizeof(Car), 1, carTable) == TRUE)
    {
        if (car.userCpf == userCpf)
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