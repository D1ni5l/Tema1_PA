#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Data;

struct Player {
    char *firstName;
    char *secondName;
    Data points;
};
typedef struct Player Player;

struct Team {
    char *team_name;
    Data number_of_players, teams_number;
    float team_points;
    struct Player *vect;  
    struct Team *next;
};
typedef struct Team Team;

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

struct BST_Node {
    Team *team;
    struct BST_Node *left;
    struct BST_Node *right;
};
typedef struct BST_Node BSTNode;

struct AVL_Node {
    Team *team;
    struct AVL_Node *left;
    struct AVL_Node *right;
    Data height;
};
typedef struct AVL_Node AVLNode;

void addAtBeginning_for_team(Team **, char *, Data);
void addAtBeginning_for_Player(Player *, Data , char *, char *, Data );
void create_list(Team **, FILE *);
void print_Team_name(Team *, FILE *);
float Team_points(Team *);
void Team_deduction( Team **);
float increase_team_points( Team *);
void free_team_members(Team *);
void free_Team(Team **);
void free_Teams(Team **);

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
void Stack_repartition( Queue *, Stack **, Stack **);
void print_win_team( Team *, FILE* );
void create_round_from_stack(Stack *, Queue* , FILE *);
void printStack_and_create_Queue(Stack *, FILE*, Team **, Queue *);
void team_copy(Team **, Team *);

BSTNode *insert_BST( BSTNode *, Team *); 
BSTNode *newNode_BST( Team *);
void print_BST_in_descending_order(BSTNode *, FILE *);
void addAtBeginning_for_list(Team **, Team *);
void list_from_BST(BSTNode *, Team **);
void free_BST(BSTNode *);

int height(AVLNode *);
int max(Data, Data );
AVLNode* newNode_AVLNode(Team *);
void print_level_AVL(AVLNode *, Data , FILE *);
AVLNode *rightRotation(AVLNode *);
AVLNode *leftRotation(AVLNode *);
int getBalance(AVLNode *);
AVLNode* insert_AVLNode(AVLNode* , Team *);
void free_AVL(AVLNode *);

void first_task(FILE *, FILE *);
void second_task( Team **,FILE *, FILE *);
void third_task(Team **,Team **, Queue *, FILE *);
void fourth_task(Team **, BSTNode **, FILE *);
void fiveth_task(Team **, BSTNode *, AVLNode **, FILE *);