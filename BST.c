#include "Player.h"
#define LINE_LENGHT 34

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

void free_BST(BSTNode *root) {
    if (root == NULL) return;

    free_BST(root->left);
    free_BST(root->right);
    free(root);
}
