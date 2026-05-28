#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define RESET "\033[1;0m"

typedef struct {
    char *name;
    char *usage;
    int ability;
} items;

typedef struct {
    int health;
    int power;
    items inventory[5];
} player;

player p = {
    .health = 100, 
    .power = 10, 
    .inventory = {
        {"None", "", 0}, {"None", "", 0}, {"None", "", 0}, {"None", "", 0}, {"None", "", 0}
    }
};

typedef struct {
    int health;
    int power;
} monster;

monster m1 = {.health = 200, .power = 15};
monster m2 = {.health = 300, .power = 20};
monster m3 = {.health = 300, .power = 25};
monster m4 = {.health = 400, .power = 35};
monster m_main = {.health = 500, .power = 50};

typedef struct {
    int room_num;
    char *room_name;
    items item[2];
    bool monster;
} room;

typedef struct {
    char *dir;
    room rooms[3]; 
} Direction;

Direction direction[4];
int bosses_defeated = 0;

void trash() {
    char trash;
    while ((trash = getchar()) != '\n' && trash != EOF);
}

bool has_key() {
    for (int i = 0; i < 5; i++) {
        if (p.inventory[i].name != NULL && strcmp(p.inventory[i].name, "Key") == 0) {
            return true;
        }
    }
    return false;
}

void use_item(items *item) {
    if (item->name == NULL || strcmp(item->name, "None") == 0) {
        printf(RED "\nThere is no item in this slot to use!\n" RESET);
        return;
    }

    printf("\n--- Using Item: %s ---\n", item->name);

    if (strcmp(item->name, "Health Potion") == 0 || strcmp(item->name, "Stamina Potion") == 0) {
        p.health += item->ability;
        printf(GREEN "Success! You consumed %s.\n" RESET, item->name);
        printf(YELLOW "Health boosted by +%d! (Current Health: %d)\n" RESET, item->ability, p.health);
        *item = (items){"None", "", 0};
    } 
    else if (strcmp(item->name, "Sword fragment") == 0 || strcmp(item->name, "Buff potion") == 0) {
        p.power += item->ability;
        printf(GREEN "Success! You equipped/consumed %s.\n" RESET, item->name);
        printf(YELLOW "Power boosted by +%d! (Current Power: %d)\n" RESET, item->ability, p.power);
        *item = (items){"None", "", 0};
    }
    else if (strcmp(item->name, "Shield fragment") == 0) {
        p.health += item->ability;
        printf(GREEN "Success! You equipped %s.\n" RESET, item->name);
        printf(YELLOW "Defense/Health boosted by +%d! (Current Health: %d)\n" RESET, item->ability, p.health);
        *item = (items){"None", "", 0};
    }
    else if (strcmp(item->name, "Key") == 0) {
        printf(BLUE "This is a Key! You cannot consume it. Keep it in your inventory to unlock Boss Rooms.\n" RESET);
    }
}

void data() {
    direction[0] = (Direction){
        .dir = "North",
        .rooms = {
            {1, "North Room 1", {{"Sword fragment", "Increases attack power.", 5}, {"Health Potion", "Restores 20 HP.", 20}}, false},
            {2, "North Room 2", {{"Sword fragment", "Increases attack power.", 5}, {"Stamina Potion", "Restores 20 SP.", 20}}, false},
            {3, "North Boss Room", {{"None", "", 0}, {"None", "", 0}}, true}
        }
    };
    direction[1] = (Direction){
        .dir = "South",
        .rooms = {
            {1, "South Room 1", {{"Shield fragment", "Increases defense.", 5}, {"Health Potion", "Restores 20 HP.", 20}}, false},
            {2, "South Room 2", {{"Shield fragment", "Increases defense.", 5}, {"Health Potion", "Restores 20 HP.", 20}}, false},
            {3, "South Boss Room", {{"None", "", 0}, {"None", "", 0}}, true}
        }
    };
    direction[2] = (Direction){
        .dir = "East",
        .rooms = {
            {1, "East Room 1", {{"Sword fragment", "Increases attack power.", 5}, {"None", "", 0}}, false},
            {2, "East Room 2", {{"Key", "Opens a locked boss door.", 0}, {"Health Potion", "Restores 20 HP.", 20}}, false},
            {3, "East Boss Room", {{"None", "", 0}, {"None", "", 0}}, true}
        }
    };
    direction[3] = (Direction){
        .dir = "West",
        .rooms = {
            {1, "West Room 1", {{"Sword fragment", "Increases attack power.", 5}, {"None", "", 0}}, false},
            {2, "West Room 2", {{"Buff potion", "Decreases enemy power.", 5}, {"Health Potion", "Restores 20 HP.", 20}}, false},
            {3, "West Boss Room", {{"None", "", 0}, {"None", "", 0}}, true}
        }
    };
}

