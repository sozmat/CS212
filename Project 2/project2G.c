#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_strlen(char *s)
{
	int counter = 0;
	while(*s != '\0')
	{
		counter++;
		s++;
	}
	return counter;
}

void str_reverse(char *str)
{
	int i;
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		char keeper = str[len - 1];
		str[len-1] = str[i];
		str[i] = keeper;
		len--;
	}
}

int main()
{
    char *str = malloc(strlen("hello world")+1);
    strcpy(str, "hello world");
    str_reverse(str);
    if (strcmp(str, "dlrow olleh") == 0)
    {
        printf("Congrats!  You have successfully reversed \"hello world\" to \"%s\"\n", str);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Project does not work yet.  You reversed \"hello world\" to \"%s\"\n", str);
        exit(EXIT_FAILURE);
    }
}
