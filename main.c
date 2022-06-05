#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"user.h"
#include"book.h"
int suite=0;
int choixEnsuite, choix_rendre;


int main(void)
{
	FILE *f,*fl,*fe;
	int n,choix,connecter = 0,choix_livre;
	char *succLog;
	
	char logn[100];
	char mdp[100];
	int rol;
	//*************************************

	f = fopen("utilisateur.txt","r+");
	fl = fopen("livres.txt","r+");
	fe = fopen("livremprunter.txt","r+");
	do{
		printf("*******************************************************\n\n");
		printf("		Application CY-BiblioTECH \n\n");
		printf("*******************************************************\n\n");
		printf("1. Se Connecter ?\n");
		printf("2. Nouvel utilisateur ?\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: printf("\n\nLogin :");
				scanf("%s",logn);
				printf("\nMot de passe :");
				scanf("%s",mdp);
				if(login(f,logn,mdp)){ 
					connecter = 1;
				}
				else{
					printf("\nL'utilisateur n'existe pas ou le mot de passe est incorrect.\n");
				}
			      break;
			case 2:
        ajouterNouveauxUtilisateur(f);
			       break;
			//default:printf("\nEntrer un choix correct !");
		}
		
		
    if(roleUtilisateur(logn,f) != -1){
			rol = roleUtilisateur(logn,f);}
    /*else{
			printf("N'existe pas\n");}*/
			
			
	//}while(connecter != 1);
	printf("\n\n\t\tBonjour %s !\t\t\n\n",logn);
  do{
	printf("\n\nQuelle action souhaitez-vous faire ? \n\n");
	printf("1. Ajouter un Livre.\n");
	printf("2. Emprunter un Nouveau Livre.\n");
	printf("3. Rendre un livre.\n");
	printf("4. Se Déconecter.\n");
	printf("\nQuels est votre choix ? ");
	scanf("%d",&choix);
	switch(choix)
	{
		case 1:
      if(rol == 2){
							printf("\n\nStock des livres présents dans la bibliothèque :\n\n");
							afficherToutLivre(fl);
							AjouterUnLivre(fl);
						}
      else{
							printf("\n\nDésolé %s,\n\nTu ne peux pas ajouter de livres car tu n'es pas un professeur.",logn);
						}
      suite=0;
			break;
		case 2:
          printf("\n\nQuels livres souhaitez-vous emprunter ?\n");
      
			    afficherToutLivre(fl); 
		      scanf("%d",&choix_livre);
      if(rol == 2){
		      emprunter2(choix_livre-1,fl,fe,logn,0);
        }
      else{
        emprunter1(choix_livre-1,fl,fe,logn,0);
        }
      suite=0;
			break;
		case 3: // todo 
      printf("\n\nQuels livres souhaitez-vous rendre ?\n");
      afficherToutLivre(fl); 
      //affiche les livres en sa possession
      scanf("%d",&choix_rendre);
      //rendre(choix_livre+1,fl,fe,logn,0);
      suite=0;
			break;
    
		case 4: // todo


      printf ("\n\nSouhaitez-vous vraiment vous déconnecter ?\n\n");
      printf ("1. Oui\n");
      printf ("2. Non\n");
      scanf ("%d", &choixEnsuite);

      switch (choixEnsuite)
	                {

	case 1:
    suite=1;
	    exit (1);
	    break;

	case 2:
	
        suite=0;
	    break;
	                }
			break;
		default : printf("\n\nEntrer un choix correct !\n");
	}
	}while(suite==0);
}while(connecter != 1);
	return 0;
}

