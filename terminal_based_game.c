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

// Initialize players with explicitly cleared item slots
player p = {
    .health = 100, 
    .power = 10, 
    .inventory = {
        {"None", "", 0}, {"None", "", 0}, {"None", "", 0}, {"None", "", 0}, {"None", "", 0}
    }
};

typedef struct{
    int health;
    int power;
}monster;

monster m1={.health = 200,.power=30};
monster m2={.health = 300,.power=40};
monster m3={.health = 300,.power=50};
monster m4={.health = 400,.power=70};
monster m_main={.health = 500, .power=100};


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

void trash() {
    char trash;
    while ((trash = getchar()) != '\n' && trash != EOF);
}

// Global inventory check to look for a "Key"
bool has_key() {
    for (int i = 0; i < 5; i++) {
        if (p.inventory[i].name != NULL && strcmp(p.inventory[i].name, "Key") == 0) {
            return true;
        }
    }
    return false;
}

void data() {
    direction[0] = (Direction){
        .dir = "North",
        .rooms = {
            {
                .room_num = 1, .room_name = "North Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 2, .room_name = "North Room 2",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"Stamina Potion", "Restores 20 stamina points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 3, .room_name = "North Room 3",
                .item = {{"None", "", 0}, {"None", "", 0}},
                .monster = true
            }
        }
    };
    direction[1] = (Direction){
        .dir = "South",
        .rooms = {
            {
                .room_num = 1, .room_name = "South Room 1",
                .item = {
                    {"Shield fragment", "A sturdy piece of armor that increases your defense.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 2, .room_name = "South Room 2",
                .item = {
                    {"Shield fragment", "A sturdy piece of armor that increases your defense.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 3, .room_name = "South Room 3",
                .item = {{"None", "", 0}, {"None", "", 0}},
                .monster = true
            }
        }
    };
    direction[2] = (Direction){
        .dir = "East",
        .rooms = {
            {
                .room_num = 1, .room_name = "East Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"None", "", 0}
                },
                .monster = false
            },
            {
                .room_num = 2, .room_name = "East Room 2",
                .item = {
                    {"Key", "A key that opens a locked door.", 0},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 3, .room_name = "East Room 3",
                .item = {{"None", "", 0}, {"None", "", 0}},
                .monster = true
            }
        }
    };
    direction[3] = (Direction){
        .dir = "West",
        .rooms = {
            {
                .room_num = 1, .room_name = "West Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"None", "", 0}
                },
                .monster = false
            },
            {
                .room_num = 2, .room_name = "West Room 2",
                .item = {
                    {"Buff potion", "A potion that decreases enemy power.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 3, .room_name = "West Room 3",
                .item = {{"None", "", 0}, {"None", "", 0}},
                .monster = true
            }
        }
    };
}

// Forward declarations using dynamic returns to keep tracking variables safe
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
            return; // Breaks the loop and drops cleanly back into direction_conditioning()
        } 
        else if (room_no == 1 || room_no == 2) {
            printf("\nNow u are in " BLUE "%s" RESET "\n", direction[dir_no-1].rooms[room_no-1].room_name);
            item_selection(dir_no, room_no);
        } 
        else if (room_no == 3) {
            if (has_key()) {
                printf(GREEN "You unlocked the Boss door with your key! The ultimate challenge begins..." RESET "\n");monster_defense(m1);
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
        
        // Item 1 Guard Check
        if (current_room->item[0].name != NULL && strcmp(current_room->item[0].name, "None") != 0 && strcmp(current_room->item[0].name, "") != 0) {
            printf("1. %s (%s)\n", current_room->item[0].name, current_room->item[0].usage);
        } else {
            printf("1. [Empty pedestal]\n");
        }
        
        // Item 2 Guard Check
        if (current_room->item[1].name != NULL && strcmp(current_room->item[1].name, "None") != 0 && strcmp(current_room->item[1].name, "") != 0) {
            printf("2. %s (%s)\n", current_room->item[1].name, current_room->item[1].usage);
        } else {
            printf("2. [Empty pedestal]\n");
        }

        printf("\nSo which item will you select? Press 1 for 1st item \nPress 2 for 2nd item\nPress 3 to get back\nPress 4 to Quit\nPlease Type: ");
        if (scanf(" %d", &item_no) != 1) { trash(); continue; }
        trash();

        if (item_no == 4) {
            printf("You will be exiting from the game...\n");
            exit(0);
        } 
        else if (item_no == 3) {
            printf("Stepping out of the room...\n");
            return; // Cleanly returns to the room choices
        } 
        else if (item_no == 1 || item_no == 2) {
            items *selected_item = &current_room->item[item_no - 1];

            // Verify the selected item actually exists
            if (selected_item->name != NULL && strcmp(selected_item->name, "None") != 0 && strcmp(selected_item->name, "") != 0) {
                printf(GREEN "\n%s will be added to your inventory!\n" RESET, selected_item->name);
                
                int i = 0;
                bool added = false;
                while(i < 5) {
                    if (strcmp(p.inventory[i].name, "None") == 0) {
                        p.inventory[i] = *selected_item; // Safe complete structure assignment
                        added = true;

                        printf("Item successfully added to inventory slot %d!\n", i + 1);
                        printf("To check inventory Press 1\nTo keep moving Press any other key: ");
                        char inv_choice;
                        scanf(" %c", &inv_choice);
                        trash();

                        if (inv_choice == '1') {
                            printf("\nItems in your inventory are: [ ");
                            for (int a = 0; a < 5; a++) {
                                printf("%s | ", p.inventory[a].name);
                            }
                            printf("]\n");
                        }
                        break;
                    }
                    i++;
                }

                if (!added) {
                    printf(RED "Your inventory is completely full!\n" RESET);
                } else {
                    // Erase the item from the map world memory only after successful pickup
                    *selected_item = (items){"None", "", 0};
                }
            } 
            else {
                printf(RED "Sorry, this item was already picked up or is not here!\n" RESET);
            }
        } 
        else {
            printf("Please type a valid option.\n");
        }
    }
}

void monster_defense(monster m){
    printf(RED "Here is the first monster you gonna face" RESET);
    printf("The front monster has health - %d, power - %d",m.health,m.power);
    int initial_h = p.health;
    int initial_p = p.power;
    while(p.health>0 || m.health>0){
        p.health = p.health-m.power;
        m.health = m.health-p.power;
        if(p.health!=0 && m.health==0){
            printf(GREEN"You have defeated the monster as a reward...."RESET);
            printf(BLUE"You recieved health +50, power +20,you health and power has been restored, and a door to go to another monster....\n"RESET);
        }else{printf("You are defeated try again....\n");direction_conditioning();}
        p.health = initial_h+50;
        p.power = initial_p+20;
    }
}




int main() {
    data();
    printf("--- Now you are in the dungeon ---\n");
    direction_conditioning(); 
    return 0;
}