#pragma once

#include <malloc.h>
#include <stdio.h>

#define NULL 0

typedef struct Node {
    int value;
    struct Node* next;
} Node;

void init(Node** head, int val);
void clear(Node** head);
Node* create(int cnt);

Node* getLast(Node* head);
Node* getPos(Node* head, int num);
int getSize(Node* head);

void addLast(Node** head, int val);
void addFirst(Node** head, int val);
void addPosition(Node** head, int val, int pos);

void delLast(Node** head);
void delFirst(Node** head);
void delPosition(Node** head, int pos);

void editLast(Node** head, int val);
void editFirst(Node** head, int val);
void editPosition(Node** head, int val, int pos);

void print(Node* head);
void printBack(Node* head);

int findValue(Node* head, int val);

Node* intersection(Node* head1, Node* head2);
Node* merge(Node* head1, Node* head2);
Node* difference(Node* head1, Node* head2);
