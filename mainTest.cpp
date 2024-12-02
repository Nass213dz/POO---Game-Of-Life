#include <vector>
#include <iostream>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;

int main() {
    vector<vector<int>> grille;
    string nomFichier;
    int nbIterations;
    string Iteration;

    cout << "Entrez le nom du fichier source : ";
    cin >> nomFichier;

    grille = GestionDeFichier::lireFichier(nomFichier);

    int largeur = grille.size(); // Taille de la grille déterminée par le fichier
    int longueur = grille[0].size(); // Taille de la première ligne pour la longueur

    Grille grid(longueur, largeur); // Construction dynamique selon les dimensions lues
    
    // Affichage de la longueur et largeur
    //cout << "Longueur : " << grid.getLongueur() << endl;
    //cout << "Largeur : " << grid.getLargeur() << endl;

    //grid.affichageGrille(); // Affichage de la grille

    grid.clearGrille(); // Supprimer toutes les cellules allouées dynamiquement

    cout << "Entrez le nombres d'iterations que vous souhaitez:";
    cin >> nbIterations;

    for (int i=0; i < nbIterations; i++){
        grid.initialisationGrille(grille); // Initialisation avec les données du fichier
        GestionDeFichier::ecrireFichier(Iteration + to_string(i + 1), grille);
    }

    return 0;
}
