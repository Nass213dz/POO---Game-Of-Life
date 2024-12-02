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

    for (int i = 0; i < nbIterations; i++) {
    grid.initialisationGrille(grille); // Initialisation avec les données du fichier
    grille_cell = grid.iteration(); // Effectuer l'itération
    grille = GestionDeFichier::convertirGrille(grille_cell); // Convertir la grille en format adéquat
    
    // Comparer avec la grille précédente et écrire le fichier si nécessaire
    static std::vector<std::vector<int>> grillePrecedente;
    if (grillePrecedente.empty() || !GestionDeFichier::comparerGrilles(grillePrecedente, grille)) {
        // Si c'est la première itération ou si les grilles sont différentes
        GestionDeFichier::ecrireFichier(iteration + to_string(i + 1), grille); // Écrire le fichier
        grillePrecedente = grille; // Mettre à jour la grille précédente
    } else {
        // Si les grilles sont identiques, arrêter la boucle
        std::cout << "Aucune difference entre l'iteration " << i + 1 << " et l'iteration precedente. Arret de l'ecriture des fichiers.\n";
        break; // Arrêter la boucle si aucune différence
    }
}

    return 0;
}
