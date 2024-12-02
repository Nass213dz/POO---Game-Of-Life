#include <ctime>
#include <cstdlib>

#include "Grille.h"
#include "GestionDeFichier.h"

using namespace std;

const int cellSize = 10;

Grille::Grille(int largeur, int longueur) : m_largeur(largeur), m_longueur(longueur), cellules(longueur, vector<Cellule*>(largeur, nullptr)) {} // Constructeur paramétré

Grille::~Grille() {
    // Destructeur qui supprime chaque cellule du vecteur
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            delete cellules[i][j];
        }
    }
}

int Grille::getLargeur() const {
    // Getter de la largeur
    return m_largeur;
}

int Grille::getLongueur() const {
    // Getter de la longueur
    return m_longueur;
}


bool Grille::getVieCellule(int i, int j) const {
    // Getter de l'état d'une cellule qui prend la position en paramètre
    return cellules[i][j]->getEtat() ? true : false; // Si getEtat() retourne true, la méthode getVieCellule retourne true, sinon false
}

int Grille::getNBRVoisinsVivants(int i, int j) {
    // Permet d'avoir le nombre de voisins vivants autour de la cellule
    int compteur_voisin_vivant = 0; // Initialisation du compteur

    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            // Permet de parcourir la grille (le vecteur cellules)
            if (k == 0 && l == 0) continue; // Si le voisin parcouru est la cellule initiale, on continue sans rien faire

            int voisin_i = i + k; // Coordonnée en i d'un voisin
            int voisin_j = j + l; // Coordonnée en j d'un voisin

            if (voisin_i >= 0 && voisin_i < m_longueur && voisin_j >= 0 && voisin_j < m_largeur) { // Vérifie pour chaque voisin s'il est bien dans la grille
                if (getVieCellule(voisin_i, voisin_j)) { // Si la cellule est vivante
                    ++compteur_voisin_vivant; // Incrémenter le compteur
                }
            }
        }
    }

    return compteur_voisin_vivant;
}

void Grille::affichageGrille() {
    cout << "Etat de la grille :" << endl;
    for (int i = 0; i < m_longueur; i++) { // Parcours des lignes (longueur)
        for (int j = 0; j < m_largeur; j++) { // Parcours des colonnes (largeur)
            cout << (cellules[i][j]->getEtat() ? "1" : "0") << " "; // Affiche "1" pour vivant et "0" pour mort
        }
        cout << endl; // Saut de ligne après chaque ligne
    }
}

void Grille::initialisationGrille(vector<vector<int>>& etats_cellules) {
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            if (etats_cellules[i][j] == 1) { // Si la cellule initialisée dans le fichier d'entrée est de 1
                cellules[i][j] = new CelluleVivante(); // Crée un nouvel objet de cellule vivante
            } else if (etats_cellules[i][j] == 0) { // Pareil mais pour une cellule morte
                cellules[i][j] = new CelluleMorte();
            }
        }
    }
}


vector<vector<Cellule*>> Grille::iteration() {
    // Création d'un vecteur pour stocker l'itération suivante
    vector<vector<Cellule*>> nouvelles_cellules(m_longueur, vector<Cellule*>(m_largeur, nullptr));
    bool changement_detecte = false; // Indicateur de changement

    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            int voisins_vivants = getNBRVoisinsVivants(i, j);

            if (getVieCellule(i, j)) { // La cellule est vivante
                if (voisins_vivants == 2 || voisins_vivants == 3) {
                    nouvelles_cellules[i][j] = new CelluleVivante();
                } else {
                    nouvelles_cellules[i][j] = new CelluleMorte();
                }
            } else { // La cellule est morte
                if (voisins_vivants == 3) {
                    nouvelles_cellules[i][j] = new CelluleVivante();
                } else {
                    nouvelles_cellules[i][j] = new CelluleMorte();
                }
            }

            // Vérifier s'il y a une différence avec l'état actuel
            if ((getVieCellule(i, j) && dynamic_cast<CelluleMorte*>(nouvelles_cellules[i][j])) ||
                (!getVieCellule(i, j) && dynamic_cast<CelluleVivante*>(nouvelles_cellules[i][j]))) {
                changement_detecte = true;
            }
        }
    }

    // Si aucun changement n'a été détecté, libérer la mémoire allouée pour les nouvelles cellules
    if (!changement_detecte) {
        for (int i = 0; i < m_longueur; i++) {
            for (int j = 0; j < m_largeur; j++) {
                delete nouvelles_cellules[i][j];
            }
        }
        cout << "Aucun changement detecte. Fin de l'evolution." << endl;
        return cellules; // Retourne les cellules actuelles si pas de changement
    }

    // Mettre à jour la grille actuelle et libérer la mémoire des anciennes cellules
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            delete cellules[i][j];
            cellules[i][j] = nouvelles_cellules[i][j];
        }
    }

    return cellules; // Retourne les nouvelles cellules
}




void Grille::clearGrille() {
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            delete cellules[i][j];
        }
    }
}

void Grille::graphique(){

}
