#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//To epipleon apo tin proigoumeni ekdosi einai oti o ipologistis elegxei ektos apto an
//an iparxei diathesimi kinisi gia na nikisei o antipalos, elegxei kai an tha exei
//diathesimi kinisi gia na nikisei o antipalos meta tin kinisi tou kathos allazoun oi
//theseis ton pithanon kiniseon
//Episis an iparxei kinisi tou ipologisti pou gia opoiadipote kinisi tou antipalou
//kerdizei stin epomeni kinisi tin paizei

void ektiposi_pinaka(char table[][7]);

void ask_player_move(char table[][7],char current_p);

int find_lower_free_row(char table[][7], int collumn);//returns row which pawn will
//be placed if played in given collumn, or 7 if collumn is full

void find_win_move(char table[][7],int move[],char player);//move[0]=7 if no winning
//in given array for given player, move[0]=r,move[1]=c if r,c is a winning move

void find_double_threat(char table[][7],int bad_moves[], int move[], char player);//move[0]=7 if no
//double threats can be created for given player, move[0]=r,move[1]=c if r,c creates one

void kinisi_pc(char table[][7],char current_p);

char elegxos_apot(char table[][7]); //returns 'c' if game continues, '*' if that player
//has connect four, '+' if that player has connect four, 'f' if table is full

void print_result(char result);

int main(int argc, char *argv[]) {
	int r,c,mode,colour,start,end=0,user,result; //if user==1 it is the user's turn
	char table[7][7],current_p,user_colour,pc_colour;
	
	do{	
		for(r=0;r<7;r++){       //make empty table
			for(c=0;c<7;c++){  
				table[r][c]=' ';
			}
		}		
		
		printf("Press \"1\" if you want to play with a friend\nOtherwise press \"2\" to play against the computer\n");
		mode=(getchar() - 48);
		
		if(mode==1){
			do{
				printf("Pick which colour will start first by typing it's symbol (\"*\" or \"+\")\n");
				colour=getchar();
				if(colour=='*'){
					printf("\"*\" will start first\n");
					current_p='*';
				}
				else if(colour=='+'){
					printf("\"+\" will start first\n");
					current_p='+';
				}
				else{
					colour='\0';
					printf("Wrong Input\nType Again\n\n");
				}
			}while(colour=='\0'); //auto to do/while einai gia na eksafaliso oti to deutero input einai sosto
			printf("\nInstructions:\nYou can make your move by pressing the number of the collumn\nto which you want to place your piece when it's your turn\n\n");
			ektiposi_pinaka(table);
			do{
				ask_player_move(table,current_p);
				if(current_p=='*')
					current_p='+';
				else if(current_p=='+')
					current_p='*';
				ektiposi_pinaka(table);
			}while( (result=elegxos_apot(table)) == 'c' );
			print_result(result);
			printf("\nPress \"r\" if you want to play again, or any other key to exit\n\n\n");
			if( getchar() == 'r'){
				mode=999;
			}		
		}	
		
		else if(mode==2){
			do{
				printf("Pick a colour by typing it's symbol (\"*\" or \"+\")\n");
				colour=getchar();
				if(colour=='*'){
					printf("User has\"*\"\n");
					user_colour=colour;
					pc_colour='+';
				}
				else if(colour=='+'){
					printf("User has\"+\"\n");
					user_colour=colour;
					pc_colour='*';
				}
				else{
					colour='\0';
					printf("Wrong Input\nType Again\n\n");
				}
			}while(colour=='\0');  //auto to do/while einai gia na eksasfaliso oti to deutero input einai sosto
			printf("Press \"f\" if you want to go first otherwise any other key\n");
			start=getchar();
			if(start=='f'){
				printf("User will start first\n");
			}
			else{
				printf("Computer will start first\n");
			}				
			printf("\nInstructions:\nYou can make your move by pressing the number of the collumn\nto which you want to place your piece when it's your turn\n\n");
		    ektiposi_pinaka(table);
			if(start=='f'){
				current_p=user_colour;
				ask_player_move(table,current_p);
				printf("\n\n\nYour move:\n");
				user=0;
			}
			else{
				current_p=pc_colour;
				kinisi_pc(table,current_p);
				printf("\n\n\nThe Computer's move:\n");
				user=1;
			}
			ektiposi_pinaka(table);
				
			if(current_p=='*')
				current_p='+';
			else if(current_p=='+')
				current_p='*';
		
			do{
				if(user){				
					ask_player_move(table,current_p);
					printf("\n\n\nYour move:\n");
					user=0;
				}
				else{
					printf("\n\n\nThe Computer's move:\n");
					kinisi_pc(table,current_p);
					user=1;
				}
				if(current_p=='*')
					current_p='+';
				else if(current_p=='+')
					current_p='*';
				ektiposi_pinaka(table);
			}while( (result = elegxos_apot(table)) == 'c' );
			print_result(result);
			printf("Press \"r\" if you want to play again, or any other key to exit\n\n\n");
			if( getchar() == 'r'){
				mode=999;
			}
		}
		
		else{
			printf("Wrong Input\nType again\n\n");
			mode=999;
		}
		
	}while(mode==999); //to megalo do/while einai gia na eksasfaliso oti to proto input tou xristi einai dekto
	return 0;
}



