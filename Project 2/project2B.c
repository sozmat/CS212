#include <stdio.h>

int main()
{
    int A[100] = { 252, 657, 268, 402, 950, 66, 391, 285, 133, 577, 649, 166, 987, 314, 954, 214, 920, 230, 904, 801, 40, 552, 369, 682, 202, 712, 395, 517, 755, 603, 134, 385, 428, 941, 443, 477, 95, 647, 687, 737, 673, 19, 325, 697, 577, 181, 45, 964, 267, 600, 858, 145, 780, 760, 949, 509, 673, 717, 446, 634, 635, 679, 466, 474, 916, 855, 216, 899, 804, 159, 237, 625, 963, 388, 437, 682, 821, 325, 805, 876, 968, 414, 190, 434, 902, 794, 752, 729, 77, 243, 705, 953, 765, 637, 765, 158, 166, 599, 70, 927 };

    /* SORT IT */
    int i = 0;
    for (i = 0; i < 100; i++)
    {
	    int j;
	    for (j = i + 1; j < 100; j++)
	    {
		    if (A[j] < A[i])
		    {
			    int tmp = A[i];
			    A[i] = A[j];
			    A[j] = tmp;
		    }
	    }
    }


    /* PRINT IT */

    int g = 0;
    while (g < 100)
    {
	    int k = 0;
	    while (k < 10)
	    {
		    printf("\t%d", A[g]);
		    k++;
		    g++;
		}
	    printf("\n");
    }
}
