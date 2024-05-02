#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int i=0;
	int a1,b1;
	long double a, b;
	long double max_error=1e-6, reminder=0;
	int g[30]={0}; //Pinakas apo g filled with 0
	printf("Give two integer (a,b) for the fraction to calculate:\n");
	scanf("%d %d",&a1, &b1);
	a=(long double)a1;
	b=(long double)b1;
	g[i]=ceil(b/a);
	reminder=a/b-1./g[i];

	while (reminder > max_error) {
		i++;
		g[i]=ceil(1./reminder);
		reminder=reminder-1./g[i];
	}

	i=0;
	printf("The denominators for the sum are:\n");
	while (g[i] != 0) {
		printf("c%d=%d\n",i+1, g[i]);
		i++;
	}

	return 0;
}
