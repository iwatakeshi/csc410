#ifndef List_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

struct node {
  int data;
  struct node* next;
};

struct node* list_create() {
  struct node *start = (struct node*)malloc(sizeof(struct node));
  return start;
}

#endif