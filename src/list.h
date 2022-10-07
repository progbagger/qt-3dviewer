#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <stdlib.h>

/**
 * @brief Union to store vertexes coordinates and vertexes indexes
 * simultaneously
 *
 */
typedef union {
  double value;
  unsigned int index;
} Data;

struct node {
  struct node *next;
  Data data;
};

typedef struct {
  struct node *head, *tail;
  size_t size;
} List;

List *init_list();

void push_back_to_list(List *l, Data value);
Data pop_front_from_list(List *l);

int is_list_empty(List *l);
void destroy_list(List *l);

#endif  // SRC_LIST_H_
