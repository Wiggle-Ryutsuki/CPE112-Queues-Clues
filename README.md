# CPE112 — Final Project

## Queue's Clues — Cat Quest Adventure Game

**Cat Quest Adventure** is a terminal-based text adventure game written in C where you explore a mysterious world in search of your lost furry friend. Along the way, you'll uncover clues, meet quirky characters, collect useful items, and make decisions that shape your journey. Every path holds secrets—will you sniff out the right one?

### Data Structures

- Graphs
- Stacks
- Hash Tables
- Linked Lists
- Arrays

### Programming Language

- C

## Features & How to Play

### Prerequisites

- A C compiler (gcc)
- Terminal or command line access

### How To Run The Game

Compile the code:

    gcc .\main.c .\game.c .\history.c .\world.c .\inventory.c .\asciiart.c .\hashTable.c -o Game

Run the game program:

    ./Game

### Explore Diverse Locations

Move between locations by typing the direction shown in [brackets] (e.g., `village`, `left`). Use `back` to return to the previous area.

### Investigate Your Surroundings

Type `look` to closely examine your current location. There might be hidden items, clues, or secrets waiting to be discovered.

### Manage Your Inventory

Type `inv` or `inventory` to check what items you're carrying. Use them by typing `use` followed by the item name (e.g., `use honey`).

### Talk to NPCs

Engage with characters by typing `talk to` followed by their name (e.g., `talk to John Smith`). They might offer helpful hints—or distractions.

### Need Help?

Type `help` or `instructions` at any time to see the list of available commands.

### Your goal

Find your lost pet—but how you get there is up to you.

## Input and Output

### Movement

Moving Correctly

**Current location:** `Your House`

    ---  Your House  ---
    Cozy, familiar, but your cat is missing! The only way out is the 'village'.
    Exits: [village]

**Choices:** [Village]

**Input:** `Village`

**Output:**

    ---  Village Square  ---
    Bustling with activity. Paths lead to the 'farm', and the 'forest'. Going 'back' home is also an option.
    Exits: [forest], [farm]

Moving Incorrectly

**Current location:** `Your House`

    ---  Your House  ---
    Cozy, familiar, but your cat is missing! The only way out is the 'village'.
    Exits: [village]

**Choices:** [Village]

**Input:** `back`

**Output:**

    You can't go back any further.

**Current location:** `Your House`

    ---  Your House  ---
    Cozy, familiar, but your cat is missing! The only way out is the 'village'.
    Exits: [village]

**Choices:** [Village]

**Input:** `forest`

**Output:**

    You can't go 'forest' from here.

### Look

**Current location:** `Forest/Growl`

    ---  Cave Entrance (Bear)  ---
    A large, grumpy bear blocks the cave entrance! It seems agitated. Maybe something sweet would calm it? You can 'approach' the cave or go 'back' to the forest entrance.
    Exits: [approach]

**Input:** `look`

**Output:**

    --- Looking Around Cave Entrance (Bear) ---
    A large, grumpy bear blocks the cave entrance! It seems agitated. Maybe something sweet would calm it? You can 'approach' the cave or go 'back' to the forest entrance.
    The bear looks really big and angry. Going near it seems like a bad idea.
    Exits: [approach]

### Inventory

**Current Inventory State:** Empty

**Input:** `inventory`

**Output:**

    ===================================================
                     INVENTORY
    ===================================================
    | Name       | Description                        |
    |------------+------------------------------------|
    ===================================================

**Current Inventory State:** Obtained Honey

**Input:** `inv`

**Output:**

    ===================================================
                        INVENTORY
    ===================================================
    | Name       | Description                        |
    |------------+------------------------------------|
    | Honey      | Sweet and Sticky!                  |
    ===================================================

### Use

**Current Inventory Status:** Honey

**Location:** Forest/Growl

**Intended Use:** Yes

**Input:** `use honey`

**Output:**

    ---  Cave Entrance (Bear)  ---
    The bear is now preoccupied with the honey, you can now 'enter' the cave, or go 'back' to the forest entrance
    Exits: [enter]

**Current Inventory Status:** Honey

**Location:** Village

**Intended Use:** No

**Input:** `use honey`

**Output:**

    That doesn't work...

**Current Inventory Status:** Honey

**Location:** Forest/Growl

**Intended Use:** No

**Input:** `use silver key`

**Output:**

    That doesn't work...

### Help

**Input:** `help`

**Output:**

    --- Instructions ---
    Objective: Explore the world and find your lost furry friend.
    Commands:

    👟 Movement: Enter a direction shown in [brackets] (e.g., 'village', 'left') to move.

          -> Enter 'back' to return to the previous location you visited.

    👀 Look: Type 'look' to examine your current surroundings more closely for hints.

    🎒 Inventory: Type 'inv' or 'inventory' to see your items.

          -> Use [item]: Type 'use' followed by an item name (e.g., 'use honey').

    👄 Talk: Type 'talk to' followed by an NPC name (e.g., 'talk to John Pork').

    🧠 Instructions: Type 'help' or 'instructions' to see this message again.

    💀 Quit: Type 'quit' to exit the game.

### Quit

**Input:** `quit`

    Exiting game.
    Time played: [Real time gameplay]
    Rank: [Letter]
    Total moves made: [Total moves player successfully made]
    Goodbye!

## Team Distribution

### Muhammad Asad Aziz

ID: 67070503472

Game Loop and World Traversal

### Maimoona Aziz

ID: 67070503473

Project Coordinator

### Sao Wa Nee

ID: 67070503456

Game Accesories
