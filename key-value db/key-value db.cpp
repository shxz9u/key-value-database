#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MAX_ENTRIES 100
#define MAX_KEY_LEN 50
#define MAX_VALUE_LEN 100

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} keyValue;

keyValue db[MAX_ENTRIES];
int db_size = 0;

void insert(const char key[], const char value[])
{
    if (db_size < MAX_ENTRIES)
    {
        strncpy(db[db_size].key, key, MAX_KEY_LEN - 1);
        strncpy(db[db_size].value, value, MAX_VALUE_LEN - 1);

        db[db_size].key[MAX_KEY_LEN - 1] = '\0';
        db[db_size].value[MAX_VALUE_LEN - 1] = '\0';

        db_size++;

        printf("Inserted : %s = %s\n", key, value);
    }
    else
    {
        printf("Database is full.\n");
    }
}

const char* search(const char key[])
{
    for (int i = 0; i < db_size; i++)
    {
        if (strncmp(db[i].key, key, MAX_KEY_LEN) == 0)
        {
            return db[i].value;
        }
    }
    return NULL;
}

void deleteDB(const char key[])
{
    for (int i = 0; i < db_size; i++)
    {
        if (strncmp(db[i].key, key, MAX_KEY_LEN) == 0)
        {
            for (int j = i; j < db_size - 1; j++)
            {
                db[j] = db[j + 1];
            }
            db_size--;
            printf("Deleted : %s\n", key);
            return;
        }
    }
    printf("Key not found : %s\n", key);
}

void printDB()
{
    if (db_size == 0)
    {
        printf("Database is empty.\n");
        return;
    }

    for (int i = 0; i < db_size; i++)
    {
        printf("Key : %s, Value : %s\n", db[i].key, db[i].value);
    }
}

void showMenu()
{
    printf("\nKey-Value DATABASE\n");
    printf("1. Add data\n");
    printf("2. Search data\n");
    printf("3. Delete data\n");
    printf("4. Show all data\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    int choice;
    char key[MAX_KEY_LEN], value[MAX_VALUE_LEN];

    while (1)
    {
        showMenu();
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            system("cls");

            printf("Enter Key : ");
            fgets(key, MAX_KEY_LEN, stdin);
            key[strcspn(key, "\n")] = '\0';

            printf("Enter Value : ");
            fgets(value, MAX_VALUE_LEN, stdin);
            value[strcspn(value, "\n")] = '\0';

            insert(key, value);
        }
        else if (choice == 2)
        {
            system("cls");

            printf("Enter Key to search : ");
            fgets(key, MAX_KEY_LEN, stdin);
            key[strcspn(key, "\n")] = '\0';

            const char* result = search(key);

            if (result)
            {
                printf("Value : %s\n", result);
            }
            else
            {
                printf("Key not found.\n");
            }
        }
        else if (choice == 3)
        {
            system("cls");

            printf("Enter key to delete : ");
            fgets(key, MAX_KEY_LEN, stdin);
            key[strcspn(key, "\n")] = '\0';

            deleteDB(key);
        }
        else if (choice == 4)
        {
            system("cls");

            printDB();
        }
        else if (choice == 5)
        {
            system("cls");

            printf("Exiting...\n");
            return 0;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}