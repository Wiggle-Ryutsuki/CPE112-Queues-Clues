#include "hashtable.h"

// Global Hash Table Declarations 
LocationHashNode* locationHashTable[HASH_TABLE_SIZE_LOCATIONS];     // Hash table of locations
ItemHashNode* itemHashTable[HASH_TABLE_SIZE_ITEMS];                 // Hash table of items
NPCHashNode* npcHashTable[HASH_TABLE_SIZE_NPCS];                    // Hash table of NPCs

// Generic Hash Function 
// Simple hash function (sum of chars modulo size). 
unsigned int hash(char *key, int table_size) {                      // Arguments are the key (names) and the table Size
    unsigned long hashValue = 0;                                   // Just to be safe
    int i;
    while ((i = *key++))
        // Make hashing case-insensitive by converting to all lowercase
        hashValue += tolower(i);
    return hashValue % table_size;
}

// Location Hash Table Implementation 
// Function to initialize the hash table of locations
void initLocationHashTable() {                                      // No arguments needed
    for (int i = 0; i < HASH_TABLE_SIZE_LOCATIONS; i++)             // Loop through the table, all 40 rows
        locationHashTable[i] = NULL;                                // Make them null for now
}

// Function to insert locations into the hash table
void insertLocation(char* key, Location* value) {                   // Arguments are the key (name), and value (ID)
    if (!key || !value) return;                                     // If Arguments are NOT given, then end function

    unsigned int index = hash(key, HASH_TABLE_SIZE_LOCATIONS);      // Create a hash
    LocationHashNode* newNode = malloc(sizeof(LocationHashNode));   // New Linked List Node
    if (!newNode) {                                                 // If failed, then oops
        printf("Failed to allocate memory for location hash node\n"); 
        return;
    }

    strncpy(newNode->key, key, MaxNameLen - 1);                     // Insert given key; used strncpy to specify size of string...
    newNode->key[MaxNameLen - 1] = '\0';                                // For laziness
    newNode->value = value;                                         // Insert given value
    newNode->next = locationHashTable[index];                       // Insert at the head
    locationHashTable[index] = newNode;                             // New Node Implemented
}

// Function to look up ID in a hash table
Location* lookupLocation(char* key) {                               // Arguments are the names of locations
    if (!key) return NULL;                                          // If arguments are not given, then end function

    unsigned int index = hash(key, HASH_TABLE_SIZE_LOCATIONS);      // Obtain hash
    LocationHashNode* current = locationHashTable[index];           // Create a pointer to travers the linked list

    while (current != NULL) {
        if (strcasecmp(current->key, key) == 0)                     // If we have a match, then...
            return current->value;                                      // return the ID
        current = current->next;                                    // Else keep traversing
    }
    return NULL;                                                    // Not found :((((((
}

// Function to delete the hash table of Locations
void freeLocationHashTable() {                                      // No arguments nedded
    for (int i = 0; i < HASH_TABLE_SIZE_LOCATIONS; i++) {           // Loop through all the rows of the hash table
        LocationHashNode* current = locationHashTable[i];           // Create a pointer to traverse the linked list
        while (current != NULL) {                                   // While pointer isn't NULL, then...
            LocationHashNode* temp = current;                           // Create a temporary pointer for deletion
            current = current->next;                                    // Traverse
            free(temp);                                                 // Delete
        }
        locationHashTable[i] = NULL;                                // I think this is also needed
    }
}

// Item Hash Table Implementation 
// Function to initialize the hash table of items
void initItemHashTable() {                                          // No arguments needed
    for (int i = 0; i < HASH_TABLE_SIZE_ITEMS; i++)                 // Loop through all 10 rows of the hash table
        itemHashTable[i] = NULL;                                    // Make it all NULL for now
}

// Function to insert Items into the hash table
void insertItem(char* key, int value) {                             // Arguments include the name and the ID
     if (!key) return;                                              // If arguments are not given, then end function

    unsigned int index = hash(key, HASH_TABLE_SIZE_ITEMS);          // create a hash
    ItemHashNode* newNode = malloc(sizeof(ItemHashNode));           // Create a new node for linked list
     if (!newNode) {                                                // If failed, then oops
        perror("Failed to allocate memory for item hash node");
        return;
    }

    strncpy(newNode->key, key, MaxNameLen - 1);                     // Insert given key; used strncpy to specify size of string...
    newNode->key[MaxNameLen - 1] = '\0';                                // For laziness
    newNode->value = value;                                         // Insert given value
    newNode->next = itemHashTable[index];                           // Insert at head
    itemHashTable[index] = newNode;                                 // New node is added
}

