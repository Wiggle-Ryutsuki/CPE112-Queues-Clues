# CPE112 — Final Project
## Queue's Clues — Adventure Game
Problem: : Embark on a quest for a lost artifact in a tightly woven world. Explore, uncover
secrets, and solve a puzzle to claim your prize.

Data Structures:
- Graphs — Represents game world
- Arrays — Player's inventory.
- Hash Table — To quickly access descriptions of locations and items.
- Stacks — Player movement (go back)

Programming Language:
- C

[Description and goal of project]

## How To Run Code
### At the beginning of the program the user can do 1 of 5 things
1. Move around
2. Open Inventory
3. Look around
4. Open Instructions
5. Quit Program

The user can pick these options by typing in their commands in the terminal, for instance, if the user wants to view their inventory, entering "Inventory" in the terminal would cause the program to prints out the entire inventory.


### Movement
Moving is done by typing in the correct direction of movement in the terminal. Moving to each location/node in the graph would display the description of that location/node, hilighting the direction in brackets. So if the description of a location/nodes states that the user can move by going [Left] or [Across] the user can type either left or across to traverse the graph.

### Inventory
Typing in 'inventory' in the terminal would display something like this:

Item_Name | Item_description

Item_Name | Item_description

Item_Name | Item_description

...

If the player types in "use" then an item's name, then the player can interact with that item.

### Looking Around 
If the player types "Look" in the terminal, the description of the locations would be displayed again, but being more descriptive and helpful so as to act as a way to give hints to the user.

### Instructions 
Typing in "Instructions" or "help" would display a guide on how to use the program.

- objective, what the player has to do.
- what each command does

### Quit 
If the Player types in "Quit" then the program closes
- Display the score and times then exit the program

### Base Case 
If the player doesn't type anything in, then nothing would happen

## Deliverables

1. Source code in a well-organized format.
2. README file with instructions.
3. Report (2-3 pages) including:
  - Problem statement
  - Explanation of the chosen data structures
  - Code walkthrough
  - Complexity analysis

Presentation Date: May 4th, 2025

## Team Distribution

### Project Lead/Coordinator

- Name: [Name]
- ID: 6707050[ID]

Code Focus:

- File: `main.c`
    - Handles the program's main menu and overall flow.
    - Calls functions developed by other team members.
    - Manages integration and ensures smooth interaction between modules.

### World and Movement Systems Developer

- Name: Muhammad Asad Aziz
- ID: 67070503472

Code Focus:

- File: `[File name]`
  - Implements [Stuff]

Helper File:

- `helperfile.h`

### Inventory and Item Interaction Developer

- Name: [Name]
- ID: 6707050[ID]

Code Focus:

- File: `[File name]`
  - Implements [Stuff]

Helper File:

- `helperfile.h`
