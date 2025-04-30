// Muhammad Asad Aziz 67070503472
#include <stdio.h>          // The basics
#include <stdlib.h>         // Memory Allocation
#include <string.h>         // For string copy and compare
#include <strings.h>        // For strcasecmp (case-insensitive compare)
#include <time.h>           // For the time score later
#include "inventory.h"      // The inventory system
#include "world.h"          // The graph
#include "history.h"        // The stack
#include "asciiart.h"       // The ASCII art

// ANSI Color Codes
// For more Finesse
// Just Realized that this doesn't work on Window's cmd :((((((((((((((((((
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
typedef struct Player
{
    Location *currentLocation;  // Pointer to the player's current location in the graph
    int moveCount;              // Counter for total moves made
    int clearanceLevel;         // Allows the player to pass certain areas
    int metThugs;               // A check for later in the game
} Player;

// NPC Data structure
typedef struct NPC
{
    int id;                 // NPC's Identification
    char name[MaxNameLen];  // NPC's Name
} NPC;

// Lazy global array
NPC NPCs[3];                // List of NPCs

// Item IDs
#define ITEM_NONE -1        // -1 means nothing
#define ITEM_HONEY 0        // 0 means Honey
#define ITEM_LUNCHBOX 1     // 1 means Lunch box
#define ITEM_SILVER_KEY 2   // 2 means Silver key
#define ITEM_RUSTY_KEY 3    // 3 means Rusty key
#define ITEM_CIGARETTES 4   // 4 means Cigarettes

// NPC IDs 
#define NPC_NONE -1         // -1 still means nothing
#define NPC_FARMER 0        // 0 means farmer
#define NPC_HUNGRY_PERSON 1 // 1 means hungry NPC
#define NPC_THUGS 2         // 2 means Thugs

// Function Prototypes
// Game functions
void initializeGame(Graph *graph, Player *player);                      // Create the game world
void displayLocation(Player *player);                                   // Function to print out location name
void lookAround(Player *player);                                        // Function to re-display the location's name and description and also give hints
void movePlayer(Graph *graph, Player *player, char *direction);         // Function to traverse the player around the graph (game world)
void goBack(Graph *graph, Player *player);                              // Function to traverse to a previous node in the graph
void displayInstructions();                                             // Function to display instructions, like how to move and interact
void useItem(Graph *graph, Player *player, char *item);                 // Function to allow player to use items
void trimTrailingWhitespace(char *str);                                 // Helper Function to trim trailing white space
void clearInputBuffer();                                                // Helper Function to clear the input buffer

/* ***************************** */
/* Game Functions Implementation */
/* ***************************** */

