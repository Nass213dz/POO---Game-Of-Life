#include <vector>
#include "Cellule.h"

using namespace std;

class Grille {
    private:
    int m_longueur;
    int m_largeur;
    vector<vector<Cellule*>> cellules;
    public:
    Grille(int taille, int tailleL);
    ~Grille();
    int getSize() const;
    bool getVieCellule(int i, int j) const;
    int getNBRVoisinsVivants(int i, int j);
    void affichageGrille();
    void initialisationGrille(vector<vector<int>>& etats_cellules);
};