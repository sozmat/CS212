#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *f_in;
	int buff_size = 0;
	char *buffer = NULL;

	f_in = fopen(argv[1], "r");
	if (f_in == NULL)
	{
		printf("%s is not a valid file.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	fseek(f_in, 0, SEEK_END);
	buff_size = ftell(f_in);
	fseek(f_in, 0, SEEK_SET);

	buffer = (char*)malloc(buff_size);
	fread(buffer, sizeof(char), buff_size, f_in);

	//find out how many words we are going to search for
	int *counter = malloc((argc-2) * sizeof(int));
	//initialize memory to 0?
	for (size_t m = 0; m < (argc-2); m++) {
		counter[m] = 0;
	}

	//separate the words in buffer
	for (int i = 0; i < buff_size; i++)
	{
		if (buffer[i] == ',' || buffer[i] == ' ' || buffer[i] == '.' || buffer[i] == '\n' || buffer[i] == EOF) 
		{
			buffer[i] = '\0';
		}
	}
	for (int j = 0; j < buff_size; j++) 
	{
		//compare every position in buffer with every word passing in
		for (int k = 0; k < argc - 2; k++)
		{
			int len = strlen(argv[k+2]);
			if (strncmp(buffer+j, argv[k+2], len) == 0) 
			{
				//main change from 2E to 2F, valgrind detects if I do *(buffer+j-1) when j=0
				//in that case I access mem that wasn't allocated
				if (j == 0) {	
						counter[k] += 1;
					}
				else {
				//not only are they same string, does char before it equal '\0'?
					if((*(buffer+j-1) == '\0') && (*(buffer+j+len) == '\0')){
						counter[k] += 1;
					}
				}
			}
		}
	}
	//counter is counting every word + how many times that word occurs	
	for (int f = 0; f < argc-2; f++)
	{
	printf("The word \"%s\" occurs %d times.\n", argv[f+2], counter[f]);
	}
	

	fclose(f_in);
	free(buffer);
	free(counter);
}
