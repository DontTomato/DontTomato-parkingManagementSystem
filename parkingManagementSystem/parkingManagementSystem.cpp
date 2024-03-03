#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1024
static int maxsize;
typedef char ElemType;

typedef struct
{
    char num[10]; // License plate
    time_t starttime, endtime; // Entry and exit time
} car; // Car

typedef struct Stack
{
    int top;
    car a;
    struct Stack* next;

} Stack;

typedef struct
{
    char a[10];
} dat;

typedef struct
{ // Queue structure definition
    dat data[MAXSIZE];
    int front;
    int rear;
} SequenQueue;

void menu(Stack* cheku, SequenQueue* paidui); // Start menu
SequenQueue* InitQueue(); // Request an empty queue
int EmptyQueue(SequenQueue* Q); // Check if queue is empty
int FullQueue(SequenQueue* Q); // Check if queue is full
int EnQueue(SequenQueue* Q, ElemType* e); // Enqueue
int DeQueue(SequenQueue* Q, ElemType* e); // Dequeue
Stack* build(); // Build linked list
void parking(Stack* cheku, SequenQueue* paidui);
int fullstack(Stack* cheku);
void leave(Stack* cheku, SequenQueue* paidui);
void check(Stack* cheku, SequenQueue* paidui);
int main()
{
    Stack* cheku = build();
    SequenQueue* paidui = InitQueue();
    printf("Please enter the maximum capacity of the garage: ");
    scanf("%d", &maxsize);
    system("cls");
    menu(cheku, paidui);
    return 0;
}

void menu(Stack* cheku, SequenQueue* paidui)
{
    printf("********** Welcome to parking! **********\n");
    printf("********** Please choose an option **********\n");
    printf("********** 1 : Park. **********\n");
    printf("********** 2 : Leave. **********\n");
    printf("********** 3 : View. **********\n");
    printf("********** 4 : Exit. **********\n");
    int option;
    scanf("%d", &option);
    system("cls");
    switch (option)
    {
    case 1:
    {
        parking(cheku, paidui);
        menu(cheku, paidui);
        break;
    }
    case 2:
    {
        leave(cheku, paidui);
        menu(cheku, paidui);
        break;
    }
    case 3:
    {
        check(cheku, paidui);
        menu(cheku, paidui);
        break;
    }
    case 4:
    {
        printf("********** Thanks for using, welcome again! **********\n");
        break;
    }
    default: {
        printf("********** Please enter a correct command! **********\n");
        Sleep(1000);
        menu(cheku, paidui);
        system("cls");
        break;
    }
    }
}

// Implementations of fullstack, InitQueue, DeQueue, EnQueue, FullQueue, EmptyQueue, build, parking, leave, and check functions follow...
int fullstack(Stack* cheku)
{
    if (cheku->top < maxsize - 1)
        return FALSE; // Stack is not full
    else
        return TRUE; // Stack is full
}

SequenQueue* InitQueue()
{
    SequenQueue* Q = (SequenQueue*)malloc(sizeof(SequenQueue));
    if (Q != NULL) {
        Q->front = Q->rear = 0;
    }
    return Q;
}

int EmptyQueue(SequenQueue* Q)
{
    return Q->front == Q->rear; // Returns TRUE if the queue is empty
}

int FullQueue(SequenQueue* Q)
{
    return (Q->rear + 1) % MAXSIZE == Q->front; // Returns TRUE if the queue is full
}

int EnQueue(SequenQueue* Q, ElemType* e)
{
    if (FullQueue(Q))
    {
        printf("The waiting line is too long, please come back later.\n");
        return FALSE;
    }
    strcpy(Q->data[Q->rear].a, e);
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return TRUE;
}

int DeQueue(SequenQueue* Q, ElemType* e)
{
    if (EmptyQueue(Q))
        return FALSE; // Queue is empty, cannot dequeue
    else
    {
        strcpy(e, Q->data[Q->front].a);
        Q->front = (Q->front + 1) % MAXSIZE;
        return TRUE;
    }
}

Stack* build()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = -1;
        s->next = NULL;
    }
    return s;
}

void parking(Stack* cheku, SequenQueue* paidui)
{
    if (fullstack(cheku) == FALSE)
    {
        printf("Enter the license plate number:\n");
        Stack* newCar = (Stack*)malloc(sizeof(Stack));
        scanf("%s", newCar->a.num);
        newCar->a.starttime = time(NULL);
        newCar->next = cheku->next;
        cheku->next = newCar;
        cheku->top++;
        printf("Parking successful.\n");
    }
    else
    {
        printf("The garage is full, please wait at the entrance.\n");
        char licensePlate[10];
        scanf("%s", licensePlate);
        EnQueue(paidui, licensePlate);
    }
}

void leave(Stack* cheku, SequenQueue* paidui)
{
    if (cheku->top == -1)
    {
        printf("The garage is empty.\n");
        return;
    }

    printf("Enter the license plate of the car leaving:\n");
    char licensePlate[10];
    scanf("%s", licensePlate);
    // Implement the search and remove logic for the car leaving
    // This will involve traversing the stack, finding the car, calculating the parking fee,
    // and potentially moving a car from the waiting queue into the garage
}

void check(Stack* cheku, SequenQueue* paidui)
{
    int waitingCars = (paidui->rear - paidui->front + MAXSIZE) % MAXSIZE;
    if (cheku->top == maxsize - 1)
    {
        printf("The garage is full, there are %d cars waiting.\n", waitingCars);
    }
    else
    {
        int availableSpaces = maxsize - cheku->top - 1;
        printf("There are %d parking spaces available.\n", availableSpaces);
    }
}

