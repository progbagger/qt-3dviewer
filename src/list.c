#include "list.h"

/**
 * @brief Function to allocate memory for the list itself
 *
 * @return List* Pointer to allocated list
 */
List *init_list() {
  List *l = malloc(sizeof(List));
  if (l) {
    l->head = l->tail = NULL;
    l->size = 0;
  }
  return l;
}

/**
 * @brief Function to add element at the end of list
 *
 * @param l List where to add element
 * @param value Value of element to add
 * @return int 0 if memory allocated; 1 otherwise
 */
void push_back_to_list(List *l, Data value) {
  if (l) {
    struct node *elem = malloc(sizeof(struct node));
    if (elem) {
      elem->data = value;
      elem->next = NULL;
      if (l->tail) l->tail->next = elem;
      l->tail = elem;
      if (!l->head) l->head = l->tail;
      l->size++;
    }
  }
}

/**
 * @brief Function to get element from head of the list and delete it
 *
 * @param l List where to pop element
 * @return Data Popped data
 */
Data pop_front_from_list(List *l) {
  Data result = {.value = -1};
  if (l) {
    struct node *elem = l->head;
    if (!elem) {
      l->tail = l->head;
    } else {
      l->head = l->head->next;
      l->size--;
      result = elem->data;
      free(elem);
    }
  }
  return result;
}

/**
 * @brief Function to check if list is empty
 *
 * @param l List to check
 * @return int 1 if empty; 0 otherwise
 */
int is_list_empty(List *l) {
  int result = 0;
  if (!l || !l->head) result = 1;
  return result;
}

/**
 * @brief Function to free memory allocated for the whole list
 *
 * @param l List to free
 */
void destroy_list(List *l) {
  if (l) {
    while (!is_list_empty(l)) pop_front_from_list(l);
    free(l);
  }
}
