#ifndef DB_CLIENT_H_INCLUDED
#define DB_CLIENT_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "string.h"
#include "limits.h"

#define USER_TABLE_PATH "userTable.bin"
#define CAR_TABLE_PATH "carTable.bin"

#define USER_NAME_MAXSIZE 100

#define CAR_CHASSIS_MAXSIZE 18
#define CAR_PLATE_MAXSIZE 9
#define CAR_BRAND_MAXSIZE 100
#define CAR_MODEL_MAXSIZE 100

typedef struct User_struct
{
    unsigned long long cpf;
    char name[USER_NAME_MAXSIZE];
} User;

typedef struct Car_struct
{
    char chassis[CAR_CHASSIS_MAXSIZE];
    char plate[CAR_PLATE_MAXSIZE];
    char brand[CAR_BRAND_MAXSIZE];
    char model[CAR_MODEL_MAXSIZE];
    unsigned long long userCpf;
} Car;

typedef struct CarNode_struct
{
    Car car;
    struct CarNode_struct *next;
} CarNode;

User *createUser(char *name, unsigned long long cpf);

Car *createCar(char *chassis, char *plate, char *brand, char *model, unsigned long long userCpf);

void saveUser(User *user);

void saveCar(Car *car);

User *findUserByCpf(unsigned long long cpf);

Car *findCarByPlate(char *plate);

Car *findCarByChassis(char *chassis);

CarNode *findAllCarsByUserCpf(unsigned long long userCpf);

void freeCarsLinkedList(CarNode *root);

#endif