#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Grille.h"
#include "GestionDeFichier.h"

using namespace std;
using namespace sf;

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

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

void Grille::setVieCellule(int x, int y, bool vivante) {
    if (x >= 0 && x < m_longueur && y >= 0 && y < m_largeur) {
        if (cellules[x][y]) {
            cellules[x][y]->changerEtat(vivante); // Appelle changerEtat de la cellule
        }
    }
}

int Grille::getNBRVoisinsVivants(int i, int j) {
    // Permet d'avoir le nombre de voisins vivants autour de la cellule
    int compteur_voisin_vivant = 0; // Initialisation du compteur

    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            // Permet de parcourir la grille (le vecteur cellules)
            if (k == 0 && l == 0) continue; // Si le voisin parcouru est la cellule initiale, on continue sans rien faire

            int voisin_i = (i + k + m_longueur) % m_longueur; // Coordonnée en i d'un voisin
            int voisin_j = (j + l + m_largeur) % m_largeur; // Coordonnée en j d'un voisin

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


vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

void Grille::graphique(sf::RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (int x = 0; x < m_longueur; ++x) {
        for (int y = 0; y < m_largeur; ++y) {
            if (cellules[x][y] && cellules[x][y]->getEtat()) { // Vérifie si la cellule existe et est vivante
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}


void Grille::ajouterMotif(const vector<vector<int>>& motif, int x, int y) {
    for (int i = 0; i < motif.size(); i++) {
        for (int j = 0; j < motif[i].size(); j++) {
            // Check if the position is within bounds of the grid
            if (x + j >= 0 && x + j < m_largeur && y + i >= 0 && y + i < m_longueur) {
                // Update the cell state based on the motif value
                if (motif[i][j] == 1) {
                    cellules[y + i][x + j] = new CelluleVivante();
                } else {
                    cellules[y + i][x + j] = new CelluleMorte();
                }
            }
        }
    }
}


