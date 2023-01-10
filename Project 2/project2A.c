#include <stdio.h>

int main()
{
	int composite = 0;
		for (int i = 10; i < 500; i++)
		{
			composite = 0;
			for (int j = 2; j < i; j++)
			{
				if ((i % j) == 0 && (i % 2) == 1)
					composite = 1;
			}
			if (composite == 1)
				printf("%d is a composite number.\n", i);
		}
}



