#include "Player.h"

int main(int argc, char *argv[]) {
   // "date/t1/d.in"
   // "out/out1.out"
    FILE *input = NULL, *output = NULL, *test = NULL;
    //pentru testul 1
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
     if( date == 1 ){
    Team *head = NULL;
    create_list(&head, input);

    print_Team_name(head, output);
   
    free_Teams(head);
     }

     fclose(test);
    fclose(input);
    fclose(output);

    return 0;
}