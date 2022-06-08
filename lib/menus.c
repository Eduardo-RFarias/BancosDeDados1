#include "menus.h"

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

void loginPrompt()
{
    printf("\n\nLogin\n\n");

    char cnh[USER_CNH_MAXSIZE];

    printf("Enter your CNH: \n");
    readString(cnh, USER_CNH_MAXSIZE);
    cnh[strlen(cnh) - 1] = '\0';

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
    name[strlen(name) - 1] = '\0';

    printf("Enter your CNH: \n");
    readString(cnh, USER_CNH_MAXSIZE);
    cnh[strlen(cnh) - 1] = '\0';

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
    brand[strlen(brand) - 1] = '\0';

    printf("Enter the model: \n");
    readString(model, CAR_MODEL_MAXSIZE);
    model[strlen(model) - 1] = '\0';

    printf("Enter the year: \n");
    scanf("%d", &year);
    getchar();

    printf("Enter the plate: \n");
    readString(plate, CAR_PLATE_MAXSIZE);
    plate[strlen(plate) - 1] = '\0';

    Car *newCar = createCar(plate, brand, model, year, loggedInUserCnh);

    saveCar(newCar);

    free(newCar);
}
