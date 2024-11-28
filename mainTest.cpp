#include <vector>
#include <iostream>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;

int main() {
    vector<vector<int>> grille;
    string nomFichier;

    cout << "Entrez le nom du fichier source : ";
    cin >> nomFichier;

    try {
        grille = GestionDeFichier::lireFichier(nomFichier);
        int largeur = grille.size(); // Taille de la grille déterminée par le fichier
        int longueur = grille[0].size();

        Grille grid(largeur, longueur); // Construction dynamique selon les dimensions lues
        grid.initialisationGrille(grille); // Initialisation avec les données du fichier
        grid.affichageGrille(); // Affichage de la grille
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
    }

    return 0;
}