// Function to start the game
void initializeGame(Graph *graph, Player *player)
{ // Arguments are the graph (game world) and the player
    // Add locations, SO CUSTOMIZABLE!!!!!
    // !REMINDER                |graph| |ID| |NAME|         |Description|!
    Location *loc0 = addLocation(graph, 0, "Your House", "Cozy, familiar, but your cat is missing! The only way out is the 'village'.");
    Location *loc1 = addLocation(graph, 1, "Village Square", "Bustling with activity. Paths lead to the 'farm', and the 'forest'.");
    Location *loc2 = addLocation(graph, 2, "Old MacDonald's Farm", "Smells like... farm. A friendly farmer is here. You can only go 'back' to the village.");
    Location *loc3 = addLocation(graph, 3, "Forest Entrance", "Tall trees loom ominously. It looks dark, and you hear something growling... There are paths leading 'deeper' (1), towards the 'growl' (2), to a 'crossroads' (3), or 'back' to the village.");
    Location *loc4 = addLocation(graph, 4, "Forest Dead End (Path 1)", "The path ends abruptly at a thick wall of thorns. Only way is 'back'.");
    Location *loc5 = addLocation(graph, 5, "Cave Entrance (Bear)", "A large, grumpy bear blocks the cave entrance! It seems agitated. Maybe something sweet would calm it? You can 'approach' the cave or go 'back' to the forest entrance.");
    Location *loc6 = addLocation(graph, 6, "Forest Crossroads", "Several paths diverge here. One seems 'overgrown' (1), another has 'scraps' (2), a third looks 'well-trodden' (3). You can also go 'back' towards the forest entrance.");
    Location *loc7 = addLocation(graph, 7, "Forest Dead End (Overgrown Path)", "Vines and bushes block the way completely. You have to go 'back'.");
    Location *loc8 = addLocation(graph, 8, "Forest Dead End (Scraps)", "Hmm, looks like someone had lunch here recently. Hey, a discarded lunch box! Only way is 'back'.");
    Location *loc9 = addLocation(graph, 9, "Forest Dead End (Well-Trodden)", "The path ends at a steep cliff face. Too dangerous to climb. Go 'back'.");

    Location *loc10 = addLocation(graph, 10, "Cave Entrance (Bear)", "You approched the bear slowly, but it felt threatened. Sadly, the bear mauled you..."); // Game over text for now
    Location *loc11 = addLocation(graph, 11, "Caverns - Left Fork", "The passage splits here. One way goes 'left' deeper, the other goes 'right' towards a faint glint. You can also head 'back' to the main chamber.");
    Location *loc12 = addLocation(graph, 12, "Caverns - Left Dead End", "The tunnel ends in a pile of rubble. Nothing here. Go 'back'.");
    Location *loc13 = addLocation(graph, 13, "Caverns - Right Dead End (Glint)", "Wedged in a crack is a shiny Silver Key! You take it. Head 'back'.");
    Location *loc14 = addLocation(graph, 14, "Caverns - Right Fork", "The path continues 'right' towards another junction and 'across' towards a passage. You can go 'back' to the main chamber.");
    Location *loc15 = addLocation(graph, 15, "Caverns - Trap!", "Oh no! The clicking sound was a pressure plate! Darts shoot from the walls!"); // Game over location
    Location *loc16 = addLocation(graph, 16, "Caverns - Crossroads", "Another junction. One path looks like a 'dead end' (1), another has a some 'rubble' (2), and the third leads to a sturdy looking 'door'. You can go 'back' to the previous fork.");
    Location *loc17 = addLocation(graph, 17, "Caverns - Dead End", "Just cold, damp rock. Go 'back'.");
    Location *loc18 = addLocation(graph, 18, "Caverns - Dead End (Rusty Key)", "You find a rusty, crooked key. It doesn't look very useful. Go 'back'.");
    Location *loc19 = addLocation(graph, 19, "Caverns - Locked Door", "A heavy silver door blocks the way. It has a silver lock. You could try to 'open door', or go 'back' to the crossroads.");

    Location *loc20 = addLocation(graph, 20, "Underground City - Entrance Plaza", "Wow! A hidden city beneath the earth! Dimly lit streets stretch before you. You can take the main 'road' or duck into a narrow 'alley'. You can also go 'back' through the door.");
    Location *loc21 = addLocation(graph, 21, "Underground City - Alleyway", "Dark and grimy. A group of tough-looking characters eye you suspiciously. They block the way forward. Maybe offer them something? You can try to 'leave' or go 'back' to the plaza.");
    Location *loc22 = addLocation(graph, 22, "Underground City - Road Fork", "The main road splits here. Going 'right' leads towards a residential area. Going 'left' heads towards what looks like a storefront. You can go 'back' to the plaza.");
    Location *loc23 = addLocation(graph, 23, "Underground City - Your Cat!", "There it is! Your furry friend is safe and sound, purring on a windowsill! YOU WIN!"); // WIN!
    Location *loc24 = addLocation(graph, 24, "Underground City - Storefront", "A small, dimly lit store. You could 'enter store' or check the 'back alley'. Or go 'back' to the road fork.");
    Location *loc25 = addLocation(graph, 25, "Underground City - Inside Store", "Dusty shelves line the walls. The shopkeeper offers various goods, including cigarettes. You can 'buy cigarettes' or 'leave store'.");
    Location *loc26 = addLocation(graph, 26, "Underground City - Back of Store", "It's dark back here. Suddenly, someone steps out of the shadows! It's a drug dealer!"); // Game over location

    // Check for failures, if found then REVIEW YOUR CODE!!!!
    if (!loc0 || !loc1 || !loc2 || !loc3 || !loc4 || !loc5 || !loc6 || !loc7 || !loc8 || !loc9 || !loc10 ||
        !loc11 || !loc12 || !loc13 || !loc14 || !loc15 || !loc16 || !loc17 || !loc18 || !loc19 || !loc20 ||
        !loc21 || !loc22 || !loc23 || !loc24 || !loc25 || !loc26)
    {
        printf("FATAL: Failed to create one or more locations during initialization. Exiting.\n");
        freeGraph(graph); // Attempt cleanup
        exit(EXIT_FAILURE); // Found a function that quits the program, lets goooo
    }

    // Add Connections (Map the Paths) 
    // !REMINDER |from||to||direction's name||edge cost)!
    // House <-> Village
    addConnection(loc0, loc1, "village", 0);                            // Edge (connection) from the house to the village

    // Village <-> Farm
    addConnection(loc1, loc2, "farm", 0);                               // Edge (connection) from the village to the farm

    // Village <-> Forest Entrance
    addConnection(loc1, loc3, "forest", 0);                             // Edge (connection) from the village to the farm

    // Forest Entrance -> Dead Ends / Bear / Crossroads
    addConnection(loc3, loc4, "deeper", 0);                             // Edge (connection) from the forest to somewhere deeper
    addConnection(loc3, loc5, "growl", 0);                              // Edge (connection) from the forest to the bear
    addConnection(loc3, loc6, "crossroads", 0);                         // Edge (connection) from the forest to the crossroads

    // Bear Cave -> Caverns
    addConnection(loc5, loc10, "approach", 0);                          // Edge (connection) from the bear to the cave

    // Forest Crossroads -> Dead Ends
    addConnection(loc6, loc7, "overgrown", 0);                          // Edge (connection) from the crossroads to the overgrowth
    addConnection(loc6, loc8, "scraps", 0);                             // Edge (connection) from the crossroads to some scaps
    addConnection(loc6, loc9, "well-trodden", 0);                       // Edge (connection) from the crossroads to a well-troden path

    // Caverns Main <-> Forks
    addConnection(loc10, loc11, "left", 1);                             // Edge (connection) from the cave entrance to the left fork
    addConnection(loc10, loc14, "right", 1);                            // Edge (connection) from the cave entrance to the right fork

    // Caverns Left Fork -> Dead Ends
    addConnection(loc11, loc12, "left", 1);                             // Edge (connection) from the left fork to the left dead end
    addConnection(loc11, loc13, "right", 1);                            // Edge (connection) from the left fork to the right dead end

    // Caverns Right Fork -> Trap / Crossroads
    addConnection(loc14, loc15, "across", 1);                           // Edge (connection) from the right fork to the death trap
    addConnection(loc14, loc16, "right", 1);                            // Edge (connection) from the right fork to the cave crossroads

    // Caverns Crossroads -> Dead Ends / Door
    addConnection(loc16, loc17, "dead end", 1);                         // Edge (connection) from the crossroads to a dead end
    addConnection(loc16, loc18, "rubble", 1);                           // Edge (connection) from the crossroads to the rusty key
    addConnection(loc16, loc19, "door", 1);                             // Edge (connection) from the crossroads to the door

    // Locked Door -> Underground City
    addConnection(loc19, loc20, "open door", 2);                        // Edge (connection) from the door to the city entrance

    // Underground City <-> Road/Alley
    addConnection(loc20, loc21, "alley", 2);                            // Edge (connection) from the entrance to the alley
    addConnection(loc20, loc22, "road", 2);                             // Edge (connection) from the entrance to the road

    // Alley -> Cat
    addConnection(loc21, loc23, "leave", 2);                            // Edge (connection) from the alley to the cat

    // Road -> Cat / Storefront
    addConnection(loc22, loc23, "right", 2);                            // Edge (connection) from the road to the cat
    addConnection(loc22, loc24, "left", 2);                             // Edge (connection) from the road to the store front

    // Storefront -> Store / Back Alley
    addConnection(loc24, loc25, "enter store", 2);                      // Edge (connection) from the store front to inside the store
    addConnection(loc25, loc25, "buy cigarettes", 2);                   // Yes, I know, you don't go anywhere, but I'm lazy alright?
    addConnection(loc24, loc26, "back alley", 2);                       // Edge (connection) from the store front to the back alley

    // Set Location Properties (NPCs, Items, Flags) 
    loc2->npcId = NPC_FARMER;           // The farmer NPC

    loc10->leadsToGameOver = 1;         // Bears are deadly

    loc10->npcId = NPC_HUNGRY_PERSON;   // Hungry person here

    loc15->leadsToGameOver = 1;         // Trap is game over

    loc21->npcId = NPC_THUGS;           // Thugs here (special interaction)

    loc23->isGoal = 1;                  // Finding the cat is the goal!

    loc26->leadsToGameOver = 1;         // Dealer is game over

    // Initialize Player
    player->currentLocation = loc0;     // Start at House
    player->moveCount = 0;              // Reset move count at the start of the game
    player->clearanceLevel = 0;         // Internal starting level
    player->metThugs = 0;               // Just started the game, the player doesn't know nobody

    // Initialize Inventory
    initInventory();

    // Initialize NPCs
    NPCs[0].id = NPC_FARMER;            // The farmer
    strcpy(NPCs[0].name, "Gabe Itch");  // Innocent name

    NPCs[1].id = NPC_HUNGRY_PERSON;     // The hungry NPC
    strcpy(NPCs[1].name, "Hunk Ree");   // Totally random name

    NPCs[2].id = NPC_THUGS;             // The thugs
    strcpy(NPCs[2].name, "Thugs");      // AI generated name
}

