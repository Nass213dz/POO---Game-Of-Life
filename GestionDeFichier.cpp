#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include "GestionDeFichier.h"
#include "Cellule.h"

using namespace std;
namespace fs = filesystem;

vector<vector<int>> GestionDeFichier::lireFichier(const string& nomFichier) {
    //méthode permettant de lire les informations du fichier source de la grille
    string premiereLigne; //ligne contenant les paramètres de la grille
    string ligne; //ligne contenant les états des cellules
    string largeurS; //largeur encore sous forme de str (récupéré à l'aide de la lecture de la première ligne)
    string longueurS; //longueur encore sous forme de str (récupéré à l'aide de la lecture de la première ligne)
    int largeurI; //largeur en int
    int longueurI; //longueur en int
    int cellule; //chacunes des cellules dans la grille

    ifstream lireMessage(nomFichier); // Lecture du fichier 
    if (!lireMessage.is_open()) {
        //si le fichier est inaccessible ou inexistant
        throw runtime_error("Impossible d'ouvrir le fichier source."); //message d'erreur personnalisé
    }

    getline(lireMessage, premiereLigne); // lecture d'une ligne
    int j=0;

    //On récupère les paramètres du tableau
    while (premiereLigne[j] != ' '){
        //lecture de la première ligne
        largeurS += premiereLigne[j]; //initialisation de la largeur en fonction du paramètre lu
        j++;
    }
    j++; //incrémentation de j afin d'éviter l'espace
    while (premiereLigne[j] != ' '){
        // lecture du deuxième élément de la première ligne
        longueurS += premiereLigne[j]; // initialisation de la longueur en fonction du paramètre lu
        j++;
    }
    for (j; j < premiereLigne.size(); j++){
        //continue de parcourir la première ligne
        if (premiereLigne[j] != ' '){
            //si il y a un autre élément
            throw runtime_error("Declaration du tableau invalide (pensez a verifier qu'il n'y a pas de caracteres en trop)"); // message d'erreur
        }
    }
    largeurI = stoi(largeurS); // conversion de la chaîne de caractère en entier
    longueurI = stoi(longueurS);

    vector<vector<int>> tableau; //vecteur d'entiers appelé tableau
    int x=0;

    //remplissage du tableau
    while(getline(lireMessage, ligne)){
        tableau.push_back(vector<int>()); // Ajoute une nouvelle ligne vide
        for (int i(0); i<ligne.size(); i += 2){
            //parcourt la ligne de 2 en 2 pour éviter les espaces
            int cellule = ligne[i] - '0'; //transforme le caractère en int à l'aide de la table ASCII
            tableau[x].push_back(cellule); //on ajoute la valeur de cellule dans le vecteur tableau (à l'indice x) 
        }
        x++;
    }
    lireMessage.ignore(); //ignore les caractères pouvant fausser l'analyse

    if (tableau.size() != largeurI){
        //si la taille du tableau ne correspond pas à la largeur entrée en paramètre
        throw runtime_error("Nombre de lignes de la matrice non conforme aux parametres donnes"); //message d'erreur
    }

    for (int i = 0; i < tableau.size(); i++){
        //parcourt de chaque ligne
        if (tableau[i].size() != longueurI){
            //si la taille du tableau ne correspond pas à la longueur entrée en paramètre
            throw runtime_error("Nombre de colonnes de la matrice non conforme aux parametres donnes"); //message d'erreur
        }   
    }
       
    return tableau;
}

vector<vector<int>> GestionDeFichier::convertirGrille(const vector<vector<Cellule*>>& grille) {
    //convertit un vecteur de Cellule en vecteur d'entier
    vector<vector<int>> grilleInt;

    for (const auto& ligne : grille) {
        //parcourt la grille ligne par ligne avec le type auto
        vector<int> ligneInt;
        for (const auto& cellule : ligne) {
            //parcourt chaque ligne cellule par cellule
            if (cellule == nullptr) {
                //si la cellule est un pointeur nul
                ligneInt.push_back(0); //changement vers un entier nul
            } else {
                ligneInt.push_back(cellule->getEtat()); //sinon changement vers l'état de la cellule 
            }
        }
        grilleInt.push_back(ligneInt);
    }

    return grilleInt;
}


void GestionDeFichier::ecrireFichier(const string& nomFichier, const vector<vector<int>>& grille, const string& dossier) {
    vector<vector<int>> grillePrecedente;
    string iterationFolder = "fichier_iteration";
    if (!fs::exists(iterationFolder)){
        fs::create_directory(iterationFolder);
    }
     
    string cheminFichier = iterationFolder + "/" + nomFichier + ".txt";
    ofstream fichier(cheminFichier);
    for (int i = 0; i < grille.size(); i++){
        for (int j = 0; j < grille[i].size(); j++){
            fichier << grille[i][j] << " ";
        }
        fichier << "\n";
    }
    fichier.close();

    grillePrecedente = grille;
}

bool GestionDeFichier::comparerGrilles(const vector<vector<int>>& grille1, const vector<vector<int>>& grille2) {
    if (grille1.size() != grille2.size()) {
        return false;
    }

    for (int i = 0; i < grille1.size(); i++) {
        if (grille1[i].size() != grille2[i].size()) {
            return false;
        }

        for (int j = 0; j < grille1[i].size(); j++) {
            if (grille1[i][j] != grille2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void GestionDeFichier::supprimerFichiersTxt(const std::string& dossier) {
    if (!fs::exists(dossier)) {
        cerr << "Le dossier " << dossier << " n'existe pas." << endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(dossier)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            try {
                fs::remove(entry.path());
                cout << "Fichier supprime : " << entry.path().string() << endl;
            } catch (const exception& e) {
                cerr << "Erreur lors de la suppression de " << entry.path().string()
                          << ": " << e.what() << endl;
            }
        }
    }
}
