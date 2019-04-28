#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

struct Client
{

	int  *Id_client;
	char **Nom;
	char **Prenom;
	char **Profession;
	char **Num_tel;

};

struct Compte
{

	int *Id_compte;
	int *Id_client;
	float *solde;
	char **date_ouverture;

};

void affichierMenuGenerale();

//Fonctions de gestion des clients :
void gestionClients();
void ajouterClient(Client &client);
void modifierClient(Client &client, int ID);
void supprimerClient(Client &client, int ID, int cmpt);
bool chercherClient(Client &client, int ID, int cmpt);

//Fonctions de gestion des comptes :
void gestionComptes();
void creeCompte(Compte &compte, int ID);
void consulterSold(Compte compte, int ID);
void fermerCompte(Compte &compte, int ID, int cpt);

//Fonctions de gestion des operations :
void gestionOperations();
void retirerMontant(Compte &compte, int ID, float montant, int cpt);
void verserMontant(Compte &compte, int IDClient1, int IDClient2, float montant, int cpt);

Client client;
Compte compte;
int comptClients = 0, comptComptes = 0, i = 0;
ofstream flux("Clients.txt", ios::out);
ofstream flux2("Comptes.txt", ios::out);
int main()
{
	client.Id_client = new int[50];
	client.Nom = new char*[50];
	client.Prenom = new char*[50];
	client.Profession = new char*[50];
	client.Num_tel = new char*[50];
	compte.Id_client = new int[50];
	compte.Id_compte = new int[50];
	compte.date_ouverture = new char*[50];
	compte.solde = new float[50];
	affichierMenuGenerale();
	flux.close();
	flux2.close();
	system("pause");
	return 0;
}
void affichierMenuGenerale()
{
	int choix;
	cout << "-----------------=[ Application pour Gestion d'une banque ]=-----------------" << endl << endl;
	cout << "==> Cette application permet de gerer les clients d'une banque tout en enregistrant les informations des clients" <<endl << " dans le fichier Clients.txt, et Comptes.txt contient les informations sur les comptes." << endl << endl;
	cout << "1. Gestion des clients" << endl;
	cout << "2. Gestion des comptes" << endl;
	cout << "3. Gestion des operations" << endl;
	cout << "4. Quitter" << endl << endl;
	cout << "[ ? ] Votre choix : ";
	cin >> choix;
	switch (choix)
	{
	case 1:
		system("cls");
		gestionClients();
		break;
	case 2:
		system("cls");
		gestionComptes();
		break;
	case 3:
		system("cls");
		gestionOperations();
		break;
	case 4:
		system("exit");
		break;
	default:
		cout << endl << "[ ! ] Mauvais choix !" << endl;
	}
}

