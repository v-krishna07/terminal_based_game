#include <stdio.h>
#include <string.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[1;0m"



void trash(){
    char trash;
    while((trash=getchar())!='\n'&& trash!=EOF){}
}
/*
//monsters
void mons(int health,int power){

};
//mc
void player(){
    int health=50; int power=5; int item_list[5];
    
    //powerpotion - 1, healing potion - 2, key- 3, lock -4, sword- 5, vest - 6, helmet -7 

}
*/
//map
void north_map(){
    char dir2;
    printf("Now u see 3 doors, 1 right, 1 left and 1 up ahead, Which door u want to 1 for right one, 2 for left one, 3 for center one and 4 to get back...\n Please enter: ");
    scanf(" %c",&dir2);
    trash();
    if(dir2=='1'||dir2=='2'||dir2=='3'||dir2=='4'){
        if(dir2=='1'){
            printf("So you selected this path....\n Now as you move forward you see 2 items.\n1. Power potion\n2. A key\nWhich will you select u can select both too....\n For selecting power potion select 1\nFor selecting key fragment(1/2) select 2\n You can take your time to select, if u want to select press 'i' that will open inventory\n");

        }
    }
    else{
        printf("You shouldn't select something out of the box just to be cool...\n Please enter something valid again...\n..\n");
        north_map();
    }
}
void east_map(){
    char dir2;
    printf("Now u see 3 doors, 1 right, 1 left and 1 up ahead, Which door u want to open 1 for right one, 2 for left one, 3 for center one and 4 to get back...\n Please enter: ");
    scanf(" %c",&dir2);
    trash();
    if(dir2=='1'||dir2=='2'||dir2=='3'||dir2=='4'){}
    else{
        printf("You shouldn't select something out of the box just to be cool...\n Please enter something valid again...\n..\n");
        east_map();
    }
}
void west_map(){
    char dir2;
    printf("Now u see 3 doors, 1 right, 1 left and 1 up ahead, Which door u want to open 1 for right one, 2 for left one, 3 for center one and 4 to get back....\n Please enter: ");
    scanf(" %c",&dir2);
    trash();
    if(dir2=='1'||dir2=='2'||dir2=='3'||dir2=='4'){}
    else{
        printf("You shouldn't select something out of the box just to be cool...\n Please enter something valid again...\n..\n");
        west_map();
    }
}
void south_map(){
    char dir2;
    printf("Now u see 3 doors, 1 right, 1 left and 1 up ahead, Which door u want to open 1 for right one, 2 for left one, 3 for center one and 4 to get back....\n Please enter: ");
    scanf(" %c",&dir2);
    trash();
    if(dir2=='1'||dir2=='2'||dir2=='3'||dir2=='4'){}
    else{
        printf("You shouldn't select something out of the box just to be cool...\n Please enter something valid again...\n..\n");
        south_map();
    }
}

//main map
void map(){
    char dir1;
    // char dir2,*collection;
    printf("Suppose u are in a dungeon, u have 4 ways u can go north,east,west and south...\nYour goal is to clear the dungeon by defeating the final boss but u don't know where the bosses are..\nNow in which direction u want to go first N,E,W or S.\n Enter here: ");
    scanf("%c",&dir1);
    trash();
        
    if(dir1=='N'||dir1=='n'||dir1=='W'||dir1=='w'||dir1=='E'||dir1=='e'||dir1=='S'||dir1=='s'){
        if(dir1=='N'||dir1=='n'){north_map();} 
        else if(dir1=='W'||dir1=='w'){west_map();}
        else if(dir1=='E'||dir1=='e'){east_map();}
        else{south_map();}
    }
    else{printf("Please try again with valid character....\nOh so u made a mistake no problem everyone makes...\n Now let's restart again...\n..\n..\n..\n..\n..\n");map();}

}

int main(){
    while(1){
        //starting loop
        char strt;
        printf(BLUE "Welcome to the text game simulation.\n If u want to start the game press s\n If u want to exit press q\n Please Type: "RESET   );
        scanf(" %c",&strt);
        trash();
        if (strt=='q'){printf("Your are exited from the game...\n");break;}
        else if(strt=='s'){printf("Your game shall begin in few moments...\n");}
        else{printf("Please enter a valid character...\n");continue;}
        map();

    }
}

