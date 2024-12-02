#include <vector>
#include <iostream>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;

int main() {
    vector<vector<Cellule*>> grille_cell;
    vector<vector<int>> grille;
    string nomFichier;
    int nbIterations;
    string iteration = "Iteration_";
    string dossier = "Fichier_Iteration";

    cout << "Entrez le nom du fichier source : ";
    cin >> nomFichier;

    grille = GestionDeFichier::lireFichier(nomFichier);

    int largeur = grille.size(); 
    int longueur = grille[0].size();

    Grille grid(longueur, largeur);

    grid.clearGrille();
    GestionDeFichier::supprimerFichiersTxt();

    cout << "Entrez le nombres d'iterations que vous souhaitez:";
    cin >> nbIterations;

    for (int i = 0; i < nbIterations; i++) {
    grid.initialisationGrille(grille);
    grille_cell = grid.iteration();
    grille = GestionDeFichier::convertirGrille(grille_cell);
    
    static std::vector<std::vector<int>> grillePrecedente;
    if (grillePrecedente.empty() || !GestionDeFichier::comparerGrilles(grillePrecedente, grille)) {
        GestionDeFichier::ecrireFichier(iteration + to_string(i + 1), grille, dossier); 
    } else {
        std::cout << "Aucune difference entre l'iteration " << i + 1 << " et l'iteration precedente. Arret de l'ecriture des fichiers.\n";
        break;
    }
}

    return 0;
}