void ektiposi_pinaka(char table[][7]){
	int r,c;
	char ch;
	printf("\t Collumns\n  ");
	for(r=0;r<7;r++){
		printf("  %d",r+1);
	}
	printf("\n");
	for(r=6;r>=0;r--){
		printf(" %d",r);
		for(c=0;c<7;c++){
			printf("%3c",table[r][c]);
		}
		printf("\n");
	}
}



void ask_player_move(char table[][7],char current_p){
	int r=5,n_move,completed_move=0;
	printf("\nPlayer with \"%c\"\nMake your next move\n\n",current_p);
	do{
		n_move=(getchar() - 48);
		if(n_move<0 || n_move>9){
			printf("Wrong Input\nType Again\n");
		}
		else if(table[6][n_move-1]!=' '){
			printf("Collumn you chose is full, choose another collumn\n\n");
		}
		else{
			do{
				if(r==-1){
					table[0][n_move-1]=current_p;
					completed_move=1;
				}				
				else if(table[r][n_move-1]!=' '){
					table[r+1][n_move-1]=current_p;
					completed_move=1;
				}
				r--;
			}while(completed_move==0);
		}
	}while(completed_move==0);
}



int find_lower_free_row(char table[][7], int collumn){
	int r,found;
	if( table[6][collumn] != ' '){
		return 7;
	}
	else{
		r=5,found=0;
		do{				
			if(table[r][collumn]!=' '){
				return r+1;
			}
			r--;
		}while(r>=0);
		return 0;		
	}
}



void find_win_move(char table[][7],int move[],char player){ //
	int r,i;                                                //
	for(i=0;i<7;i++){                                       //
		while( i<7 && (r=find_lower_free_row(table,i)) == 7 ){
			i++;                                              
		}
		if( i>=7 )
			break;
		table[r][i]=player;
		if( elegxos_apot(table) != 'c' ){
			table[r][i]=' ';
			move[0]=r;
			move[1]=i;
			return;
		}
		else{
			table[r][i]=' ';
		}
	}
	move[0]=7;
}



void find_double_threat(char table[][7],int bad_moves[], int move[], char player){
	int r,rn,i,j,l;
	char opponent;
	if( player == '*')
		opponent='+';
	else if( player == '+')
		opponent='*';
	for(i=0;i<7;i++){
		for(l=0;l<7;l++){
			if(i==bad_moves[l]){
				i++,l=-1;
			}
		}
		while( (r=find_lower_free_row(table,i)) == 7 && i<7 ){
			i++;
			for(l=0;l<7;l++){
				if(i==bad_moves[l]){
					i++,l=-1;
					if(i>=7)
						break;
				}
			}                                            
		}
		if( i>=7 )
			break;
		table[r][i]=player;
		for(j=0;j<7;j++){
			while( j<7 && (rn=find_lower_free_row(table,j)) == 7 ){
				j++;                                              
			}
			if( j>=7 )
				break;
			table[rn][j]=player;
			find_win_move(table,move,player);
			if( move[0] == 7 ){
				table[rn][j]=' ';
				table[r][i]=' ';
				break;
			}
			table[rn][j]=' ';
		}	
		table[r][i]=' ';
		if(j==7){
			move[0]=r;
			move[1]=i;
			return;
		}
	}
	move[0]=7;
}



