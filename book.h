// Structure de livre

typedef struct
{
	char titre[100]; // title
	char auteur[100]; // auteur
	int numIden; // Numero d'identification
	int categories; // 
}Livre;



int nombreDeLivre(FILE *f)
{
	int count = 0;
	Livre l; 
	while(fscanf(f,"%s %s %d %d",l.titre,l.auteur,&l.numIden,&l.categories) == 4)
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
	while(fscanf(f,"%s %s %d %d",t[i].titre,t[i].auteur,&t[i].numIden,&t[i].categories) == 4)
		i++;
	rewind(f);
	return t;
}


void display(Livre l)
{
	//printf("%s -- %s -- %d -- %d \n",l.titre,l.auteur,l.numIden,l.categories);
	printf("Titre: %s Auteur: %s ID: %d Catégorie: %d \n",l.titre,l.auteur,l.numIden,l.categories);
}

void afficherToutLivre(FILE *f)
{
	int n; // la taille du tableau
	Livre * tab;
	tab = remplireTableau(f);	
	n = nombreDeLivre(f);
	for(int i = 0 ; i < n ; i++)
	{
		printf("%d --",i+1);
		display(tab[i]);
	}
}





Livre lireUnLivre()
{
	Livre l;
	printf("\n");
	printf("Titre: ");
	scanf("%s",l.titre);
	printf("Auteur: ");
	scanf("%s",l.auteur);
	printf("ID: ");
	scanf("%d",&l.numIden);
	printf("Categorie: ");
	scanf("%d",&l.categories);
	return l;
}

void AjouterUnLivre(FILE *f)
{

	Livre l = lireUnLivre();
	fseek(f, 0, SEEK_END);
	fprintf(f,"%s  %s  %d  %d\n",l.titre,l.auteur,l.numIden,l.categories);
	printf("\n\nVotre livre a bien été ajouté à la bibliothèque !\n\n");
	rewind(f);


}




void emprunter(int choixL,FILE *fl,FILE *fe,char *login,int role)
{
	Livre *tab;
	tab = remplireTableau(fl);
	fseek(fe, 0, SEEK_END);
	fprintf(fe,"%s %d  |    %s %s %d %d\n",login,role,tab[choixL].titre,tab[choixL].auteur,tab[choixL].numIden,tab[choixL].categories);
	printf("\n\nLivre emprunté avec succès !\n");
	rewind(fe);
}


//********************************************















