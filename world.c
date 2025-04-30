#include "world.h"

/* ****************************** */
/* Graph Functions Implementation */
/* ****************************** */

// Function to create a graph (game world)
Graph *createGraph()
{                                                   // No arguments needed
    Graph *graph = malloc(sizeof(Graph));           // Allocate memory
    if (!graph)
    {                                               // if graph doesn't exist after allocating, then print error
        perror("Failed to allocate graph");         // print error
        exit(EXIT_FAILURE);                         // Exit code
    }
    graph->numLocations = 0;                        // We just created our graph, so naturally we have 0 nodes
    for (int i = 0; i < MaxLocations; i++)
    {                                               // Create all the nodes (locations) in our graph (game world)
        graph->locations[i].id = -1;                // -1 indicates unused slot
        graph->locations[i].connections = NULL;     // The node isn't connected to any other nodes
        graph->locations[i].lookCount = 0;          // The player hasn't called the lookaround command, so by default it's 0
        graph->locations[i].isGoal = 0;             // The specified nodes will not end the game by default unless coded otherwise
        graph->locations[i].leadsToGameOver = 0;    // Moving to this node will cause a game over (default is false)
        graph->locations[i].npcId = -1;             // The node contains an NPC (default is none)
    }
    return graph;                                   // Return the graph as whatever variable it is initialized to be
}

// Function to add a node (location) to the graph (game world)
Location *addLocation(Graph *graph, int id, char *name, char *description){ // Arguments are, the graph, a given ID, a given name and a given description.
    if (!graph) return NULL;                                                // Stop the function IF the graph isn't initialized first, as a graph is needed

    if (id < 0 || id >= MaxLocations)                                       // If ID is out of bounds, then...
    {                                                                       // Raise and error and stop function
        fprintf(stderr, "Error: Invalid location ID %d.\n", id);            // Print error
        return NULL;                                                        // End function
    }

    graph->numLocations++;                                                  // The number of nodes (locations) increase in our graph (game world)
    Location *newLoc = &graph->locations[id];                               // Get pointer to the location in the array of locations
    newLoc->id = id;                                                        // Assign the given ID
    strncpy(newLoc->name, name, MaxNameLen - 1);                            // Assign the given name
    newLoc->name[MaxNameLen - 1] = '\0';                                    // Add the terminating character
    strncpy(newLoc->description, description, MaxDescLen - 1);              // Assign the given description
    newLoc->description[MaxDescLen - 1] = '\0';                             // Add the terminating character
    newLoc->connections = NULL;                                             // New node (location) means no connections
    newLoc->lookCount = 0;                                                  // it's a fresh node, so the player hasn't called the look around command yet
    newLoc->isGoal = 0;                                                     // Assume node doesn't win the game
    newLoc->leadsToGameOver = 0;                                            // Assume node doesn't cause a game over
    newLoc->npcId = -1;                                                     // Assume node doesn't contain NPCs

    return newLoc;                                                          // Return the node (loctaion)
}

// Function to add edges (connections)
void addConnection(Location *from, Location *to, char *directionName, int requiredClearance){   // Arguments are source, destination, name (left, right), and clearence required.
    if (!from || !to){                                                                          // If source and destination goes nowhere (NULL), then stop function
        fprintf(stderr, "Error: Cannot add connection with NULL location(s).\n");               // Print error
        return;                                                                                 // Stop function
    }

    LocationNode *newConnection = malloc(sizeof(LocationNode));                                 // Allocate memory for the edge (connection)
    if (!newConnection){                                                                        // If it fails, then raise error and stop function
        perror("Failed to allocate connection node");                                           // Print error
        return;                                                                                 // Stop function
    }

    newConnection->destination = to;                                                            // Assign the given destination
    strncpy(newConnection->directionName, directionName, MaxNameLen - 1);                       // Assign the given description
    newConnection->directionName[MaxNameLen - 1] = '\0';                                        // Add the terminating character
    newConnection->requiredClearance = requiredClearance;                                       // Assign the given clearence level

    // Add to the beginning of the 'from' location's connection list
    newConnection->next = from->connections;                                                    // The Source is added to the linked list of edges (Connections)
    from->connections = newConnection;                                                          // Add the node to the location's Linked list
}

// Function to delete the graph from memory
void freeGraph(Graph *graph){                                           // Arguments are the graph (game world) to delete
    if (!graph) return;                                                 // If graph (game world) isn't made yet, then stop the function
    
    for (int i = 0; i < MaxLocations; i++){                             // Loop though all nodes (locations)
        if (graph->locations[i].id != -1){                              // Check if location slot was used
            LocationNode *current = graph->locations[i].connections;    // If used, then create a pointer to traverse the linked list of edges (connections)
            while (current != NULL){                                    // Loop until no edges are left
                LocationNode *temp = current;                           // Create a temporary pointer for deletion of linked list nodes (connections)
                current = current->next;                                // Traverse the linked list
                free(temp);                                             // Free each edge (connection)
            }
        }
    }

    free(graph);                                                        // In the end, delete the graph (game world)
}