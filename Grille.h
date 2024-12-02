#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Cellule.h"

using namespace std;

class Grille {
private:
    int m_longueur;   // Longueur de la grille
    int m_largeur;    // Largeur de la grille
    vector<vector<Cellule*>> cellules; // Matrice de cellules (grille)
    
public:
    Grille(int longueur, int largeur);
    ~Grille();

    int getLongueur() const;
    int getLargeur() const;
    bool getVieCellule(int i, int j) const;
    int getNBRVoisinsVivants(int i, int j);
    void affichageGrille();
    void initialisationGrille(vector<vector<int>>& etats_cellules);
    vector<vector<Cellule*>> iteration();
    void clearGrille();

    void graphique(sf::RenderWindow &window);
};

#endif
