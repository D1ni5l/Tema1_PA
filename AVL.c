#include "Player.h"

int height(AVLNode *root) {
    if (root == NULL)
        return -1;
    return root->height;
}

int getBalance(AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

int max(Data a, Data b) {
    if( a > b ) return a;
    return b;
}

AVLNode *rightRotation(AVLNode *z) {
    AVLNode *y = z->left;
    AVLNode *T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode *leftRotation(AVLNode *z) {
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode *LeftRightRotation(AVLNode *z) {
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

AVLNode *RightLeftRotation(AVLNode *z) {
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

AVLNode *insert_AVLNode(AVLNode *node, Team *team) {
    // 1. Inserare normală în BST
    if (node == NULL){
        AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
        newNode->team = team;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 0; // Inițializează înălțimea la 1
        return newNode;
    }

    if (team->team_points < node->team->team_points)
        node->left = insert_AVLNode(node->left, team);
    else if (team->team_points > node->team->team_points)
        node->right = insert_AVLNode(node->right, team);
    else { // Dacă punctele sunt egale, sortăm după nume în ordine descrescătoare
        if (strcmp(team->team_name, node->team->team_name) < 0)
            node->left = insert_AVLNode(node->left, team);
        else
            node->right = insert_AVLNode(node->right, team);
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int k = getBalance(node);

    if (k > 1 && getBalance(node->left) >= 0)
        return rightRotation(node);
    if (k < -1 && getBalance(node->right) <= 0)
        return leftRotation(node);

    if (k > 1 && getBalance(node->left) < 0)
        return LeftRightRotation(node);

    if (k < -1 && getBalance(node->right) > 0) 
        return RightLeftRotation(node);

    return node;
}

void print_level_AVL(AVLNode *root, Data level, FILE *output) {
    if (root == NULL)
        return;
    if (level == 0)
        fprintf(output, "%s\n", root->team->team_name);
    else if (level > 0) {
        print_level_AVL(root->right, level - 1, output);
        print_level_AVL(root->left, level - 1, output);
    }
}

void free_AVL(AVLNode *root) {
    if (root == NULL)
        return;

    free_AVL(root->left);
    free_AVL(root->right);

    free(root->team); 
    free(root);      
   // root = NULL;
}