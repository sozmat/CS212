/*
 * I believe I have completed:
 *  Map based on linked lists: no (attempted)
 *  Double hashing: yes
 *  Performance study: yes 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;

void PrintCompany(Company *c)
{
    printf("%s:\n", c->name);
    printf("\tSymbol: %s\n", c->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", c->lastSale);
    printf("\tMarket Capitalization: %.2f\n", c->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", c->IPOyear);
}

void ReadFile(const char *filename, Company **companies_rv, int *numCompanies_rv)
{
    int  i, j;

    if (filename == NULL)
    {
        fprintf(stderr, "No filename specified!\n");
        exit(EXIT_FAILURE);
    }
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f_in, 0, SEEK_END);
    int numChars = ftell(f_in);
    // printf("The number of characters is %d\n", numChars);
    fseek(f_in, 0, SEEK_SET);

    char *file_contents = malloc(sizeof(char)*numChars+1);
    fread(file_contents, sizeof(char), numChars, f_in);
    file_contents[numChars] = '\0';
    fclose(f_in);
    /* Note: the memory for this array is used to populate
     * the fields of the companies.  If it is freed, then
     * the company structs all become invalid.  For the
     * context of this program, this array should not be 
     * freed. */

    // Find out how many lines there are
    int numLines = 0;
    for (i = 0 ; i < numChars ; i++)
        if (file_contents[i] == '\n')
            numLines++;
    // printf("Number of lines is %d\n", numLines);

    int      numCompanies = numLines-1; // first line is header info 
    Company *companies    = malloc(sizeof(Company)*numCompanies);

    /* strtok will parse the file_contents array.  
     * The first time we call it, it will replace every '"' with '\0'.
     * It will also return the first word before a 
     */
    int numColumns = 9;
    int numberOfQuotesPerColumn = 2;
    strtok(file_contents, "\"");
    for (i = 0 ; i < numberOfQuotesPerColumn*numColumns-1 ; i++)
         strtok(NULL, "\"");
    for (i = 0 ; i < numCompanies ; i++)
    {
         companies[i].symbol = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].name = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].lastSale = atof(strtok(NULL, "\""));
         strtok(NULL, "\"");
         companies[i].marketCap = atof(strtok(NULL, "\""));
         strtok(NULL, "\""); 

         /* Skip ADR TSO */
         strtok(NULL, "\"");
         strtok(NULL, "\"");

         companies[i].IPOyear = atoi(strtok(NULL, "\""));
         strtok(NULL, "\"");

         /* Skip Sector, Industry, Summary Quote */
         for (j = 0 ; j < 6 ; j++)
             strtok(NULL, "\"");

         //PrintCompany(companies+i);
    }

    /* Set parameters to have output values */
    *companies_rv    = companies;
    *numCompanies_rv = numCompanies;
}

int hash(char *name, long array_size)
{
    int hashval = 0;
    char *p = name;
    while (*p != '\0')
    {
        hashval = 31*hashval + *p;
        p++;
    }

    return hashval%array_size;
}

int hash2(long key, long array_size)
{
	unsigned long ans = (unsigned long)key;
	return (long)(ans % array_size);
}

typedef struct 
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;

void InitializeMapBasedOnHashTable(MapBasedOnHashTable *map, int numElements)
{
    map->numElements = numElements;
    map->keys = malloc(sizeof(char *)*numElements);
    map->companies = malloc(sizeof(Company)*numElements);
    for (int i = 0 ; i < numElements ; i++)
        map->keys[i] = NULL;
}

void StoreTo_MapBasedOnHashTable(MapBasedOnHashTable *map, Company *c)
{
    int hashval = hash(c->symbol, map->numElements);
    int hashval2 = hash2(hashval, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval2*i)%(map->numElements);
        if (idx < 0) idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            map->keys[idx]      = c->symbol;
            map->companies[idx] = *c;
            return;
        }
    }
}

Company *
FetchFrom_MapBasedOnHashTable(MapBasedOnHashTable *map, char *key)
{
    int hashval = hash(key, map->numElements);
    int hashval2 = hash2(hashval, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval2*i)%(map->numElements);  //basically gonna go over once each time so more collisions may occur
        if (idx < 0) idx+= map->numElements;       //instead of using 1 as increment, skip by whatever hash val 2 is
        if (map->keys[idx] == NULL)
        {
            return NULL;
        }

        if (strcmp(map->keys[idx], key) == 0)
        {
            return &(map->companies[idx]);
        }
    }
    
    return NULL;
}

