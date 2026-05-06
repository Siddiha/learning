// ─────────────────────────────────────────
//  STRUCTS, UNIONS, ENUMS & LINKED LISTS
//  (C has no classes — structs + pointers
//   are the foundation for data structures)
// ─────────────────────────────────────────

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ── Basic struct ──────────────────────────
struct Point {
    int x;
    int y;
};

// typedef removes the need to write "struct" every time
typedef struct {
    char   name[50];
    int    age;
    double salary;
} Employee;

// ── Nested struct ─────────────────────────
typedef struct {
    char street[100];
    char city[50];
    int  zip;
} Address;

typedef struct {
    char    name[50];
    int     age;
    Address address;
} Person;

// ── Self-referential struct (singly linked list node) ─
typedef struct Node {
    int          data;
    struct Node* next;   // must use "struct Node*" here, not "Node*"
} Node;

// ── Linked list helpers ───────────────────
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) { perror("malloc"); return NULL; }
    node->data = data;
    node->next = NULL;
    return node;
}

void listAppend(Node** head, int data) {
    Node* node = createNode(data);
    if (!*head) { *head = node; return; }
    Node* cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void listPush(Node** head, int data) {   // prepend
    Node* node = createNode(data);
    node->next = *head;
    *head      = node;
}

void listPrint(const Node* head) {
    for (const Node* cur = head; cur; cur = cur->next)
        printf("%d -> ", cur->data);
    printf("NULL\n");
}

int listLength(const Node* head) {
    int len = 0;
    for (const Node* cur = head; cur; cur = cur->next) len++;
    return len;
}

Node* listDelete(Node* head, int target) {
    if (!head) return NULL;
    if (head->data == target) {
        Node* next = head->next;
        free(head);
        return next;
    }
    Node* cur = head;
    while (cur->next && cur->next->data != target)
        cur = cur->next;
    if (cur->next) {
        Node* tmp = cur->next->next;
        free(cur->next);
        cur->next = tmp;
    }
    return head;
}

void listFree(Node* head) {
    while (head) {
        Node* tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(void) {

    // ════════════════════════════════════
    //  BASIC STRUCTS
    // ════════════════════════════════════

    // Designated initializers (C99)
    struct Point p1 = {.x = 3, .y = 4};
    struct Point p2 = {10, 20};   // positional

    printf("p1: (%d, %d)\n", p1.x, p1.y);
    printf("p2: (%d, %d)\n", p2.x, p2.y);

    // Struct copy — fully independent value copy
    struct Point p3 = p1;
    p3.x = 99;
    printf("p1.x still: %d\n", p1.x);   // 3 — unchanged

    Employee e1 = {"Alice", 30, 75000.0};
    printf("Name: %s, Age: %d, Salary: %.2f\n", e1.name, e1.age, e1.salary);

    // ── Pointer to struct — use -> ────────────
    Employee* ePtr = &e1;
    printf("Via ptr: %s\n", ePtr->name);   // same as (*ePtr).name
    ePtr->age = 31;
    printf("Updated age: %d\n", e1.age);   // 31

    // ── Nested struct ─────────────────────────
    Person person = {
        .name = "Bob",
        .age  = 25,
        .address = {
            .street = "123 Main St",
            .city   = "Springfield",
            .zip    = 12345
        }
    };
    printf("%s lives at %s, %s %d\n",
        person.name,
        person.address.street,
        person.address.city,
        person.address.zip);

    // ── Array of structs ──────────────────────
    Employee team[3] = {
        {"Carol", 28, 68000},
        {"Dave",  35, 82000},
        {"Eve",   22, 55000}
    };
    for (int i = 0; i < 3; i++)
        printf("%-8s age %d salary %.0f\n",
            team[i].name, team[i].age, team[i].salary);

    // ── Dynamic struct allocation ─────────────
    Employee* dynEmp = (Employee*)malloc(sizeof(Employee));
    if (!dynEmp) { perror("malloc"); return 1; }
    snprintf(dynEmp->name, sizeof(dynEmp->name), "Frank");
    dynEmp->age    = 40;
    dynEmp->salary = 95000;
    printf("Dynamic: %s %d\n", dynEmp->name, dynEmp->age);
    free(dynEmp);

    printf("sizeof(Employee) = %zu bytes\n", sizeof(Employee));

    // ════════════════════════════════════
    //  SINGLY LINKED LIST
    // ════════════════════════════════════

    Node* head = NULL;
    listAppend(&head, 1);
    listAppend(&head, 2);
    listAppend(&head, 3);
    listPush(&head, 0);          // prepend

    listPrint(head);              // 0 -> 1 -> 2 -> 3 -> NULL
    printf("Length: %d\n", listLength(head));

    head = listDelete(head, 2);
    listPrint(head);              // 0 -> 1 -> 3 -> NULL

    head = listDelete(head, 0);   // delete head node
    listPrint(head);              // 1 -> 3 -> NULL

    listFree(head);
    head = NULL;

    // ════════════════════════════════════
    //  UNION — same memory, different types
    // ════════════════════════════════════
    union Data {
        int   i;
        float f;
        char  str[4];
    };

    union Data d;
    d.i = 65;
    printf("int:   %d\n",   d.i);      // 65
    printf("char:  %c\n",   d.str[0]); // 'A' (same bytes as int 65)
    d.f = 3.14f;
    printf("float: %f\n",   d.f);      // 3.14 (overwrote i — only last member valid)

    // ════════════════════════════════════
    //  ENUM
    // ════════════════════════════════════
    typedef enum { MON=1, TUE, WED, THU, FRI, SAT, SUN } Day;
    Day today = WED;
    printf("Day: %d\n", today);   // 3

    typedef enum { RED=0xFF0000, GREEN=0x00FF00, BLUE=0x0000FF } Color;
    Color c = GREEN;
    printf("Color: 0x%06X\n", c);   // 0x00FF00

    (void)p2; (void)p3;
    return 0;
}
