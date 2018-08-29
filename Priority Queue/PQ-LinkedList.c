
/*
* Purpose: Priority Queue using linked list implementation
*/

#include<stdio.h>
#include<stdlib.h>


typedef  struct QueueElement{
    //int data;
    char data[100];
    int priority;
} QueueElement;

typedef struct QueueNode
{
	QueueElement element;
	struct QueueNode *next;
} QueueNode;

typedef struct Queue{
    QueueNode * front;
    QueueNode * rear;
    int size;
} Queue;

void InitiateQueue(Queue *ptrQ) {
    ptrQ->front= NULL;
    ptrQ->rear = NULL;
    ptrQ->size = 0;
}

void display(Queue *ptrQ)
{
	QueueNode *temp;
	temp = ptrQ->front;
	printf("\nPriority Queue: ");
	while(temp!=NULL)
	{
		printf("%s,%d ",temp->element.data, temp->element.priority);
		temp=temp->next;
	}
//printf("\n");
}

void enqueue(int value, int num, Queue *ptrQ)
{
	if (num<1 || num>5){
		num=5;
	}
	QueueNode *temp, *temp2;
	temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
	//temp->element.data=value;
	strcpy(temp->element.data, value);
	temp->element.priority=num;
	temp->next=NULL;
	
	if(ptrQ->front==NULL){
		ptrQ->front=temp;
		ptrQ->rear=temp;
	}
	else if(ptrQ->front->element.priority > num)
	{
		temp->next=ptrQ->front;
		ptrQ->front=temp;
	}
	else
	{
		temp2=ptrQ->front;
		while(temp2->next != NULL && (temp2->next->element.priority) <= num)
			temp2=temp2->next;
		
		if(temp2->next == NULL){
			ptrQ->rear = temp;
		}
			
		temp->next=temp2->next;
		temp2->next=temp;
	}
	
	ptrQ->size++;
	display(ptrQ);
}

void dequeue(Queue *ptrQ) 
{
	if(ptrQ->front!=NULL)
	{
	printf("\n\tRemoved: %d",ptrQ->front->element);
	ptrQ->front = ptrQ->front->next;
	ptrQ->size--;
	display(ptrQ);
	}
	else
	printf("\nError: List Empty");
}

void peek(Queue *ptrQ){
	printf("\n%s\n", ptrQ->front->element.data);
}

void size(Queue *ptrQ){
	printf("\n%d\n", ptrQ->size);
}

int isRegular(Queue *ptrQ){
	if(ptrQ->front->element.priority == ptrQ->rear->element.priority){
		//printf("\nIt is a regular queue.\n");
		return 1;
	}else{
	//	printf("\nIt is a priority queue.\n");
	return 0;
	}
}

int isEmpty(Queue *ptrQ){
	return ptrQ->size == 0;
}

int  isFull(Queue *ptrQ){
  return 0;
}
	
int main()
{
	int menuChoice, data, check=1;
	//int val;
	char val[100]; 
	int pr;
	//char val[100];
	
	Queue *ptrQ;
	ptrQ = (struct Queue *)malloc(sizeof(struct Queue));
	//QueueNode *myNode;
	InitiateQueue(ptrQ);
	int priority;
	char str[10];
	
	while(check==1)
	{
		printf("\nSelect:\n1. Insert\n2. Remove\n3. Peek\n4. isRegular?\n5. Size\n6. isEmpty\n7. isFull\n8. Display\n9. Exit\n");
		scanf("%d",&menuChoice);
		switch(menuChoice)
		{
			case 1:
				getchar();
				printf("\nEnter data: ");
				fgets(val, 100, stdin);
				val[strlen(val) - 1] = '\0';
				//scanf("%d", &val); //input from user
				printf("\nEnter priority: ");
				scanf("%d", &pr);
				enqueue(val, pr, ptrQ);	//Send Element and its priority for insertion
				break;
			case 2:
				dequeue(ptrQ);
				break;
			case 3:
				peek(ptrQ);
				break;
			case 4:
				if(isRegular(ptrQ)){
					printf("\nQueue is regular.\n");
				}else{
					printf("\nQueue is not regular; queue is priority queue.\n");
				}
				break;
			case 5:
				size(ptrQ);
				break;
			case 6:
				if(isEmpty(ptrQ)){
					printf("\nQueue is empty.\n");
				}else {
					printf("\nQueue is not empty.\n");
					}
				break;
			case 7:
				if(isFull(ptrQ)){
					printf("\nQueue is full.\n");
				}else {
					printf("\nQueue is not full.\n");
				}
				break;
			case 8:
				display(ptrQ);
				break;
			case 9:
				check=0; //stops the loop
				break;
			default:
				printf("Error, please select from menu: ");
				printf("\nPress 1 to continue or 0 to exit: ");
				scanf("%d",&check);
	
		}
	}
return 0;
}
