#include "Player.h"
#define max_name_length 70
#define LAST_EIGHT 8

void addAtBeginning_for_team(Team **head, char *team_name, Data number_of_players) {
    Team* newNode = (Team*)malloc(sizeof(Team));
    newNode->team_name = (char *)malloc((strlen(team_name) + 1) * sizeof(char));
    strcpy(newNode->team_name, team_name); 
    newNode->number_of_players = number_of_players;
    newNode->vect = (Player*)malloc(number_of_players * sizeof(Player));
    newNode->next = *head;
    *head = newNode;
}

void addAtBeginning_for_Player(Player *vect, Data j, char *firstName, char *secondName, Data points) {
    vect[j].firstName = (char *)malloc((strlen(firstName) + 1) * sizeof(char)); 
    strcpy(vect[j].firstName, firstName); 
    vect[j].secondName = (char *)malloc((strlen(secondName) + 1) * sizeof(char));
    strcpy(vect[j].secondName, secondName);
    vect[j].points = points;
}

void create_list(Team **head, FILE *input) {
    char trash;
    char team_name[max_name_length], firstName[max_name_length], secondName[max_name_length];
    int nr_of_teams, nr_of_team_players, points;

    fscanf(input, "%d", &nr_of_teams);
    for (int i = 0; i < nr_of_teams; i++) {
        fscanf(input, "%d", &nr_of_team_players);
        fscanf(input, "%c", &trash);
        fgets(team_name, max_name_length, input);
        strcpy(team_name + strlen(team_name) - 2, team_name + strlen(team_name));
        //daca echipa are un spatiu in plus;
        if( team_name[strlen(team_name) - 1] == ' ')
        strcpy(team_name + strlen(team_name) - 1, team_name + strlen(team_name));

        addAtBeginning_for_team(head, team_name, nr_of_team_players); 

        for (int j = 0; j < nr_of_team_players; j++) {
            fscanf(input, "%s", firstName);
            fscanf(input, "%s", secondName);
            fscanf(input, "%d", &points);
            addAtBeginning_for_Player((*head)->vect, j, firstName, secondName, points);
        }
        (*head)->teams_number = nr_of_teams;
    }
}

void print_Team_name(Team *head, FILE *output) {

    Team *head_copy = head;
    while (head_copy != NULL) {
        fprintf(output, "%s\n", head_copy->team_name); 
        head_copy = head_copy->next;
    }
}

void free_team_members(Team *team) {
    for (int i = 0; i < team->number_of_players; i++) {
        free(team->vect[i].firstName);
        free(team->vect[i].secondName);
    }
    free(team->vect);
    free(team->team_name);
    free(team);
}

void free_Teams(Team *head) {
    Team *head_copy;
    while (head != NULL) {
        head_copy = head;
        head = head->next;
        free_team_members(head_copy);
    }
    return;
} 

void free_Team(Team *head) {
    Team *head_copy;
        head_copy = head;
        free_team_members(head_copy);
} 

float Team_points( Team *head){
    float total_points = 0;

    for( int i = 0; i < head->number_of_players; i++)
      total_points = total_points + head->vect[i].points;
    return total_points / head->number_of_players;
}

void Team_deduction( Team ** head){
    int n_max = 1;
    while( n_max * 2 <= (*head)->teams_number )
      n_max *= 2;
    while( (*head)->teams_number > n_max ){
        Team *head_copy = *head;
        float min = head_copy->team_points;
        while( head_copy !=  NULL)
        {
            if( head_copy->team_points < min )
             min = head_copy->team_points;
             head_copy = head_copy->next;
        }
        head_copy = *head;
        if( (*head)->team_points == min ){
            *head = (*head)->next;
            free_Team(head_copy);
        }
        else {
           while( head_copy->next->team_points != min && head_copy->next != NULL)
               head_copy = head_copy->next;

               Team *copy = head_copy->next;
               if(head_copy->next != NULL)
               head_copy->next = head_copy->next->next;
               else head_copy->next = NULL;
               
               free_Team(copy);
        }        
        n_max++;
       }
}

float increase_team_points( Team *head){
    for(int i = 0; i < head->number_of_players; i++)
        head->vect[i].points++;
    head->team_points = Team_points(head); 
    return head->team_points;
}