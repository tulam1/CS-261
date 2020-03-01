/***************************************************************************************
 * Name: Tu Lam
 * Email: lamtu@oregonstate.edu
 * Date: 10/22/2019
 * Description: This file contains a simple implementation of a dynamic array. See the
 * documentation below for more information on the individual functions in this 
 * implementation.
 **************************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "dynarray.h"

/********************************************************************
 * This structure is used to represent a single dynamic array.
 *******************************************************************/
struct dynarray {
  void** data;
  int size;
  int capacity;
  int start;
};

#define DYNARRAY_INIT_CAPACITY 4

/****************************************************************************
 * This function allocates and initializes a new, empty dynamic array and
 * returns a pointer to it.
 ***************************************************************************/
struct dynarray* dynarray_create() {
  struct dynarray* da = malloc(sizeof(struct dynarray));
  assert(da);

  da->data = malloc(DYNARRAY_INIT_CAPACITY * sizeof(void*));
  assert(da->data);
  da->size = 0;
  da->start = 0;
  da->capacity = DYNARRAY_INIT_CAPACITY;

  return da;
}

/*********************************************************************************
 * This function frees the memory associated with a dynamic array.  Freeing
 * any memory associated with values stored in the array is the responsibility
 * of the caller.
 *
 * Params:
 *   da - the dynamic array to be destroyed.  May not be NULL.
 ********************************************************************************/
void dynarray_free(struct dynarray* da) {
  assert(da);
  free(da->data);
  free(da);
}

/*********************************************************************************
 * This function returns the size of a given dynamic array (i.e. the number of
 * elements stored in it, not the capacity).
 ********************************************************************************/
int dynarray_size(struct dynarray* da) {
  assert(da);
  return da->size;
}


/*****************************************************************************
 * Auxilliary function to perform a resize on a dynamic array's underlying
 * storage array.
 ****************************************************************************/
void _dynarray_resize(struct dynarray* da, int new_capacity) {
  assert(new_capacity > da->size);

  //Allocate space for the new array.
  void** new_data = malloc(new_capacity * sizeof(void*));
  assert(new_data);

  //Copy data from the old array to the new one.
  for (int i = 0; i < da->size; i++) {
    int j = dynarray_index(da,i);
    new_data[i] = da->data[j];
  }

  //Put the new array into the dynarray struct.
  da->start = 0;
  free(da->data);
  da->data = new_data;
  da->capacity = new_capacity;
}

/***********************************************************************************
 * This function inserts a new value to a given dynamic array.  The new element
 * is always inserted at the *end* of the array.
 *
 * Params:
 *   da - the dynamic array into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 **********************************************************************************/
void dynarray_insert(struct dynarray* da, void* val) {
  assert(da);

  //Make sure we have enough space for the new element.  Resize if needed.
  if (da->size == da->capacity) {
    _dynarray_resize(da, 2 * da->capacity);
  }

  //Put the new element at the end of the array.
  int new_idx = dynarray_index(da,da->size);
  da->data[new_idx] = val;
  da->size++;
}

/***********************************************************************************
 * This function removes an element at a specified index from a dynamic array.
 * All existing elements following the specified index are moved forward to
 * fill in the gap left by the removed element.
 *
 * Params:
 *   da - the dynamic array from which to remove an element.  May not be NULL.
 *   idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 **********************************************************************************/
void dynarray_remove(struct dynarray* da, int idx) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  //Move all elements behind the one being removed forward one index, overwriting the element to be removed in the process.
  for (int i = idx; i < da->size - 1; i++) {
    da->data[i] = da->data[i+1];
  }

  da->size--;
}

/*******************************************************************************
 * This function returns the value of an existing element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array from which to get a value.  May not be NULL.
 *   idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 ******************************************************************************/
void* dynarray_get(struct dynarray* da, int idx) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  int new_index = dynarray_index(da,idx);

  return da->data[new_index];
}

/*************************************************************************************
 * This function updates (i.e. overwrites) the value of an existing element in
 * a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 ************************************************************************************/
void dynarray_set(struct dynarray* da, int idx, void* val) {
  assert(da);
  assert(idx < da->size && idx >= 0);

  da->data[idx] = val;
}

/*******************************************************************
 * This function check to see if the dynamic array is empty or not.
 ******************************************************************/
int dynarray_check(struct dynarray* da) {

  int check_size = 0;
  check_size = dynarray_size(da);
  
  if (check_size > 0) {
    return 0;
  }

  else {
    return 1;
  }
}

/**************************************************
 * This function remove the element in the queue.
 *************************************************/
void dynarray_pop(struct dynarray* da, int idx) {

  if (da->size > 0) { 
    da->start++; 
    da->size--;
  }
}

/*********************************************************************************
 * This function help to mod the logical index to match with the physical index.
 ********************************************************************************/
int dynarray_index(struct dynarray* da, int logical) {

  int physical = 0;
  physical = ((da->start + logical) % da->capacity);

  return physical;
}
