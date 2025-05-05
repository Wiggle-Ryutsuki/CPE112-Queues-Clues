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

### 👟 Movement: Exploring the World

Getting around is simple! Look for exits listed in `[brackets]` within the location description. Type the name of the place you want to go. Feeling lost? Type `back` to retrace your steps to the previous area.

#### Scenario 1: Moving to a New Location

- **You find yourself in:** `Your House`
>
    > --- Your House ---
    > Cozy, familiar, but your cat is missing! The only way out is the 'village'.
    > Exits: [village]

>
- **Your Command:** `village`

- **Game Output:** You step out into the village...
>
    > --- Village Square ---
    > Bustling with activity. Paths lead to the 'farm', and the 'forest'. Going 'back' home is also an option.
    > Exits: [forest], [farm]
>

(You successfully moved to the Village Square!)

---

#### Scenario 2: Trying an Invalid Direction

- **You find yourself in:** `Your House`
>
    > --- Your House ---
    > Cozy, familiar, but your cat is missing! The only way out is the 'village'.
    > Exits: [village]
>
- **Your Command:** `forest`

- **Game Output:** That path isn't accessible from here.
>
    > You can't go 'forest' from here.
>

(Your location remains `Your House`)

---

#### Scenario 3: Trying to Go `back` Too Far

- **You find yourself in:** `Your House` (the starting point)
>
    > --- Your House ---
    > Cozy, familiar, but your cat is missing! The only way out is the 'village'.
    > Exits: [village]
>
- **Your Command:** `back`

- **Game Output:** You can't go back further than where you began!
>
    > You can't go back any further.
>

(Your location remains `Your House`)

---

### 👀 Look: Examining Your Surroundings

Use `look` to get a more detailed description of your current location and potentially find hidden details.

#### Scenario: Looking around the Cave Entrance

- **You find yourself in:** `Cave Entrance (Bear)`
>
    > ---  Cave Entrance (Bear)  ---
    > A large, grumpy bear blocks the cave entrance! It seems agitated. Maybe something sweet would calm it? You can 'approach' the cave or go 'back' to the forest entrance.
    > Exits: [approach]
>
- **Your Command:** `look`

- **Game Output:** You take a closer look...
>
    > --- Looking Around Cave Entrance (Bear) ---
    > A large, grumpy bear blocks the cave entrance! It seems agitated. Maybe something sweet would calm it? You can 'approach' the cave or go 'back' to the forest entrance.
    > The bear looks really big and angry. Going near it seems like a bad idea.
    > Exits: [approach]
>

(You get a more detailed description of the area.)

---

### 🎒 Inventory: Checking Your Items

Type `inv` or `inventory` to see the items you are currently carrying.

#### Scenario 1: Checking an Empty Inventory

- **Current Inventory State:** Empty
- **Your Command:** `inventory`
- **Game Output:** You check your pockets...
>
    > ===================================================
    >                      INVENTORY
    > ===================================================
    > | Name       | Description                        |
    > |------------+------------------------------------|
    > ===================================================
>

(Your inventory is currently empty.)

---

#### Scenario 2: Checking Inventory with an Item

- **Current Inventory State:** You are carrying `Honey`.
- **Your Command:** `inv`
- **Game Output:** You check your pockets...
>
    > ===================================================
    >                         INVENTORY
    > ===================================================
    > | Name       | Description                        |
    > |------------+------------------------------------|
    > | Honey      | Sweet and Sticky!                  |
    > ===================================================
>

(You see the `Honey` you picked up earlier.)

---

### 🛠️ Use: Interacting with Items

Use items from your inventory by typing `use` followed by the item name. Items can only be used in specific locations or situations.

#### Scenario 1: Using an Item Successfully

- **You find yourself in:** `Cave Entrance (Bear)`
- **Current Inventory State:** You are carrying `Honey`.
- **Situation:** A grumpy bear blocks the path.
- **Your Command:** `use honey`
- **Game Output:** You offer the honey to the bear...
>
    > ---  Cave Entrance (Bear)  ---
    > The bear sniffs the honey, takes the jar, and seems much calmer now, licking happily. The entrance is clear! You can 'enter' the cave or go 'back' to the forest entrance.
    > Exits: [enter]
>

(The `Honey` is consumed, the bear is pacified, and a new path `enter` opens up.)

---

#### Scenario 2: Using an Item in the Wrong Place

- **You find yourself in:** `Village Square`
- **Current Inventory State:** You are carrying `Honey`.
- **Situation:** No apparent use for honey here.
- **Your Command:** `use honey`
- **Game Output:** You look around, but...
>
    > That doesn't seem to do anything here.
>

(The `Honey` remains in your inventory. Nothing changes in the location.)

---

#### Scenario 3: Trying to Use an Item Not Applicable (or Not Possessed)

- **You find yourself in:** `Cave Entrance (Bear)`
- **Current Inventory State:** You are carrying `Honey`.
- **Situation:** Bear blocks the path, but you try using something else.
- **Your Command:** `use silver key`
- **Game Output:** You fumble with a non-existent (or irrelevant) key...
>
    > You can't use 'silver key' here.
>

(Or, if you don't have the item: `You don't have 'silver key'!`)

(Nothing changes. The bear remains grumpy.)

---

### 🧠 Help: Getting Instructions

If you forget the commands, just type `help` or `instructions`.

#### Scenario: Requesting Help

- **Any Location**
- **Your Command:** `help`
- **Game Output:** The game reminds you how to play...

>
    > --- Instructions ---
    > Objective: Explore the world and find your lost furry friend.
    > Commands:
    >
    > 👟 Movement: Enter a direction shown in [brackets] (e.g., 'village', 'left') to move.
    >
    >       -> Enter 'back' to return to the previous location you visited.
    >
    > 👀 Look: Type 'look' to examine your current surroundings more closely for hints.
    >
    > 🎒 Inventory: Type 'inv' or 'inventory' to see your items.
    >
    >       -> Use [item]: Type 'use' followed by an item name (e.g., 'use honey').
    >
    > 👄 Talk: Type 'talk to' followed by an NPC name (e.g., 'talk to John Pork').
    >
    > 🧠 Instructions: Type 'help' or 'instructions' to see this message again.
    >
    > 💀 Quit: Type 'quit' to exit the game.
>

(You are shown the list of available commands.)

---

### 💀 Quit: Exiting the Game

Type `quit` to end your adventure.

#### Scenario: Ending the Game Session

- **Any Location**
- **Your Command:** `quit`
- **Game Output:** The game prepares to close...
>
    > Exiting game.
    > Time played: 0h 15m 32s
    > Rank: B
    > Total moves made: 42
    > Goodbye!
>

(The game exits, displaying your session statistics.)

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
