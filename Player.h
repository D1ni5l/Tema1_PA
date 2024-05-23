#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Data;

struct Player {
    char *firstName;
    char *secondName;
    Data points;
};

typedef struct Team Team;
typedef struct Player Player;

struct Team {
    char *team_name;
    Data number_of_players, teams_number;
    float team_points;
    struct Player *vect;  
    struct Team *next;
};

struct node{
     Team *team_1;
     Team *team_2;
     struct node *next;
};
typedef struct node Node;
struct queue{
    Node *front;
    Node *rear;
};
typedef struct queue Queue;

struct stack{
  Team *team;
  struct stack *next;
};
typedef struct stack Stack;

void addAtBeginning_for_team(Team **, char *, Data);
void addAtBeginning_for_Player(Player *, Data , char *, char *, Data );
void create_list(Team **, FILE *);
void free_team_members(Team *);
void free_Teams(Team *);
void print_Team_name(Team *, FILE *);
void print_teams_name_players_and_points(Team *, FILE *);
float Team_points(Team *);
void Team_deduction( Team **);
void free_Team(Team *);
float increase_team_points( Team *);

Queue* createQueue();
void enQueue(Queue *, Team *, Team * );
Node* deQueue(Queue *);
int isEmpty(Queue*);
void deleteQueue(Queue *);
void print_Queue( Queue *,FILE*);
void print_Winners( Queue *, FILE *);

int isEmpty_Stack(Stack*);
void deleteStack(Stack **);
Team* pop(Stack **);
void push(Stack **, Team *); 
Team* top_Stack(Stack *);
void Stack_repartition( Queue *, Stack **, Stack **);
void print_win_team( Team *, FILE* );
void create_round_from_stack(Stack *, Queue* , FILE *);
void printStack_and_create_Queue(Stack *, FILE*, Team **, Queue *);
void team_copy(Team **, Team *);
