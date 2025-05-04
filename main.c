/* ************************* */
/* Main Function (Game Loop) */
/* ************************* */

#include "game.h"

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
    int timeSpent = difftime(endTime, startTime);                                                                   // Calculate the time spent playing
    if (timeSpent < 60)                                                                                             // Less than 1 min
        printf("Time played: %i seconds.\n", timeSpent);                                                          // Display the time spent, just the seconds
    else if (timeSpent < 3600){                                                                                     // Less than 1 hour
        int seconds = timeSpent % 60;                                                                               // Calculate seconds
        int minutes = timeSpent / 60;                                                                               // Calculate minutes
        printf("Time played: %i minutes and %i seconds.\n", minutes, seconds);                                      // Display time spent, both minutes and seconds
    }
    else if (timeSpent >= 3600){
        int seconds = timeSpent % 60;                                                                               // Calculate seconds
        int totalMinutes = timeSpent / 60;                                                                          // Calculate minutes
        int minutes = totalMinutes % 60;                                                                            // Calculate total minutes
        int hours = totalMinutes / 60;                                                                              // Calculate hours
        printf("Time played: %i hours %i minutes and %i seconds.\n", hours, minutes, seconds);                      // Display time spent, in hours, minutes, and seconds
    }
    
    // Display final score based on move count
    if (player.currentLocation->leadsToGameOver == 1 || strcasecmp(inputBuffer, "quit") == 0 || strcasecmp(inputBuffer, "-1") == 0) // -1 is EOF
        printf("Rank: " AnsiBrightRed "F\n" AnsiColorReset);                                                        // It's an easy game, failing is cringe
    else{
        if (player.moveCount <= 20) printf("Rank: " AnsiBrightGreen "A!" AnsiColorReset);                           // A Rank!
        else if (player.moveCount <= 30) printf("Rank: " AnsiBrightCyan "B!" AnsiColorReset);                       // B Rank
        else if (player.moveCount <= 40) printf("Rank: " AnsiBrightYellow "C" AnsiColorReset);                      // C Rank
        else if (player.moveCount > 40)  printf("Rank: " AnsiColorBlue "D..." AnsiColorReset);                      // D Rank...
        puts("");                                                                                                   // New Line Rank !!!!!!!!!
    }
        
        
    printf("Total moves made: %d\n", player.moveCount);                                                             // Display Final Score

    // ----------------
    // --- Clean up ---
    // ----------------
    // printf("Cleaning up resources...\n");
    freeGraph(world);                                                                                               // Delete the Graph
    world = NULL;                                                                            // Revert back to OG code page

    printf("Goodbye!\n" AnsiColorReset);                                                                            // Momma taught me manners
}
