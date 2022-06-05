#include"bibli.h"
#include<unistd.h>
int suite=0;
int choixEnsuite,choix_rendre;



int main(void)
{
	FILE *f,*fl,*fe;
	int n,choix,connecter = 0,choix_livre;
	//char *succLog;
	
	char logn[100];
	char mdp[100];
	int rol;

	//*************************************

	f = fopen("utilisateur.txt","r+");
	fl = fopen("livres.txt","r+");
	fe = fopen("livremprunter.txt","r+");
	
	interface();
	
	
	do{
		
		
		printf("1. Se Connecter.\n");
		printf("2. Nouvel utilisateur ?\n");
		scanf("%d",&n);
		
		switch(n)
		{
			case 1: 
				
				printf("Login: ");
				scanf("%s",logn);
				
				printf("Mot de passe: ");
				scanf("%s",mdp);
				
				if(login(f,logn,mdp)){ 
					connecter = 1;
				}
				else{
					printf("\nutilisateur introuvable ou login incorrect\n");
				}
				
			      break;
			      
			case 2:
				
				ajouterNouveauxUtilisateur(f);
				
			       break;
			       
			default:printf("Entrer E ou P");
		}
		
		//lire le role avant
		
		if(roleUtilisateur(logn,f) != -1){
			rol = roleUtilisateur(logn,f);
		}/*else{
			printf("n'exist pas \n");
		}*/
		
		
	//}while(connecter != 1);
	
	if(connecter == 1){
	
	//printf("\n\n\t\tBonjour %s !\t\t\n\n",logn); 
	
	do
	{
			printf("\n\n\t\tBonjour %s !\t\t\n\n",logn);
			printf("Souhaitez-vous : \n\n");
			printf("1. Ajouter un livre \n");
			printf("2. Emprunter un livre\n");
			printf("3. Rendre un livre \n");
			printf("4. Se Deconecter \n\n");
			scanf("%d",&choix);
	
	
			switch(choix)
			{
				case 1:
					if(rol == 2){
					//afficherToutLivre(fl);
					printf("\n\n");

					printf("Avant d'ajouter un livre, il faut savoir que les catégories sont représentées par des chiffres :\n\n");
					printf("1. Fantastique\n2. Epistolaire\n3. Policier\n4. Nouvel\n5. Horreur\n\n");
					AjouterUnLivre(fl);
				 	}else{
				 		printf("\nMalheuresement, seul les professeurs peuvent ajouter des livres  \n");
						}
					
					suite=0;
					break;
					
				case 2:
					
					
					printf("Quelle livre souhaites-tu emprunter ? \n\n");
					afficherToutLivre(fl); 
					scanf("%d",&choix_livre);
					emprunter(choix_livre-1,fl,fe,logn,0);
					printf("Vous devez le rendre dans 3min.\n\n( il y a un compte à rebours de seulement 10 sec pour vérifier rapidement, un menu s'affiche ensuite\n");
					sleep(10);
					printf("\nVeuillez rendre le livre.\n");
					
				       printf("\n1. Rendre le livre\n2. Accepter la sanction et le rendre en retard\n3.Se déconnecter");
				       int RA;
				       scanf("%d",&RA);
				       			switch(RA)
				       			{
				       				case 1 : //void rendre livre
				       			
				       					break;
				       					
				       				case 2: //void sanction
				       				
				       					break;
				       				case 3:
				       					printf ("\n\nSouhaitez-vous vraiment vous deconnecter ?\n\n");
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
				       			
				       suite=0;			}
					break;
					
					
				case 3: 
					// 
					 printf("\n\nQuels livres souhaitez-vous rendre ?\n");
					 afficherToutLivre(fl); 
					 
					scanf("%d",&choix_rendre);
					//rendre(choix_livre+1,fl,fe,logn,0);
     
					
					suite=0;
					break;
					
				  case 4: // todo


            					printf ("\n\nSouhaitez-vous vraiment vous deconnecter ?\n\n");
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
					
				default : printf("entrez un bon nombre svp \n");
			}
		}while(suite==0);
	}
}while(connecter != 1);
	return 0;
}
	

