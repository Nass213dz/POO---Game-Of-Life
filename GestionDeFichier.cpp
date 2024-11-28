#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include "GestionDeFichier.h"

using namespace std;
using namespace filesystem;

vector<vector<int>> GestionDeFichier::lireFichier(const string& nomFichier) {
    string premiereLigne;
    string ligne;
    string largeurS;
    string longueurS;
    int largeurI;
    int longueurI;
    int cellule;

    ifstream lireMessage(nomFichier);
    if (!lireMessage.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier source.");
    }

    getline(lireMessage, premiereLigne);
    int j(0);

    //On récupère les paramètres du tableau
    while (premiereLigne[j] != ' '){
        largeurS += premiereLigne[j];
        j++;
    }
    j++;
    while (premiereLigne[j] != ' '){
        longueurS += premiereLigne[j];
        j++;
    }
    for (j; j < premiereLigne.size(); j++){
        if (premiereLigne[j] != ' '){
            throw runtime_error("Declaration du tableau invalide.");
        }
    }
    largeurI = stoi(largeurS); // Convertit la chaîne en entier
    longueurI = stoi(longueurS);

    vector<vector<int>> tableau;
    int x(0);

    //Remplissage du tableau
    while(getline(lireMessage, ligne)){
        tableau.push_back(vector<int>()); // Ajoute une nouvelle ligne vide
        for (int i(0); i<ligne.size(); i += 2){
            int cellule = ligne[i] - '0';
            tableau[x].push_back(cellule);
        }
        x++;
    }
    lireMessage.ignore();

    if (tableau.size() != largeurI){
        throw runtime_error("Nombre de lignes de la matrice non conforme aux parametres donnes");
    }

    for (int i = 0; i < tableau.size(); i++){
        if (tableau[i].size() != longueurI){
            throw runtime_error("Nombre de colonnes de la matrice non conforme aux parametres donnes");
        }   
    }
       
    return tableau;
}


void GestionDeFichier::ecrireFichier(const string& nomFichier, const string& contenu) {
    string iteration_folder;
    if (!filesystem::exist(iteration_folder)){
        filesystem::create_directory(iteration_folder);
    }
    ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier de destination.");
    }
    fichier << contenu;
    fichier.close();
}
