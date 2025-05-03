#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "world.h"      // For Location*
#include "inventory.h"  // For Items
#include <ctype.h>      // for toLower
#include <strings.h>    // For strcasecmp 


// Configuration 
// Table sizes
#define HASH_TABLE_SIZE_LOCATIONS 40            // 27 locations so lets have 40
#define HASH_TABLE_SIZE_ITEMS 10                // 5 Items, but try with 10
#define HASH_TABLE_SIZE_NPCS 5                  // 3 NPCs, but y'know

// Location Hash Table 
typedef struct LocationHashNode {
    char key[MaxNameLen];                       // key of length 50
    Location* value;                            // Store pointer to the actual Location
    struct LocationHashNode* next;              // It's a linked list for chaining method
} LocationHashNode;

extern LocationHashNode* locationHashTable[HASH_TABLE_SIZE_LOCATIONS];  // Hash table for 40 locations, declared here, DON'T DECLARE AGAIN

void initLocationHashTable();                                           // Initialize the Hash Table for locations
void insertLocation(char* key, Location* value);                  // Insert a location into the hash table
Location* lookupLocation(char* key);                              // Find locations ID just by typing in the names
void freeLocationHashTable();                                           // Delete the hash table

// Item Hash Table 
typedef struct ItemHashNode {
    char key[MaxNameLen];                       // Use MaxNameLen for consistency, though item names are shorter
    int value;                                  // Store the Item ID
    struct ItemHashNode* next;                  // Same with the linked lists
} ItemHashNode;

extern ItemHashNode* itemHashTable[HASH_TABLE_SIZE_ITEMS];              // Hash table for 10 items, declared here, DON'T DECLARE AGAIN

void initItemHashTable();                                               // Initialize the hash table for items
void insertItem(char* key, int value);                            // Insert an item into the hash table
int lookupItem(char* key);                                        // Find Item ID just by typing in the names
void freeItemHashTable();                                               // Delete the hash table


// NPC Hash Table
typedef struct NPCHashNode {
    char key[MaxNameLen];                       // People can have long names
    int value;                                  // Store the NPC ID
    struct NPCHashNode* next;                   // Still a linked list
} NPCHashNode;

extern NPCHashNode* npcHashTable[HASH_TABLE_SIZE_NPCS];                 // Hash table for 5 NPCs, declared here, DON'T DECLARE AGAIN

void initNPCHashTable();                                                // Initialize the hash table for NPCs
void insertNPC(char* key, int value);                             // Insert an NPC into the hash table
int lookupNPC(char* key);                                         // Find NPC id just by typing in the names
void freeNPCHashTable();                                                // Delete the hash Table


#endif 