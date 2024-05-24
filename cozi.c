#include "Player.h"
#define INT_MAX 999999999
#define LINE_LENGHT 68

Queue* createQueue(){
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	if (q==NULL) return NULL;	
	q->front=q->rear=NULL;
	return q;	
}

void enQueue(Queue *q, Team *team1, Team *team2){
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    newNode->team_1 = team1;
    newNode->team_2 = team2;
    newNode->next = NULL;
    if (q->rear == NULL){
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    if( q->front == NULL)
    q->front = q->rear;
}


Node* deQueue(Queue *q) {  
    if (isEmpty(q)) return NULL;
    Node *aux = q->front; 
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    return aux;    
}

int isEmpty(Queue*q){
	return (q->front==NULL);
}

void deleteQueue(Queue *q){
    while (!isEmpty(q)){
        Node *aux = q->front;
        q->front = q->front->next;
        free(aux->team_1);
        free(aux->team_2);
    }
    free(q);
}

void print_Queue(Queue *q, FILE *output){
    Node *current = q->front;
    
    while (current != NULL){
        int line = LINE_LENGHT;
        line /= 2; 
        fprintf(output,"%s", current->team_1->team_name);
        line -= strlen(current->team_1->team_name);
        
        for( int i = 0; i < line - 1; i++)
            fprintf(output,"%c",' ');

        fprintf(output,"%c",'-');
        line = LINE_LENGHT;
 
        for( int i = 35; i < line - strlen(current->team_2->team_name); i++)
            fprintf(output,"%c",' ');
        fprintf(output,"%s\n", current->team_2->team_name);
        current = current->next;
    }
}

void copy_team(Team **team_copy, Team *team) {
    if (team == NULL || team_copy == NULL) return;

    *team_copy = (Team *)malloc(sizeof(Team)); 
    (*team_copy)->team_name = (char *)malloc((strlen(team->team_name) + 1) * sizeof(char));
    strcpy((*team_copy)->team_name, team->team_name);

    (*team_copy)->number_of_players = team->number_of_players;
    (*team_copy)->teams_number = 8;

    (*team_copy)->team_points = team->team_points;

    (*team_copy)->vect = (Player *)malloc(team->number_of_players * sizeof(Player));
    for (int i = 0; i < team->number_of_players; i++) {
        (*team_copy)->vect[i].firstName = (char *)malloc((strlen(team->vect[i].firstName) + 1) * sizeof(char));
        strcpy((*team_copy)->vect[i].firstName, team->vect[i].firstName);
        (*team_copy)->vect[i].secondName = (char *)malloc((strlen(team->vect[i].secondName) + 1) * sizeof(char));
        strcpy((*team_copy)->vect[i].secondName, team->vect[i].secondName);
        (*team_copy)->vect[i].points = team->vect[i].points;
    }
    (*team_copy)->next = NULL;
}


