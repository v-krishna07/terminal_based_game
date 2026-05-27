#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define RESET "\033[1;0m"


typedef struct{
    char *name;
    char *usage;
    int ability;
}items;


typedef struct{
    int health;
    int power;
    // items inventory[5];
}player;

player p = {100,10};

typedef struct{
    char *room_num;
    items item[2];
    bool monster;
}room;

typedef struct{
    char *dir;
    room rooms[3];
}dir;

typedef struct{
    int health;
    int power;
}monster;

void trash(){
    char trash;
    while((trash = getchar()) != '\n' && trash != EOF);
}

typedef struct {
    char *dir;
    room rooms[3]; // 3 rooms deep in each direction
} Direction;

Direction direction[4];



void data(){
    direction[0] = (Direction){
        .dir = "North",
        .rooms = {
            {
                .room_num = "North Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = "North Room 2",
                .item = {},                    
                .monster = true
            },
            {
                .room_num = "North Room 3",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"Stamina Potion", "Restores 20 stamina points.", 20}
                },
                .monster = false
            }
        }
    };
    direction[1] = (Direction){
        .dir = "South",
        .rooms = {
            {
                .room_num = "South Room 1",
                .item = {
                    {"Shield fragment", "A sturdy piece of armor that increases your defense.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = "South Room 2",
                .item = {0},
                .monster = true
            },
            {
                .room_num = "South Room 3",
                .item = {
                    {"Shield fragment", "A sturdy piece of armor that increases your defense.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            }
        }
    };
    direction[2] = (Direction){
        .dir = "East",
        .rooms = {
            {
                .room_num = "East Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {0}
                },
                .monster = false
            },
            {
                .room_num = "East Room 2",
                .item = {0},
                .monster = true
            },
            {
                .room_num = "East Room 3",
                .item = {
                    {"Key", "A key that opens a locked door.", 0},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            }
        }
    };
    direction[3] = (Direction){
        .dir = "West",
        .rooms = {
            {
                .room_num = "West Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {0}
                },
                .monster = false
            },
            {
                .room_num = "West Room 2",
                .item = {0},
                .monster = true
            },
            {
                .room_num = "West Room 3",
                .item = {
                    {"Buff potion", "A potion that decreases enemy power.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            }
        }
    };

}

void monster_data(){
    monster m1 = {100, 50};
    monster m2 = {150, 70};
    monster m3 = {200, 100};
    monster m4 = {250, 150};
    monster final_boss = {500, 200};
}

int main(){
    data();
    monster_data();
    return 0;
}