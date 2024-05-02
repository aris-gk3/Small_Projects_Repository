#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLLUMNS 31
#define ROWS 30000

// getch() -> getch_() manual implementation
#include <termios.h>
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void up_to_low(char word[]);
void print_dictionary(char words_table[][31],int num_of_words);

int after_ast(char *s1,char *s2,int i,int j){
	int letter_after_ast;
	i++;
	j++;
	letter_after_ast=i;
	if(s1[i]=='\0' || s1[i]==0 || s1[i]=='\n')
		return 1;
	while( s2[j] != '\0' && s2[j] != '\000' && s2[j] != 0 && s2[j] != '\n'){
		if( s1[i] == '*'){
			if( after_ast(s1,s2,i,j) )
				return 1;
		}
		else if( s1[i] == s2[j] )
			i++;
		else if(s1[i]=='?')
			i++;
		else
			i=letter_after_ast;
		j++;
	}
	if( s1[i] == '\0' || s1[i] == 0 || s1[i] == '*' || s1[i] == '\n' )
		return 1;
	else
		return 0;
}

int fqm(char *s1,char *s2){
	int i=0,j,k;
	while(s1[i]!='*'){
		if( (s1[i]=='\n' || s1[i]==0) && (s2[i]=='\n' || s2[i]==0))
			return 1;
		else if(s1[i]!=s2[i] && s1[i]!='?')
			return 0;
		i++;
	}
	j=i;
	if(s2[j]!='\0')
		k=after_ast(s1,s2,i,j);
	return k;
}

int main(int argc, char *argv[]) {
	int r,c,i,j,ok,re,ptrs[1000],np;
	char s1[31];
	char s2[]="testingtesting",ch;
	//printf("%d",fqm(s1,s2));
	char (*array)[COLLUMNS];                     //ftiaxno megalo pinaka gia na
	array = malloc(sizeof(int[ROWS][COLLUMNS])); // apothikeuso tis lekseis p dinontai
	
	printf("Type the word with special characters:\n");
	//scanf("%s",&s1);
	fgets(s1, 31, stdin);//fgets(buffer, MAX_LENGTH, stdin);
	//scanf("%s",&s1);

	do{
		r=c=ok=0;
		printf("Type the words with spaces in between and press enter:\n(until 10.000 characters)\n");
		for(;;){
			if( (ch=getche()) == '\r' || ch == '\n'){
				array[r][c]='\0';
				break;
			}
			else if(ch==' '){
				array[r][c]='\0';
				r++;
				c=0;
			}
			else if( ch<65 || (ch>90 && ch<97) || ch>122 ){
				printf("\nWrong Input, not English Charachters\nTry Again\n\n");
				ok=1;
				for(i=0;i<r;i++){
					for(j=0;j<30;j++){
						array[i][j]='\0';
					}
				}
				break;
			}
			else{
				if( (c+1)>30){
					do{
						if( (ch=getche()) =='\r'){
							printf("\nLength of a given word is too big,\nTry Again\n\n");
							ok=1;
							for(i=0;i<r;i++){
								for(j=0;j<31;j++){
									array[i][j]='\0';
								}
							}
						}
					}while( ch != '\r' );
					break;
				}
				else{
					array[r][c]=ch;
					c++;
				}
			}
		}                          //an ftasei mexri edo exo balei tis lekseis
	}while(ok);                      //p dothikan stin eisodo ston array
	if(array[r][0]!='\0')
		r++; //isoutai me ton arithmo ton rows tou array
	for(re=0;re<r;re++){
		up_to_low(array[re]);
	}
	printf("\n\nYour Words:\n");
	print_dictionary(array,r);  
	np=0;
	for(i=0;i<r;i++){
		if( fqm(s1,array[i]) ){
			ptrs[np]=i;
			np++;
		}
	}
	if(np==1){
		printf("\nThe word that can be created from %s is: %s",s1,array[ptrs[0]]);
	}
	else if(np>1){
		printf("\nThe words that can be created from %s are: %s ",s1,array[ptrs[0]]);
		for(i=1;i<np;i++){
			printf(", %s",array[ptrs[i]]);
		}
	}
	else{
		printf("\nThere are no words that can be created from %s",s1);
	}
	printf("\n");
	return 0;
}



void up_to_low(char word[]){    //pairnei leksi kai tin metatrepei se peza
	int i=0;
	do{
		if(word[i]>=65 && word[i]<=90){
			word[i]+=32;
		}
		else if(word[i]>=97 && word[i]<=122);
		else{
			word[i+1]='\0';
			printf("Wrong Input\n")	;	
		}
		i++;
	}while(word[i]!='\0' && word[i]!=' ' && word[i]!='\n');
}



void print_dictionary(char words_table[][31],int num_of_words){
	int i;
	printf("\n");
	for(i=0;i<num_of_words;i++){
		printf("%d) %s\n",i+1,words_table[i]);
	}
}
