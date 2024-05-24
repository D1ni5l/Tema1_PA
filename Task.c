#include "Player.h"
#define win_team 1
#define NO_WINNER_TEAM 2
#define LEVEL_PRINT 2
#define LAST_EIGHT_WINNNERS 16
#define START 1

void first_task(FILE *input, FILE *output){
     Team *head = NULL;
      //creeare lista
      create_list(&head, input);
      //afisare din lista
      print_Team_name(head, output);
      //eliberare memorie
      free_Teams(&head);
}

void second_task( Team **head, FILE *input, FILE *output){
    Team *head_copy;
      //creeare lista
      create_list(head, input);
      //calculare punctaj echipa
      head_copy = (*head);
      while(head_copy != NULL){
        head_copy->team_points = Team_points(head_copy);
        head_copy = head_copy->next;
      }
      //reducere echipe
      Team_deduction(head);
      //afisare echipe dupa ce este indeplinit criteriul cerut
      print_Team_name((*head), output);  
}

void third_task(Team **head,Team **last_eight, Queue *q, FILE *output){
   Team *head_copy;      
      head_copy = (*head);
      int round = START, teams_number_copy = START;
      while( teams_number_copy * 2 <= (*head)->teams_number )
        teams_number_copy *= 2;
       
       //creere prima runda
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
        if( teams_number_copy == LAST_EIGHT_WINNNERS ){
           printStack_and_create_Queue(winners, output, last_eight, q);
        }
        // creere meciuri pentru runda urmatoare  
        else if( teams_number_copy > NO_WINNER_TEAM)
           create_round_from_stack(winners, q, output);
        else print_win_team(winners->team, output);
                   
        teams_number_copy = teams_number_copy / 2;
         round++;
      }
      //eliberare memorie
    deleteQueue(q);
}

void fourth_task(Team **last_eight, BSTNode **root, FILE *output){

     Team *copy_last_eight = (*last_eight);
  
     //creere arbore tip BST
     while( copy_last_eight != NULL ){
       (*root) = insert_BST( (*root), copy_last_eight);
       copy_last_eight = copy_last_eight->next;
     }

     //afisarea arbosrelui
     fprintf(output,"\n%s\n", "TOP 8 TEAMS:");
     print_BST_in_descending_order( (*root), output);


}

void fiveth_task(Team **Last_eight, BSTNode *root, AVLNode **root_Avl, FILE *output){
   
    //memorare echipe in ordinea descrescatoare din BST
    list_from_BST(root, Last_eight);

    //creere arbore echilibrat
    Team *copy_Last_eight  = (*Last_eight);

    while (copy_Last_eight  != NULL) {
        (*root_Avl) = insert_AVLNode((*root_Avl), copy_Last_eight );
        copy_Last_eight = copy_Last_eight->next;
    }

    // Afișarea echipelor de pe nivelul 2
    Data k = LEVEL_PRINT;
    fprintf(output,"\nTHE LEVEL 2 TEAMS ARE:\n");

    print_level_AVL((*root_Avl), k, output);
}