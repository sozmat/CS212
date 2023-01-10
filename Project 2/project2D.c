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
	} else if (*op == '/') {
		operation = DIVIDE;
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
    double v = StringToDouble(argv[1]);
    MathOperation op = GetOperation(argv[2]);
    double v2 = StringToDouble(argv[3]);
    double result = 0.;
    switch (op)
    {
       case ADD:
         result = v+v2;
         break;
       case MULTIPLY:
	 result = v*v2;
	 break;
       case SUBTRACT:
	 result = v-v2;
	 break;
       case DIVIDE:
	 result = v/v2;
	 break;
       case UNSUPPORTED:
	 printf("This is an unsupported operator\n");
	 break;
    }
    printf("%d\n", (int) result);
 
    return 0;
}
