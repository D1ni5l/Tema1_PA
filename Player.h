#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Data;

struct Player {
    char *firstName;
    char *secondName;
    Data points;
};

struct Team {
    char *team_name;
    Data number_of_players;
    float team_points;
    struct Player *vect;  
    struct Team *next;
};

typedef struct Team Team;
typedef struct Player Player;

void addAtBeginning_for_team(Team **, char *, Data);
void addAtBeginning_for_Player(Player *, Data , char *, char *, Data );
void create_list(Team **, FILE *);
void free_team_members(Team *);
void free_Teams(Team *);
void print_Team_name(Team *, FILE *);
void print_teams_name_players_and_points(Team *);
