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
    FILE *userTable = openFileOrCreateForReadingAndWriting(USER_TABLE_PATH);

    insertUserToTable(user, userTable);

    fclose(userTable);
}

void insertUserToTable(User *user, FILE *userTable)
{
    char isNotEmpty = FALSE;
    char isNotLastOne = FALSE;
    User userRead;

    while (fread(&userRead, sizeof(User), 1, userTable) == TRUE)
    {
        isNotEmpty = TRUE;

        if (userRead.cpf == user->cpf)
        {
            printf("User with same CPF already exists.\n");
            printf("Press ENTER to continue...\n");
            getchar();
            return;
        }
        else if (userRead.cpf > user->cpf)
        {
            isNotLastOne = TRUE;
            fseek(userTable, -sizeof(User), SEEK_CUR);
            break;
        }
    }

    fwrite(user, sizeof(User), 1, userTable);
    fflush(userTable);

    User userRead2;

    while (fread(&userRead2, sizeof(User), 1, userTable) == TRUE)
    {
        fseek(userTable, -sizeof(User), SEEK_CUR);
        fwrite(&userRead, sizeof(User), 1, userTable);
        fflush(userTable);
        userRead = userRead2;
    }

    if (isNotEmpty == TRUE && isNotLastOne == TRUE)
    {
        fwrite(&userRead, sizeof(User), 1, userTable);
        fflush(userTable);
    }
}

void saveCar(Car *car)
{
    FILE *carTable = openFileOrCreateForReadingAndWriting(CAR_TABLE_PATH);

    insertCarToTable(car, carTable);

    fclose(carTable);
}

void insertCarToTable(Car *car, FILE *carTable)
{
    char isNotEmpty = FALSE;
    char isNotLastOne = FALSE;
    Car carRead;

    while (fread(&carRead, sizeof(Car), 1, carTable) == TRUE)
    {
        isNotEmpty = TRUE;

        if (strcmp(carRead.chassis, car->chassis) == 0 || strcmp(carRead.plate, car->plate) == 0)
        {
            printf("Car with the same Chassis or Plate already exists.\n");
            printf("Press ENTER to continue...\n");
            getchar();
            return;
        }
        else if (strcmp(carRead.chassis, car->chassis) > 0)
        {
            isNotLastOne = TRUE;
            fseek(carTable, -sizeof(Car), SEEK_CUR);
            break;
        }
    }

    fwrite(car, sizeof(Car), 1, carTable);
    fflush(carTable);

    Car carRead2;

    while (fread(&carRead2, sizeof(Car), 1, carTable) == TRUE)
    {
        fseek(carTable, -sizeof(Car), SEEK_CUR);
        fwrite(&carRead, sizeof(Car), 1, carTable);
        fflush(carTable);
        carRead = carRead2;
    }

    if (isNotEmpty == TRUE && isNotLastOne == TRUE)
    {
        fwrite(&carRead, sizeof(Car), 1, carTable);
        fflush(carTable);
    }
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