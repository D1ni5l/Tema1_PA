#include "Player.h"

BSTNode *newNode_BST( Team *data){
BSTNode *node = ( BSTNode*) malloc ( sizeof (BSTNode));
node->team = data ;
node->left = node->right = NULL ;
return node ;
}

BSTNode *insert_BST( BSTNode * node, Team* key ) {
// daca ( sub ) arborele este gol , creaza nod
if ( node == NULL ) return newNode_BST( key );
// altfel , coboara la stanga sau dreapta
if ( key->team_points < node->team->team_points || (key->team_points == node->team->team_points && strcmp( node->team->team_name, key->team_name) > 0) )
node->left = insert_BST( node->left, key);
else if ( key->team_points > node->team->team_points || (key->team_points == node->team->team_points && strcmp( node->team->team_name, key->team_name) < 0))
node->right = insert_BST( node->right , key );
// ! pointerul node se intoarce nemodificat pe acest return
return node ;
}

// functia afiseaza echuipa din arbore in ordine descrescatoare
void print_BST_in_descending_order(BSTNode *root, FILE *output) {
    if (root == NULL) return;

    print_BST_in_descending_order(root->right, output);
    print_win_team(root->team, output);
    print_BST_in_descending_order(root->left, output);
}

void addAtBeginning_for_list(Team **head, Team *root) {
    Team* newNode = (Team*)malloc(sizeof(Team));
    newNode->team_name = (char *)malloc((strlen(root->team_name) + 1) * sizeof(char));
    strcpy(newNode->team_name, root->team_name); 
    newNode->number_of_players = root->number_of_players;
    newNode->vect = (Player*)malloc(root->number_of_players * sizeof(Player));
    newNode->teams_number = root->teams_number;
    newNode->team_points = root->team_points;
    newNode->next = *head;
    *head = newNode;
}

void list_from_BST(BSTNode *root, Team **list) {
    if (root == NULL) return;
    list_from_BST(root->left, list);
    addAtBeginning_for_list(list, root->team);
    list_from_BST(root->right, list);
}

void free_BST(BSTNode *root) {
    if (root == NULL) return;

    free_BST(root->left);
    free_BST(root->right);
    free(root);
}