void FetchAndPrint(MapBasedOnHashTable *mfht, char *key)
{
    Company *c = FetchFrom_MapBasedOnHashTable(mfht, key);
    if (c == NULL)
    {
        printf("Key %s has no corresponding company\n", key);
    }
    else
    {
        PrintCompany(c);
    }

}

//Implementation of Linked Lists
struct ll_node
{
    struct ll_node *next;
    Company *companies; //pointer to company struct
    char *key;
};

struct ll_node *StoreTo_MapBasedOnLinkedList(Company *companies, struct ll_node *cur_head)
{
    struct ll_node *rv = malloc(sizeof(struct ll_node));
    rv -> key = malloc(sizeof(char *));
    rv -> key = companies -> symbol;
    rv -> next = cur_head;
    return rv;
}

struct ll_node *FetchFrom_MapBasedOnLinkedList(Company *companies, struct ll_node *cur_head)
{
    if (cur_head == NULL)
	return NULL;

    //special case for cur_head matching companies 
    if (strcmp(cur_head->key, companies->symbol) == 0)
	return cur_head->next;

    struct ll_node *prev = cur_head;
    struct ll_node *curr = cur_head->next;
    while (curr != NULL)
    {
	if (strcmp(curr->key, companies->symbol) == 0)
	{
		prev->next = curr->next;
		free(curr);
		return cur_head;
	}
	prev = curr;
	curr = curr->next;
    }
    return cur_head;
}

int main(int argc, char *argv[])
{
    Company *companies = NULL;
    struct ll_node *cur_head = NULL; // for linked list
    cur_head = malloc(sizeof(struct ll_node));
    int      numCompanies;
    double total_hashstore_time = 0., total_hashfetch_time = 0., total_llstore_time = 0., total_llfetch_time = 0.;
    struct timeval startTime;
    struct timeval endTime;
    ReadFile(argv[1], &companies, &numCompanies);
    MapBasedOnHashTable mfht;
    printf("num companies is %d\n", numCompanies);
    InitializeMapBasedOnHashTable(&mfht, numCompanies*2);
    for (int i = 0 ; i < numCompanies ; i++)
    {
	gettimeofday(&startTime, NULL);
        StoreTo_MapBasedOnHashTable(&mfht, companies+i);
        gettimeofday(&endTime, NULL);
        total_hashstore_time += (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.;
    }

    
    for (int i = 0; i < numCompanies; i++) 
    {
	gettimeofday(&startTime, NULL);
	cur_head = StoreTo_MapBasedOnLinkedList(companies+i, cur_head);
	gettimeofday(&endTime, NULL);
	total_llstore_time += (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.;
    }
    
    printf("The average time for Hash Store function to complete is %g\n", total_hashstore_time / numCompanies);
    printf("The average time for Linked List Store function is %g\n", total_llstore_time / numCompanies);

    for (int i = 0; i < numCompanies; i ++)
    {
	gettimeofday(&startTime, NULL);
	FetchFrom_MapBasedOnHashTable(&mfht, companies->symbol);
	gettimeofday(&endTime, NULL);
	total_hashfetch_time += (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.;
	companies++;
    }
   
    /*
    for (int i = 0; i < numCompanies; i++) 
    {
	gettimeofday(&startTime, NULL);
	FetchFrom_MapBasedOnLinkedList(companies+1, cur_head);
	gettimeofday(&endTime, NULL);
	total_llfetch_time += (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.;

    }
    */
    printf("The average time for Hash Fetch function to complete is %g\n", total_hashfetch_time / numCompanies);
    printf("The average time for Linked List Fetch function is %g\n", total_llfetch_time / numCompanies);
    
    FetchAndPrint(&mfht, "ZNWAA");
    FetchAndPrint(&mfht, "Z");
    FetchAndPrint(&mfht, "ZIOP");
    /*
    FetchAndPrint(&mfht, "ZIOQ");
    FetchAndPrint(&mfht, "YIOQ");
    FetchAndPrint(&mfht, "QIOQ");
    FetchAndPrint(&mfht, "WIOQ");
    FetchAndPrint(&mfht, "XIOQ");
    FetchAndPrint(&mfht, "TIOQ");
    FetchAndPrint(&mfht, "UIOQ");
    FetchAndPrint(&mfht, "VIOQ");
    */
}

/* My choice for the second hash function was a simple modular one. I wasn't able to completely finish the performance study due to my inability to get the Linked List Fetch Function working, but from what I can tell for storing, the hash table is pretty effective, although I think that storing the elements in a linked list actually may be faster than storing them in a hash table. As for the traversal, I think the hash based map would be better since you'd have to iterate over every single struct belonging in the linked list when you want to find the element you're looking for. 
 */
