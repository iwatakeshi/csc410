#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* next;
};

struct queue {
  struct node* head;
  struct node* tail;
};

struct queue* queue_create() {
  struct queue* q;
  q->head = NULL;
  q->tail = NULL;
  return q;
}
struct queue* queue_insert(struct queue* q, int value) {
  struct node* ptr = (struct node*)malloc(sizeof(struct node));
  ptr->data = value;
  if (q->head == NULL) {
    q->head = ptr;
    q->tail = ptr;
    q->head->next = q->tail->next = NULL;
  } else {
    q->tail->next = ptr;
    q->tail = ptr;
    q->tail->next = NULL;
  }
  return q;
}
struct queue* queue_remove(struct queue* q) {
  struct node* ptr;
  ptr = q->head;
  if (q->head == NULL)
    return NULL;
  else {
    q->head = q->head->next;
    free(ptr);
  }
  return q;
}

void queue_print(struct queue* q) {
  struct node* ptr = q->head;
  if (ptr != NULL) {
    while (ptr != q->tail) {
      printf("%d\t", ptr->data);
      ptr = q->tail;
    }
    printf("%d\t", ptr->data);
  }
}

int queue_peek(struct queue* q) {
  if (q->head == NULL) {
    return -(1);
  } else
    return q->head->data;
}

#endif