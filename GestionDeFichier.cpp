#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include "GestionDeFichier.h"

using namespace std;
namespace fs = filesystem;

vector<vector<int>> GestionDeFichier::lireFichier(const string& nomFichier) {
    string premiereLigne;
    string ligne;
    string largeurS;
    string longueurS;
    int largeurI;
    int longueurI;
    int cellule;

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
            throw runtime_error("Declaration du tableau invalide (pensez à verifier qu'il n'y a pas de caractères en trop)"); // message d'erreur
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


void GestionDeFichier::ecrireFichier(const string& nomFichier, const string& grille) {
    string iteration_folder;
    if (!fs::exists(iteration_folder)){
        fs::create_directory(iteration_folder);
    }
     
    string cheminFichier = iteration_folder + "/" + nomFichier;
    ofstream fichier(cheminFichier);
    fichier << grille;
    fichier.close();
}
