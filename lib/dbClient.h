#ifndef DB_CLIENT_H_INCLUDED
#define DB_CLIENT_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "string.h"

#define USER_TABLE_PATH "userTable.bin"
#define CAR_TABLE_PATH "carTable.bin"

#define USER_CPF_MAXSIZE 15
#define USER_NAME_MAXSIZE 100

#define CAR_CHASSIS_MAXSIZE 20
#define CAR_PLATE_MAXSIZE 15
#define CAR_BRAND_MAXSIZE 100
#define CAR_MODEL_MAXSIZE 100

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

User *createUser(char *name, char *cpf);

Car *createCar(char *chassis, char *plate, char *brand, char *model, char *userCpf);

void saveUser(User *user);

void saveCar(Car *car);

User *findUserByCpf(char *cpf);

Car *findCarByPlate(char *plate);

Car *findCarByChassis(char *chassis);

CarNode *findAllCarsByUserCpf(char *userCpf);

void freeCarsLinkedList(CarNode *root);

#endif