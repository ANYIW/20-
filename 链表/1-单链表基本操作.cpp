#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node {
    int data;
    Ptr next;
};
Ptr Create(int n) {
    Ptr head, tail;
    //哨兵
    head = tail = (Ptr)malloc(sizeof(struct Node));
    head->data = 0;
    head->next = NULL;
    //读取
    int d;
    for (int i = 0; i < n; i++) {
        scanf("%d", &d);
        Ptr tmp = (Ptr)malloc(sizeof(struct Node));
        tmp->data = d;
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
    }
    return head;
}
void Insert(Ptr head, int front, int data) {
    int count = 0;
    Ptr traversal = head;
    while (traversal->next != NULL && count != front) {
        traversal = traversal->next;
        count++;
    }
    if (count == front) {
        Ptr tmp = (Ptr)malloc(sizeof(struct Node));
        tmp->data = data;
        tmp->next = traversal->next;
        traversal->next = tmp;
    }
}
void Delete(Ptr head, int index) {
    if (index == 0)
        return;
    int count = 0;
    Ptr front = NULL;
    Ptr traversal = head;
    while (traversal != NULL && index != count) {
        front = traversal;
        traversal = traversal->next;
        count++;
    }
    if (traversal != NULL) {
        front->next = traversal->next;
        free(traversal);
    }
}
void Release(Ptr head) {
    Ptr tmp;
    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}
void Manage(Ptr head, int n) {
    int order;
    for (int i = 0; i < n; i++) {
        scanf("%d", &order);
        if (order == 0) {
            int front, data;
            scanf("%d%d", &front, &data);
            Insert(head, front, data);
        }
        else {
            if (order == 1) {
                int index;
                scanf("%d", &index);
                Delete(head, index);
            }
        }
    }
}
void Print(Ptr head) {
    if (head == NULL)
        return;
    head = head->next;//跳过哨兵
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}
int main() {
    int n;
    scanf("%d", &n);
    Ptr head = Create(n);
    scanf("%d", &n);
    Manage(head, n);
    Print(head);
    Release(head);
    return 0;
}