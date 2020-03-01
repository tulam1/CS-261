/***********************************************************************************
 * Name: Tu Lam
 * Email: lamtu@oregonstate.edu
 * Date: 11/19/2019
 * Description: In this file, you will write the structures and functions needed to
 * implement a priority queue. Feel free to implement any helper functions you need 
 * in this file to implement a priority queue. 
 **********************************************************************************/

#include <stdlib.h>
#include "pq.h"
#include "dynarray.h"

/****************************************************************************
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 ***************************************************************************/
struct pq {
  struct dynarray* array;
};


/************************************************************************
 * This is the structure that helps identify each node in the array.
 ***********************************************************************/
struct node {
  int priority;
  void* val;
};


/****************************************************************************
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 ***************************************************************************/
struct pq* pq_create() {

  struct pq* new_pq = malloc(sizeof(struct pq));
  new_pq->array = dynarray_create();

  return new_pq;
}


/*******************************************************************************
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 ******************************************************************************/
void pq_free(struct pq* pq) {

  while (!pq_isempty(pq)) {
    pq_remove_first(pq);
  }

  dynarray_free(pq->array);
  free(pq);

  return;
}


/******************************************************************************
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 *****************************************************************************/
int pq_isempty(struct pq* pq) {

  int arr_size = 0;
  arr_size = dynarray_size(pq->array);

  if (arr_size == 0) {
    return 1;
  }

  else {
    return 0;
  }
}


/******************************************************************************
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 *****************************************************************************/
void pq_insert(struct pq* pq, void* value, int priority) {

  int size = 0, current = 0, check = 0;
  struct node* tmp = malloc(sizeof(struct node));

  tmp->val = value;
  tmp->priority = priority;
  size = (dynarray_size(pq->array));
  current = size;
    
  dynarray_insert(pq->array, tmp);
  

  while (check == 0) {
    int parent = pq_parent(current);
    struct node* parent_n = dynarray_get(pq->array, parent);

    if ((parent_n->priority) > priority) {
      if (current == 0) {
        check = 1;
      }

      dynarray_set(pq->array, parent, tmp);
      dynarray_set(pq->array, current, parent_n);
      current = parent;
    }

    else {
      check = 1;
    }
  }

  return;
}


/********************************************************************************
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 *******************************************************************************/
void* pq_first(struct pq* pq) {

  int size = 0;
  size = dynarray_size(pq->array);

  if (size == 0 || pq->array == NULL) {
    return 0;
  }

  struct node* data = dynarray_get(pq->array, 0);

  return data->val;
}


/******************************************************************************
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 *****************************************************************************/
int pq_first_priority(struct pq* pq) {

  int size = 0;
  size = dynarray_size(pq->array);

  if (size == 0 || pq->array == NULL) {
    return 0;
  }

  struct node* data = dynarray_get(pq->array, 0);

  return data->priority;
}


/******************************************************************************
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 *****************************************************************************/
void* pq_remove_first(struct pq* pq) {

  int size = 0, parent = 0, left = 0, right = 0;
  size = (dynarray_size(pq->array) - 1);
  struct node* root = dynarray_get(pq->array, 0);
  struct node* last = dynarray_get(pq->array, size);
  void* value1 = root->val;
  left = pq_left(parent);
  right = pq_right(parent);

  if (size > 0) {
    root->priority = last->priority;
    root->val = last->val;
    free(last);
    dynarray_remove(pq->array, size);
    pq_percolate(pq, parent, left, right); 

    return value1;  
  }
 
  else {
    struct node* tmp = dynarray_get(pq->array, 0);
    void* value2 = tmp->val;
    free(tmp);
    dynarray_remove(pq->array, 0);

    return value2;
  }  
}


/**************************************************************
 * This function helps to calculate the parent node location
 * in the array.
 *************************************************************/
int pq_parent(int index) {

  int parent = 0;
  parent = ((index - 1) / 2);

  return parent;
}


/*******************************************************
 * This function helps to calculate the left child and
 * where is it to place in the array.
 ******************************************************/
int pq_left(int index) {

  int left = 0;
  left = ((2 * index) + 1);

  return left;
}


/*******************************************************
 * This function helps to calculate the right child and
 * where is it to place in the array.
 ******************************************************/
int pq_right(int index) {

  int right = 0;
  right = ((2 * index) + 2);

  return right;
}


/************************************************************
 * This function helps to percolate down on the tree/array
 * to help remove the node at that point.
 ***********************************************************/
void pq_percolate(struct pq* pq, int parent, int left, int right) {

  int arr_size = 0;
  struct node* parent_n = dynarray_get(pq->array, parent);
  arr_size = dynarray_size(pq->array);

  if ((right < arr_size) && (left < arr_size)) {
    struct node* left_n = dynarray_get(pq->array, left);
    struct node* right_n = dynarray_get(pq->array, right);

    if ((left_n->priority) <= (right_n->priority)) {
      if ((parent_n->priority) > (left_n->priority)) { 
        dynarray_set(pq->array, left, parent_n);
        dynarray_set(pq->array, parent, left_n);
        int left1 = pq_left(left);
        int left2 = pq_right(left);
        pq_percolate(pq, left, left1, left2);
      }
    }

    else {
      if ((parent_n->priority) > (right_n->priority)) { 
        dynarray_set(pq->array, right, parent_n);
        dynarray_set(pq->array, parent, right_n);
        int right1 = pq_left(right);
        int right2 = pq_right(right);
        pq_percolate(pq, right, right1, right2);
      }
    }  
  }

  else if ((left < arr_size) && (right >= arr_size)) {
    struct node* left_n = dynarray_get(pq->array, left);
    
    if ((parent_n->priority) > (left_n->priority)) { 
      dynarray_set(pq->array, left, parent_n);
      dynarray_set(pq->array, parent, left_n);
      int left1 = pq_left(left);
      int left2 = pq_right(left);
      pq_percolate(pq, left, left1, left2);
    }
  }  
}
