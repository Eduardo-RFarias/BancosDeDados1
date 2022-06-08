#ifndef DB_CLIENT_H_INCLUDED
#define DB_CLIENT_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "string.h"

#define USER_TABLE_PATH "userTable.bin"
#define CAR_TABLE_PATH "carTable.bin"

#define USER_CNH_MAXSIZE 15
#define USER_NAME_MAXSIZE 100

#define CAR_PLATE_MAXSIZE 15
#define CAR_BRAND_MAXSIZE 100
#define CAR_MODEL_MAXSIZE 100

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

User *createUser(char *name, char *cnh);

Car *createCar(char *plate, char *brand, char *model, int year, char *userCnh);

void saveUser(User *user);

void saveCar(Car *car);

User *findUserByCnh(char *cnh);

Car *findCarByPlate(char *plate);

Car *findFirstCarByUserCnh(char *userCnh);

CarNode *findAllCarsByUserCnh(char *userCnh);

void freeCarsLinkedList(CarNode *root);

#endif