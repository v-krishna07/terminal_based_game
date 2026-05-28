# 🗡️ Terminal-Based Dungeon Game

A text-based dungeon crawler written in C. This project focuses on utilizing nested `struct` architecture, memory-safe pointer handling, dynamic inventory arrays, and controlled logic loops to create an interactive map system.

## 🗺️ Current Game Architecture
The game world is built using a deeply nested structure to handle areas dynamically:
* **The Hub:** The player starts in a central area with 4 directional choices (North, South, East, West).
* **The Corridors:** Each direction contains 3 distinct rooms.
* **The Rooms:** * Rooms 1 and 2 in each direction contain up to 2 lootable items (Weapons, Shields, Potions, Buffs, or Keys).
  * Room 3 in every direction is a locked **Boss Room**.
* **The Inventory:** The player has a persistent 5-slot inventory array that tracks items picked up from the floor. 

## 🛠️ Technical Milestones Achieved
* **Safe Map Indexing:** Refactored multidimensional array calls to prevent out-of-bounds pointer crashes (Segmentation Faults).
* **Clean Loop Flow:** Replaced infinite recursive function calls with `return` breaks to prevent Stack Overflows when moving backward through menus.
* **Memory Management:** Implemented strict `NULL` and `"None"` guard checks so players cannot interact with empty memory slots or infinitely duplicate items on the floor.
* **Inventory System:** Built a dynamic inventory scanner that finds the first empty slot, saves the item, and physically removes the item from the room data.
* **Boss Key Logic:** Wired a global inventory checker (`has_key()`) that scans the player's backpack to grant or deny access to Room 3.

## 🚀 How to Run the Game
1. Compile the file using GCC:
   ```bash
   gcc terminal_based_game.c -o dungeon_game