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

