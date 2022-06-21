#include "options.h"

static struct Options long_options[]=
{
	{"help", no_argument, 0, 'h'},
	{"infile",required_argument, 0, 'i'}
};

char usage[] = "\nSPscore [OPTIONS]\n\
	\n\
	-h, --help			usage: [-i file]\n\
	-i, --infile			MSA file\n\
	\n";

void print_help_statement(){
	printf("%s", &usage[0]);
	return;
}

void parse_options(int argc, char **argv, Options *opt){
	int option_index, success;
	char c;
	if (argc==1){
		print_help_statement();
		exit(0);
	}
	while(1){
		c=getopt_long(argc,argv,"hi:",long_options, &option_index);
		if (c==-1) break;
		switch(c){
			case 'h':
				print_help_statement();
				exit(0);
				break;
			case 'i':
				success = sscanf(optarg, "%s", opt->msa);
				if (!success)
					fprintf(stderr, "Invalid MSA file.\n");
				break;
		}
	}
}
