
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct
{
	char *elements[QUEUE_SIZE];
	int num_elements;
	int front; //index for the front of the queue
	int back; //index for the back of the queue
	int count;
	
} Queue;

//Method to Initialize Queue
void InitializeQueue(Queue *q)
{
	for (int i = 0; i < QUEUE_SIZE; i++) {
		q->elements[i] = malloc(sizeof(char**)*(QUEUE_SIZE));}
	q->num_elements = 0;
	q->front = 0;
	q->back = 0;
	q->count = 0;
}

//Method to add to Queue (Enqueue)
void Enqueue(Queue *q, char *s)
{
	if (q->count >= QUEUE_SIZE){
		exit(EXIT_FAILURE);}
	q->elements[(q->num_elements)%QUEUE_SIZE] = s;
	q->num_elements++;
	q->back = (q->back +1) % QUEUE_SIZE;  //so wraps back around
	q->count++;
}

char *Dequeue(Queue *q)
{
	char *dequeued = q->elements[q->front];
	q->front = (q->front+1) % QUEUE_SIZE;   //so wraps back around
	q->count--;
	return dequeued;

}

void
PrintQueue(Queue *q)
{
    int i = 0;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front);
    printf("\tThe index for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->elements[i%QUEUE_SIZE]);
    }
}

void PrettyPrintQueue(Queue *q, char *type)
{
    if (q->front == q->back)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
	int iterate = (q->back) - (q->front);
	int i = 0;
        while ((i < iterate))   //this is where my problem is
        {
	    s = Dequeue(q);
            printf("%s\n", s);
	    i++;
        }
    }
}

char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}



int main(int argc,char *argv[]){

 
    Queue female_donors;
    InitializeQueue(&female_donors);
	
    Queue female_recipients;
    InitializeQueue(&female_recipients);

    Queue male_donors;
    InitializeQueue(&male_donors);

    Queue male_recipients;
    InitializeQueue(&male_recipients);

    Queue hospitals;
    InitializeQueue(&hospitals);
    
    FILE *f_in;
    
    f_in = fopen(argv[1], "r");
    if (f_in == NULL) {
	printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    char *name;
    char str[256];
    while(fgets(str, 256, f_in)!= NULL){
	char check = str[0];
	char check2 = str[2];
	if (check == 'H') {
		char *name = NewString(str+2);
		if ((female_donors.count > 0) && (female_recipients.count > 0)){
			printf("MATCH: %s donates to %s at hospital %s\n", Dequeue(&female_donors), Dequeue(&female_recipients), name);
		}
		else if ((male_donors.count > 0) && (male_recipients.count > 0)) {
			printf("MATCH: %s donates to %s at hospital %s\n", Dequeue(&male_donors), Dequeue(&male_recipients), name);
		}
		else {
			Enqueue(&hospitals, name);
		}
	}
	else if (check == 'R'){
		if (check2 == 'F'){
			char *name = NewString(str+4);
			if ((female_donors.count > 0) && (hospitals.count > 0)){
				printf("MATCH: %s donates to %s at hospital %s\n", Dequeue(&female_donors), name, Dequeue(&hospitals));
			}
			else {
			Enqueue(&female_recipients, name);
			}
		}
		else {
			char *name = NewString(str+4);
			if ((male_donors.count > 0) && (hospitals.count > 0)) {
				printf("MATCH: %s donates to %s at hospital %s\n", Dequeue(&male_donors), name, Dequeue(&hospitals));
			}
			else {
			Enqueue(&male_recipients, name);
			}
		}
	}
	else {
		if (check2 == 'F') {
			char *name = NewString(str+4);
			if ((female_recipients.count > 0) && (hospitals.count > 0)) {
				printf("MATCH: %s donates to %s at hospital %s\n", name, Dequeue(&female_recipients), Dequeue(&hospitals));
			}
			else {
			Enqueue(&female_donors, name);
			}
		}
		else {
			char *name = NewString(str+4);
			if ((male_recipients.count > 0) && (hospitals.count > 0)) {
				printf("MATCH: %s donates to %s at hospital %s\n", name, Dequeue(&male_recipients), Dequeue(&hospitals));
			}
			else {
			Enqueue(&male_donors, name);
			}
		}
	}
}			

   PrettyPrintQueue(&female_donors, "female donors");
   PrettyPrintQueue(&female_recipients, "female recipients");
   PrettyPrintQueue(&male_donors, "male donors");
   PrettyPrintQueue(&male_recipients, "male recipients");
   PrettyPrintQueue(&hospitals, "hospitals");

    fclose(f_in);
}