// Function that displays the location (Current node player is in) of the player
void displayLocation(Player *player) {                                                  // Argument is just the player itself
    if (!player || !player->currentLocation) return;                                    // If the player isn't made yet, then stop function

    Location *loc = player->currentLocation;                                            // Create a pointer to the player's location
    printf(AnsiBold AnsiBrightYellow"\n---  %s  ---\n"AnsiColorReset, loc->name);       // Display the location's name to the player
    printf("%s\n", loc->description);                                                   // Display the locations's desctiption to the player

    if (loc->npcId != NPC_NONE)                                                         // If there is an NPC present, then...
        printf("Someone is here: [" AnsiBrightMagenta "%s" AnsiColorReset "]\n", NPCs[loc->npcId].name); // Display name of NPC

    printf(AnsiColorCyan "Exits: " AnsiColorReset);                                     // Display all paths the player can take
    LocationNode *conn = loc->connections;                                              // Create a pointer to point at the start of the linked list of edges (connections)
    if (!conn)                                                                          // If an edge (connection) doesn't exist, then...
        printf("None");                                                                     // Inform the player
    else {                                                                              // Display all possible paths/edges/connections to player
        int first = 1;                                                                  // Print ", " only once after an initial print
        while (conn != NULL) {                                                          // Print all the edges (connections) until none are left
            if (!first) printf(", ");                                                   // Print ", " if more than 1 edge (connection)
            printf("[" AnsiColorGreen "%s" AnsiColorReset "]", conn->directionName);    // Brackets would signify commands
            first = 0;                                                                  // First only happens once so change to 0
            conn = conn->next;                                                          // Traverse the linked list of edges (connections)
        }
    }
    printf("\n");                                                                       // Print new line
}

// Function for the look around command
void lookAround(Player *player) {                                                       // Argument is just the player
    if (!player || !player->currentLocation) return;                                    // If player isn't made yet, then stop function
    Location *loc = player->currentLocation;                                            // Create a pointer that pointer to the player's location
    loc->lookCount++;                                                                   // Increase the location's look counter

    printf("\n--- " AnsiBold AnsiColorCyan "Looking Around %s " AnsiColorReset "---\n", loc->name); // Signify to player that the command is beign executed
    printf("%s\n", loc->description);                                                   // Display only the base description first

    // Use (Grey) for hints
    printf(AnsiBrightBlack);                                                            // Start hint color

    // Add Hints based on look count and location flags 
    if (loc->id == 5 && player->clearanceLevel == 0) {                                                      // Bear Cave
        if(loc->lookCount == 1)                                                                             // Looking around for a second time
            printf("The bear looks really big and angry. Going near it seems like a bad idea.\n");          // Give a hint
        else if (loc->lookCount >= 2)                                                                       // Looking around for a third time
            printf("Maybe if you had something to appease the bear?\n");                                    // Give a more obvious hint
        } 
    else if (loc->id == 14) {                                                                               // Right fork before trap
        if (Inventory[1].used == 1)                                                                         // If lunchbox was used
        {
            if (loc->lookCount >= 1)                                                                        // Looking around for a second time
                printf("You remember the warning about a trap nearby. Going 'across' feels dangerous.\n");  // Give a hint (it's obvious enough)
        }
    }
    else if (loc->id == 19 && player->clearanceLevel == 1)                                                  // Locked Door
    {
        if (loc->lookCount == 1)                                                                            // Looking around for a second time
            printf("The lock looks like it needs a specific key.\n");                                       // Give a hint
        else if (loc->lookCount >= 2)                                                                       // Looking around for a third time
            printf("The lock shines faintly, it looks like silver.\n");                                     // Give a more obvious hint
    }
    else if (loc->id == 21 && loc->npcId == NPC_THUGS)                                                      // Alleyway Thugs
    {
        if (loc->lookCount == 1)                                                                            // Looking around for a second time
            printf("These thugs don't look friendly. They seem to want something.\n");                      // Give a hint
        else if (loc->lookCount >= 2)                                                                       // Looking around for a third time
            printf("One of them keeps glancing at an empty pack of cigarettes on the floor. Maybe that's what they're after?\n"); // Give a more obvious hint
    }
    else if (loc->id == 22)                                                                                 // Road fork before Store/Cat
    {   
        if (player->metThugs == 1) {                                                                        // Check if plater has met the thugs
            if (loc->lookCount >= 1)                                                                        // Looking around for a second time or more
                printf("You feel uneasy, as if being watched. Going 'right' might be dangerous after that encounter in the alley.\n"); // Give a hint (it's obvious enough)
        } 
        else {                                                                                              // if NOT met thugs
            if (loc->lookCount >= 1)                                                                        // Looking around for a second time or more
                printf("The path 'right' seems quiet, while 'left' leads to a store.\n");                   // Give a hint (it's obvious enough)
        }
    }
    else {                                                                                                  // Default look messages if no specific hints
        if (loc->lookCount == 1)                                                                            // Looking around for a second time
            printf("You scan the area more closely.\n");                                                    // Give a hint
        else if (loc->lookCount == 2)                                                                       // Looking around for a third time
            printf("You examine every nook and cranny.\n");                                                 // Give a more obvious hint
        else                                                                                                // Looking around for more than 3 times
            printf("You've already examined this area extensively.\n");                                     // Do nothingggggg
    }

    printf(AnsiColorReset);                                                                                 // Reset color after hints

    // Display NPCs again 
    if (loc->npcId != NPC_NONE)                                                                             // If the node contains an NPC
        printf("Someone is here: " AnsiBrightMagenta "%s" AnsiColorReset "\n", NPCs[loc->npcId].name);         // Display the NPC's name

    // Repeat exits for convenience after looking
    printf(AnsiColorCyan "Exits: " AnsiColorReset);                                     // Copy paste the same code for displaying connections
    LocationNode *conn = loc->connections;                                              // Create a pointer to point at the start of the linked list of edges (connections)
    
    if (!conn){                                                                         // If an edge (connection) doesn't exist, then inform the player
        printf("None");                                                                 // Should not be possible...
    } else {                                                                            // Display all possible paths/edges/connections to player
        int first = 1;                                                                  // Print ", " only once after an initial print
        while (conn != NULL) {                                                          // Print all the edges (connections) until none are left
            if (!first) printf(", ");                                                   // Print ", " if more than 1 edge (connection)
            printf("[" AnsiColorGreen "%s" AnsiColorReset "]", conn->directionName);    // Brackets would signify commands
            first = 0;                                                                  // First only happens once so change to 0
            conn = conn->next;                                                          // Traverse the linked list of edges (connections)
        }
    }
    printf("\n");                                                                       // Print new line
}

