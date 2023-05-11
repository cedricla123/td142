#include<stdio.h>
#include<stdlib.h>
#include"stat.h"
int main()
{
	int choix;
	printf("\t Voulez-vous réaliser une étude :\n");
	printf("\t 1) Sur variable discrète ?\n");
	printf("\t 2) Sur variable continue ?\n");

	scanf("%d", &choix);

	if(choix == 1)
		etude_discrete();
	else
		if(choix == 2)
			etude_continue();
		else
			printf("Option invalide\n");

	return 0;
}