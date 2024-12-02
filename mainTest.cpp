#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;
using namespace sf;

// Constantes pour la grille
const int gridWidth = 20;   // Largeur de la grille
const int gridHeight = 20;  // Hauteur de la grille
const int cellSize = 10;    // Taille d'une cellule en pixels

int main() {
    int mode;

    cout << "Quel mode souhaitez-vous exécuter ?\n1) Mode console\n2) Mode graphique" << endl;
    cin >> mode;

    if (mode == 1) {
        // Mode console
        vector<vector<Cellule*>> grille_cell;
        vector<vector<int>> grille;
        int nbIterations;
        const string iterationPrefix = "Iteration_";
        const string outputFolder = "fichier_iteration";

        // Fichier source prédéfini
        string nomFichier = "test.txt";

        try {
            grille = GestionDeFichier::lireFichier(nomFichier);
        } catch (const std::exception& e) {
            cerr << "Erreur lors de la lecture du fichier : " << e.what() << endl;
            return -1;
        }

        int largeur = grille.size();
        int longueur = grille[0].size();

        Grille grid(longueur, largeur);
        grid.clearGrille();
        GestionDeFichier::supprimerFichiersTxt(outputFolder);

        cout << "Entrez le nombre d'itérations que vous souhaitez effectuer : ";
        cin >> nbIterations;

        for (int i = 0; i < nbIterations; i++) {
            grid.initialisationGrille(grille);
            grille_cell = grid.iteration();
            grille = GestionDeFichier::convertirGrille(grille_cell);

            static vector<vector<int>> grillePrecedente;
            if (grillePrecedente.empty() || !GestionDeFichier::comparerGrilles(grillePrecedente, grille)) {
                GestionDeFichier::ecrireFichier(iterationPrefix + to_string(i + 1), grille, outputFolder);
                grillePrecedente = grille;
            } else {
                cout << "Aucune différence entre l'itération " << i + 1 << " et l'itération précédente. Arrêt de l'écriture des fichiers.\n";
                break;
            }
        }
        return 0;

    } else if (mode == 2) {
        // Mode graphique
        RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

        // Fichier source prédéfini
        string nomFichier = "test.txt";
        vector<vector<int>> grille;

        try {
            grille = GestionDeFichier::lireFichier(nomFichier);
        } catch (const std::exception& e) {
            cerr << "Erreur lors de la lecture du fichier : " << e.what() << endl;
            return -1;
        }

        int largeur = grille.size();
        int longueur = grille[0].size();

        Grille grid(longueur, largeur);
        grid.initialisationGrille(grille);

        // Variables pour gérer le délai entre les itérations
        Clock clock;
        float delay = 0.5f; // Délai initial en secondes (0.5s)

        while (window.isOpen()) {
            // Gestion des événements
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                } else if (event.type == Event::KeyPressed) {
                    // Ajuster le délai avec les touches
                    if (event.key.code == Keyboard::Up) {
                        delay = max(0.1f, delay - 0.1f); // Réduction du délai, minimum 0.1s
                        cout << "Délai réduit : " << delay << "s" << endl;
                    } else if (event.key.code == Keyboard::Down) {
                        delay += 0.1f; // Augmentation du délai
                        cout << "Délai augmenté : " << delay << "s" << endl;
                    }
                }
            }

            // Exécution de l'itération après le délai défini
            if (clock.getElapsedTime().asSeconds() >= delay) {
                grid.iteration(); // Mise à jour de la grille
                clock.restart();
            }

            // Affichage graphique
            window.clear(Color::Black); // Nettoyage de la fenêtre
            grid.graphique(window);    // Dessin de la grille
            window.display();          // Affichage dans la fenêtre
        }

        return 0;
    } else {
        cerr << "Mode non valide. Veuillez choisir 1 ou 2." << endl;
        return -1;
    }
}