// Function to move player to different nodes (locations)
void movePlayer(Graph *graph, Player *player, char *direction){                         // Arguments include, the graph (game world), the player, and the user given direction
    if (!player || !player->currentLocation || !direction || !history || !graph) return;// If none of the arguments aren't met (why would you?!??!), then stop function

    Location *currentLoc = player->currentLocation;                                     // Create a pointer that points to the player's current location
    LocationNode *conn = currentLoc->connections;                                       // Create a pointer that points to the node's (location's) linked list of edges (connections)
    Location *destination = NULL;                                                       // Create a pointer that WILL point to a destination
    int requiredClearanceForMove = 0;                                                   // Store the required clearance for the found path

    // Find the connection matching the direction
    while (conn != NULL) {                                                              // Traverse ALL of the edges (connections) of the current node (location)
        // Use strcasecmp for case-insensitive comparison
        if (strcasecmp(conn->directionName, direction) == 0) {                          // If a direction in the Linked List of edges (connections) match with the given direction, then...
            destination = conn->destination;                                                // The destination pointer will now point at the chosen ditection
            requiredClearanceForMove = conn->requiredClearance;                             // Get the requirement for this specific edge
            break;                                                                          // Stop traversing the linked list of edges (connections)
        }
        conn = conn->next;                                                              // Traverse the linked list of edges (connections) if destination not found yet
    }

    // If destinations are still not found
    if (!destination)                                                                   // if destination is STILL NULL, then...
    {
        printf(AnsiColorYellow "You can't go '%s' from here.\n" AnsiColorReset, direction); // Print disclaimer
        return;                                                                             // Stop function
    }

    //// Clearance Level Check FOR DEBUGGING
    if (player->clearanceLevel < requiredClearanceForMove)                              // If clearance is not high enough
    {
        printf("Something blocks your path ");                                               // Say so
        return;                                                                         // end code                     
    }

    // Check for a game over node
    if (destination->leadsToGameOver)                                                   // If the destination node's (location's) game over flag is true, then...
    {
        printf("\n--- " AnsiBold AnsiColorRed "%s" AnsiColorReset " ---\n", destination->name); // Show the location briefly
        printf("%s\n", destination->description);                                       // Show its description (the game over text)
        printf("\n"AnsiBold AnsiColorRed"\n");                                          // setup the red
        printGameOver();                                                                // print game over
        printf(AnsiColorReset);                                                         // remove the color and bold

        // Need a way to signal game over to the main loop
        // For now, just print and maybe move player there for score calculation???
        player->currentLocation = destination; 
        return;                                                                         // Stop further processing
    }

    // If all checks pass, perform the move
    if (strcasecmp(direction, "buy cigarettes") != 0)                                   // This is where my laziness comes back to bite me...
    {
        // Display ASCII Art
        if (strstr(destination->name, "Forest") != NULL){                               // If at a forest, then...
            printf(AnsiColorGreen);                                                        // Set up the green paint
            printForest();                                                                  // Display a forest
            printf(AnsiColorReset);                                                     // Remove the paint
        }
        else if (destination->id == 5 && Inventory[0].used != 1)                        // If at the bear AND not used the honey, then...
            printBearDisappointed();                                                        // Print a grumpy bear
        else if (destination->id == 5 && Inventory[0].used == 1)                        // If at the bear AND did used honey, then...
            printBearWithHoney();                                                           // Print happy bear
        else if (destination->id == 10)                                                 // If at cave, then...
        {
            printCave();                                                                    // Print the cave 
            printHomelessMan();                                                             // And the hungry NPC
        }
        else if (strstr(destination->name, "Underground") != NULL)                      // If in the city, then...
            printCity();                                                                    // Print the city
        else if (destination->id == 19)                                                  // If at the door, then...
            printDoor();                                                                    // Display Door
        else if (destination->id == 2)                                                  // If at the farmer, then...
            printFarmer();                                                                  // Display the farmer

        push(currentLoc);                                                               // Push the current location onto the history stack BEFORE moving
        player->currentLocation = destination;                                          // Update player's location
        player->moveCount++;                                                            // Increment Score
        player->currentLocation->lookCount = 0;                                         // Reset look count for the new location upon entering
        displayLocation(player);                                                        // Display the new location info
    }

    // Post-Move Actions (Pick up item automatically)
    // Basically, if the player is at a node that contains an item AND they don't have the item in their inventory AND they never used the item, then...
    if (player->currentLocation->id == 8 && Inventory[1].id == -1 && Inventory[1].used == 0) 
        addItem(ITEM_LUNCHBOX, "Lunch Box", "Looking inside, it contains dry stale crackers, some shrivled up turkey slices, moldy cheese, a sports drink, and a tiny chocolate bar");

    else if (player->currentLocation->id == 13 && Inventory[2].id == -1 && Inventory[2].used == 0)
        addItem(ITEM_SILVER_KEY, "Silver Key", "Can be used on silver locks");

    else if (player->currentLocation->id == 18 && Inventory[3].id == -1 && Inventory[3].used == 0)
        addItem(ITEM_RUSTY_KEY, "Rusty Crooked Key", "It looks really fragile");

    else if (player->currentLocation->id == 25 && strcasecmp(direction, "buy cigarettes") == 0 && Inventory[4].used == 0)
        addItem(ITEM_CIGARETTES, "A pack of cigarettes", "Warning: Cigarettes may cause but are not limited to lung cancer, throat cancer, mouth cancer, tongue rot, bad breath, premature aging, yellow teeth, coughing fits, raspy voice, wheezing, shortness of breath, chronic bronchitis, emphysema, heart disease, stroke, erectile dysfunction, fertility issues, spontaneous coughing in complete silence, early death, really early death, financial ruin, bad dates, loneliness, ash-covered everything, fire hazards, cold weather smoking shame, secondhand smoke guilt, thirdhand smoke mystery, social segregation, accidental hole-burning in car seats, questionable life choices, addiction stronger than your willpower, the smell of regret in your hair, morning-after lung regret, and the gradual realization that you've been paying to slowly self-destruct in style. Please light responsibly. Or, you know... not at all.");

    // Check if player is at thugs ally
    if (player->currentLocation->id == 21 && player->metThugs == 0){                    // Hasn't met thugs yet AND is on the node with thugs
        player->metThugs = 1;                                                           // Now player has met the thugs
        graph->locations[19].leadsToGameOver = 1;                                       // Going back angers the thugs
        strcpy(graph->locations[19].description, "You tried to escape the thugs...");   // Game over text
        graph->locations[23].leadsToGameOver = 1;                                       // same ^^
        strcpy(graph->locations[23].description, "You tried to escape the thugs...");   // same ^^
    }
}

