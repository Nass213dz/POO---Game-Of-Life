#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Cellule.h"

using namespace std;

class Grille {
private:
    int m_longueur;   //longueur de la grille
    int m_largeur;    //largeur de la grille
    vector<vector<Cellule*>> cellules; //vecteur de cellules (grille)
    
public:
    Grille(int longueur, int largeur);
    ~Grille();

    int getLongueur() const;
    int getLargeur() const;
    bool getVieCellule(int i, int j) const;
    void setVieCellule(int x, int y, bool vivante);
    int getNBRVoisinsVivants(int i, int j);
    void affichageGrille();
    void initialisationGrille(vector<vector<int>>& etats_cellules);
    vector<vector<Cellule*>> iteration();
    void clearGrille();

    void graphique(sf::RenderWindow &window);

    void ajouterMotif(const vector<vector<int>>& motif, int x, int y);
};

#endif
