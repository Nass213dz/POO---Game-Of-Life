#include "Grille.h"

using namespace std;

Grille::Grille(int taille) : m_taille(taille), m_tailleL(taille_l), cellules(taille, vector<Cellule*>(taille, nullptr)){} //Constructeur parametré

Grille::~Grille(){
    //Destructeur qui supprime chaque cellule du vecteur
    for(int i=0;i<m_taille; i++){
        for(int j=0; j<m_taille; j++){
            delete cellules[i][j];
        }
    }
}

int Grille::getSize() const {
    //Getter de la taille
    return m_taille;
}

bool Grille::getVieCellule(int i, int j) const {
    //Getter de l'état d'une cellule qui prend la position en paramètre
    return cellules[i][j]->getEtat() ? true : false; //si getEtat() retourne true, la méthode getVieCellule retourne true et false sinon
}

int Grille::getNBRVoisinsVivants(int i, int j) {
    //Permet d'avoir le nombre de voisins vivants autour de la cellule (int)
    int compteur_voisin_vivant = 0;                  // initialisation d'un compteur

    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            //permet de parcourir la grille (le vecteur cellules)
            if (k == 0 && l == 0) continue;          // Si le voisin parcouru est la cellule initiale, on continue sans rien faire

            int voisin_i = i + k;                    // coordonnée en i d'un voisin
            int voisin_j = j + l;                    // coordonnée en j d'un voisin

            if (voisin_i >= 0 && voisin_i < m_taille && voisin_j >= 0 && voisin_j < m_taille) { //Vérifie pour chaque voisin si il est bien dans la grille
                if (getVieCellule(voisin_i, voisin_j)) { //si la cellule est vivante
                    ++compteur_voisin_vivant; // incrémenter le compteur
                }
            }
        }
    }

    return compteur_voisin_vivant;
}


void Grille::affichageGrille(){
    //permet d'afficher la grille dans la console
    for(int i=0;i<m_taille; i++){
        for(int j=0; j<m_taille; j++){
            cout << (cellules[i][j]->getEtat() ? 1 : 0) << " " << endl; // affiche l'état (0 ou 1) de chaque cellules
        }
    }
}

void Grille::initialisationGrille(vector<vector<int>>& etats_cellules){
    for(int i=0;i<m_taille;i++){
        for(int j=0; j<m_taille; j++){
            if (etats_cellules[i][j]==1){ //si la cellule initialisée dans le fichier d'entrée est de 1
                cellules[i][j] = new CelluleVivante(); //créé un nouvel objet de cellule vivante
            }
            else if (etats_cellules[i][j]==0){ //pareil mais pour une cellule morte
                cellules[i][j] = new CelluleMorte();
            }
        }
    }
}