// Function for going back, uses the stack (Movement History) to move back to the previous location
void goBack(Graph *graph, Player *player)
{ // Arguments include, the graph (game wolrd), the player, and the stack (movement history)
    if (!graph || !player || !history) return;      // If arguments don't exist, then stop function

    Location *prevLocationPtr = pop(history);       // Pop the stack once and store the location pointer of the previous node (location) the player was on

    // Check if pop failed (stack was empty)
    if (prevLocationPtr == NULL)                    // IF previous location is stack (movement history) returns NULL, then...
    {
        printf(AnsiColorYellow "You can't go back any further.\n" AnsiColorReset); // Print disclaimer
        return;                                     // End code
    }
    else // Pop was successful, prevLocationPtr points to the previous location
    {
        player->currentLocation = prevLocationPtr; // Update the player's location
        player->moveCount++;                       // Increment Score
        printf("You backtrack...\n");              // Signify to player that the command is executed

        if (player->currentLocation->leadsToGameOver == 1)
        {
            printf("\n--- " AnsiBold AnsiColorRed "%s" AnsiColorReset " ---\n", player->currentLocation->name); // Show the location briefly
            printf("%s\n", player->currentLocation->description);                                               // Show its description (the game over text)
            printf("\n" AnsiBold AnsiColorRed "\n");                                                            // setup the red
            printGameOver();                                                                                    // print game over
            printf(AnsiColorReset);                                                                             // remove the color and bold

            return; // Stop further processing
        }

        displayLocation(player);                   // Display the player's new location
    }
}

// Function for using items
void useItem(Graph *graph, Player *player, char *item){                                 // Arguments are the graph, the player, and the item to use
    if (!player || !player->currentLocation || !item) return;                           // If none of the arguments are met then stop function
    Location *currentLoc = player->currentLocation;                                     // Create a pointer that points to the player's current location, Dejavu?

    // Bear cave
    if (currentLoc->id == 5 && strcasecmp(item, "honey") == 0)                          // If player is at the bear cave AND they want to use the honey, then...
    {
        if (Inventory[0].id == ITEM_HONEY)                                              // Check if the player actually has honey, if they do, then ...
        {
            printf("You offer the " AnsiColorGreen "honey" AnsiColorReset ". The bear sniffs it, takes it gently, and seems calmer, letting you pass.\n"); // Tell player that the honey worked
            removeItem(0);                                                              // Remove the honey from the inventory (it's been used)
            Inventory[0].used = 1;                                                      // Mark the item as used
            strcpy(graph->locations[5].description, "The bear is now preoccupied with the honey, you can now 'enter' the cave, or go 'back' to the forest entrance");                                                   // Change Description
            strcpy(graph->locations[5].connections->directionName, "enter");            // Change direction name
            graph->locations[10].leadsToGameOver = 0;                                   // Bear won't kill anymore
            strcpy(graph->locations[10].name, "Caverns - Main Chamber");                // Replace with correct name
            strcpy(graph->locations[10].description, "Dark and damp. Water drips somewhere nearby. A figure huddles in the corner, looking hungry. Passages lead 'left' and 'right'. You can also go 'back' towards the bear cave entrance."); // Replace with correct Description
            player->clearanceLevel++;                                                   // Player can now go to nodes with a cost of 2
            printBearWithHoney();                                                       // Show happy Bear
        }
        else
            printf("You don't have a " AnsiBrightRed "%s" AnsiColorReset, item);        // They didn't obtain the item
    }
    // Hungry NPC
    else if (currentLoc->id == 10 && strcasecmp(item, "lunch box") == 0)                // If player is at the hungry NPC AND they want to use the lunch box, then...
    {
        if (Inventory[1].id == ITEM_LUNCHBOX)                                           // Check if the player actually has the lunch box, if they do, then ...
        {
            printf(AnsiBrightMagenta "Hunk Ree:" AnsiColorReset " Food... oh, thank the depths... thank you... (Coughs weakly) Listen... listen close... Just ahead... the darkness plays tricks... there's a wire... low to the ground... near the right wall... almost invisible... (Takes a shaky breath) Trip it... and the ceiling comes down. Rocks... crushing... Be... careful... so careful...\n"); // Tell player that the lunch box worked
            removeItem(1);                                                              // Remove the lunch box from the inventory (it's been used)
            Inventory[1].used = 1;                                                      // Mark the item as used
            strcpy(graph->locations[10].description, "The hungry individual is now occupied with his meal, it's best not to disturb him. Passages lead 'left' and 'right'. You can also go 'back' towards the bear cave entrance."); // Change description AGAIN
        }
        else
            printf("You don't have a " AnsiBrightRed "%s" AnsiColorReset, item); // They didn't obtain the item
    }
    // Locked Door
    else if (currentLoc->id == 19 && strcasecmp(item, "silver key") == 0)               // If player is at the door AND they want to use the silver key, then...
    {
        if (Inventory[2].id == ITEM_SILVER_KEY)                                         // Check if the player actually has the silver key, if they do, then ...
        {
            printf("You insert the " AnsiBrightGreen "Silver Key" AnsiColorReset ". *Click!* The heavy door swings open.\n"); // Tell player that the silver key worked
            strcpy(graph->locations[19].description, "The silver door is unlocked now, what waits on the other side? You could 'open door' if you're brave enough");
            removeItem(2);                                                              // Remove the silver key from the inventory (it's been used)
            Inventory[2].used = 1;                                                      // Mark the item as used
            player->clearanceLevel++;                                                   // Player can now go to nodes with a cost of 3
        }
        else
            printf("You don't have a " AnsiBrightRed "%s" AnsiColorReset, item); // They didn't obtain the item
    }
    // Locked Door ( with false key)
    else if (currentLoc->id == 19 && strcasecmp(item, "Rusty Key") == 0)                // If player is at the door AND they want to use the Rusty Key, then...
    {
        if (Inventory[3].id == ITEM_RUSTY_KEY)                                          // Check if the player actually has the Rusty Key, if they do, then ...
        {
            printf("You insert the " AnsiBrightGreen "Rusty key" AnsiColorReset "... But it broke while you turned it...\n"); // Tell player that the Rusty Key failed
            removeItem(3);                                                              // Remove the Rusty Key from the inventory (it's been used)
            Inventory[3].used = 1;                                                      // Mark the item as used
        }
        else
            printf("You don't have a " AnsiBrightRed "%s" AnsiColorReset, item); // They didn't obtain the item
    }
    // Thugs
    else if (currentLoc->id == 21 && (strcasecmp(item, "Cigarettes") == 0 || strcasecmp(item, "Cigs") == 0)) // If player is with the thugs AND they want to use the cigarettes, then...
    {
        if (Inventory[4].id == ITEM_CIGARETTES)                                         // Check if the player actually has the cigarettes, if they do, then ...
        {
            printf(AnsiBrightMagenta "Thugs: " AnsiColorReset "Huh, you actually got some? Give it here! You can 'leave' now.\n"); // Wink Wink Nudge Nudge
            printf("You offer the " AnsiBrightGreen "cigarettes" AnsiColorReset ". They take them with a grunt and let you pass.\n"); // Tell player that the cigarettes worked
            removeItem(4);                                                              // Remove the cigarettes from the inventory (it's been used)
            Inventory[4].used = 1;                                                      // Mark the item as used
            player->clearanceLevel = 2;                                                 // Player can now go to more places
            graph->locations[19].leadsToGameOver = 0;                                   // You're safe now
            strcpy(graph->locations[19].description, "The silver door is unlocked now, what waits on the other side? You could 'open door' if you're brave enough");                                                                   // Revert description change
            graph->locations[23].leadsToGameOver = 0;                                     // same ^^
            strcpy(graph->locations[23].description, "There it is! Your furry friend is safe and sound, purring on a windowsill! YOU WIN!"); // same ^^
            strcpy(graph->locations[21].description, "The thugs have let you go! You see something furry in the distance, you can 'leave' to find out what it is");
        }
        else
            printf("You don't have a " AnsiBrightRed "%s" AnsiColorReset, item); // They didn't obtain the item
    }
    else if ((strcasecmp(item, "honey") != 0) && (strcasecmp(item, "lunch box") != 0) && (strcasecmp(item, "silver key") != 0) && (strcasecmp(item, "Rusty Key") != 0) && (strcasecmp(item, "Cigarettes") != 0))                                           // Using an item that doesn't exist
        printf("You don't have a " AnsiBrightRed "%s" AnsiColorReset, item);        // It's non-existant, so yeah

    else printf("That doesn't work...\n");                                              // Using an item anywhere else
    displayLocation(player);
}

