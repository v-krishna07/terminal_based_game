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
    items inventory[5];
}player;

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

