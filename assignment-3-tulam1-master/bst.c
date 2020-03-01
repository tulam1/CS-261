/*************************************************************************************************
 * Name: Tu Lam
 * Email: lamtu@oregonstate.edu
 * Date: 10/30/2019
 * Description: This file is where you should implement your binary search tree. It already
 * contains skeletons of the functions you need to implement (along with documentation for each 
 * function). Feel free to implement any additional functions you might need. Also, don't forget 
 * to include your name and @oregonstate.edu email address above.
 ************************************************************************************************/

#include <stdlib.h>
#include "bst.h"

/***********************************************************************************
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 **********************************************************************************/
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*****************************************************************************
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 ****************************************************************************/
struct bst {
  struct bst_node* root;
};

/****************************************************************************
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 ***************************************************************************/
struct bst* bst_create() {

  struct bst* new_bst = malloc(sizeof(struct bst));
  new_bst->root = NULL;

  return new_bst;
}

/*****************************************************************************
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 ****************************************************************************/
void bst_free(struct bst* bst) {

  bst_delete(bst->root);
  free(bst);

  return;
}

/*********************************************************
 * This function ook at to delete the entire binary tree
 * using recursion.
 ********************************************************/
void bst_delete(struct bst_node* root) {

  if (root == NULL) {
    return;
  }

  bst_delete(root->right);
  bst_delete(root->left);
  free(root);
}

/******************************************************************************
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 *****************************************************************************/
int bst_size(struct bst* bst) {

  int size = 0;

  size = bst_count(bst->root);

  return size;
}

/***************************************************************
 * This function look at the binary tree and start to increase
 * the count for the size unil it read the entire tree.
 **************************************************************/
int bst_count(struct bst_node* root) {

  int left_count = 0, right_count = 0;

  if (root == NULL) {
    return 0;
  }

  else if (root != NULL) {
    if (root->left != NULL) {
      left_count = bst_count(root->left);
    }

    if (root->right != NULL) {
      right_count = bst_count(root->right);
    }

    return (1 + left_count + right_count);
  }
}

/********************************************************************************
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *******************************************************************************/
void bst_insert(struct bst* bst, int key, void* value) {

  bst->root = bst_add(bst->root, key, value);  

  return;
}

/*********************************************************************
 * This function insert/add a new key/value pair into the BST. This
 * function is a subset function of the bst_insert() function.
 ********************************************************************/
struct bst_node* bst_add(struct bst_node* root, int key, void* val) {

  if (root == NULL) {
    root = malloc(sizeof(struct bst_node));
    root->value = val;
    root->key = key;
    root->left = NULL;
    root->right = NULL;

    return root;
  }

  else if (key < (root->key)) {
    root->left = bst_add(root->left, key, val);
  }

  else if (key > (root->key)) {
    root->right = bst_add(root->right, key, val);
  }

  return root;
}

/********************************************************************************
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 *******************************************************************************/
void bst_remove(struct bst* bst, int key) {

  bst->root = bst_eliminate(bst->root, key);

  return;
}

/*******************************************************************
 * This function help to remove the key/value pair based on the key
 * index value that it is located on the tree. This is also a 
 * subset function of te bst_remove().
 ******************************************************************/
struct bst_node* bst_eliminate(struct bst_node* root, int key) {

  if ((root->key) == key) {
    if ((root->right) == NULL) {
      struct bst_node* tmp1 = root->left;
      free(root);
      return tmp1;
    }

    else if ((root->left) == NULL) {
      struct bst_node* tmp2 = root->right;
      free(root);
      return tmp2;
    }

    else if ((root->left) != NULL && (root->right) != NULL) {
      root->key = bst_min_key(root->right);
      root->value = bst_min_val(root->right);
      root->right = bst_eliminate(root->right, root->key);
      return root;
    }

    else if ((root->left) == NULL && (root->right) == NULL) {
      free(root);
      return NULL;
    }
  }

  else if ((root->key) != key) {
    if (key < (root->key)) {
      root->left = bst_eliminate(root->left, key);
    }

    else if (key > (root->key)) {
      root->right = bst_eliminate(root->right, key);
    }
  }

  return root;
}

/*******************************************************
 * This function help to find the minimal root->key 
 * on the left of the the BST and return that key value
 ******************************************************/
int bst_min_key(struct bst_node* root) {

  while ((root->left) != NULL) {
    root = root->left;
  }

  return root->key;
}

/******************************************************
 * This function help on finding the value at the node
 * that is connected to the key value and return that
 * value.
 *****************************************************/
void* bst_min_val(struct bst_node* root) {

  while ((root->left) != NULL) {
    root = root->left;
  }

  return root->value;
}

/********************************************************************************
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 *******************************************************************************/
void* bst_get(struct bst* bst, int key) {

  void* data = bst_value(bst->root, key);

  return data;
}

/*************************************************
 * This function return the value at the key that
 * the user want to display. This is a subset 
 * fucntion of bst_get().
 ************************************************/
void* bst_value(struct bst_node* root, int key) {

  if (root == NULL) {
    return NULL;
  }

  if (key == (root->key)) {
    void* val = root->value;
    return val;
  }

  else if (key < (root->key)) {
    bst_value(root->left, key);
  }

  else if (key > (root->key)) {
    bst_value(root->right, key);
  }
}
