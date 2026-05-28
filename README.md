# 🗡️ Terminal-Based Dungeon Game

A text-based dungeon crawler written in C. This project was built to master memory-safe pointer handling, deeply nested custom data structures (`struct`), dynamic inventory management, and bounded logic loops.

## 📜 Origin & Credits
* **Developer:** Krishna
* **Concept & Prompt:** The core project challenge prompt was provided by **Claude**.
* **Debugging & Polish:** Code architecture debugging, segmentation fault resolution, and final touches assisted by **Gemini**.

## 🗺️ Game Architecture & Features
The game world relies on a nested structure to handle areas dynamically without hardcoding state checks:
* **The Hub:** The player spawns in a central area with 4 directional corridors (North, South, East, West).
* **The Rooms:** Each direction contains 3 rooms. Rooms 1 and 2 contain loot. Room 3 is a locked Boss Room.
* **The Inventory:** A dynamic 5-slot array. Players can pick up items, which are physically removed from the floor memory. 
* **Item Consumption:** Players can consume potions to restore HP or equip weapons/armor to permanently scale their attack and defense stats.
* **Combat System:** A turn-based combat loop against structurally defined monsters that scales dynamically depending on the player's current loaded stats.
* **Win State:** A global tracking system monitors boss defeats. Clearing all 4 directional boss rooms triggers the victory sequence.

## 🛠️ Technical Milestones Achieved
* **Memory Management:** Implemented strict `NULL` and `"None"` guard checks to prevent interacting with empty memory slots or duplicating ground items.
* **Safe Map Indexing:** Refactored multidimensional array calls to eliminate out-of-bounds pointer crashes.
* **Stat Scaling:** Resolved variable shadowing bugs to ensure item buffs permanently attach to the player state prior to boss encounters.
* **Clean Loop Flow:** Replaced mutual recursion with standard `return` breaks to prevent Stack Overflows during deep menu navigation.

## 🚀 How to Run the Game
1. Compile the C file using GCC:
   ```bash
   gcc terminal_based_game.c -o dungeon_game```
2. ```./dungeon_game