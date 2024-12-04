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
    //destructeur qui supprime chaque cellule du vecteur
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            delete cellules[i][j];
        }
    }
}

int Grille::getLargeur() const {
    //getter de la largeur
    return m_largeur;
}

int Grille::getLongueur() const {
    //getter de la longueur
    return m_longueur;
}


bool Grille::getVieCellule(int i, int j) const {
    //getter de l'état d'une cellule à une position donnée en parametre
    return cellules[i][j]->getEtat() ? true : false; //si getEtat() retourne true la méthode getVieCellule retourne true sinon false (condition ternaire)
}

void Grille::setVieCellule(int x, int y, bool vivante) {
    //setter qui permet de changer l'état d'une cellule à une position prédéfinie
    if (x >= 0 && x < m_longueur && y >= 0 && y < m_largeur) {
            cellules[x][y]->changerEtat(vivante); //change l'état en vivant ou mort en fonction du booléen entré en paramètre
    }
}

int Grille::getNBRVoisinsVivants(int i, int j) {
    //calcule le nombre de voisins vivants autour de la cellule (à une position entrée en paramètre)
    int compteur_voisin_vivant = 0; //init du compteur

    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            //parcourt les 8 voisins autour de la cellule
            if (k == 0 && l == 0) continue; //skip la cellule initiale

            int voisin_i = (i + k + m_longueur) % m_longueur; //coordonnée en i d'un voisin avec un modulo pour la grille torique
            int voisin_j = (j + l + m_largeur) % m_largeur; //coordonnée en j d'un voisin avec un modulo pour la grille torique

            if (voisin_i >= 0 && voisin_i < m_longueur && voisin_j >= 0 && voisin_j < m_largeur) { //vérifie pour chaque voisin s'il est bien dans la grille
                if (getVieCellule(voisin_i, voisin_j)) { //si la cellule est vivante
                    ++compteur_voisin_vivant; //incrementation du compt
                }
            }
        }
    }

    return compteur_voisin_vivant;
}

void Grille::affichageGrille() {
    //affiche la grille
    cout << "Etat de la grille :" << endl;
    for (int i = 0; i < m_longueur; i++) { //parcours des lignes
        for (int j = 0; j < m_largeur; j++) { // parcours des colonnes
            cout << (cellules[i][j]->getEtat() ? "1" : "0") << " "; //affiche "1" pour vivant et "0" pour mort
        }
        cout << endl; //saut de ligne
    }
}

void Grille::initialisationGrille(vector<vector<int>>& etats_cellules) {
    //initialise la grille afin de créer des objets correspondants à l'état d'une cellule
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            if (etats_cellules[i][j] == 1) { //si la cellule lue dans le fichier d'entrée est de 1
                cellules[i][j] = new CelluleVivante(); //crée un nouvel objet de cellule vivante
            } else if (etats_cellules[i][j] == 0) { //pareil mais pour une cellule morte
                cellules[i][j] = new CelluleMorte();
            }
        }
    }
}


vector<vector<Cellule*>> Grille::iteration() {
    //création d'un vecteur pour stocker l'itération suivante
    vector<vector<Cellule*>> nouvelles_cellules(m_longueur, vector<Cellule*>(m_largeur, nullptr));
    bool changement_detecte = false; //false en cas de changement, true sinon

    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            int voisins_vivants = getNBRVoisinsVivants(i, j);

            if (getVieCellule(i, j)) { //la cellule est vivante
                if (voisins_vivants == 2 || voisins_vivants == 3) {
                    //règle permettant qu'une cellule vivante reste vivante
                    nouvelles_cellules[i][j] = new CelluleVivante();
                } else {
                    nouvelles_cellules[i][j] = new CelluleMorte();
                }
            } else { //la cellule est morte
                if (voisins_vivants == 3) {
                    //règle permettant à une cellule morte de devenir vivante
                    nouvelles_cellules[i][j] = new CelluleVivante();
                } else {
                    nouvelles_cellules[i][j] = new CelluleMorte();
                }
            }

            //vérification de différence entre l'état actuel et le prochain
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

    //mise à jour de la grille et libération de la mémoire des anciennes cellules
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            delete cellules[i][j]; //suppression des anciennes cellules
            cellules[i][j] = nouvelles_cellules[i][j]; //MAJ des cellules une par une
        }
    }

    return cellules; // return les nouvelles cellules
}




void Grille::clearGrille() {
    //méthode qui libere la mémoire pour toute la grille
    for (int i = 0; i < m_longueur; i++) {
        for (int j = 0; j < m_largeur; j++) {
            delete cellules[i][j]; //libération de la mémoire
        }
    }
}


vector<vector<int>> grid(gridWidth, vector<int>(gridHeight)); //initialisation d'un vecteur grid

void Grille::graphique(RenderWindow& window) {
    //méthode qui prend en charge l'interface graphique
    for (int i = 0; i < cellules.size(); ++i) {
        for (int j = 0; j < cellules[i].size(); ++j) {
            //dessin de la cellule
            RectangleShape cell(Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);  //calculer la position pour chaque cellule

            if (dynamic_cast<CelluleVivante*>(cellules[i][j])) {
                cell.setFillColor(Color::White);  //cellule vivante en blanc
            } else {
                cell.setFillColor(Color::Black);  //cellule morte en noir
            }

            window.draw(cell); //dessin de l'interface en respectant les caractéristiques de 'cell'
        }
    }
}




void Grille::ajouterMotif(const vector<vector<int>>& motif, int x, int y) {
    //méthode permettant d'ajouter un motif prédéfini dans la grille
    for (int i = 0; i < motif.size(); ++i) {
        //vérification que les indices sont dans les limites de la grille
        for (int j = 0; j < motif[i].size(); ++j) {
            int newX = x + i; //nouvelles coordonnées
            int newY = y + j;

            if (newX >= 0 && newX < m_longueur && newY >= 0 && newY < m_largeur) {
                //vérifier si la position est dans les limites de la grille
                if (motif[i][j] == 1) {
                    //libération de la cellule existante si besoin
                    if (dynamic_cast<CelluleMorte*>(cellules[newX][newY])) {
                        //si la cellule doit devenir vivante, vérifier si elle n'est pas déjà vivante
                        delete cellules[newX][newY]; //suppression des anciennes cellules
                        cellules[newX][newY] = new CelluleVivante(); //création des cellules correspo,ndant au motif
                    }
                } else {
                    //si la cellule doit devenir morte vérifier si elle n'est pas déjà morte
                    if (dynamic_cast<CelluleVivante*>(cellules[newX][newY])) {
                        delete cellules[newX][newY];
                        cellules[newX][newY] = new CelluleMorte();
                    }
                }
            } else {
                //affichage d'un message d'avertissement si le motif dépasse les limites de la grille
                cout << "Attention : le motif dépasse les limites de la grille à la position ("
                     << newX << ", " << newY << "). Motif non ajouté à cette position.\n";
            }
        }
    }
}







