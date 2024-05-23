#include "Player.h"
#define LINE_LENGHT 34

int isEmpty_Stack(Stack*top){
	return top==NULL;
}

void deleteStack(Stack **top) {
    Stack *temp;
    while ( (*top) != NULL) {
        temp = (*top);
        (*top) = (*top)->next;
        free(temp);
    }
}

Team* pop(Stack **top) {
    if (isEmpty_Stack(*top)) return NULL; 
    Stack *temp = (*top);  
    Team *team = temp->team;
    (*top) = (*top)->next;
    free(temp);
    return team;
}

void push(Stack **top, Team *team) {
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    newNode->team = team;
    newNode->next = (*top);
    (*top)= newNode;
}

Team* top_Stack(Stack *top) {
    if (isEmpty_Stack(top)) return NULL;
    return top->team;
}

// functia pregateste coada de meciuri pentru urmatoare runda
void create_round_from_stack(Stack *stack, Queue* q, FILE *output){
     while (!isEmpty_Stack(stack)) {
        Team *team_1= pop(&stack);
        if( team_1 != NULL)
        print_win_team( team_1, output);
        Team *team_2= pop(&stack);
        if( team_2 != NULL)
        print_win_team( team_2, output);

        enQueue(q, team_1, team_2);
    }
}

void print_win_team( Team *team, FILE* output){
        fprintf(output,"%s", team->team_name);
 
        for( int i = strlen(team->team_name); i < LINE_LENGHT; i++)
        fprintf(output,"%c", ' ');
        fprintf(output,"-  %.2f\n", team->team_points);
}

// functia repartizeaza ecipele in stivele de pierzatori si castigatori in functie de criteriile oferite
void Stack_repartition( Queue *q, Stack **win, Stack **lose){
    Queue *q_copy = q;
    while(q_copy->front != NULL){    
    if( q_copy->front->team_1->team_points <= q_copy->front->team_2->team_points){
        q_copy->front->team_2->team_points = increase_team_points(q_copy->front->team_2);
        push(win, q_copy->front->team_2);
        push(lose, q_copy->front->team_1);
    }
    else {
        q_copy->front->team_1->team_points = increase_team_points(q_copy->front->team_1);
        push(win, q_copy->front->team_1);
        push(lose, q_copy->front->team_2);
 
    }
    q->front = q->front->next;
    }
}

//funtia copiaza echipa cu scopul de a putea elibera memoria din stiva fara a afecta echipele retinute si totodata pentru a patra punctajul acumulat pana in momentul respectiv
void team_copy(Team **copy, Team *head) {
    if (head == NULL || copy == NULL) return;
    *copy = (Team *)malloc(sizeof(Team));
    if (*copy == NULL) exit(1);
    (*copy)->team_name = (char *)malloc((strlen(head->team_name) + 1) * sizeof(char));
    if ((*copy)->team_name == NULL) exit(1);
    strcpy((*copy)->team_name, head->team_name);

    (*copy)->number_of_players = head->number_of_players;
    (*copy)->team_points = head->team_points;

    (*copy)->vect = (Player *)malloc(head->number_of_players * sizeof(Player));
    if ((*copy)->vect == NULL)  exit(1);

    for (int i = 0; i < head->number_of_players; i++) {
        (*copy)->vect[i].firstName = (char *)malloc((strlen(head->vect[i].firstName) + 1) * sizeof(char));
        if ((*copy)->vect[i].firstName == NULL) exit(1);
        strcpy((*copy)->vect[i].firstName, head->vect[i].firstName);

        (*copy)->vect[i].secondName = (char *)malloc((strlen(head->vect[i].secondName) + 1) * sizeof(char));
        if ((*copy)->vect[i].secondName == NULL) exit(1);
        
        strcpy((*copy)->vect[i].secondName, head->vect[i].secondName);

        (*copy)->vect[i].points = head->vect[i].points;
    }
    (*copy)->next = NULL;
}

//fata de functia care creaza urmatoare runda, aici este creata si lista ultimilor 8 echipe

void printStack_and_create_Queue(Stack *stack, FILE* output, Team **head, Queue *q) {
    while (!isEmpty_Stack(stack)) {
        Team *team_1 = pop(&stack), *team_2 = pop(&stack);
        if (team_1 != NULL) print_win_team(team_1, output);
        if (team_2 != NULL) print_win_team(team_2, output);
        enQueue(q, team_1, team_2);

        Team *newNode1 = NULL, *newNode2 = NULL;
        team_copy(&newNode1, team_1);
        team_copy(&newNode2, team_2);

        if (newNode1 != NULL) {
            newNode1->next = *head;
            *head = newNode1;
        }

        if (newNode2 != NULL) {
            newNode2->next = *head;
            *head = newNode2;
        }
    }
}


   
