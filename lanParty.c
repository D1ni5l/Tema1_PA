#include "Player.h"
#define c_in 1
#define d_in 2
#define out_out 3

#define TASK_1 1
#define TASK_2 2
#define TASK_3 3
#define TASK_4 4
#define TASK_5 5

int main(int argc, char *argv[]) {
    //declarare, deschidere si verificare fisiere
    FILE *input = NULL, *output = NULL, *test = NULL;
   // deschidere fisier cerinte
    test = fopen(argv[c_in], "rt");
    if (test == NULL) {
        perror("Fisierul de intrare pt checker nu poate fi deschis");
        exit(1);
      }
    // concluzionarea cerinta
     int date = 0, t;
     for( int i = 0; i < 5; i++){
        fscanf(test, "%d", &t);
        date += t;
     }
    //deschidere fisier date de intrare
    input = fopen(argv[d_in], "rt");
    if (input == NULL) {
        perror("Fisierul de intrare nu poate fi deschis");
        exit(1);
        }
     //deschidere fisier date de iesire
     output= fopen(argv[out_out], "wt");
      if (output == NULL) {
        perror("Fisierul de iesire nu poate fi deschis");
        exit(1);
      }
    
       // task 1
if( date == TASK_1 ){
        first_task(input, output);
     }
      
       //task 2
     Team *head = NULL;
if( date >= TASK_2 ){
      second_task(&head, input, output);       
     }

      //task 3
      Team *last_eight = NULL;
      Queue *q;
if( date >= TASK_3 ){
      third_task( &head, &last_eight, q, output);
     }
    
    //task 4
    BSTNode *root = NULL;
if( date >=  TASK_4 ){
      fourth_task(&last_eight, &root, output);
     }

 //task 5
 AVLNode *root_Avl = NULL;
 Team *Last_eight = NULL;
if( date >= TASK_5 ){
     fiveth_task(&Last_eight, root, &root_Avl,output);
     }
    
   //eliberare memorie
   free_BST(root);
   free_AVL(root_Avl);
   free_Teams(&head);
   free_Teams(&last_eight);

   //inchidere fisiere
    fclose(test);
    fclose(input);
    fclose(output);

    return 0;
}