// Function for the instructions command
void displayInstructions(){                                                                             // No arguments needed
    printf(AnsiBold AnsiColorCyan"\n--- Instructions ---\n"AnsiColorReset);                             // Sweet little UI for the menu of instructions
    printf("Objective: Explore the world and find your lost furry friend.\n");                          // Nice and simple Objective
    printf(AnsiBold "Commands:\n" AnsiColorReset);                                                      // Tell the user how to use commands
    printf(" \nMovement: Enter a direction shown in [" AnsiColorGreen "brackets" AnsiColorReset "] (e.g., '" AnsiColorGreen "village" AnsiColorReset "', '" AnsiColorGreen "left" AnsiColorReset "') to move.\n");                                                                  // Explain movement first
    printf("        Enter '" AnsiColorYellow "back" AnsiColorReset "' to return to the previous location you visited.\n");                                                                                                    // Explain back tracking
    printf(" \nLook: Type '" AnsiColorYellow "look" AnsiColorReset "' to examine your current surroundings more closely for hints.\n");                                                                                               // Explain the look around system, it's just asking for hints
    printf(" \nInventory: Type '" AnsiColorYellow "inv" AnsiColorReset "' or '" AnsiColorYellow "inventory" AnsiColorReset "' to see your items.\n");                                                                                               // Explain the inventory system
    printf("        Use [item]: Type '" AnsiColorYellow "use" AnsiColorReset "' followed by an item name (e.g., '" AnsiColorYellow "use " AnsiColorMagenta "honey" AnsiColorReset "').\n");                                                                            // Explain how to use items
    printf(" \nTalk: Type '" AnsiColorYellow "talk to" AnsiColorReset "' followed by an NPC name (e.g., '" AnsiColorYellow "talk to " AnsiColorYellow "John Pork" AnsiColorReset "').\n");                                                                                           // Explain how to talk
    printf(" \nInstructions: Type '" AnsiColorYellow "help" AnsiColorReset "' or '" AnsiColorYellow "instructions" AnsiColorReset "' to see this message again.\n");                                                                                               // Explain how to open the instructions menu again
    printf(" \nQuit: Type '" AnsiColorYellow "quit" AnsiColorReset "' to exit the game.\n");            // Explain how to win the game
}

