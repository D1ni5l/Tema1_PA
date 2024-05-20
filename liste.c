#include "Player.h"
#define max_name_length 70

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
        strcpy(team_name + strlen(team_name) - 1, team_name + strlen(team_name));

        addAtBeginning_for_team(head, team_name, nr_of_team_players); 

        for (int j = 0; j < nr_of_team_players; j++) {
            fscanf(input, "%s", firstName);
            fscanf(input, "%s", secondName);
            fscanf(input, "%d", &points);
            addAtBeginning_for_Player((*head)->vect, j, firstName, secondName, points);
        }
    }
}



void print_Team_name(Team *head, FILE *output) {

    Team *head_copy = head;
    while (head_copy != NULL) {
        fprintf(output, "%s\n", head_copy->team_name); 
        head_copy = head_copy->next;
    }
}

void print_teams_name_players_and_points(Team *head, FILE *output) {
    
    Team *head_copy = head;
    while (head_copy != NULL) {
        fprintf(output, "%s\n", head_copy->team_name);
        for (int i = 0; i < head_copy->number_of_players; i++) {
            fprintf(output, "%s %s %d\n", head_copy->vect[i].firstName, head_copy->vect[i].secondName, head_copy->vect[i].points);
        }
        head_copy = head_copy->next;
    }

    fclose(output);
}

void Team_points(Team *head) {
    Team *head_copy = head;
    while (head_copy != NULL) {
        Data total_team_points = 0;  
        for (int i = 0; i < head_copy->number_of_players; i++) {
            total_team_points += head_copy->vect[i].points;
        }
        head_copy->team_points = (float)total_team_points;
        printf("Team: %s, Total Points: %f\n", head_copy->team_name, head_copy->team_points);
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
} 