#include "inventory.h"

Item Inventory[MAX_OBJECTS];


// Function that initializes inventory
void initInventory(){   
    // Set everything as empty aka -1
    for(int i = 0; i < MAX_OBJECTS; i++){
        Inventory[i].id = -1;
        Inventory[i].used = 0;
    }
}


// Function that adds item to inventory
void addItem(int ID, char Name[], char Desc[]){
    // Error checking
    if (ID < 0 || ID >= MAX_OBJECTS) { // Inventory must be available and ID must be from 0-5
        printf("Error: Inventory full or invalid ID.\n");
        return;
    }
    if (Inventory[ID].id != -1) { // Check for invalid slots to prevent overwriting
        printf("Slot %d already occupied by %s.\n", ID, Inventory[ID].name);
        return;
    }
    
    // Add to inventory
    Inventory[ID].id = ID;
    strcpy(Inventory[ID].name, Name);
    strcpy(Inventory[ID].description, Desc);

    // Success output
    printf("You have obtained \x1b[92m[ %s ] !\x1b[0m  \n", Inventory[ID].name);
}


void removeItem(int ID){
    // Error checking
    if (ID < 0 || ID >= MAX_OBJECTS || Inventory[ID].id == -1) {
        printf("No item found at ID %d.\n", ID);
        return;
    }

    // -1 is empty, rest is blank
    Inventory[ID].id = -1;
    strcpy(Inventory[ID].name, "");
    strcpy(Inventory[ID].description, "");
}


// Function that shows inventory (obtained items only)
void printInventory(){
    // Print headers
    printf("===================================================\n");
    printf("                     INVENTORY                     \n");
    printf("===================================================\n");
    printf("| Name       | Description                        |\n");
    printf("|------------+------------------------------------|\n");

    // Print name and description
    for(int i = 0; i < MAX_OBJECTS; i++){
        if (Inventory[i].id != -1){
            printf("| %-10s | %-34s |\n", Inventory[i].name, Inventory[i].description);
        }
    }
    printf("===================================================\n\n");
}