
// Structure de livre

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	char titre[100]; // titre
	char auteur[100]; // auteur
	int numIden; // Numero d'identification
	char categories[100]; // catégorie
}Livre;

Livre lireUnLivre()
{
	Livre l;
	printf("Titre :");
	scanf("%s",l.titre);
	printf("\nAuteur :");
	scanf("%s",l.auteur);
	printf("\nNuméro d'Identification :");
	scanf("%d",&l.numIden);
	printf("\nCategorie :");
	scanf("%s",l.categories);
	return l;
}
void ajouterUnLivre(Utilisateur u,Livre l,FILE *f)
{
	if(u.role == 2) // role == 2 ==> Professeur
	{
		//fprintf(f,"%s %s %d %s\n",l.titre,l.auteur,l.numIden,l.categories);
    	Livre l = lireUnLivre();
	  fprintf(f,"%s %s %d %s\n",l.titre,l.auteur,l.numIden,l.categories);
	  rewind(f);
	}
	rewind(f);
}

int nombreDeLivre(FILE *f)
{
	int count = 0; // counteur
	Livre l; 
	while(fscanf(f,"%s %s %d %s",l.titre,l.auteur,&l.numIden,l.categories) == 4)
		count++;
	rewind(f);
	return count;
}

Livre * allouerTabLivre(int taille)
{
	Livre *tab = malloc(taille * sizeof(Livre));
	return tab;
}

Livre * remplireTableau(FILE *f)
{
	int taille = nombreDeLivre(f);
	Livre *t = allouerTabLivre(taille);
	int i = 0;
	while(fscanf(f,"%s %s %d %s",t[i].titre,t[i].auteur,&t[i].numIden,t[i].categories) == 4)
		i++;
	rewind(f);
	return t;
}
	


void display(Livre l)
{
	printf("Titre:%s, Auteur: %s, Numéro d'Identification: %d, Catégorie: %s \n",l.titre,l.auteur,l.numIden,l.categories);
}

void afficherToutLivre(FILE *f)
{
	int n; // la taille du tableau
	Livre * tab;
	tab = remplireTableau(f);	
	n = nombreDeLivre(f);
	for(int i = 0 ; i < n ; i++)
	{
		printf("\n%d. ",i+1);
		display(tab[i]);
	}
}



void AjouterUnLivre(FILE *f)
{
  fseek(f, 0, SEEK_END);
	Livre l = lireUnLivre();
	fprintf(f,"%s %s %d %s\n",l.titre,l.auteur,l.numIden,l.categories);
	rewind(f);
}

void emprunter1(int choixL,FILE *fl,FILE *fe,char *login,int role)
{
 	Livre *tab;
	tab = remplireTableau(fl);
	fseek(fe, 0, SEEK_END);
 
  fseek(fe, 0, SEEK_END);
	fprintf(fe,"%s %d  |    %s %s %d %s\n",login,role,tab[choixL].titre,tab[choixL].auteur,tab[choixL].numIden,tab[choixL].categories);
    printf("\nLivre emprunté !");
    printf("\n\nVous devrez rendre %s de %s dans 3 minutes.",tab[choixL].titre, tab[choixL].auteur);
     printf("\n\n( jai mis seulement 5 sec pour ne pas à avoir à attendre 5min)\n");
    sleep(5);
    printf("\n\nIl est l'heure de rendre %s de %s !",tab[choixL].titre, tab[choixL].auteur);
	rewind(fe);
  }

void emprunter2(int choixL,FILE *fl,FILE *fe,char *login,int role)
{
 	Livre *tab;
	tab = remplireTableau(fl);
	fseek(fe, 0, SEEK_END);
 
  fseek(fe, 0, SEEK_END);
	fprintf(fe,"%s %d  |    %s %s %d %s\n",login,role,tab[choixL].titre,tab[choixL].auteur,tab[choixL].numIden,tab[choixL].categories);
    printf("\nLivre emprunté !");
    printf("\n\nVous devrez rendre %s de %s dans 5 minutes.",tab[choixL].titre, tab[choixL].auteur);
    printf("\n\n(jai mis seulement 10 sec pour ne pas à avoir à attendre 5min)\n");
     sleep(10);
 
    printf("\n\nIl est l'heure de rendre %s de %s !",tab[choixL].titre, tab[choixL].auteur);
	rewind(fe);
  }
/******************************************** 

void rendre(choix_rendre,FILE *fl,FILE *fe,char *login,int role)
{
	Livre *tab;
	//tab = remplireTableau(fl);
  fseek(fe, 0, SEEK_END);
  char ti[] = tab[choix_rendre].titre;
  char a[] = tab[choix_rendre].auteur;
  char n[] = tab[choix_rendre].numIden;
  char c[] = tab[choix_rendre].categories;
        delnword(ti, "tab[choix_rendre].titre", -1);
        delnword(a, "tab[choix_rendre].auteur", -1);
        delnword(n, "tab[choix_rendre].numIden", -1);
        delnword(c, "tab[choix_rendre].categories", -1);
  
	//fprintf(fe,"Utilisateur:%s Rôle:%d à rendu: %s %s %d %s",login,role,tab[choixR].titre,tab[choixR].auteur,tab[choixR].numIden,tab[choixR].categories);
  
  printf("\nLivre rendu !");
	rewind(fe);
}
*/
void delnword(char *t, char *c, int n)
{
    int i = 0, lenc = strlen(c);
 
    while((t = strstr(t, c)) != NULL)
    {
        if(i == n || n == -1)
            memmove(t, t + lenc, strlen(t) - lenc + 1);
        else
            t += lenc; // On saute le mot, c'est pas lui qu'on enlève
        i++;
    }
}


/*void sleep(int nbr_seconds)
{
	clock_t goal;
	goal = (nbr_seconds * CLOCKS_PER_SEC) + clock();
	while(goal > clock())
	{
		;
	}
} */



