#include <iostream>

using namespace std;

struct STOCK
{
    string name;
    double price;
    STOCK* next;
};

STOCK* SortedMerge(STOCK* a, STOCK* b)
{
    STOCK* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->price >= b->price) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(STOCK* source, STOCK** frontRef, STOCK** backRef)
{
    STOCK* fast;
    STOCK* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void MergeSort(STOCK** headRef)
{
    STOCK* head = *headRef;
    STOCK* a;
    STOCK* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = SortedMerge(a, b);
}

void push(STOCK** head_ref, string new_data, double stockPrice)
{
    STOCK* new_node = new STOCK();
    new_node->name = new_data;
    new_node->price = stockPrice;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(STOCK* node)
{
    while (node != NULL)
    {
        cout << node->name << " " << node->price << endl;
        node = node->next;
    }
}

int main()
{
    STOCK* head = NULL;

    push(&head, "sugar", 3.45);
    push(&head, "cheese", 12.20);
    push(&head, "bread", 1.10);
    push(&head, "milk", 2.20);
    push(&head, "chocolate", 1.50);

    MergeSort(&head);

    printList(head);
}