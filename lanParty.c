#include "Player.h"

int main(int argc, char *argv[]){
    FILE *input,*output;

    input=fopen("d.in","rt");
    if(input==NULL){
        perror("Fisierul d.in imposibil de accesat");
        exit(1);
        }
    output=fopen("r.out","wt");
    if(output==NULL){
        perror("Fisierul r.out imposibil de accesat");
        exit(1);
        }

    fclose(input);
    fclose(output);
    return 0;
}