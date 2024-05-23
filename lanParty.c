#include "Player.h"
#define c_in 1
#define d_in 2
#define out_out 3
#define win_team 1
#define NO_WINNER_TEAM 2

int main(int argc, char *argv[]) {
    //declarare, deschidere si verificare fisiere
    FILE *input = NULL, *output = NULL, *test = NULL;
    
    test = fopen(argv[c_in], "rt");
    if (test == NULL) {
        perror("Fisierul de intrare pt checker nu poate fi deschis");
        exit(1);
      }
      int date = 0, t;
     for( int i = 0; i < 5; i++){
        fscanf(test, "%d", &t);
        date += t;
     }
    input = fopen(argv[d_in], "rt");
    if (input == NULL) {
        perror("Fisierul de intrare nu poate fi deschis");
        exit(1);
      }
    output= fopen(argv[out_out], "wt");
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

     if( date > 2 ){
      Team *head = NULL, *head_copy, *last_eight ;
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
      int round = 1, teams_number_copy = 1;
      
      while( teams_number_copy * 2 <= head->teams_number )
       teams_number_copy *= 2;
       
       //creere prima runda
       Queue *q;
        q = createQueue();
        while(head_copy!=NULL && head_copy->next!=NULL)
        {
            enQueue(q, head_copy, head_copy->next);
            head_copy=head_copy->next->next;
        }

      while( teams_number_copy > win_team){
        //pentru styleing fisier output
        fprintf(output,"\n--- ROUND NO:%d\n", round);

        //pentru a fisarea meciurilor
        print_Queue(q,output);
        
        //creere stive castigatori si pierzatori
        Stack *losers = NULL, *winners = NULL;
        Stack_repartition(q, &winners, &losers);
        
        //eliberare stiva invinsi
        deleteStack(&losers);       
          
        //pentru styleing fisier output
        fprintf(output,"\nWINNERS OF ROUND NO:%d\n", round);
        
        //eliberare coada meciuri
        deleteQueue(q);
        q = createQueue();
        // daca in joc au mai ramas doar 8 echipe in stiva winners atunci trebuie realizata lista
        if( teams_number_copy == 16 ){
           printStack_and_create_Queue(winners, output, &last_eight, q);
           
        }
        // creere meciuri pentru runda urmatoare  
        else if( teams_number_copy > NO_WINNER_TEAM)
           create_round_from_stack(winners, q, output);
        else print_win_team(winners->team, output);
                   
        teams_number_copy = teams_number_copy / 2;
         round++;
      }
      
      //eliberare memorie
     free_Teams(last_eight);
     free_Teams(head);
     }

    //inchidere fisiere
    fclose(test);
    fclose(input);
    fclose(output);

    return 0;
}