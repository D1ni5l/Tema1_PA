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

void printStack(Stack *stack, FILE* output) {
    while (!isEmpty_Stack(stack)) {
        Team *team = pop(&stack);
        fprintf(output,"%s", team->team_name);
        int line = LINE_LENGHT;
        for( int i = strlen(team->team_name); i < LINE_LENGHT; i++)
        fprintf(output,"%c", ' ');
        fprintf(output,"- %.2f\n", team->team_points);
    }
}

void print_win_team( Team *team, FILE* output){
        fprintf(output,"%s", team->team_name);
        int line = LINE_LENGHT;
        for( int i = strlen(team->team_name); i < LINE_LENGHT; i++)
        fprintf(output,"%c", ' ');
        fprintf(output,"-  %.2f\n", team->team_points);
}

void create_round_from_stack(Stack *stack, Queue* q, FILE *output){
     while (!isEmpty_Stack(stack)) {
        Team *team_1= pop(&stack);
        print_win_team( team_1, output);
        Team *team_2= pop(&stack);
        print_win_team( team_2, output);
        enQueue(q, team_1, team_2);
    }
}

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


