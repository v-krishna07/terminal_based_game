#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define RESET "\033[1;0m"


void trash(){
    char trash;
    while((trash=getchar())!='\n'&& trash!=EOF){}
}


struct map{
    int dir[4];
    int room[3];
    int items[2];
    int boss_room[1];
};
struct player{
    int health;
    int power;
    int checklist[5];
};
struct player p_main = {100,10};

int maps(int room_index){
    //dir - 0 for north, 1 for east, 2 for west and 3 for south
    //room - 0 for normal room, 1 for item room and 2 for boss room
    printf("Now choose which room you want to enter...\n1 for right one, 2 for left one, 3 for center one, 4 to get back and 5 to quite the game....\n Please enter: ");
    char dir2;
    scanf(" %c",&dir2);
    trash();
    if(dir2=='1'||dir2=='2'||dir2=='3'||dir2=='4'||dir2=='5'){
        if(dir2=='1'){
            printf("You have entered the right door...\nNow as you move forward you see 2 items\nWhich will you select you can select both if u have enough storage");
            if(maps(0)){
                printf("Press 1 for Power potion that instantly increases your power by 5\nPress 2 for key that may help you to open the boss gate\nPress any other key to get back to the entry\n Please enter: ");
                char inv;
                scanf(" %c",&inv);
                trash();
                if(inv=='1'){
                    printf("You have selected power potion\n Your power has been increased by 5\n");
                    p_main.power+=5;
                    printf("Now that u have selected 1 item u will be back ...\n");
                    maps(0);
                }
                else if(inv=='2'){
                    printf("You have selected key\n You have gained 1 key that can help you open the boss room\n");
                    p_main.checklist[0]=3;
                    printf("Now that u have selected 1 item u will be back ...\n");
                    maps(0);
                }
                else{
                    printf("Now u will be sent back as u don't want to open inventory...\n");
                    maps(0);
                }
            }
            else if(maps(1)){
                printf("Press 1 for Health potion that can increase your health by 50\nAlso you see a sword that can increase your power by 10\nPress any other key to get back to the entry\n Please enter: ");
                char inv;
                scanf(" %c",&inv);
                trash();
                if(inv=='1'){
                    printf("You have selected health potion\n Your health has been increased by 50\n");
                    p_main.health+=50;
                    printf("Now that u have selected 1 item u will be back ...\n");
                    maps(0);
                }
                else if(inv=='2'){
                    printf("You have selected sword\n You have gained a sword that can help you open the boss room\n");
                    p_main.checklist[1]=5;
                    printf("Now that u have selected 1 item u will be back ...\n");
                    maps(0);
                }
                else{
                    printf("Now u will be sent back as u don't want to open inventory...\n");
                    maps(0);
                }
            }
        }
    }
}

int initial(){
    printf("Suppose u are in a dungeon, u have 4 ways u can go north,east,west and south...\nYour goal is to clear the dungeon by defeating the final boss but u don't know where the bosses are..\nNow in which direction u want to go first N,E,W or S.\n Enter here: ");
    char dir1;
    scanf(" %c",&dir1);
    trash();
    if(dir1=='N'||dir1=='n'||dir1=='W'||dir1=='w'||dir1=='E'||dir1=='e'||dir1=='S'||dir1=='s'){
        if(dir1=='N'||dir1=='n'){printf("So you have decided to go this way....\n");maps(0);} 
        else if(dir1=='W'||dir1=='w'){printf("So you have decided to go this way....\n");maps(1);}
        else if(dir1=='E'||dir1=='e'){printf("So you have decided to go this way....\n");maps(2);}
        else{printf("So you have decided to go this way....\n");maps(3);}
    }
    else{
        printf("Please try again with valid character....\nOh so u made a mistake no problem everyone makes...\n Now let's restart again...\n..\n..\n..\n..\n..\n");
        initial();
    }
}



int main(){
    while(p_main.health>0){
        //starting
        char strt;
        printf("Welcome to the text game simulation.\n If u want to start the game press s\n If u want to exit press q\n Please Type: "   );
        scanf(" %c",&strt);
        trash();
        if (strt=='q'){printf("Your are exited from the game...\n");break;}
        else if(strt=='s'){
            printf("Your game shall begin in few moments...\n");
            
        }
        else{printf("Please enter a valid character...\n");continue;}
    }
}