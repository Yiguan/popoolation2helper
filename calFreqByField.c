#include <stdio.h>
#include <string.h>
#include <stdlib.h>


double  calFreq(char *ref, char *field, int min_depth, int max_depth, int *linesum0,int *linesum1,int *linesum2,int *linesum3)
{
    int a0,a1,a2,a3,a4,a5;
    double total;
    sscanf(field,"%d:%d:%d:%d:%d:%d",&a0,&a1,&a2,&a3,&a4,&a5);
    double freq=0.0;
    total = (double) (a0+a1+a2+a3);
    // summary line allele count
    *linesum0 = *linesum0 + a0;
    *linesum1 = *linesum1 + a1;
    *linesum2 = *linesum2 + a2;
    *linesum3 = *linesum3 + a3;
    // set flag, if position coverage not satisfied,
    // return 9.99 as flag value
    if(total > max_depth || total < min_depth)
    {
        return 9.99;
    }
    else
    {
        switch (*ref)
        {
        case 'a':
        case 'A':
            freq = a0/total;
            break;
        case 't':
        case 'T':
            freq = a1/total;
            break;
        case 'c': 
        case 'C':
            freq = a2/total;
            break;
        case 'g':
        case 'G':
            freq = a3/total;
            break;
        case 'N':
            printf("Reference allele: N?\n");
            // exit(0);
        case 'D':
            printf("Refereence allele: indel?\n");
            // exit(0);
        default:
            printf("Error! Reference allele not in A,T,C,G,N,D\n");
            exit(0);
        }
        return freq; 
    }
}
