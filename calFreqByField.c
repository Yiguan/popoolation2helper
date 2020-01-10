#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double calFreq(char *ref, char *field)
{
    int a0,a1,a2,a3,a4,a5;
    double total;
    sscanf(field,"%d:%d:%d:%d:%d:%d",&a0,&a1,&a2,&a3,&a4,&a5);
    double freq=0.0;
    total = (double) (a0+a1+a2+a3);
    switch (*ref)
    {
    case 'A':
        freq = a0/total;
        break;
    case 'T':
        freq = a1/total;
        break;
    case 'C':
        freq = a2/total;
        break;
    case 'G':
        freq = a3/total;
        break;
    case 'N':
        printf("Refereence allele: N?\n");
        exit(0);
    case 'D':
        printf("Refereence allele: indel?\n");
        exit(0);
    default:
        printf("Error! Reference allele not in A,T,C,G,N,D\n");
        exit(0);
    }
    return freq; 
}