// Function to look up Item ID given a name
int lookupItem(char* key) {                                         // Argument is just the name
    if (!key) return -1;                                            // If not given, then end function

    unsigned int index = hash(key, HASH_TABLE_SIZE_ITEMS);          // Obtain hash
    ItemHashNode* current = itemHashTable[index];                   // Create a pointer to traverse the linked list

    while (current != NULL) {                                       // While the pointer is not NULL, then...
        if (strcasecmp(current->key, key) == 0)                         // Check if we have a match, if we do, then...
            return current->value;                                          // Return the ID
        current = current->next;                                        // Else, traverse the linked lists
    }
    return -1;                                                      // Not found
}

// Function to delete the hash table
void freeItemHashTable() {                                          // No arguments needed
     for (int i = 0; i < HASH_TABLE_SIZE_ITEMS; i++) {              // Loop through all the rows of the hash table
        ItemHashNode* current = itemHashTable[i];                   // Create a pointer to traverse the linked list
        while (current != NULL) {                                   // While pointer isn't NULL, then...
            ItemHashNode* temp = current;                               // Create a temporary pointer for deletion
            current = current->next;                                    // Traverse
            free(temp);                                                 // Delete
        }
        itemHashTable[i] = NULL;                                    // I think this is also needed
    }
}

// NPC Hash Table Implementation 
// Function to initialize the hash table
void initNPCHashTable() {                                           // No arguments needed
    for (int i = 0; i < HASH_TABLE_SIZE_NPCS; i++)                  // Loop though all 5 rows of the hash table
        npcHashTable[i] = NULL;                                     // Make it all NULL for now
}

// Function to insert NPCs to the hash table
void insertNPC(char* key, int value) {                              // Arguments are the name and ID
     if (!key) return;                                                  // If arguments are not given, then end function

    unsigned int index = hash(key, HASH_TABLE_SIZE_NPCS);           // create a hash
    NPCHashNode* newNode = malloc(sizeof(NPCHashNode));             // Create a new node for linked list
    if (!newNode) {                                                 // If failed, then oops
        perror("Failed to allocate memory for npc hash node");
        return;
    }

    strncpy(newNode->key, key, MaxNameLen - 1);                     // Insert given key; used strncpy to specify size of string...
    newNode->key[MaxNameLen - 1] = '\0';                                // For laziness
    newNode->value = value;                                         // Insert given value
    newNode->next = npcHashTable[index];                            // Insert at head
    npcHashTable[index] = newNode;                                  // New node is added
}

// Function to get NPC id from just a name
int lookupNPC(char* key) {                                          // Argument is just the name
    if (!key) return -1;                                            // If not given, then end function

    unsigned int index = hash(key, HASH_TABLE_SIZE_NPCS);           // Obtain hash
    NPCHashNode* current = npcHashTable[index];                     // Create a pointer to traverse the linked list

    while (current != NULL) {                                       // While the pointer is not NULL, then...
        if (strcasecmp(current->key, key) == 0)                         // Check if we have a match, if we do, then...
            return current->value;                                          // Return the ID
        current = current->next;                                        // Else, traverse the linked lists
    }
    return -1;                                                      // Not found
}

// Delete the hash Table
void freeNPCHashTable() {                                           // No arguments needed
    for (int i = 0; i < HASH_TABLE_SIZE_NPCS; i++) {                // Loop through all the rows of the hash table
        NPCHashNode* current = npcHashTable[i];                     // Create a pointer to traverse the linked list
        while (current != NULL) {                                   // While pointer isn't NULL, then...
            NPCHashNode* temp = current;                                // Create a temporary pointer for deletion
            current = current->next;                                    // Traverse
            free(temp);                                                 // Delete
        }
        npcHashTable[i] = NULL;                                     // I think this is also needed
    }
}