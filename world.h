#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Constants
#define MaxNameLen 50
#define MaxDescLen 250
#define MaxConnections 4    // Max exits per location
#define MaxLocations 30     // Max locations in the game world

// Forward Declarations
struct Location;            // Needed because LocationNode refers to Location

// Graph Data Structure
// Represents the a node in the linked list of connections (edges)
typedef struct LocationNode
{
    struct Location *destination;   // Pointer to the location this connection leads to
    char directionName[MaxNameLen]; // "go village", "path 1", "use door", etc.
    int requiredClearance;          // Acting as edge weight/price
    struct LocationNode *next;      // For linked list of connections from a single location
} LocationNode;

// Represents a location (vertex) in the game world
typedef struct Location
{
    int id;                         // Unique identifier
    char name[MaxNameLen];          // Name of the location "forest" "caverns" "Underground city"
    char description[MaxDescLen];   // Description of the location "lot's of trees..." "very dark..." "Dangerous..."
    LocationNode *connections;      // Head of the linked list of connections
    int lookCount;                  // How many times player looked around here
    int isGoal;                     // Simple flag for win condition

    // Flags for Game Logic
    int leadsToGameOver;            // Flag if entering directly causes game over (trap, dealer)
    int npcId;                      // ID of NPC present here (-1 if none)
} Location;

// Represents the entire game map (graph)
typedef struct Graph
{
    Location locations[MaxLocations]; // Array storing all locations
    int numLocations;                 // Current number of locations added
} Graph;

// Function Prototypes
// Graph functions
Graph *createGraph();                                                                         // Function to initialize the graph (game world)
Location *addLocation(Graph *graph, int id, char *name, char *description);                   // Function to add a node, needs: ID, name, description
void addConnection(Location *from, Location *to, char *directionName, int requiredClearance); // Function to add an edge between 2 nodes in a graph
void freeGraph(Graph *graph);                                                                 // Important for memory management

#endif