void direction_conditioning();
void room_conditioning(int dir_no);
void item_selection(int dir_no, int room_no);
void monster_defense(monster m);

void direction_conditioning() {
    int dir_no;
    while(1) {
        printf("\nYou have 4 directions to go. Which direction will you choose N,E,W,S?\n");
        printf("Please enter(1 for North, 2 for South, 3 for East, 4 for West and 5 to quit): ");
        if (scanf(" %d", &dir_no) != 1) { trash(); continue; }
        trash();
        
        if (dir_no >= 1 && dir_no <= 4) {
            printf("\nNow you are in " YELLOW "%s" RESET " direction\n", direction[dir_no-1].dir);
            room_conditioning(dir_no); 
        } 
        else if (dir_no == 5) {
            printf("Thank you for playing the game....\n");
            exit(0);
        } 
        else {
            printf(RED "Please enter a correct direction number...\n" RESET);
        }
    }
}

void room_conditioning(int dir_no) {
    int room_no;
    while (1) {
        printf("\nNow you see 3 rooms in front of you out of which 1 has boss and u require key to open it...\n");
        printf("To open Room 1 click 1,\nTo open Room 2 click 2,\nTo open boss Room click 3\nTo get back Click 4,\nTo Quit click 5,\nType Here: ");
        if (scanf(" %d", &room_no) != 1) { trash(); continue; }
        trash();
        
        if (room_no == 4) {
            printf("Going back to the main hub...\n");
            return; 
        } 
        else if (room_no == 1 || room_no == 2) {
            printf("\nNow u are in " BLUE "%s" RESET "\n", direction[dir_no-1].rooms[room_no-1].room_name);
            item_selection(dir_no, room_no);
        } 
        else if (room_no == 3) {
            if (has_key()) {
                printf(GREEN "You unlocked the Boss door with your key! The battle begins..." RESET "\n");
                if (dir_no == 1) monster_defense(m1);
                else if (dir_no == 2) monster_defense(m2);
                else if (dir_no == 3) monster_defense(m3);
                else if (dir_no == 4) monster_defense(m4);
                direction[dir_no-1].rooms[room_no-1].monster = false;

                // ---- ADD THE WIN CHECK HERE ----
                if (bosses_defeated == 4) {
                    printf(YELLOW "\n🏆🏆🏆 CONGRATULATIONS! 🏆🏆🏆\n" RESET);
                    printf(GREEN "You have conquered all 4 legendary monsters and cleared the dungeon!\n" RESET);
                    printf(BLUE "You are the ultimate champion. Thank you for playing!\n\n" RESET);
                    exit(0);
                }
                // --------------------------------
            } else {
                printf(RED "The door is sealed shut! You need to find a 'Key' from the other rooms first.\n" RESET);
            }
        } 
        else if (room_no == 5) {
            printf("You will be exiting from the game...\n");
            exit(0);
        } 
        else {
            printf(RED "Please enter a valid number...\n" RESET);
        }
    }
}

