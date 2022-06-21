#include <stdio.h>
#include <stdlib.h>
#include "global.h"

int main(int argc, char **argv){
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	int i,j, k;
	FILE* MSA_file;
	Options opt;
	parse_options(argc, argv, &opt);
	if ((MSA_file=fopen(opt.msa,"r"))==NULL ){ puts("Cannot open MSA file!"); exit(-1);}
	int length_of_MSA=0;
	int number_of_seqs=0;
	while((read=getline(&line, &len, MSA_file)) != -1){
		if (line[0] == '>'){
		}else{
			length_of_MSA = strlen(line);
			break;
		}
	}
	fclose(MSA_file);
	if ((MSA_file=fopen(opt.msa,"r"))==NULL ){ puts("Cannot open MSA file!"); exit(-1);}
	while((read=getline(&line, &len, MSA_file)) != -1){
		if (line[0] == '>'){
			number_of_seqs++;
		}else{
		}
	}
	fclose(MSA_file);
	char **MSA = (char**)malloc(number_of_seqs*sizeof(char*));
	for(i=0; i<number_of_seqs; i++){
		MSA[i]=(char*)malloc((length_of_MSA+1)*sizeof(char));
		for(j=0; j<length_of_MSA+1; j++){
			MSA[i][j]='\0';
		}
	}
	printf("number of sequences: %d\n",number_of_seqs);
	i=0;
	if ((MSA_file=fopen(opt.msa,"r"))==NULL ){ puts("Cannot open MSA file!"); exit(-1);}
	while((read=getline(&line, &len, MSA_file)) != -1){
		if (line[0] != '>'){
			strcpy(MSA[i],line);
		}
	}
	int numpairs=0;
	double SPscore=0;
	for(i=0; i<length_of_MSA; i++){
		for(j=0; j<number_of_seqs; j++){
			for(k=j+1; k<number_of_seqs; k++){
				if (MSA[j][i]==MSA[k][i]){
					SPscore=SPscore+3;
				}else if ( MSA[j][i] != 'N' && MSA[k][i] != 'N' && MSA[j][i] != 'n' && MSA[k][i] != 'n' && MSA[j][i] != MSA[k][i]){
					SPscore=SPscore-2;
				}else{
					SPscore--;
				}
				numpairs++;
			}
		}
	}
	double exponent;
	exponent = (-5.0/2.0);
	printf("Raw SPscore: %d\n",SPscore);
	printf("Number of pairs: %d\n",numpairs);
	//SPscore=SPscore/number_of_seqs;
	//SPscore=SPscore/numpairs;
	SPscore=SPscore/(number_of_seqs*exp(-5/2));
	SPscore=SPscore/numpairs;
	printf("Scaled SPscore: %lf\n",SPscore);
}
