#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include "Cellule.h"

using namespace std;

class Grille {
private:
    int m_longueur;   // Longueur de la grille
    int m_largeur;    // Largeur de la grille
    vector<vector<Cellule*>> cellules; // Matrice de cellules (grille)
    
public:
    // Constructeur paramétré avec longueur et largeur
    Grille(int longueur, int largeur);

    // Destructeur
    ~Grille();

    // Getters pour la longueur et la largeur
    int getLongueur() const;
    int getLargeur() const;

    // Getter de l'état d'une cellule
    bool getVieCellule(int i, int j) const;

    // Méthode pour obtenir le nombre de voisins vivants
    int getNBRVoisinsVivants(int i, int j);

    // Méthode pour afficher l'état de la grille
    void affichageGrille();

    // Méthode pour initialiser la grille avec les états des cellules
    void initialisationGrille(vector<vector<int>>& etats_cellules);

    vector<vector<Cellule*>> iteration();

    void clearGrille();

    void graphique();
};

#endif
