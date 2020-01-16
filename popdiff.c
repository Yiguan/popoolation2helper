#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calFreqByField.h"

// determine the number of field
int total_field_num(char *line)
{
    int count=1;
    while(*line != '\n')
    {
        if(*line == '\t')
        {
            count++;
        }
        line++;
    }
    return count;
}
// check depth, 
// if contain 9.99, return 0, indicate unsatisfied depth
// if not, return 1, indicate satisfied depth 
int checkDepth(double *arr)
{
	while (*arr)
	{
		if(*arr==9.99)
		{
			return 0;
		}
		arr++;
	}
	return 1;
}

int main(int argc, char const *argv[])
{
	// ***** Parse argument
	// $this -i input_filename -p 1-2,3-4,3-5
	char *filename=NULL;
	int pair[255]={0};
	int pairNum=0;
	int depth[2] = {0,999};
	for (int i = 1; i < argc; )
	{
		char flag;
		if(strlen(argv[i]) != 2 || *(argv[i]) != '-')
		{
			printf("Argument flag error!\n");
			exit(0);
		}
		flag = *(argv[i]+1);
		char *pp;
		char *ff;
		switch (flag)
		{
			case 'i':
				filename = (char *) argv[i+1];
				break;
			case 'p':
				pp = strtok((char *)argv[i+1],",");
				while(pp!=NULL)
				{
					sscanf(pp,"%d-%d",&pair[pairNum],&pair[pairNum+1]);
					pp = strtok(NULL,",");
					pairNum = pairNum + 2;
				}
				break;
			case 'd':
				sscanf(argv[i+1],"%d,%d", &depth[0],&depth[1]);
				break;
			default:
				printf("Argument Error!\n");
				exit(0);
		}
		i = i + 2;
	}
	// check compulsary arguments
	if(filename == NULL)
	{
		printf("Argument error,please enter input file!\n");
		exit(0);
	}
	if(pair[0] == 0)
	{
		printf("Enter compared groups: e.g. 2-3,1-4\n");
		exit(0);
	}

	// **************

	FILE * infp = fopen(filename,"r");
	char outname[90];
	strcpy(outname, filename);
	strcat(outname,".diff");
	FILE * outfp = fopen(outname,"w");
	if (infp && outfp)
	{
		char line[1024]; // line size
		fgets(line,sizeof(line), infp);
		int allField = total_field_num(line);
		fseek(infp, 0, SEEK_SET); // set file inner pointer to beginning
		// output col names
		fprintf(outfp, "chrom\tpos\tref\t");

		int m = 0;
		while(pair[m]!=0)
		{
			int mm = 0;
			int nn = 0;
			mm = pair[m];
			nn = pair[m+1];
			fprintf(outfp, "%c%d%c%d\t",'p',mm,'_',nn);
			m = m + 2;
		}
		fprintf(outfp, "\n");

		while(fgets(line,sizeof(line),infp) != NULL)
		{
			char chr[80];
			int pos;
			char ref;
			double allelefreq[allField-3];
			char *linep;
			linep = strtok(line,"\t");
			int field_num = 0;
			int lineSum[4] = {0,0,0,0};
			while(linep!=NULL)
			{	
				switch (field_num)
				{
					case 0:
						// fprintf(outfp, "%s\t", linep);
						sscanf(linep,"%s",chr);
						break;
					case 1:
						sscanf(linep,"%d",&pos);
						// fprintf(outfp, "%d\t", pos);
						break;
					case 2:
						ref = *linep;
						// fprintf(outfp, "%c\t", ref);
						break;
					default:
						allelefreq[field_num-3] = calFreq(&ref,linep,depth[0],depth[1],&lineSum[0],&lineSum[1],&lineSum[2],&lineSum[3]);
				}
				linep = strtok(NULL,"\t");
				field_num++;
			}
			// check biallelic
			int zeroNum = 0;
			int h=0;
			for(h=0;h<4;h++)
			{
				if(lineSum[h]==0)
				{
					zeroNum++;
				}
			}
			// check reference
			int checkref = 0;
			switch (ref)
			{
			case 'A':
			case 'a':
			case 'T':
			case 't':
			case 'C':
			case 'c':
			case 'G':
			case 'g':
				checkref = 1;
				break;
			default:
				checkref = 0;
				break;
			}
			
			// decide if print line
			if(checkDepth(allelefreq) && zeroNum ==2 && checkref)
			{
				fprintf(outfp, "%s\t%d\t%c\t", chr,pos,ref);
				int j = 0;
				while(pair[j]!=0)
				{
					int k = pair[j];
					int l = pair[j+1];
					fprintf(outfp, "%lf\t",allelefreq[k-1] - allelefreq[l-1]);
					j=j+2;
				}
				fprintf(outfp,"\n");
			}
		}
		fclose(infp);
		fclose(outfp);
	}
	else
	{
		printf("File I/O error!\n");
		exit(0);
	}
	return 0;
}
