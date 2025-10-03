#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} CircularLinkedList;

CircularLinkedList* createList();
int isEmpty(CircularLinkedList* list);
int getSize(CircularLinkedList* list);
void addFront(CircularLinkedList* list, int data);
void addEnd(CircularLinkedList* list, int data);
void addAt(CircularLinkedList* list, int data, int position);
void removeFront(CircularLinkedList* list);
void removeEnd(CircularLinkedList* list);
void removeAt(CircularLinkedList* list, int position);
int search(CircularLinkedList* list, int key);
void traverse(CircularLinkedList* list);
void clear(CircularLinkedList* list);
void display(CircularLinkedList* list);
Node* getHead(CircularLinkedList* list);
Node* getTail(CircularLinkedList* list);

CircularLinkedList* createList() {
    CircularLinkedList* list = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    list->head = list->tail = NULL;
    list->size = 0;
    return list;
}

int isEmpty(CircularLinkedList* list) {
    return list->size == 0;
}

int getSize(CircularLinkedList* list) {
    return list->size;
}

void addFront(CircularLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (isEmpty(list)) {
        list->head = list->tail = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = list->head;
        list->tail->next = newNode;
        list->head = newNode;
    }
    list->size++;
}

void addEnd(CircularLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (isEmpty(list)) {
        list->head = list->tail = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = list->head;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void addAt(CircularLinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position!\n");
        return;
    }
    if (position == 0) {
        addFront(list, data);
    } else if (position == list->size) {
        addEnd(list, data);
    } else {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        Node* temp = list->head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        list->size++;
    }
}

void removeFront(CircularLinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = list->head;
    if (list->head == list->tail) { 
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->tail->next = list->head;
    }
    free(temp);
    list->size--;
}

void removeEnd(CircularLinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = list->tail;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        Node* prev = list->head;
        while (prev->next != list->tail) {
            prev = prev->next;
        }
        prev->next = list->head;
        list->tail = prev;
    }
    free(temp);
    list->size--;
}

void removeAt(CircularLinkedList* list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Invalid position!\n");
        return;
    }
    if (position == 0) {
        removeFront(list);
    } else if (position == list->size - 1) {
        removeEnd(list);
    } else {
        Node* temp = list->head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        Node* delNode = temp->next;
        temp->next = delNode->next;
        free(delNode);
        list->size--;
    }
}

int search(CircularLinkedList* list, int key) {
    if (isEmpty(list)) return -1;
    Node* temp = list->head;
    int index = 0;
    do {
        if (temp->data == key) return index;
        temp = temp->next;
        index++;
    } while (temp != list->head);
    return -1;
}

void traverse(CircularLinkedList* list) {
    if (isEmpty(list)) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = list->head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != list->head);
    printf("(back to head)\n");
}

void clear(CircularLinkedList* list) {
    while (!isEmpty(list)) {
        removeFront(list);
    }
}

void display(CircularLinkedList* list) {
    traverse(list);
}

Node* getHead(CircularLinkedList* list) {
    return list->head;
}

Node* getTail(CircularLinkedList* list) {
    return list->tail;
}

int main() {
    CircularLinkedList* list = createList();
    int choice, data, pos;

    do {
        printf("\n--- Circular Linked List Menu ---\n");
        printf("1. Add Front\n2. Add End\n3. Add At Position\n");
        printf("4. Remove Front\n5. Remove End\n6. Remove At Position\n");
        printf("7. Search\n8. Traverse/Display\n9. Size\n10. Is Empty\n");
        printf("11. Clear\n12. Get Head\n13. Get Tail\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Enter data: "); scanf("%d", &data); addFront(list, data); break;
            case 2: printf("Enter data: "); scanf("%d", &data); addEnd(list, data); break;
            case 3: printf("Enter data and position: "); scanf("%d %d", &data, &pos); addAt(list, data, pos); break;
            case 4: removeFront(list); break;
            case 5: removeEnd(list); break;
            case 6: printf("Enter position: "); scanf("%d", &pos); removeAt(list, pos); break;
            case 7: printf("Enter key: "); scanf("%d", &data);
                    pos = search(list, data);
                    if (pos != -1) printf("Found at position %d\n", pos);
                    else printf("Not found\n");
                    break;
            case 8: display(list); break;
            case 9: printf("Size: %d\n", getSize(list)); break;
            case 10: printf(isEmpty(list) ? "List is empty\n" : "List is not empty\n"); break;
            case 11: clear(list); break;
            case 12: if (getHead(list)) printf("Head: %d\n", getHead(list)->data); else printf("List empty\n"); break;
            case 13: if (getTail(list)) printf("Tail: %d\n", getTail(list)->data); else printf("List empty\n"); break;
        }
    } while (choice != 0);

    clear(list);
    free(list);
    return 0;
}