void gestionClients()
{

	int choix, ID;
	cout << "-----------------=[ Gestion des clients ]=-----------------" << endl << endl;
	cout << "1. Ajouter un client" << endl;
	cout << "2. Modifer un client" << endl;
	cout << "3. Supprimer un client" << endl;
	cout << "4. Chercher un client" << endl;
	cout << "5. Retour" << endl << endl;
	cout << "[ ? ] Votre choix : ";
	cin >> choix;
	switch (choix)
	{
	case 1:
		comptClients++;
		system("cls");
		ajouterClient(client);
		break;
	case 2:
		cout << "[ ? ] ID du client : ";
		cin >> ID;
		modifierClient(client, ID);
		break;
	case 3:
		cout << "[ ? ] ID du client : ";
		cin >> ID;
		supprimerClient(client, ID, comptClients);
		break;
	case 4:
		cout << "[ ? ] ID du client : ";
		cin >> ID;
		if (chercherClient(client, ID, comptClients)){
			cout << "[ + ] Le client exist dans la base de donne !" << endl;
			Sleep(2000);
			system("cls");
			gestionClients();
		}
		else{
			cout << "[ - ] Client non existant dans la base de donnee !" << endl;
			Sleep(2000);
			system("cls");
			gestionClients();
		}
		break;
	case 5:
		system("cls");
		affichierMenuGenerale();
		break;
	default:
		cout << endl << "[ ! ] Mauvais choix !" << endl;
		break;
	}
}
void gestionComptes()
{
	int choix, ID;
	cout << "-----------------=[ Gestion des comptes ]=-----------------" << endl << endl;
	cout << "1. Cree un compte (ID Client)" << endl;
	cout << "2. Consulter un compte (ID Client)" << endl;
	cout << "3. Fermer un compte (ID Client)" << endl;
	cout << "4. Retour" << endl << endl;
	cout << "[ ? ] Votre choix : ";
	cin >> choix;
	switch (choix)
	{
	case 1:
		cout << "[ ? ] ID du client : ";
		cin >> ID;
		comptComptes++;
		creeCompte(compte, ID);
		break;
	case 2:
		cout << "[ ? ] ID du client : ";
		cin >> ID;
		consulterSold(compte, ID);
		break;
	case 3:
		cout << "[ ? ] ID du client : ";
		cin >> ID;
		fermerCompte(compte, ID, comptComptes);
		break;
	case 4:
		system("cls");
		affichierMenuGenerale();
		break;
	default:
		cout << endl << "[ ! ] Mauvais choix !" << endl;
		break;
	}
}
void gestionOperations()
{
	int choix, ID, ID2;
	float montant;
	cout << "-----------------=[ Gestion des operations ]=-----------------" << endl << endl;
	cout << "1. Retirer montant" << endl;
	cout << "2. Verser motant" << endl;
	cout << "3. Retour" << endl << endl;
	cout << "[ ? ] Votre choix : ";
	cin >> choix;
	switch (choix)
	{
	case 1:
		cout << "[ ? ] Montant a retirer : ";
		cin >> montant;
		cout << "[ ? ] ID Client : ";
		cin >> ID;
		retirerMontant(compte, ID, montant, comptClients);
		break;
	case 2:
		cout << "[ ? ] Montant a retirer : ";
		cin >> montant;
		cout << "[ ? ] ID Client (qui verse la monnaie) : ";
		cin >> ID;
		cout << "[ ? ] ID Client (a qui vous voulez verser la monnaie) : ";
		cin >> ID2;
		verserMontant(compte, ID, ID2, montant, comptClients);
		break;
	case 3:
		system("cls");
		affichierMenuGenerale();
		break;
	default:
		cout << endl << "[ ! ] Mauvais choix !" << endl;
		break;
	}
}
void ajouterClient(Client &client){


	cout << "-----------------=[ Ajout d'un client ]=-----------------" << endl << endl;
	if (flux){
		client.Nom[i] = new char[50];
		client.Prenom[i] = new char[50];
		client.Profession[i] = new char[50];
		client.Num_tel[i] = new char[50];
		client.Id_client[i] = i + 1;
		flux << "Id : " << client.Id_client[i];
		flux << endl;
		cout << "[ ? ] Nom : ";
		cin >> client.Nom[i];
		flux << "Nom : " << client.Nom[i];
		flux << endl;
		cout << "[ ? ] Prenom : ";
		cin >> client.Prenom[i];
		flux << "Prenom : " << client.Prenom[i];
		flux << endl;
		cout << "[ ? ] Profession : ";
		cin >> client.Profession[i];
		flux << "Profession : " << client.Profession[i];
		flux << endl;
		cout << "[ ? ] Numero du telephone : ";
		cin >> client.Num_tel[i];
		flux << "Numero du telephone : " << client.Num_tel[i];
		flux << endl;
		i++;
		cout << "[ + ] Le client a ete ajoute avec success !" << endl;
		Sleep(2000);
		system("cls");
		gestionClients();

	}
	else
	{
		cerr << "[ ! ] Impossible d'ouvrir le fichier !" << endl;
	}
}
void modifierClient(Client &client, int ID){
	int i = 0;
	ofstream flux("Clients.txt", ios::out);
	cout << "-----------------=[ Modification d'un client ]=-----------------" << endl << endl;
	cout << "Modification du client avec ID " << ID << " : " << endl;
	if (flux){
		client.Nom[i] = new char[50];
		client.Prenom[i] = new char[50];
		client.Profession[i] = new char[50];
		client.Num_tel[i] = new char[50];
		client.Id_client[i] = i + 1;
		flux << "Id : " << client.Id_client[i];
		flux << endl;
		cout << "[ ? ] Nom : ";
		cin >> client.Nom[i];
		flux << "Nom : " << client.Nom[i];
		flux << endl;
		cout << "[ ? ] Prenom : ";
		cin >> client.Prenom[i];
		flux << "Prenom : " << client.Prenom[i];
		flux << endl;
		cout << "[ ? ] Profession : ";
		cin >> client.Profession[i];
		flux << "Profession : " << client.Profession[i];
		flux << endl;
		cout << "[ ? ] Numero du telephone : ";
		cin >> client.Num_tel[i];
		flux << "Numero du telephone : " << client.Num_tel[i];
		flux << endl;
		i++;
		cout << "[ + ] Le client a ete modifie avec success !" << endl;
		Sleep(2000);
		system("cls");
		gestionClients();
		flux.close();
	}
	else
	{
		cerr << "[ ! ] Impossible d'ouvrir le fichier !" << endl;
	}
}
void supprimerClient(Client &client, int ID, int cpt){
	int i = 0, count = 0;
	ofstream flux("Clients.txt", ios::out);
	cout << "-----------------=[ Supression d'un client ]=-----------------" << endl << endl;
	cout << "Supression du client avec ID " << ID << " : " << endl;
	for (i = 0; i<cpt; i++)
	{
		if (client.Id_client[i] == ID)
		{
			for (int j = i; j<(cpt - 1); j++)
			{
				client.Nom[j] = client.Nom[j + 1];
				client.Prenom[j] = client.Prenom[j + 1];
				client.Profession[j] = client.Profession[j + 1];
				client.Num_tel[j] = client.Num_tel[j + 1];
			}
			count++;
			break;
		}
	}
	if (count == 0)
	{
		cout << "[ - ] Erreur dans l'ID !";
	}
	else{
		if (flux){
			for (i = 0; i < (cpt - 1); i++)
			{
				flux << "Id : " << client.Id_client[i];
				flux << endl;
				flux << "Nom : " << client.Nom[i];
				flux << endl;
				flux << "Prenom : " << client.Prenom[i];
				flux << endl;
				flux << "Profession : " << client.Profession[i];
				flux << endl;
				flux << "Numero du telephone : " << client.Num_tel[i];
				flux << endl;
			}
			cout << "[ + ] Le client a ete supprime avec success !" << endl;
			Sleep(2000);
			system("cls");
			gestionClients();
			flux.close();
		}
		else
		{
			cerr << "[ ! ] Impossible d'ouvrir le fichier !" << endl;
		}
	}


}
bool chercherClient(Client &client, int ID, int cmpt){
	for (int i = 0; i < cmpt; i++){
		if (client.Id_client[i] == ID){
			return true;
			break;
		}
		else
		{
			return false;
		}
	}
}
void creeCompte(Compte &compte, int ID){
	cout << "-----------------=[ Creation du compte ]=-----------------" << endl << endl;
	cout << "Creation du compte pour le client avec ID " << ID << " : " << endl;
	time_t temps;
	struct tm date;
	char  format[32];
	time(&temps);
	date = *localtime(&temps);
	strftime(format, 32, "%Y-%m-%d", &date);
	compte.date_ouverture[ID - 1] = format;
	compte.Id_client[ID - 1] = ID;
	compte.Id_compte[ID - 1] = ID;
	compte.solde[ID - 1] = 0.00;
	flux2 << "Id Client : " << compte.Id_client[ID - 1];
	flux2 << endl;
	flux2 << "Id Compte : " << compte.Id_compte[ID - 1];
	flux2 << endl;
	flux2 << "Sold : " << compte.solde[ID - 1];
	flux2 << endl;
	flux2 << "Date d'ouverture : " << compte.date_ouverture[ID - 1];
	flux2 << endl;
	cout << "[ + ] Le compte a ete supprime avec success !" << endl;
	Sleep(2000);
	system("cls");
	gestionComptes();
}
void consulterSold(Compte compte, int ID){
	cout << "-----------------=[ Consultation du sold ]=-----------------" << endl << endl;
	cout << "[ + ] Votre sold est : " << compte.solde[ID - 1] << " MAD" << endl;
	Sleep(2000);
	system("cls");
	gestionComptes();
}
void fermerCompte(Compte &compte, int ID, int cpt){
	ofstream flux2("Comptes.txt", ios::out);
	int count = 0;
	for (i = 0; i<cpt; i++)
	{
		if (compte.Id_client[i] == ID)
		{
			for (int j = i; j<(cpt - 1); j++)
			{
				compte.Id_client[j] = compte.Id_client[j + 1];
				compte.date_ouverture[j] = compte.date_ouverture[j + 1];
				compte.Id_compte[j] = compte.Id_compte[j + 1];
				compte.solde[j] = compte.solde[j + 1];
			}
			cpt--;
			count++;
			break;
		}
	}
	if (count == 0)
	{
		cout << "[ - ] Erreur dans l'ID !";
	}
	else{
		if (flux2){
			for (i = 0; i < cpt; i++)
			{
				flux2 << "Id Client : " << compte.Id_client[i];
				flux2 << endl;
				flux2 << "Id Compte : " << compte.Id_compte[i];
				flux2 << endl;
				flux2 << "Sold : " << compte.solde[i];
				flux2 << endl;
				flux2 << "Date d'ouverture : " << compte.date_ouverture[i];
				flux2 << endl;

			}
			cout << "[ + ] Le compte a ete ferme avec success !" << endl;
			flux2.close();
			Sleep(2000);
			system("cls");
			gestionComptes();
		}
		else{
			cerr << "[ ! ] Impossible d'ouvrir le fichier !" << endl;
		}
	}
}
void retirerMontant(Compte &compte, int ID, float montant, int cpt){
	ofstream flux("Comptes.txt", ios::out);
	cout << "-----------------=[ Retirer un montant ]=-----------------" << endl << endl;
	if (montant > 0){
		compte.solde[ID - 1] = compte.solde[ID - 1] - montant;
	}
	if (flux2){
		for (i = 0; i < cpt; i++)
		{
			flux2 << "Id Client : " << compte.Id_client[i];
			flux2 << endl;
			flux2 << "Id Compte : " << compte.Id_compte[i];
			flux2 << endl;
			flux2 << "Sold : " << compte.solde[i];
			flux2 << endl;
			flux2 << "Date d'ouverture : " << compte.date_ouverture[i];
			flux2 << endl;
			flux2.close();
		}
		cout << "[ + ] Le montant " << montant << " MAD a ete retirer !" << endl;
		flux2.close();
		Sleep(2000);
		system("cls");
		gestionOperations();
	}
}
void verserMontant(Compte &compte, int IDClient1, int IDClient2, float montant, int cpt){
	ofstream flux("Comptes.txt", ios::out);
	cout << "-----------------=[ Verser un montant ]=-----------------" << endl << endl;
	if (montant > 0){
		compte.solde[IDClient2 - 1] = compte.solde[IDClient2 - 1] + montant;
		compte.solde[IDClient1 - 1] = compte.solde[IDClient1 - 1] - montant;
	}
	if (flux2){
		for (i = 0; i < cpt; i++)
		{
			flux2 << "Id Client : " << compte.Id_client[i];
			flux2 << endl;
			flux2 << "Id Compte : " << compte.Id_compte[i];
			flux2 << endl;
			flux2 << "Sold : " << compte.solde[i];
			flux2 << endl;
			flux2 << "Date d'ouverture : " << compte.date_ouverture[i];
			flux2 << endl;
			
		}
		cout << "[ + ] Le montant " << montant << " MAD a ete verse avec success au Client ID : " << IDClient2 << " !" << endl;
		flux2.close();
		Sleep(2000);
		system("cls");
		gestionOperations();
	}

}
