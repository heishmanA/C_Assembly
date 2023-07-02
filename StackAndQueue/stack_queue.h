/* 	stack_queue.h file
	Supplied by Braeden Jeske
	Aaron Heishman
*/

/* Some helpful constants you can use when writing tests. :)*/
#define NUM_ENTRIES 20000
#define NUM_QUEUES 2
#define DEFAULT_RESULT -1
/* For table doubling, this should ideally be a power of 2. */
#define MIN_SIZE 4


/* Structs for Linked list style approaches. */
typedef struct LLNode{
	int data;
	struct LLNode *next;
}LLNode;


/* Queue.h */
typedef struct Queue{
	void 	*vars;
	void 	(*enqueue)	(struct Queue*, int);
	int 	(*dequeue)	(struct Queue*);
	int 	(*length)	(struct Queue*);
	void 	(*del)		(struct Queue*);
}Queue;


/* Queue1.h */
typedef struct Queue1{
	int length; /* Helper variable :) */
	LLNode *firstNode;
	LLNode *lastNode;
}Queue1;

Queue* 	newQueue1		();
void 	enqueueQueue1	(Queue*, int);
int 	dequeueQueue1	(Queue*);
int 	lengthQueue1	(Queue*);
void 	delQueue1		(Queue*);


/* Queue2.h */
typedef struct Queue2{
    int length;
    int curFront;
	int arrSize;
    int *entries;
}Queue2;

Queue* 	newQueue2		();
void 	enqueueQueue2	(Queue*, int);
int 	dequeueQueue2	(Queue*);
int 	lengthQueue2	(Queue*);
void 	delQueue2		(Queue*);


/* Stack.h*/
typedef struct Stack{
	void* 	vars;
	void 	(*push)		(struct Stack*, int);
	int 	(*pop)		(struct Stack*);
	int 	(*length)	(struct Stack*);
	void	(*del)		(struct Stack*);
}Stack;


/* Stack1.h*/
typedef struct Stack1{
	int length;
	LLNode *firstNode;
	LLNode *lastNode;
}Stack1;

Stack* 	newStack1		();
void 	pushStack1		(Stack*, int);
int 	popStack1		(Stack*);
int 	lengthStack1	(Stack*);
void 	delStack1		(Stack*);


/* Stack2.h*/
typedef struct Stack2{
	int length;
	int arrSize;
	int *entries;
}Stack2;

Stack* 	newStack2		();
void 	pushStack2		(Stack*, int);
int 	popStack2		(Stack*);
int 	lengthStack2	(Stack*);
void 	delStack2		(Stack*);
