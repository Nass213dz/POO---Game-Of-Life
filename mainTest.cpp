#include <vector>
#include <iostream>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;

int main(){
    string nomFichier;
    cout << "Entrez le nom du fichier source : ";
    cin >> nomFichier;
    GestionDeFichier::lireFichier(nomFichier);
    Grille grid(5);
    grid.affichageGrille();
}