void kinisi_pc(char table[7][7], char current_p){
	int pc_move,move[2],completed_move=0,r,rr,i,j,bad_moves[7]={7,7,7,7,7,7,7},num_bad_moves=0,bad;
	char opponent;
	
	if( current_p == '*')    //briskei to xroma tou antipalou
		opponent='+';
	else if( current_p== '+')
		opponent='*';
	
	find_win_move(table,move,current_p);
	if( move[0] != 7 ){
		table[move[0]][move[1]]=current_p;
		return;
	}
	
	find_win_move(table,move,opponent);
	if( move[0] != 7 ){
		table[move[0]][move[1]]=current_p;
		return;
	}
	
	for(i=0;i<7;i++){                      //elegxei an kapoia kinisi tou tha kanei//diathesimi thesi pou simplironei tetrada//gia ton antipalo                                 
		while( i<7 && (r=find_lower_free_row(table,i)) == 7 ){
			i++;                                              
		}
		if( i>=7 )
			break;
		table[r][i]=current_p;
		find_win_move(table,move,opponent);
		if( move[0] != 7 ){
			bad_moves[num_bad_moves]=i;
			num_bad_moves++;
		}
		table[r][i]=' ';
	}	
	
	find_double_threat(table,bad_moves,move,current_p);
	if( move[0] != 7){
		table[move[0]][move[1]]=current_p;
		return;
	}
	
	do{                               //epilegei tixaia epitrepti kinisi
		bad=0;
		srand(time(NULL)); 
		pc_move=rand() % 7;
		for(i=0;i<num_bad_moves;i++){
			if(pc_move==bad_moves[i]){
				bad=1;
			}
		}
	}while( table[6][pc_move] != ' ' || bad);
	
	r=6,completed_move=0;             //paizei tin tixaia kinisi
	do{
		if(r==-1){
			table[0][pc_move]=current_p;
			completed_move=1;
		}				
		else if(table[r][pc_move]!=' '){
			table[r+1][pc_move]=current_p;
			completed_move=1;
			}
		r--;
	}while(completed_move==0);
	return;	
}



char elegxos_apot(char table[][7]){ //tha mporousa na elegxo mono tous sindiasmous me to kanourio pioni
	int r,c,rn,cn,current_streak;
	char current_colour_streak;
	if(table[6][0]!=' ' && table[6][1]!=' ' && table[6][2]!=' ' && table[6][3]!=' ' && table[6][4]!=' ' && table[6][5]!=' ' && table[6][6]!=' '){
		return 'f';
	}
	current_streak=0; //elegxos orizontias tetradas
	for(r=0;r<7;r++){
		current_streak=0;
		for(c=0;c<7;c++){
			if(table[r][c]==' ')
				current_streak=0;
			else if(current_streak==0){
				current_colour_streak=table[r][c];
				current_streak++;
			}
			else if(table[r][c]==current_colour_streak){
				current_streak++;
				if(current_streak==4){
					return current_colour_streak;	
				}		
			}
			else{
				current_colour_streak=table[r][c];
				current_streak=1;
			}
		}
	}
	current_streak=0; //elegxos gia katheti tetrada
	for(c=0;c<7;c++){
		current_streak=0;
		for(r=0;r<7;r++){
			if(table[r][c]==' ')
				current_streak=0;
			else if(current_streak==0){
				current_colour_streak=table[r][c];
				current_streak++;
			}
			else if(table[r][c]==current_colour_streak){
				current_streak++;
				if(current_streak==4){
					return current_colour_streak;	
				}		
			}
			else{
				current_colour_streak=table[r][c];
				current_streak=1;
			}
		}
	}
	current_streak=0; //elegxos gia diagonies tetrades
	for(r=0;r<7;r++){       
		for(c=0;c<7;c++){   //pleonasmos
			current_streak=0,rn=r,cn=c;
			do{
				if(table[rn][cn]==' ')
					current_streak=0;
				else if(current_streak==0){
					current_colour_streak=table[rn][cn];
					current_streak=1;
				}
				else if(table[rn][cn]==current_colour_streak){
					current_streak++;
					if(current_streak==4){
						return current_colour_streak;
					}
				}
				else{
					current_streak=1;
					current_colour_streak=table[rn][cn];
				}
				rn++,cn--;
			}while(rn>=0 && rn<7 && cn>=0 && cn<7);
			current_streak=0,rn=r,cn=c;
			do{
				if(table[rn][cn]==' ')
					current_streak=0;
				else if( current_streak==0){
					current_colour_streak=table[rn][cn];
					current_streak=1;
				}
				else if(table[rn][cn]==current_colour_streak){
					current_streak++;
					if(current_streak==4){
						return current_colour_streak;
					}
				}
				else{
					current_streak=1;
					current_colour_streak=table[rn][cn];
				}				
				rn++,cn++;
			}while(rn>=0&&rn<7&&cn>=0&&cn<7);
		}
	}	
	return 'c';
}



void print_result(char result){
	if( result == 'f')
		printf("\n\n\nThe table is full\nIt's a DRAW\n");
	else if( result == '*' || result == '+')
		printf("\nThere is a connect four!\nThe Winner is \"%c\"\n",result);
}
