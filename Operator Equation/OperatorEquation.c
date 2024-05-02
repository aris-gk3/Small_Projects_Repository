#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//thelo na ftiakso mia sinartisi p na pairnei san orisma tin lista ton arithmon, tin lista 
//ton prakseon kai to epithmito apotelesma kai na epistrefei 1 an isxiei i tautotita/tiponei mnma
int make_oper(float num[],char oper[],int result){
	int num_of_operands=7,crowd_of_numbers=8,i,j; //tha mporousa na exo ena apta dio plithi
	                                             //giati panta num_of_operands+1=crowd_of_numbers
	                                            //alla ta kratao gia katanoisi ton prakseon
	                                           //
	char operf[7];
	double numf[8],sum;							//antigrafo tis listes oper[] kai num se nees listes					
	for(i=0;i<7;i++){                           //entos tis sinartiseis gia na min tis allakso
		operf[i]=oper[i];
	}
	for(i=0;i<8;i++){
		numf[i]=num[i];
	}
	
	for(i=0;i<num_of_operands;i++){ //proto loop gia sinenosi arithmon
		if(operf[i]=='s'){
			numf[i]=(10.0*numf[i]+numf[(i+1)]);
			for(j=i+1;j<(crowd_of_numbers-1);j++){
				numf[j]=numf[j+1];
			}
			numf[j]=0;
			for(j=i;j<(num_of_operands-1);j++){
				operf[j]=operf[j+1];
			}
			operf[j]='0';
			num_of_operands--;
			crowd_of_numbers--;
			i--;
		}
	}
	for(i=0;i<num_of_operands;i++){ //deutero loop gia pol/smo k diairesi
		if(operf[i]=='*'){
			numf[i]=numf[i]*numf[i+1];
			for(j=i+1;j<(crowd_of_numbers-1);j++){
				numf[j]=numf[j+1];
			}
			numf[j]=0;
			for(j=i;j<(num_of_operands-1);j++){
				operf[j]=operf[j+1];
			}
			operf[j]='0';
			num_of_operands--;
			crowd_of_numbers--;
			i--;
		}
		if(operf[i]=='/'){
			numf[i]=numf[i]/numf[i+1];
			for(j=i+1;j<(crowd_of_numbers-1);j++){
				numf[j]=numf[j+1];
			}
			numf[j]=0;
			for(j=i;j<(num_of_operands-1);j++){
				operf[j]=operf[j+1];
			}
			operf[j]='0';
			num_of_operands--;
			crowd_of_numbers--;
			i--;
		}	
	}
	sum=numf[0];
	for(i=0;i<num_of_operands;i++){ //trito loop gia prosthesi k afairesi
		if(operf[i]=='+'){
			sum=sum+numf[i+1];
		}
		else if(operf[i]=='-'){
			sum=sum-numf[i+1];
		}
	}
	if(sum==result){
		return 1;
	}
	else{
		return 0;
	}
}

char int_to_char(int a){
	switch(a){
		case 0:
			return 's';
		case 1:
			return '+';
		case 2:
			return '-';
		case 3:
			return '*';
		case 4:
			return '/';
	}
}

int main(int argc, char *argv[]) {
	int i,i0,i1,i2,i3,i4,i5,i6,result=36,arithmos_liseon=0;
	float num[8]={8.,7.,6.,5.,4.,3.,2.,1.};
	char oper[7];
	for(i0=0;i0<5;i0++){
		oper[0]=int_to_char(i0);
		for(i1=0;i1<5;i1++){	
			oper[1]=int_to_char(i1);
			for(i2=0;i2<5;i2++){
				oper[2]=int_to_char(i2);
				for(i3=0;i3<5;i3++){
					oper[3]=int_to_char(i3);
					for(i4=0;i4<5;i4++){
						oper[4]=int_to_char(i4);
						for(i5=0;i5<5;i5++){
							oper[5]=int_to_char(i5);
							for(i6=0;i6<5;i6++){
								oper[6]=int_to_char(i6);
								if(make_oper(num,oper,result)){
									arithmos_liseon++;
									printf("Operator Solution:\n");
									for(i=0;i<7;i++){
										printf("%.0f",num[i]);
										if(oper[i]!='s')
											printf("%c",oper[i]);
									}
									printf("%.0f=36\n",num[i]);
								}
							}
						}
					}
				}
			}
		}
	}
	printf("Number of Solutions: %d\n",arithmos_liseon);
	return 0;
}