// Function to talk to NPCs
void talkTo(Player *player, char *name){                                                // Argument is just the player
    if (!player || !player->currentLocation) return;                                    // If none of the arguments are met then stop function
    Location *loc = player->currentLocation;                                            // Create a pointer to the player's location
    int choice = -1;                                                                    // Dialogue choices that the player can make

    if (loc->npcId == NPC_NONE){                                                        // If there isn't an NPC present, then...
        printf("There's no one to talk to...\n");                                           // print disclaimer
        printf("\n> *sigh*");                                                               // Damn
        getchar();                                                                          // Press Enter
    }                                                         
        
    
    else if (loc->npcId == NPC_FARMER && (strcasecmp(NPCs[0].name, name) == 0)){          // If farmer found, then...
        if (Inventory[0].id == -1)                                                      // If player doesn't have honey yet 
        {
            printf(AnsiColorYellow "Gabe Itch:" AnsiColorReset " Well howdy there, stranger! Don't see many new faces 'round these parts. Somethin' I can help ya with? You look like you're searchin' for somethin'.\n");

            printf("\nPick a dialogue option:\n");                                      // Multiple choice interactions
            printf(" 1. I'm looking for my lost cat. Have you seen one?\n");            // choice 1
            printf(" 2. Just exploring. Nice farm you have here.\n");                   // choice 2
            printf(" 3. (Say nothing and leave)\n");                                    // chice 3
            printf("> ");                                                               // Nice UI

            scanf("%i", &choice); // Obtain input 
            
            if (choice == 1)                                                            
            {
                printf(AnsiColorYellow "\nGabe Itch:" AnsiColorReset " Your cat, ya say? Aww, that's a shame. Hate to see a critter lost. Hmm... you know, it's funny you mention that. Earlier this mornin', I did see a flash of fur boltin' past my field. Real quick little thing.\n");

                clearInputBuffer();                                                     // Stops automatically continuing
                printf("\n> Continue...");                                              // Little pause
                getchar();                                                              // Press enter to continue

                printf(AnsiColorYellow "\nGabe Itch:" AnsiColorReset " Couldn't get a good look, mind you, but it definitely hightailed it straight into the forest, maybe towards that old cave entrance people talk about? Might be worth checkin' out, eh?\n");

                printf("\n> OK, thanks.");                                              // Little pause
                getchar();                                                              // Press enter to continue

                printf(AnsiColorYellow "\nGabe Itch:" AnsiColorReset " Tell ya what, that cave can be a bit dark and gloomy. Here...(Farmer pulls out a small jar of honey) Take this. Fresh from my hives. A little sweetness might keep your spirits up on your search. Good luck findin' your furry friend!\n\n");

                printf("\n> Why thank you!");                                           // Little pause
                getchar();                                                              // Press enter to continue

                addItem(ITEM_HONEY, "Honey", "Sweet and Sticky!");                      // Obtain honey
            }
            else if (choice == 2)
                printf(AnsiColorYellow "\nGabe Itch:" AnsiColorReset " Why thank you kindly! Takes a lot of work, but it's honest work. Be careful wanderin' around, especially in that forest.\n");
            else if (choice == 3)
                printf("\nYou nod silently and back away.\n");
            else
                printf(AnsiColorYellow "\nGabe Itch:" AnsiColorReset " looks at you quizzically.\n");
        }
        else{
            printf("\nThere's nothing left to talk about...\n");
            printf("\n> Bye");
            getchar();
        }
            
    }
    else if (loc->npcId == NPC_HUNGRY_PERSON && strcasecmp(NPCs[1].name, name) == 0)
    { // If hungry NPC is found then...
        printf("\nA figure huddles in the corner, shivering slightly. They look weak and malnourished.\n");

        // Check if the lunchbox has already been used (given to Hunk Ree)
        if (Inventory[1].used == 1)                                                     // If the lunchbox has been used
            printf(AnsiColorYellow "\nHunk Ree:" AnsiColorReset " Oh... it's you... *cough*... thanks again... for the food... Remember... the warning... be careful...\n");

        // Check if the player currently has the lunchbox and hasn't used it yet
        else if (Inventory[1].id == 1 && Inventory[1].used == 0)                        // If player HAS the lunchbox, but didn't use it
        {
            printf(AnsiColorYellow "\nHunk Ree:" AnsiColorReset " *Ugh... so hungry... haven't eaten in... days... anything... please...*\n");
            printf("\nWhat do you want to say?\n");                                     // Multiple choice interactions
            printf(" 1. Are you okay? What happened?\n");                               // choice 1
            printf(" 2. Have you seen a cat?\n");                                       // choice 2
            printf(" 3. (Say nothing)\n");                                              // choice 3
            printf("> ");                                                               // Nice UI

            // Simple input handling
            scanf("%i", &choice);                                                       // Obtain Input

            if (choice == 1)
            {
                printf(AnsiColorYellow "\nHunk Ree:" AnsiColorReset " *Okay? No... starving... Lost... down here... Need... food... Can't think straight... Got anything? Anything edible?*\n");
                printf("\n(You have a Lunch Box. Maybe you should 'use lunch box'?)\n");
            }
            else if (choice == 2)
            {
                printf(AnsiColorYellow "\nHunk Ree:" AnsiColorReset " *Cat...? Furry...? Maybe... saw something quick... but... head hurts... so hungry... Food first... then maybe remember... Do you have food?*\n");
                printf("\n(Perhaps giving them the Lunch Box would help them remember. Try 'use lunch box'.)\n");
            }
            else if (choice == 3)
            {
                printf("\nYou stay silent. The figure continues to moan softly about hunger.\n");
            }
            else
            {
                printf("\nHunk Ree looks at you with empty eyes, not understanding.\n");
            }
            clearInputBuffer();
        }
        // Player doesn't have the lunchbox (or never picked it up)
        else
        {
            printf(AnsiColorYellow "\nHunk Ree:" AnsiColorReset " *So... hungry... Need... food... Can't help... anyone... like this... Go away... unless you have food...*\n");
            printf(AnsiBrightBlack"\nYou don't seem to have anything that could help them right now.\n"AnsiColorReset);
        }
    }
    else if (loc->npcId == NPC_THUGS && strcasecmp(NPCs[2].name, name) == 0) // If thugs are found, then...
    {
        // Check if the player has used the cigarettes (given them to the thugs)
        if (Inventory[4].used == 1)                                                     // if used cigs
            printf("\nOne of the thugs nods curtly as you pass. They seem occupied with their smokes.\n");

        // Check if player has cigarettes but hasn't used them
        else if (Inventory[4].id == ITEM_CIGARETTES && Inventory[4].used == 0)                        // If HAVE cigs, but not used
        {
            printf("\nThe thugs block the alleyway, looking you up and down menacingly.\n");
            printf(AnsiColorYellow "\nThug Leader:" AnsiColorReset " Hold it right there. This is our turf. What's your business?\n");
            printf("\nWhat do you do?\n");                                              // Multiple choice interactions
            printf(" 1. Try to talk your way past.\n");                                 // choice 1
            printf(" 2. Ask what they want.\n");                                        // choice 2
            printf(" 3. (Say nothing and wait)\n");                                     // choice 3
            printf("> ");                                                               // Nice UI

            scanf("%d", &choice) != 1;                                                  // Obtain input

            if (choice == 1)
            {
                printf(AnsiColorYellow "\nThug Leader:" AnsiColorReset " Talk? We don't want talk. We want smokes. Got any?\n");
                printf("\n(You have Cigarettes. Maybe 'use cigarettes' would work?)\n");
            }
            else if (choice == 2)
            {
                printf(AnsiColorYellow "\nThug Leader:" AnsiColorReset " What do we want? *He scoffs and points to an empty cigarette pack on the ground.* What do ya think we want? Smokes. Hand 'em over if ya got 'em.\n");
                printf("\n(You could try 'use cigarettes'.)\n");
            }
            else if (choice == 3)
            {
                printf(AnsiColorYellow "\nThug Leader:" AnsiColorReset " Playin' silent, huh? Doesn't matter. Just give us your smokes if you wanna pass.\n");
                printf("\n(They seem fixated on cigarettes. Try 'use cigarettes'.)\n");
            }
            else
            {
                printf("\nThe thugs look unimpressed by your response.\n");
            }
            clearInputBuffer();
        }
        // Player doesn't have cigarettes
        else
        {
            printf("\nThe thugs block the alleyway, looking you up and down menacingly.\n");
            printf(AnsiColorYellow "\nThug Leader:" AnsiColorReset " Hold it right there. This is our turf. Got any smokes on ya? No? Then beat it.\n");
            printf("\nThey don't seem willing to let you pass without some kind of offering.\n");
        }
    }

    displayLocation(player);                                                                // Redisplay the location
}

