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
    int room_num;
    char *room_name;
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
                .room_num = 1,
                .room_name = "North Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 2,
                .room_name = "North Room 2",
                .item = {},                    
                .monster = true
            },
            {
                .room_num = 3,
                .room_name = "North Room 3",
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
                .room_num = 1,
                .room_name = "South Room 1",
                .item = {
                    {"Shield fragment", "A sturdy piece of armor that increases your defense.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            },
            {
                .room_num = 2,
                .room_name = "South Room 2",
                .item = {},
                .monster = true
            },
            {
                .room_num = 3,
                .room_name = "South Room 3",
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
                .room_num = 1,
                .room_name = "East Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {}
                },
                .monster = false
            },
            {
                .room_num = 2,
                .room_name = "East Room 2",
                .item = {},
                .monster = true
            },
            {
                .room_num = 3,
                .room_name = "East Room 3",
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
                .room_num = 1,
                .room_name = "West Room 1",
                .item = {
                    {"Sword fragment", "A sharp blade that increases your attack power.", 5},
                    {}
                },
                .monster = false
            },
            {
                .room_num = 2,
                .room_name = "West Room 2",
                .item = {},
                .monster = true
            },
            {
                .room_num = 3,
                .room_name = "West Room 3",
                .item = {
                    {"Buff potion", "A potion that decreases enemy power.", 5},
                    {"Health Potion", "Restores 20 health points.", 20}
                },
                .monster = false
            }
        }
    };

}

/*void monster_data(){
    monster m1 = {100, 50};
    monster m2 = {150, 70};
    monster m3 = {200, 100};
    monster m4 = {250, 150};
    monster final_boss = {500, 200};
}
*/
void room_conditioning(int dir_no,int room_no);
void direction_conditioning(int dir_no,int room_no){
    
    printf("you have 4 directions to go which diection will you choose N,E,W,S,\nPlease enter(1 for North, 2 for East, 3 for West, 4 for South and 5 to quit):");
    scanf(" %d",&dir_no);
    trash();
    if(dir_no<=4){printf("Now you are in %s direction",direction[dir_no-1].dir);room_conditioning(dir_no,room_no);}
    else if(dir_no==5){printf("Thank you for playing the game....");exit(0);}
    else{printf("Please enter the correct room number...\n");direction_conditioning(dir_no,room_no);}
}

void room_conditioning(int dir_no,int room_no){
    while (1){
        printf("Now you see 3 rooms in front of you out of which 1 has boss and u require key to open it...\n");
        printf("To open Room 1 click 1,\nTo open Room 2 click 2,\nTo open boss Room click 3\n To get back Click 4,\nTo Quit click 5,\nType Here:");
        scanf(" %d",&room_no);
        trash();
        if(room_no==4){printf("So you have been sent back...Now\n"),direction_conditioning(dir_no,room_no);}
        else if(room_no<=3){
            printf("Now u are in %s \n",direction[dir_no-1].rooms[room_no-1].room_name);
        }
        else if(room_no==5){printf("You will be exiting from the game...\n");exit(0);}
        else{printf("Please enter a valid number...\n");continue;}
    }

}

int main(){
    data();
    //monster_data();
    int dir_no=0;
    int room_no=0;
    printf("Now you are in the dungeon");
    direction_conditioning(dir_no,room_no);
    room_conditioning(dir_no,room_no);
    return 0;
}