#include "List.h"

Node* intersection(Node* head1, Node* head2)
{
    Node* result = NULL; // итоговый список

    Node* ptr = head1;
    while (ptr) { // проход по всем элементам 1 списка
        if (findValue(head2, ptr->value) != -1) // если число из 1 списка содержится во 2
            if (findValue(result, ptr->value) == -1) // и при этом его еще не вставляли в список-результат
                addLast(&result, ptr->value); // добавить в конец списка-результата
        ptr = ptr->next;
    }

    return result;
}

Node* merge(Node* head1, Node* head2)
{
    Node* result = NULL; // итоговый список

    Node* ptr = head1;
    while (ptr) { // проход по всем элементам 1 списка
        if (findValue(result, ptr->value) == -1) // если число не вставляли в список-результат
            addLast(&result, ptr->value); // добавить в конец списка-результата
        ptr = ptr->next;
    }

    ptr = head2;
    while (ptr) { // аналогично для 2 списка
        if (findValue(result, ptr->value) == -1)
            addLast(&result, ptr->value);
        ptr = ptr->next;
    }

    return result;
}

Node* difference(Node* head1, Node* head2)
{
    Node* result = NULL; // итоговый список

    Node* ptr = head1;
    while (ptr) { // проход по всем элементам 1 списка
        if (findValue(head2, ptr->value) == -1) // если число из 1 списка НЕ содержится во 2
            if (findValue(result, ptr->value) == -1) // и при этом его еще не вставляли в список-результат
                addLast(&result, ptr->value); // добавить в конец списка-результата
        ptr = ptr->next;
    }

    return result;
}

int findValue(Node* head, int val)
{
    int cnt = 0;
    while (head) {
        if (head->value == val)
            return cnt;
        head = head->next;
        cnt++;
    }
    return -1;
}

Node* create(int cnt)
{
    Node* head = NULL;
    for (int i = 0; i < cnt; i++) {
        int num = rand() % 10;
        if (!head)
            init(&head, num);
        else
            addLast(&head, num);
    }
    return head;
}

void editPosition(Node** head, int val, int pos)
{
    if (*head) {
        if (pos < 0)
            editFirst(head, val);
        else {
            Node* ptr = getPos(*head, pos);
            ptr->value = val;
        }
    }
}

void editFirst(Node** head, int val)
{
    if (*head) {
        (*head)->value = val;
    }
}

void editLast(Node** head, int val)
{
    if (*head) {
        Node* ptr = getLast(*head);
        ptr->value = val;
    }
}

void delPosition(Node** head, int num)
{
    if (*head) {
        if (num <= 0)
            delFirst(head);
        else if (num >= getSize(*head)) {
            delLast(head);
        }
        else {
            Node* ptr = getPos(*head, num - 1);
            Node* elem = ptr->next;
            ptr->next = elem->next;
            free(elem);
        }
    }
}

void delLast(Node** head)
{
    if (*head) {
        if ((*head)->next) {
            Node* ptr = getPos(*head, getSize(*head) - 2);
            free(ptr->next);
            ptr->next = NULL;
        }
        else {
            free(*head);
            *head = NULL;
        }
    }
}

void delFirst(Node** head)
{
    if (*head) {
        Node* ptr = (*head)->next;
        free(*head);
        *head = ptr;
    }
}

void addPosition(Node** head, int val, int pos)
{
    if (*head) {
        if (pos < 0)
            addFirst(head, val);
        else {
            Node* ptr = getPos(*head, pos);
            Node* tmp = (Node*)malloc(sizeof(Node));
            tmp->value = val;
            tmp->next = ptr->next;
            ptr->next = tmp;
        }
    }
    else init(head, val);
}

void addFirst(Node** head, int val)
{
    if (*head) {
        Node* tmp = (Node*)malloc(sizeof(Node));
        tmp->value = val;
        tmp->next = *head;
        *head = tmp;
    }
    else init(head, val);
}

void addLast(Node** head, int val)
{
    if (*head) {
        Node* ptr = getLast(*head);
        Node* tmp = (Node*)malloc(sizeof(Node));
        tmp->value = val;
        tmp->next = NULL;
        ptr->next = tmp;
    }
    else init(head, val);
}

void init(Node** head, int val)
{
    (*head) = (Node*)malloc(sizeof(Node));
    (*head)->value = val;
    (*head)->next = NULL;
}

Node* getLast(Node* head)
{
    if (!head) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}


Node* getPos(Node* head, int num) {
    if (head) {
        int cnt = 0;
        while (cnt < num && head->next) {
            head = head->next;
            cnt++;
        }
        return head;
    }
    else
        return NULL;
}

int getSize(Node* head)
{
    int cnt = 0;

    if (!head)
        return cnt;

    while (head->next) {
        head = head->next;
        cnt++;
    }
    return cnt + 1;
}

void print(Node* head)
{
    Node* ptr = head;
    while (ptr) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
}

void printBack(Node* node)
{
    if (node) {
        printBack(node->next);
        printf("%d ", node->value);
    }
}

void clear(Node** head)
{
    if (*head) {
        Node* now = NULL;
        while ((*head)->next) {
            now = (*head);
            (*head) = (*head)->next;
            free(now);
        }
        free(*head);
        *head = NULL;
    }
}