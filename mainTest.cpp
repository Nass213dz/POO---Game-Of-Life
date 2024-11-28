#include <vector>
#include <iostream>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;

int main(){
    vector<vector<int>> grille;
    string nomFichier;
    cout << "Entrez le nom du fichier source : ";
    cin >> nomFichier;
    grille = GestionDeFichier::lireFichier(nomFichier);
    Grille grid(5);
    grid.initialisationGrille(grille);
    grid.affichageGrille();
}