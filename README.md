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
### At the beginning of the program a menu would display:
1. Movement
2. Inventory
3. Look around
4. Instructions
5. Quit

### Picking option 1 (movement) will display a submenu:
1. go left
2. go right
3. go back
4. previous menu

### Picking option 2 (Inventory) will display the inventory and a submenu:

Item_Name | Item_description

Item_Name | Item_description

Item_Name | Item_description

...

1. Use an item

   - Prompt user to enter item name (challenge)
   
2. previous menu

### Picking option 3 (Look Around) will display:
Area information
Picking this option 3 times will give more obvious clues.

### Picking option 4 (Instructions) will explain:

- objective, what the player has to do.
- what each command does

### Picking option 5 (Quit) will:
- Display the score and times then exit the program

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
