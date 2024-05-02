#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLLUMNS 31
#define ROWS 67201

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void up_to_low(char word[]);
void putf_in_table(char words_table[][31]);
void print_dictionary(char words_table[][31],int num_of_words);
int find_unique_letters_of_word(char word[],char unique_letters[]);
int check_for_unique_letter_in_dictionary(char words_table[][31],int rows_of_words_table,int exception);
int check_for_comb_in_dictionary(char words_table[][31],int len_of_words_table,int exception,char smallest_unique_parts[100][31],int num_cons_letters);



int main(int argc, char *argv[]) {

	int written,r,c,i,j,ok,w,word_size,re,ce;
	char ch,smallest_unique_parts[100][31],unique_letters[27];
	
	char (*array)[COLLUMNS];                     //ftiaxno megalo pinaka gia na
	array = malloc(sizeof(int[ROWS][COLLUMNS])); // apothikeuso tis lekseis p dinontai

	do{
		r=c=ok=0;
		printf("Type the words (until 30 characters, using space in between) and press enter:\n");
		for(;;){
			if( (ch=getchar()) == '\r' || ch == '\n' ){
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
						if( (ch=getchar()) =='\r'){
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
	print_dictionary(array,r);       //tiponei tis lekseis p dothikan san eisodos
	if(r==1){
		if( strlen(array[0]) == 1){
			printf("\n\"%c\" is a unique letter",array[0][0]);
		}
		else{
			printf("\n\"%s\" contains unique letters:\n",array[0]);
			find_unique_letters_of_word(array[0],unique_letters);
			printf("%c ",unique_letters[0]);
			j=1;
			while( unique_letters[j] != '\0' ){
				printf(", %c  ",unique_letters[j]);
				j++;
			}
		}
	}
	else{
		for(i=0;i<r;i++){
			if( strlen(array[i]) == 1 ){
				for(re=ce=0;;){
					if(re==i)
						if(re==(r-1)){
							printf("\n\"%c\" is a unique letter\n",array[i][0]);
							break;
						}
						else{
							re++;
							ce=0;
						}
					else if( array[re][ce] == '\0'){
						if(re==(r-1)){
							printf("\n\"%c\" is a unique letter\n",array[i][0]);
							break;
						}
						else{
							re++;
							ce=0;
						}
					}
					else if( array[i][0] == array[re][ce]){
						printf("\n\"%c\" is not a unique letter\n",array[i][0]);
						break;
					}
					else
						ce++;
				}
			}
			else{
				if( check_for_unique_letter_in_dictionary(array,r,i) );
				else{
					for(j=2;j<= (strlen(array[i]));j++){
						if( check_for_unique_letter_in_dictionary(array,r,i) )
							break;
						else if(check_for_comb_in_dictionary(array,r,i,smallest_unique_parts,j)){
							printf("\n\"%s\" contains unique combination of letters in the words given\nSmallest unique parts:\n",array[i]);
							printf("%s ",smallest_unique_parts[0]);
							for(w=1;;w++){
								if(smallest_unique_parts[w][0]=='\0'){
									break;
								}
								printf(", %s",smallest_unique_parts[w]);
							}
							printf("\n");
							break;
						}
						else if( j == (strlen(array[i])) )
							printf("\n\"%s\" doesn't contain unique letter or combination of letters in the words given\n",array[i]);
					}
				}
			}	
		}	
	}
	free(array);
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
	}while(word[i]!='\0' && word[i]!=' ');
}



void putf_in_table(char words_table[][31]){
	FILE *fp;
	if((fp = fopen("englishWords.txt", "r")) == NULL){
		printf("Error opening file\n");
	}
	
	int r=0,c=0;
	char ch;
	
	for(;;){
		if( (ch=fgetc(fp)) == EOF )
			break;
		else if(ch==' ' || ch=='\n'){
			words_table[r][c]='\0';
			r++;
			c=0;
		}
		else{
			words_table[r][c]=ch;
			c++;
		}
	}
	fclose(fp);
}



void print_dictionary(char words_table[][31],int num_of_words){
	int i;
	printf("\n");
	for(i=0;i<num_of_words;i++){
		printf("%d) %s\n",i+1,words_table[i]);
	}
}


int find_unique_letters_of_word(char word[],char unique_letters[]){
	int i=0,j=0,num_of_unique_letters=0,unique;
	while( word[i] != '\0'){                              //Dimourgo lista me ta grammata pou sinanto(mia fora to kathe gramma)
		unique=1;
		for(j=0;j<num_of_unique_letters;j++){
			if(word[i]==unique_letters[j]){
				unique=0;
				break;
			}
		}
		if(unique){
			unique_letters[num_of_unique_letters]=word[i];
			num_of_unique_letters++;
		}
		i++;
	}
	unique_letters[num_of_unique_letters]='\0';
	return num_of_unique_letters;
}



int check_for_unique_letter_in_dictionary(char words_table[][31],int rows_of_words_table,int exception){
	int num_letters_to_check,i,r,c,unique_letters_found_num=0;
	char unique_letters_to_check[27]={},unique_letters_found[27]={};
	num_letters_to_check=find_unique_letters_of_word(words_table[exception],unique_letters_to_check);
	for(i=0;i<num_letters_to_check;i++){
		r=c=0;
		for(;;){
			if(r==exception){
				if( r == (rows_of_words_table - 1) ){
					unique_letters_found[unique_letters_found_num]=unique_letters_to_check[i];
					unique_letters_found_num++;
					break;
				}
				else{
					r++;
					c=0;
				}
			}
			else if(words_table[r][c]=='\0'){
				if(r==(rows_of_words_table-1)){
					unique_letters_found[unique_letters_found_num]=unique_letters_to_check[i];
					unique_letters_found_num++;
					break;
				}
				else{
					r++;
					c=0;	
				}
			}
			else if(words_table[r][c]==unique_letters_to_check[i]){
				break;
			}
			else
				c++;
		}
	}
	if(unique_letters_found_num>=1){
		printf("\n\"%s\" has the below unique letters:\n%c ",words_table[exception],unique_letters_found[0]);
		for(i=1;i<unique_letters_found_num;i++){
			printf(", %c",unique_letters_found[i]);
		}
		printf("\n");
		return 1;
	}
	else	
		return 0;
}



int check_for_comb_in_dictionary(char words_table[][31],int rows_of_words_table,int exception,char smallest_unique_parts[100][31],int num_cons_letters){
	int i,r,c,num_of_parts=0,j,neww,aa,ab;
	i=num_cons_letters-1;
	while(words_table[exception][i]!='\0'){
		r=c=0;
		if(exception==0)
			r=1;
		for(;;){
			if(words_table[r][c+num_cons_letters-1]=='\0'){
				if(r==(rows_of_words_table-1)){
					neww=1;
					for(aa=0;aa<num_of_parts;aa++){
						for(ab=0;ab<num_cons_letters;ab++){
							if(smallest_unique_parts[aa][ab]!=words_table[exception][i-num_cons_letters+1+ab])
								break;
						}
						if(ab==num_cons_letters){
							neww=0;
							break;
						}
					}
					if(neww){
						for(j=0;j<num_cons_letters;j++){
							smallest_unique_parts[num_of_parts][j]=words_table[exception][i-num_cons_letters+1+j];	
						}
						smallest_unique_parts[num_of_parts][j]='\0';
						num_of_parts++;
					}
					break;
				}
				r++;
				c=-1;
				if(r==exception){
					if(r==(rows_of_words_table-1)){
						neww=1;
						for(aa=0;aa<num_of_parts;aa++){
							for(ab=0;ab<num_cons_letters;ab++){
								if(smallest_unique_parts[aa][ab]!=words_table[exception][i-num_cons_letters+1+ab])
									break;
							}
							if(ab==num_cons_letters){
								neww=0;
								break;
							}
						}						
						if(neww){
							for(j=0;j<num_cons_letters;j++){
								smallest_unique_parts[num_of_parts][j]=words_table[exception][i-num_cons_letters+1+j];
							}
							smallest_unique_parts[num_of_parts][j]='\0';
							num_of_parts++;
						}
						break;
					}
					else{
						r++;
						c=-1;
					}
				}
			}
			else if(words_table[r][c]==words_table[exception][i-num_cons_letters+1]){
				for(j=1;j<num_cons_letters;j++){
					if(words_table[r][c+j]==words_table[exception][i-num_cons_letters+1+j]);
					else{
						j=0;
						break;	
					}			
				}
				if(j)
					break;
			}
			c++;
		}
		i++;
	}
	smallest_unique_parts[num_of_parts][0]='\0';
	if(num_of_parts>=1)
		return 1;
	else	
		return 0;
}
