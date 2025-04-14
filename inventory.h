#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <string.h>

#define MAX_OBJECTS 5

typedef struct item {
    int id;
    char name[20];
    char description[1000];
} Item;

extern Item Inventory[MAX_OBJECTS];

void initInventory();
void addItem(int ID, char Name[], char Desc[]);
void removeItem(int ID);
void printInventory();

#endif
