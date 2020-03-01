/*******************************************************************************
 * This file contains the definition of the interface for the binary search
 * tree you'll implement.  You should not modify anything in this file.  You
 * can find descriptions of the binary search tree functions, including their
 * parameters and their return values, in bst.c.
 ******************************************************************************/

#ifndef __BST_H
#define __BST_H

/******************************************************
 * Structure used to represent a binary search tree.
 *****************************************************/
struct bst;

/**************************************************************************
 * Binary search tree interface function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 *************************************************************************/
struct bst* bst_create();
void bst_free(struct bst* bst);
int bst_size(struct bst* bst);
void bst_insert(struct bst* bst, int key, void* value);
void bst_remove(struct bst* bst, int key);
void* bst_get(struct bst* bst, int key);

//New Function Prototypes
struct bst_node* bst_add(struct bst_node* root, int key, void* val);
struct bst_node* bst_eliminate(struct bst_node* root, int key);
void* bst_value(struct bst_node* root, int key);
int bst_count(struct bst_node* root);
void bst_delete(struct bst_node* root);
void* bst_min_val(struct bst_node* root);
int bst_min_key(struct bst_node* root);

#endif
