#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int val;
  struct node *next;
} Node;

int compare_nodes(const void *a, const void *b) {
  int val_a = ((Node *) a)->val;
  int val_b = ((Node *) b)->val;
  return val_a-val_b;
}

int main() {
  Node *a = malloc(sizeof(Node));
  Node *b = malloc(sizeof(Node));
  a->val = 1;
  b->val = 2;
  int i = compare_nodes(a,b);
  printf("%d",i);
  return 0;
}
