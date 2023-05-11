#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"stat.h"
	
void etude_discrete(void)
{
	float** matrice;
	int nb , i;
	matrice = malloc(sizeof(float*)*2);

	printf("Quelle est le nombre d'echantillon ??\n");
	scanf("%d", &nb);
	matrice[0] = malloc(sizeof(float)*nb);
	matrice[1] = malloc(sizeof(float)*nb);

	printf("Entrer les valeurs de la variable X\n");
	for(i = 0 ; i < nb ; i++)
		matrice[0][i] = nombre_positif();
	printf("Entrer les valeurs des Effectifs \n");
	for(i = 0 ; i < nb ; i++)
		matrice[1][i] = nombre_positif();

	printf("****MATRICE DE DONNEES*****\n");
	affiche_tableau(matrice[0] , nb);
	affiche_tableau(matrice[1] , nb);

	printf("*******EFFECTIFS CUMMULE CROISSANT*******: \n");
	float* ecc = malloc(sizeof(float)*nb);
	ECC(matrice[1] , ecc , nb);
	affiche_tableau(ecc , nb);

	printf("******FREQUENCE CUMMULES CROISSANTE*******\n");
	float* fcc = malloc(sizeof(float)*nb);
	FCC(ecc , fcc , nb);
	affiche_tableau(fcc, nb);

	free(fcc);
	printf("******VALEUR DE LA TENDANCE CENTRALE******\n");
	int mode;
	mode = max(matrice[1] , nb);
	printf("\t mode = %.2f\n", matrice[0][mode]);

	float moy =0;
	for(i = 0 ; i < nb ; i++)
		moy += (matrice[0][i]*matrice[1][i])/ecc[nb-1];
	printf("\t moyenne = %.2f\n", moy);

	int mediane = 0;
	while(ecc[mediane] < ecc[nb-1]/2)
		mediane++;
	printf("\t mediane = %.2f\n", matrice[0][mediane]);

	int Q1 = 0;
	while(ecc[Q1] < ecc[nb-1]/4)
		Q1++;
	printf("\t Q1 = %.2f\n", matrice[0][Q1]);

	printf("\t Q2 = %.2f\n", matrice[0][mediane]);

	int Q3 = 0;
	while(ecc[Q3] < ecc[nb-1]*3/4)
		Q3++;
	printf("\t Q3 = %.2f\n", matrice[0][Q3]);

	printf("VALEUR DE DISPERSION : \n");
	float variance =0;
	for(i = 0 ; i < nb ; i++)
		variance += (matrice[0][i]*matrice[1][i]*matrice[0][i])/ecc[nb-1];
	variance = variance - moy*moy;
	printf("\t variance = %.2f\n", variance);

	printf("\t Ecart-type = %.2f\n",sqrt(variance));
	printf("\t Intervalle inter-quantile = %.2f\n", matrice[0][Q3]-matrice[0][Q1]);
	printf("\t Etendue = %.2f\n", matrice[0][nb-1] - matrice[0][0]);
	printf("\t coefficient de variation = %.2f\n", sqrt(variance)/moy);
	free(ecc);
	free(matrice[0]);
	free(matrice[1]);

}
void etude_continue(void)
{
	float** matrice;
	int nb , i;
	matrice = malloc(sizeof(float*)*3);

	printf("Quelle est le nombre d'element ? \n");
	scanf("%d", &nb);
	matrice[0] = malloc(sizeof(float)*nb);
	matrice[1] = malloc(sizeof(float)*nb);
	matrice[2] = malloc(sizeof(float)*nb);

	printf("Entrer les valeurs de la variable de la borne inferieur\n");
	for(i = 0 ; i < nb ; i++)
		matrice[0][i] = nombre_positif();
	printf("Entrer les valeurs de la variable de la borne supperieur\n");
	for(i = 0 ; i < nb ; i++)
		matrice[1][i] = nombre_positif();
	printf("Entrer les valeurs des Effectifs \n");
	for(i = 0 ; i < nb ; i++)
		matrice[2][i] = nombre_positif();

	printf("*******MATRICE DE DONNEES*****\n");
	affiche_tableau(matrice[0] , nb);
	affiche_tableau(matrice[1] , nb);
	affiche_tableau(matrice[2] , nb);

	printf("******EFFECTIFS CUMMULES CROISSANT*****\n");
	float* ecc = malloc(sizeof(float)*nb);
	ECC(matrice[2] , ecc , nb);
	affiche_tableau(ecc , nb);

	printf("**********FREQUENCE CUMMULES CROISSANT*********\n");
	float* fcc = malloc(sizeof(float)*nb);
	FCC(ecc , fcc , nb);
	affiche_tableau(fcc, nb);
	
	free(fcc);
	printf("VALEURS DE TENDANCE CENTRALE\n");

	float classm;
	classm = max(matrice[2] , nb);
	/*printf("\tclasse modale = [%.2f ; %.2f[\n", matrice[0][classm] , matrice[1][classm]);
	printf("\tmode = %.2f\n",(matrice[0][classm]+matrice[1][classm])/2);*/

	float moy = 0;
	for(i = 0 ; i < nb ; i++)
		moy += ((((matrice[0][i]+matrice[1][i])/2)*matrice[2][i]) / ecc[nb-1]);
	printf("\t moyenne = %.2f\n", moy);
	
	int mediane = 0;
	while(ecc[mediane] < ecc[nb-1]/2)
		mediane++;
	printf("\t mediane = %.2f\n", (matrice[0][mediane]+matrice[1][mediane]) / 2);

	int Q1 = 0;
	while(ecc[Q1] < ecc[nb-1]/4)
		Q1++;
	printf("\t Q1 = %.2f\n", (matrice[0][Q1]+matrice[1][Q1]) / 2);

	printf("\t Q2 = %.2f\n", (matrice[0][mediane]+matrice[1][mediane]) / 2);

	int Q3 = 0;
	while(ecc[Q3] < ecc[nb-1]*3/4)
		Q3++;
	printf("\t Q3 = %.2f\n", (matrice[0][Q3]+matrice[1][Q1]) / 2);
	
	printf("VALEUR DE DISPERSION : \n");
	float variance = 0;
	float ci;
	for(i = 0 ; i < nb ; i++)
	{
		ci = ((matrice[0][i]+matrice[1][i])/2);
		variance += ci*ci*matrice[2][i]/ecc[nb-1];
	}
	variance = variance - moy*moy;
	printf("\t variance = %.2f\n", variance);

	printf("\t Ecart-type = %.2f\n",sqrt(variance));
	printf("\t Intervalle inter-quantile = [%.2f ; %.2f[ \n", matrice[0][Q3]-matrice[0][Q1], matrice[1][Q3]-matrice[1][Q1]);
	printf("\t Etendue = [%.2f ; %.2f[ \n", matrice[0][nb-1] - matrice[0][0] , matrice[1][nb-1] - matrice[1][0]);
	printf("\t coefficient de variation = %.2f\n", sqrt(variance)/moy);
	free(ecc);

	free(matrice[0]);
	free(matrice[1]);
	free(matrice[2]);

}
void affiche_tableau(float* tab, int nb)
{
	for(int i = 0 ; i < nb ; i++)
		printf("%10.2f", tab[i]);
	printf("\n");
}
float nombre_positif()
{
	float x;
	do
	{
		printf("Entrer un nombre positif\n");
		scanf("%f", &x);
		if(x < 0)
			printf("ce nombre n'est pas positif!!\n");
	}while(x < 0);
	return x;
}
void ECC(float* eff, float* ecc , int nb)
{
	int i;
	ecc[0] = eff[0];
	for(i = 1 ; i < nb ; i++)
		ecc[i] = ecc[i-1] + eff[i]; 
}
void FCC(float* ecc , float* fcc , int nb)
{
	int i;
	for(i = 0 ; i < nb ; i++)
		fcc[i] = ecc[i] / ecc[nb-1]; 
}
int max(float* tab, int nb)
{
	int max = 0;
	for(int i = 1 ; i < nb ;i++)
		if(tab[max] < tab[i])
			max = i;
	return max;	
}