#include "Player.h"

int main(int argc, char *argv[]) {
    //declarare, deschidere si verificare fisiere
    FILE *input = NULL, *output = NULL, *test = NULL;
    if( argv[0] == NULL ){
        perror("Nu merge");
        exit(1);
    } 
    test = fopen(argv[1], "rt");
    if (test == NULL) {
        perror("Fisierul de intrare pt checker nu poate fi deschis");
        exit(1);
      }
      int date = 0, t;
     for( int i = 0; i < 5; i++){
        fscanf(test, "%d", &t);
        date += t;
     }
    input = fopen(argv[2], "rt");
    if (input == NULL) {
        perror("Fisierul de intrare nu poate fi deschis");
        exit(1);
      }
    output= fopen(argv[3], "wt");
      if (output == NULL) {
        perror("Fisierul de iesire nu poate fi deschis");
        exit(1);
      }

      // task 1
     if( date == 1 ){
      Team *head = NULL;
      //creeare lista
      create_list(&head, input);
      //afisare din lista
      print_Team_name(head, output);
      //eliberare memorie
      free_Teams(head);
     }
     
       //task 2
      if( date == 2 ){
      Team *head = NULL, *head_copy;
      //creeare lista
      create_list(&head, input);

      //calculare punctaj echipa
      head_copy = head;
      while(head_copy != NULL){
        head_copy->team_points = Team_points(head_copy);
        head_copy = head_copy->next;
      }
      //reducere echipe
      Team_deduction(&head);
      print_Team_name(head, output);

      //eliberare memorie
      free_Teams(head);
          
     }

     if( date == 3 ){
      Team *head = NULL, *head_copy;
      //creeare lista
      create_list(&head, input);

      //calculare punctaj echipa
      head_copy = head;
      while(head_copy != NULL){
        head_copy->team_points = Team_points(head_copy);
        head_copy = head_copy->next;
      }
      //reducere echipe
      Team_deduction(&head);
      print_Team_name(head, output);
      
      
      head_copy=head;
      int round = 1, teams_number_copy = head->teams_number;
       
       Queue *q;
        q = createQueue();
        while(head_copy!=NULL && head_copy->next!=NULL)
        {
            enQueue(q, head_copy, head_copy->next);
            head_copy=head_copy->next->next;
        }

      while( teams_number_copy > 1){
        fprintf(output,"\n--- ROUND NO:%d\n", round);
        
        print_Queue(q,output);
        Stack *losers = NULL, *winners = NULL;
        Stack_repartition(q, &winners, &losers);
        
        fprintf(output,"\nWINNERS OF ROUND NO:%d\n", round);
        
        deleteQueue(q);
        q = createQueue();
        if( teams_number_copy > 2 )
        create_round_from_stack(winners, q, output);

        else print_win_team(winners->team, output);
        
        teams_number_copy = teams_number_copy / 2;
         round++;
      }
      //eliberare memorie
     free_Teams(head);
            
     }
    //inchidere fisiere
    fclose(test);
    fclose(input);
    fclose(output);

    return 0;
}