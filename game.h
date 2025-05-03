#ifndef GAME_H
#define GAME_H

#include <stdio.h>          // The basics
#include <stdlib.h>         // Memory Allocation
#include <string.h>         // For string copy and compare
#include <strings.h>        // For strcasecmp (case-insensitive compare)
#include <time.h>           // For the time score later
#include <windows.h>        // WHY DOESN'T WINDOWS KNOW WHAT UTF-8 ISSSSSSSSSSSSSSSSSSsss >:((((
#include "inventory.h"      // The inventory system
#include "world.h"          // The graph
#include "history.h"        // The stack
#include "asciiart.h"       // The ASCII art
#include "hashtable.h"      // The hash table

// ANSI Color Codes
// For more Finesse
#define AnsiColorReset "\x1b[0m"    // Reset
#define AnsiBold "\x1b[1m"          // Bold/Bright text
#define AnsiColorBlack "\x1b[30m"   // Black
#define AnsiColorRed "\x1b[31m"     // Red
#define AnsiColorGreen "\x1b[32m"   // Green
#define AnsiColorYellow "\x1b[33m"  // Yellow
#define AnsiColorBlue "\x1b[34m"    // Blue
#define AnsiColorMagenta "\x1b[35m" // Magenta
#define AnsiColorCyan "\x1b[36m"    // Cyan

// Bright versions
#define AnsiBrightBlack "\x1b[90m"  // Grey
#define AnsiBrightRed "\x1b[91m"    // Bright Red
#define AnsiBrightGreen "\x1b[92m"  // Bright Green
#define AnsiBrightYellow "\x1b[93m" // Bright Yellow
#define AnsiBrightBlue "\x1b[94m"   // Bright Blue
#define AnsiBrightMagenta "\x1b[95m"// Bright magenta
#define AnsiBrightCyan "\x1b[96m"   // Bright Cyan

// Player Data Structure
typedef struct Player{
    Location *currentLocation;  // Pointer to the player's current location in the graph
    int moveCount;              // Counter for total moves made
    int clearanceLevel;         // Allows the player to pass certain areas
    int metThugs;               // A check for later in the game
} Player;

// NPC Data structure
typedef struct NPC{
    int id;                 // NPC's Identification
    char name[MaxNameLen];  // NPC's Name
} NPC;

// Function Prototypes
// Game functions
void initializeGame(Graph *graph, Player *player);                      // Create the game world
void displayLocation(Player *player);                                   // Function to print out location name
void lookAround(Player *player);                                        // Function to re-display the location's name and description and also give hints
void movePlayer(Graph *graph, Player *player, char *direction);         // Function to traverse the player around the graph (game world)
void goBack(Graph *graph, Player *player);                              // Function to traverse to a previous node in the graph
void displayInstructions();                                             // Function to display instructions, like how to move and interact
void talkTo(Player *player, char *name);
void useItem(Graph *graph, Player *player, char *item);                 // Function to allow player to use items
void trimTrailingWhitespace(char *str);                                 // Helper Function to trim trailing white space
void clearInputBuffer();                                                // Helper Function to clear the input buffer

#endif