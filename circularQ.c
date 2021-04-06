/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;
    printf("[----- [김태인] [2018038033] -----]\n");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //QueueType크기만큼 cQ의 동적할당
	cQ->front = 0; 
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ); //cQ의 동적할당 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
    if(cQ->front == cQ->rear) //front와 rear 이 같으면 cQ안은 비어있음을 알 수 있다.
    {    
        return 1; //1반환을 통해 if조건문 true 로 성립
    }   
    else
    {   
        return 0; //0반환을 통해 if조건문 false 로 성립
    }
}

/* complete the function */
int isFull(QueueType *cQ)
{
    int temp = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear이 4가 되는순간 0으로 바꾸기 위한 식
    if(temp == cQ->front) //rear + 1이 front와 같으면 cQ안은 꽉 차 있음을 알 수 있다.
    {    
        return 1; //1반환을 통해 if조건문 true 로 성립
    }
    else
    {
        return 0; //0반환을 통해 if조건문 false 로 성립
    }

    
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{   
    if (isFull(cQ)) //isFull이 1이면 참, 0이면 false 이다
    {
        printf(" Circular Queue is Full");
    }
    else
	{
        cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear + 1이 4가 넘어가지 않기 위한 식
        cQ->queue[cQ->rear] = item; //queue[cQ->rear]에 item을 넣는다.
    }
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    if (isEmpty(cQ)) //isEmpty이 1이면 참, 0이면 false 이다
    {
        printf(" Circular Queue is Empty");
    }
    else
    {   
        cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front + 1이 4가 넘어가지 않기 위한 식
        return cQ->queue[cQ->front]; //queue[cQ->front]에 있는 수를 지운다.
    }
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //front + 1이 4가 넘어가지 않기 위한 식
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //rear + 1이 4가 넘어가지 않기 위한 식

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