// ♥♥♥ Helper function to trim annoying whitespaces (like newline) from end of string ♥♥♥
void trimTrailingWhitespace(char *str) {                                                                        // Arguments is just any string
    if (!str) return;                                                                                           // if no arguments entered, then stop function
    int len = strlen(str);                                                                                      // Get the length of the string
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r' || str[len-1] == ' ' || str[len-1] == '\t')) {  // Loop through the entire string character by character
        str[len-1] = '\0';                                                                                      // Replace the whitespace character with the terminating character 
        len--;                                                                                                  // Decrease string length by 1
    }
}

// ♥♥♥ Helper function to remove new lines in input buffers ♥♥♥
void clearInputBuffer(){                                                                                        // No arguments
    int c;                                                                                                      // Variable to detect \n and Ctrl + c
    while ((c = getchar()) != '\n' && c != EOF);                                                                // Keep popping the input buffer
}

/* ************************* */
/* Main Function (Game Loop) */
/* ************************* */

int main() {                                                                                                        // Where it all starts...
    Graph *world = createGraph();                                                                                   // Create the graph (game world)
    Player player;                                                                                                  // Create the player

    initializeGame(world, &player);                                                                                 // Initialize everything

    char inputBuffer[100];                                                                                          // Create a buffer to obtain user input
    int playing = 1;                                                                                                // Game loop flag

    // Store start time
    time_t startTime = time(NULL);                                                                                  // Time the player

    printf(AnsiBold AnsiColorCyan "*************************************\n");                                       // Nice UI
    printf(" Welcome to the Cat Quest Adventure!\n");                                                               // Greet the Player
    printf("*************************************\n" AnsiColorReset);                                               // Nice UI
    displayInstructions();                                                                                          // Show instructions at the start
    displayLocation(&player);                                                                                       // Show starting location

    while (playing)
    {
        // Check for Game Over state based on current location BEFORE prompt
        // This catches entering a game over location immediately
        if (player.currentLocation && player.currentLocation->leadsToGameOver)                                      // If the player is somewhere AND that somewhere is a gameover, then...
        {
            // The game over message was likely printed in movePlayer already
            playing = 0;                                                                                            // Stop the loop
            break;                                                                                                  // Exit immediately
        }

        // Check for Win condition
        if (player.currentLocation && player.currentLocation->isGoal)                                               // If the player is somewhere AND that somewhere is a win condition, then...
        {
            printf("\n" AnsiBold AnsiColorGreen "*****************************************\n");      // Nice UI
            printf("Congratulations! You found your cat!\n");                                        // Inform user that the best game they ever played has ended
            printf("          !!! YOU WIN !!!\n");                                                                  // Tell player they won
            printf("*****************************************\n" AnsiColorReset);                                   // Nice UI
            printRandomCat();                                                                                       // Beggers can't be choosers
            playing = 0;                                                                                            // Player is no longer playing soo... change the variable
            break;                                                                                                  // Exit loop after winning
        }

        printf("\n> ");                                                                                             // Prompt for user input

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {                                               // No input is added... Quit game
            printf("\nError reading input or EOF reached. Quitting.\n");                                            // Print error
            playing = 0;                                                                                            // Exit loop on read error or EOF
            break;                                                                                                  // Break exits a loop
        }

        // Remove trailing newline/whitespace
        trimTrailingWhitespace(inputBuffer);                                                                        // For more freedom in inputs

        // ---------------------
        // --- Process Input ---
        // ---------------------

        // Use case-insensitive comparisons for commands
        if (strcasecmp(inputBuffer, "quit") == 0)                                                                   // Plater wants to quit...
            playing = 0;                                                                                                // Therefore they are no longer playing (playing = 0)
        else if ((strcasecmp(inputBuffer, "look") == 0) || strcasecmp(inputBuffer, "look around") == 0)             // Player wants to look...
            lookAround(&player);                                                                                        // Call the lookAround() function
        else if (strcasecmp(inputBuffer, "help") == 0 || strcasecmp(inputBuffer, "instructions") == 0)              // Player wants to read instructions...
            displayInstructions();                                                                                      // Then display the instructions
        else if ((strcasecmp(inputBuffer, "back") == 0) || (strcasecmp(inputBuffer, "go back") == 0))               // Player wants to move back a node (location)
            goBack(world, &player);                                                                                     // Try to move the player back
        else if (strcasecmp(inputBuffer, "inv") == 0 || strcasecmp(inputBuffer, "inventory") == 0)                  // Player wants to view inventory
            printInventory();                                                                                           // Display inventory
        else if (strncasecmp(inputBuffer, "use ", 4) == 0)                                                          // Player wants to use items in the inventory
            useItem(world, &player, inputBuffer + 4);                                                                   // Try to use them
        else if (strncasecmp(inputBuffer, "talk to ", 8) == 0)                                                      // Player wants to talk to NPCs
            talkTo(&player, inputBuffer + 8);                                                                           // if NPCs are there, then let them
        else if (strlen(inputBuffer) > 0)                                                                           // Assume the player want to move to another node (location)
            movePlayer(world, &player, inputBuffer);                                                                    // Move player
        else                                                                                                        // The case where the player just enters nothing
            printf("Please enter a command.\n");                                                                        // Pls
    } // End while(playing) loop

    // ----------------
    // --- Game End ---
    // ----------------

    printf("\nExiting game.\n");                                                                                    // Tell Player than the game is ending

    // Calculate time
    time_t endTime = time(NULL);                                                                                    // Capture the ending time
    double timeSpent = difftime(endTime, startTime);                                                                // Calculate the time spent playing
    printf("Time played: %.0f seconds.\n", timeSpent);                                                              // Display the time spent
    
    // Display final score based on move count
    printf("Total moves made (Score): %d\n", player.moveCount);                                                     // Display Final Score

    // ----------------
    // --- Clean up ---
    // ----------------
    // printf("Cleaning up resources...\n");
    freeGraph(world);                                                                                               // Delete the Graph
    world = NULL;

    printf("Goodbye!\n" AnsiColorReset);                                                                            // Momma taught me manners
}
