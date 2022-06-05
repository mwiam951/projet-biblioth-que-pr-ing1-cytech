

// define structure of the users
//

typedef struct
{
	char login[100]; //login
	char mdp[100]; //mdp securiser
	int role; // 1:etudiant 2:Professeur
}Utilisateur;


// diviser les taches pour les fonctions majuscules , muniscule ... etc
int siMaj(char c)
{
	return c >= 'A' && c <= 'Z' ? 1 : 0;
}

int siMin(char c)
{
	return c >= 'a' && c <= 'z' ? 1 : 0;
}

int siChiffre(char c)
{
	return c >= '0' && c <= '9' ? 1 : 0;
}

// fonction pour verifier le mot de passe
int verifierMdp(char *mdp)
{
	int checker[3] = {0};
	if(strlen(mdp) > 8){
		for(int i = 0 ; i < strlen(mdp) ; i++)
		{
			if(siMaj(mdp[i]))
				checker[0]++;
			if(siMin(mdp[i]))
				checker[1]++;
			if(siChiffre(mdp[i]))
				checker[2]++;
		}
		for(int i = 0 ; i < 3 ; i ++)
			if(checker[i] == 0)
				return 0; // false : mot de passe n'est pas securiser
		return 1;
	}
	return 0;
}

// fonction qui lit un utlisateur et return
Utilisateur lireUtilisateur()
{
	char choix;
	Utilisateur t;
	printf("Entrer votre login :");
	scanf("%s",t.login);
	printf("Entrer votre mot de passe :");
	scanf("%s",t.mdp);
	// verifier le mot de passe
	while(verifierMdp(t.mdp) == 0)
	{
		printf("\nEntrer mot de passe sécuriser comportant:\n");
    printf("\n - Un Chiffre\n - Une Majuscule\n - Une Minuscule\n - Ainsi que 8 caractères minimum.\n");
		scanf("%s",t.mdp);
	}	
	printf("Êtes-vous un Étudiant ou un Professeur ?\n\n");
	printf("1. Étudiant\n2. Professeur\n");
	scanf("%c",&choix);
	while(choix != '1' && choix != '2')
	{
		printf("\nEntrer un choix correct !\n");
		printf("1 ou 2 ?\n");
		scanf("%c",&choix);
	}
	if(choix == '1'){
		t.role = 1;}
       	else{
		t.role = 2;	}
	return t;
}


// fonction pour comparer deux utilisateur 
int comparer(Utilisateur u1,Utilisateur u2)
{
	if(strcmp(u1.login,u2.login) == 0 && strcmp(u1.mdp,u2.mdp) == 0 && u1.role == u2.role)
		return 1; // égaux
	return 0; // ne sont pas les mêmes
}

//Fonction pour tester si l'utilisateur existe deja dans le fichier
int testSiExist(FILE *f,Utilisateur t)
{
	Utilisateur u;
	while(fscanf(f,"%s %s %d",u.login,u.mdp,&u.role) == 3)
	{
		if(comparer(t,u)) // la valeur retourner égale à 1
			return 1; // l'utilisateur existe deja
	}
	rewind(f); // pour le pointeur de fichier qu'il pointe aux début
	return 0; // l'utilisateur n'existe pas
}

// ajouter un utilisateur dans un fichier
void ajouterU(FILE *f,Utilisateur u)
{
	fprintf(f,"%s %s %i\n",u.login,u.mdp,u.role);
	rewind(f);
}


// fonction pour ajouter l'utilisateur au fichier pour se connecter 
void ajouterNouveauxUtilisateur(FILE *f)
{
	Utilisateur u = lireUtilisateur();
	// tester si l'utlisateur existe deja dans le fichier 
	if(testSiExist(f,u))
	{
		printf("L'utilisateur existe déjà !!\n");
		ajouterNouveauxUtilisateur(f); // repeter du le debut
	}

	// ajouter aux fichier
	ajouterU(f,u);
	rewind(f);
}

// chercher l'utilisateur dans le fichier
//
int testLogin(char *usr,char *mdp,FILE *f)
{
	Utilisateur u;
	while(fscanf(f,"%s %s %d",u.login,u.mdp,&u.role) == 3)
	{
		if(strcmp(usr,u.login) == 0 && strcmp(mdp,u.mdp) == 0)
			return 1;
	}
	rewind(f); // pionteur retourner aux debut
	return 0; // login incorrect

}

int login(FILE *f,char *login,char *mdp) // retourner la valeur de test est le nom d'utilisateur
{
	if(testLogin(login,mdp,f) == 1)
	{
		return 1; // login success
	}
       	else	
		return 0; // login incorrect utilisateur n'existe pas ou les donné incorrect
}

int roleUtilisateur(char *login,FILE *f) // retourner le role dans les parametre
{
	Utilisateur tmp;      
	fseek(f,0,SEEK_SET);
	while(fscanf(f,"%s %s %d",tmp.login,tmp.mdp,&tmp.role) == 3)
	{
		if(strcmp(login,tmp.login) == 0)
		{
			rewind(f);
			return tmp.role;
		}
	}
}
//**************************************************
int nombreUtilisateur(FILE *f)
{
	int count = 0;
	Utilisateur tmp;
	fseek(f,0,SEEK_SET);
	while(fscanf(f,"%s %s %d",tmp.login,tmp.mdp,&tmp.role) == 3)
		count++;
	rewind(f);
	return count;
}

// pas utiliser
Utilisateur * tabUser(FILE *f,int *length)
{
	*length = nombreUtilisateur(f);
	Utilisateur *t;
	t = malloc(sizeof(Utilisateur));
	return t;
}

Utilisateur *remplireTab(FILE *f,int *l)
{
	int taille;
	Utilisateur *tab = tabUser(f,&taille);
	*l = taille;
	int i = 0;
	Utilisateur tmp;
	while(i < taille)
	{
		fscanf(f,"%s %s %d",tmp.login,tmp.mdp,&tmp.role);
		tab[i++] = tmp;
	} 
	rewind(f);
	return tab;
}


int get_Indice(char *login,FILE *f)
{
	int count = 0;
	Utilisateur t;
	while(fscanf(f,"%s %s %d",t.login,t.mdp,&t.role) == 3)
	{
		count++;
		if(strcmp(login,t.login) == 0)
		{
			break;
		}
	}
	rewind(f);
	return count;
}