void item_selection(int dir_no, int room_no) {
    int item_no;
    room *current_room = &direction[dir_no-1].rooms[room_no-1];

    while(1) {
        printf("\nNow as you move in this room you see 2 items:\n");
        if (current_room->item[0].name != NULL && strcmp(current_room->item[0].name, "None") != 0) {
            printf("1. %s (%s)\n", current_room->item[0].name, current_room->item[0].usage);
        } else { printf("1. [Empty pedestal]\n"); }
        
        if (current_room->item[1].name != NULL && strcmp(current_room->item[1].name, "None") != 0) {
            printf("2. %s (%s)\n", current_room->item[1].name, current_room->item[1].usage);
        } else { printf("2. [Empty pedestal]\n"); }

        printf("\nPress 1 for 1st item\nPress 2 for 2nd item\nPress 3 to get back\nPress 4 to Quit\nPlease Type: ");
        if (scanf(" %d", &item_no) != 1) { trash(); continue; }
        trash();

        if (item_no == 4) exit(0);
        else if (item_no == 3) return;
        else if (item_no == 1 || item_no == 2) {
            items *selected_item = &current_room->item[item_no - 1];

            if (selected_item->name != NULL && strcmp(selected_item->name, "None") != 0) {
                printf(GREEN "\n%s added to your inventory!\n" RESET, selected_item->name);
                
                bool added = false;
                for (int i = 0; i < 5; i++) {
                    if (strcmp(p.inventory[i].name, "None") == 0) {
                        p.inventory[i] = *selected_item;
                        *selected_item = (items){"None", "", 0}; 
                        added = true;

                        printf("Item added to inventory slot %d!\n", i + 1);
                        printf("To check/use inventory Press 1\nTo keep moving Press any other key: ");
                        char inv_choice;
                        scanf(" %c", &inv_choice);
                        trash();

                        if (inv_choice == '1') {
                            while(1) {
                                printf("\n=== CURRENT INVENTORY ===");
                                for (int a = 0; a < 5; a++) {
                                    printf("\nSlot %d: %s", a + 1, p.inventory[a].name);
                                }
                                printf("\n=========================");
                                printf("\nYour Stats -> Health: %d | Power: %d", p.health, p.power);
                                printf("\n\nEnter a slot number (1-5) to USE/EQUIP an item, or 0 to go back: ");
                                
                                int slot_choice;
                                if (scanf(" %d", &slot_choice) != 1) { trash(); continue; }
                                trash();

                                if (slot_choice == 0) break;
                                else if (slot_choice >= 1 && slot_choice <= 5) {
                                    use_item(&p.inventory[slot_choice - 1]);
                                } else {
                                    printf(RED "Invalid slot selection!\n" RESET);
                                }
                            }
                        }
                        break;
                    }
                }
                if (!added) printf(RED "Your inventory is completely full!\n" RESET);
            } else { printf(RED "Nothing here to pick up!\n" RESET); }
        }
    }
}

void monster_defense(monster m) {
    printf(RED "\n⚔️ A dangerous monster blocks your path! ⚔️\n" RESET);
    printf("Monster Stats -> Health: %d | Power: %d\n", m.health, m.power);
    printf("Your Stats    -> Health: %d | Power: %d\n\n", p.health, p.power);
    
    int initial_h = p.health;
    int initial_p = p.power;

    while (p.health > 0 && m.health > 0) {
        printf("You strike the monster for %d damage!\n", p.power);
        m.health -= p.power;

        if (m.health <= 0) break; 

        printf("The monster counters and hits you for %d damage!\n", m.power);
        p.health -= m.power;
    }

    if (p.health > 0) {
        printf(GREEN "\n🎉 You have defeated the monster! 🎉\n" RESET);
        printf(BLUE "Reward: Your health and power are restored, plus you gain +50 Max HP and +20 Power!\n" RESET);
        
        p.health = initial_h + 50;
        p.power = initial_p + 20;
        bosses_defeated++;
    } 
    else {
        printf(RED "\n💀 You were defeated... Game Over! 💀\n" RESET);
        exit(0); 
    }
}

int main() {
    
    data();
    printf("--- Now you are in the dungeon ---\n");
    direction_conditioning(); 
    return 0;
}