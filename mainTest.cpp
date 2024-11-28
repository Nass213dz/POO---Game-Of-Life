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

    grille = GestionDeFichier::lireFichier(nomFichier);

    int largeur = grille.size(); // Taille de la grille déterminée par le fichier
    int longueur = grille[0].size(); // Taille de la première ligne pour la longueur

    Grille grid(longueur, largeur); // Construction dynamique selon les dimensions lues
    grid.initialisationGrille(grille); // Initialisation avec les données du fichier

    // Affichage de la longueur et largeur
    cout << "Longueur de la grille : " << grid.getLongueur() << endl;
    cout << "Largeur de la grille : " << grid.getLargeur() << endl;

    grid.affichageGrille(); // Affichage de la grille

    return 0;
}
