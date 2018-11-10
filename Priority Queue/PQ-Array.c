/* 
* Purpose: Priority Queue using array implementation
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXQUEUE 3

typedef  struct QueueElement{
    int data;
    int priority;
} QueueElement;

typedef struct Queue {
  	int front;
  	int rear;
  	int size;
    QueueElement element[MAXQUEUE];
} Queue;
  

void InitiateQueue(Queue *ptrQ) {
    ptrQ->front= 0;
    ptrQ->rear = -1;
    ptrQ->size = 0;
}

void enqueue(Queue *ptrQ, QueueElement myElement) {
  	
	if(myElement.priority < 1 || myElement.priority>5){
		myElement.priority = 5;
	  }
  
    QueueElement temp;
    int i, j;

	if (ptrQ->front == -1) {
        ptrQ->front = 0;
    }
    ptrQ->rear++;
    ptrQ->element[ptrQ->rear] = myElement;
    
    for (i = ptrQ->front; i < ptrQ->rear; i++) {
        for (j = i + 1; j <= ptrQ->rear; j++) {
            // place the element with high priority at the front 
            if (ptrQ->element[i].priority > ptrQ->element[j].priority) {
                temp = ptrQ->element[i];
                ptrQ->element[i] = ptrQ->element[j];
                ptrQ->element[j] = temp;
            } 
        }
    }
    ptrQ->size++;
    display(ptrQ);
  }

  void dequeue(Queue *ptrQ) {
    if (ptrQ->front == -1) {
        printf("Priority Queue underflow\n");
        return;
    }

    if (ptrQ->front == ptrQ->rear) {
        ptrQ->front = ptrQ->rear = -1;
    } else {     
        ptrQ->front++;
    }
    ptrQ->size--;
	  display(ptrQ);
  }

  void display(Queue *ptrQ) {
        int i;
        if (ptrQ->front == -1) {
          printf("Priority Queue Underflow\n");
          return;
        }
        for (i = ptrQ->front+1; i <= ptrQ->rear; i++) {
            printf("%d,%d ", ptrQ->element[i].data, ptrQ->element[i].priority);    
        }
        printf("\nsize: %d\n", ptrQ->size);  
  }
  
  int isFull(Queue *ptrQ){
  	if (ptrQ->size == MAXQUEUE) {
     // printf("PQ is full\n");
      return 1;
	  }else{
		  return 0;
	  }
  }
  
  int isEmpty(Queue *ptrQ){
  	//return ptrQ->front == -1;
  	//return ptrQ->size;
  	if(ptrQ->size > 0){
  		return 0;
	  }
	  else{
	  	return 1;
	  }
  }
  
  void size(Queue *ptrQ){
	  printf("\nsize of PQ: %d\n", ptrQ->size);
}


int isRegular(Queue *ptrQ){
	int i = ptrQ->front + 1;
	int j = ptrQ->rear;
	
	if(ptrQ->element[i].priority == ptrQ->element[j].priority){
		//printf("\nIt is a regular queue.\n");
		return 1;
	}else{
	//	printf("\nIt is a priority queue.\n");
	return 0;
	}
}

void peek(Queue *ptrQ){
	int i = ptrQ->front + 1;
	printf("\n%d,%d\n", ptrQ->element[i].data, ptrQ->element[i].priority);
}


int main() {
  Queue *ptrQ;
  QueueElement myElement;
  int i, menuChoice;

  memset(&ptrQ, 0, sizeof (Queue));
  //ptrQ.front = ptrQ.rear = -1;
  //ptrQ.size = 0;

  int check=1;

  while (check) {
      printf("\nSelect:\n1. Insert\n2. Remove\n3. Peek\n4. isRegular?\n5. Size\n6. isEmpty\n7. isFull\n8. Display\n9. Exit\n");

        scanf("%d", &menuChoice);
        switch (menuChoice) {
          case 1:
            if(isFull(&ptrQ)){ // #Nawal: put inside enqueue function?
              printf("\nQueue is full.\n");
            }else{
              printf("\nEnter data: ");
              scanf("%d", &myElement.data);
              printf("\nEnter Priority: ");
              scanf("%d", &myElement.priority);
              printf("\n");
              enqueue(&ptrQ, myElement);
              }
              break;
          case 2:
              dequeue(&ptrQ);
              break;
          case 3:
              peek(&ptrQ);
              break;
          case 4:
            if(isRegular(&ptrQ)){ 
              printf("\nQueue is regular.\n");
            }else{
              printf("\nQueue is not regular; queue is priority queue.\n");
            }
            break;
          case 5:
            size(&ptrQ);
            break;
          case 6:
            if(isEmpty(&ptrQ)){
              printf("\nQueue is empty.\n");
            }else {
              printf("\nQueue is not empty.\n");
            }
            break;
          case 7:
            if(isFull(&ptrQ)){
              printf("\nQueue is full.\n");
            }else {
              printf("\nQueue is not full.\n");
            }
          break;
          case 8:
            display(&ptrQ);
            break;
          case 9:exit(0);
          default:
              printf("Error, please select from menu: ");
              printf("\nPress 1 to continue or 0 to exit: ");
              scanf("%d",&check);
        }
  }
  return 0;
}
