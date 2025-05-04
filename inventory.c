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


void printInventory(){
    int maxWIDTH = 91;
    int maxNameLen = 4; // To at least fit "Name" for header.
    int maxDescLen = 11; // To at least fit "Description" for header.
    for (int i = 0; i < MAX_OBJECTS; i++){
        int nLen = strlen(Inventory[i].name);
        int dLen = strlen(Inventory[i].description);

        if (nLen > maxNameLen) {
            maxNameLen = nLen;
        }
        if (dLen > maxDescLen) {
            maxDescLen = dLen;
        }
    }

    int totalWidth = maxNameLen + maxDescLen + 7;

    // Printing title and headers
    if (totalWidth <= maxWIDTH){
        for (int i = 0; i < totalWidth; i++){
            printf("=");
        } printf("\n");

        int padding = (totalWidth - 9) / 2;
        for (int i = 0; i < padding; i++){
            printf(" ");
        } printf("INVENTORY\n");

        for (int i = 0; i < totalWidth; i++){
            printf("=");
        } printf("\n");

        // Printing headings
        printf("| %-*s | %-*s |\n", maxNameLen, "Name", maxDescLen, "Description");

        // Printing separators
        printf("|");
        for (int i = 0; i < maxNameLen + 2; i++) {
            printf("-");
        }
        printf("+");
        for (int i = 0; i < maxDescLen + 2; i++) {
            printf("-");
        } 
        printf("|\n");
    } else {
        maxDescLen = maxWIDTH - maxNameLen - 7;
        totalWidth = maxWIDTH;

        for (int i = 0; i < totalWidth; i++){
            printf("=");
        } printf("\n");
    
        int padding = (totalWidth - 9) / 2;
        for (int i = 0; i < padding; i++){
            printf(" ");
        } printf("INVENTORY\n");
    
        for (int i = 0; i < totalWidth; i++){
            printf("=");
        } printf("\n");
    
        // Printing headings
        printf("| %-*s | %-*s |\n", maxNameLen, "Name", maxDescLen, "Description");
    
        // Printing separators
        printf("|");
        for (int i = 0; i < maxNameLen + 2; i++) {
            printf("-");
        }
        printf("+");
        for (int i = 0; i < maxDescLen + 2; i++) {
            printf("-");
        } 
        printf("|\n");
    }

    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (Inventory[i].id != -1) {
            char desc = Inventory[i].description;
            int descLen = strlen(desc);
            int printed = 0;
    
            printf("| %-*s | %-*.*s |\n", maxNameLen, Inventory[i].name, maxDescLen, maxDescLen, desc);
            printed += maxDescLen;
    
            while (printed < descLen) {
                printf("| %-*s |%-*.*s  |\n", maxNameLen, "", maxDescLen, maxDescLen, desc + printed);
                printed += maxDescLen;
            }
        }
    }

    //Print bottom border
    for (int i = 0; i < totalWidth; i++) {
        printf("=");
    } printf("\n\n");
}