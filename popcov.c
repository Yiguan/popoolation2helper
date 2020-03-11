#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cal_depth(char * ss)
{
    int a,t,c,g;
    sscanf(ss,"%d:%d:%d:%d",&a,&t,&c,&g);
    return a+t+c+g;
}

int main(int argc, const char * argv[])
{
    FILE * fp = fopen(argv[1],"r");
    char outName[strlen(argv[1])+1];
    strcpy(outName, argv[1]);
    strcat(outName,".cov");
    FILE * outp = fopen(outName,"w");
    if(fp && outp)
    {
        printf("%s successfully open.\n", argv[1]);
        printf("Calculating read depth ... \n");
        char tt[2048];
        while(fgets(tt,2048,fp)!=NULL)
        {
            char * scf = strtok(tt,"\t");
            char * pos = strtok(NULL,"\t");
            char * ref = strtok(NULL,"\t");
            fprintf(outp,"%s\t%s\t%s",scf,pos,ref);
            char * ff = strtok(NULL,"\t");
            while(ff!=NULL){
                int sum = cal_depth(ff);
                fprintf(outp,"\t%d",sum);
                ff = strtok(NULL,"\t");
            }
            fprintf(outp,"\n");
        }
        fclose(fp);
        fclose(outp);
        printf("DONE!\n");
    }
    else
    {
        printf("Can't open file!\n");
    }
    return 0;
}
