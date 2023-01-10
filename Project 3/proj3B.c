#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
   ADD,
   MULTIPLY,
   SUBTRACT,
   DIVIDE,
   UNSUPPORTED
} MathOperation;

void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}
void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

struct stack
{
	float *items;
	int maxsize;
	int top;
};

struct stack* createStack(int capacity)
{
	struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
	
	pt->maxsize = capacity;
	pt->top = -1;
	pt->items = (float*)malloc(sizeof(float) * capacity);

	return pt;
}

int isEmpty(struct stack *pt)	//check to see if stack empty
{
	return pt->top == -1;
}

int isFull(struct stack *pt)	//check to see if stack full
{
	return pt->top == pt->maxsize-1;
}

void push(struct stack *pt, float x)
{
	if (isFull(pt))
	{
	//printf("Stack is full\n"); this was throwing off my output
	exit(EXIT_FAILURE);	
	}
	pt->items[++pt->top] = x; 
	
}

float pop(struct stack *pt)
{
	if (isEmpty(pt))
	{
	//printf("Stack is empty"); this was throwing off my output
	exit(EXIT_FAILURE);
	}
	return pt->items[pt->top--];
}

MathOperation GetOperation(char *op)
{
	char operation;
	int check = strlen(op);
	if (check > 1) {
			IssueBadOperationError();
	} else if (*op == '+') {
		operation = ADD;
	} else if (*op == 'x') {
		operation = MULTIPLY;
	} else if (*op == '-') {
		operation = SUBTRACT;
	} else {
		IssueBadOperationError();
	} return operation;
}


double CalculateFraction(int val1, int val2)
{
	double fraction = (double)val1 / (double)val2;
	return fraction;
}

double StringToDouble(char *str)
{
	double value = 0;
	double remainder = 0;
	if (*str == '-') {
		str = (str + 1);
		while (*str != '\0'){	
			{if ((*str == '5') || (*str == '1') || (*str == '0') || (*str == '2') || (*str == '3') || (*str == '4') || (*str == '6') || (*str == '7') || (*str == '8') || (*str == '9') || (*str == '-') || (*str == '.')) {}	
				else {
					IssueBadNumberError();}}
				if (*str == '.') {
					str = (str + 1);
					int len = strlen(str);
					int num = 0;
					int base = 10;
					for (int i = 1; i < len; i++) {
						base *= 10; }
					while (*str != '\0') {
						{if ((*str == '0') || (*str == '1') || (*str == '2') || (*str == '3') || (*str == '4') || (*str == '5') ||(*str == '6') || (*str == '7') || (*str == '8') || (*str == '9')) {}
							else{
							IssueBadNumberError();}}
						num = 10 * num + (int) (*str -'0');
						str ++;}	
					remainder = CalculateFraction(num, base);
					value += remainder;
					break;
				}	
				else {
					value = 10 * value + (double) (*str - '0');
					str++;
					} 
				}
		value *= -1;
	}
	else 
	{
		while (*str != '\0')
		{
			{
			if ((*str == '0') || (*str == '1') || (*str == '2') || (*str == '3') || (*str == '4') || (*str == '5') || (*str == '6') || (*str == '7') || (*str == '8') || (*str == '9') || (*str == '-') || (*str == '.')){}
			else {
				IssueBadNumberError();}}
			if (*str == '.') {
				str = (str + 1);
				int len = strlen(str);
				int num = 0;
				int base = 10;
				for (int i = 1; i < len; i++) {
					base *= 10; }
				while (*str != '\0')
				{
					{if ((*str == '0') || (*str == '1') || (*str == '2') || (*str == '3') || (*str == '4') || (*str == '5') || (*str == '6') || (*str == '7') || (*str == '8') || (*str == '9')) {}
					else {
						IssueBadNumberError();}
					}
					num = 10 * num + (int) (*str - '0');
					str++;
				}
				remainder = CalculateFraction(num, base);
				value += remainder;
				break;
			}
			else {
				value = 10 * value + (double) (*str - '0');
				str++;
				}
		}
	return value;
}
}

int main(int argc, char *argv[])
{
	struct stack *pt = createStack(10);
	int length = argc - 1;
	int i = 1;
	float result = 0.;
	while (i-1  <  length) {
		if ((*argv[i] == '+') || (*argv[i] == '-') || (*argv[i] == 'x')) 
		{
			MathOperation op = GetOperation(argv[i]);
			//take two recent ints and perform op
			float v = pop(pt);
			float v2 = pop(pt);
			switch (op)
			{
				case ADD:
					result = v+v2;
					break;
				case MULTIPLY:
					result = v*v2;	
					break;
				case SUBTRACT:
					result = v2-v;
					break;
			}
			push(pt, result);
		}		
		else{
			float num = StringToDouble(argv[i]);
			//add to stack
			push(pt, num);
		}
		i++;
   }
   printf("The total is %d\n",(int) result);
    return 0;
}
