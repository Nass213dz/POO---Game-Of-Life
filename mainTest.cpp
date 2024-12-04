#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;
using namespace sf;

const int cellSize = 10; //taille d'une cellule

int main() {
    int mode;

    cout << "Quel mode souhaitez-vous exécuter ?\n{1} Mode console\n{2} Mode graphique" << endl;
    cin >> mode;

    if (mode == 1) {
        //mode console
        vector<vector<Cellule*>> grille_cell;
        vector<vector<int>> grille;
        int nbIterations;
        const string iterationPrefix = "Iteration_";
        const string outputFolder = "fichier_iteration";

        //fichier source prédéfini
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
        //mode graphique
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

        const int gridWidth = grid.getLargeur(); //largeur de la grille
        const int gridHeight = grid.getLongueur(); //hauteur de la grille

        RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life"); //création de la fenêtre graphique

        grid.initialisationGrille(grille);

        //variables pour gérer le temps entre chaque itération
        Clock clock;
        float delay = 0.5f; //delai initial en secondes

        while (window.isOpen()) {
            //gestion des événements clavier et souris
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    grid.clearGrille();
                    window.close();
                } else if (event.type == Event::KeyPressed) {
                    //augmenter ou diminuer le délai avec les flèches du clavier
                    if (event.key.code == Keyboard::Up) {
                        delay = max(0.1f, delay - 0.1f); //diminution du délai (avec un minimum de 0.1s)
                        cout << "Délai réduit : " << delay << "s" << endl;
                    } else if (event.key.code == Keyboard::Down) {
                        delay += 0.1f; //augmentation du délai (pas de maximum)
                        cout << "Délai augmenté : " << delay << "s" << endl;
                    }
                } else if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Middle) {
                        //clique molette ajoute un glider
                        Vector2i mousePosition = Mouse::getPosition(window); //position de la souris dans la grille
                        int y = mousePosition.x / cellSize;  //conversion en coordonnées
                        int x = mousePosition.y / cellSize;

                        try {
                            vector<vector<int>> glider = GestionDeFichier::lireFichier("glider.txt"); //récupération du fichier glider

                            //ajouter le glider à la position de la souris
                            grid.ajouterMotif(glider, x, y);
                            cout << "Glider ajouté à (" << x << ", " << y << ")" << endl;
                        } catch (const std::exception& e) {
                            cerr << "Erreur : " << e.what() << endl;
                        }
                    } else if (event.mouseButton.button == Mouse::Right) {
                        //clic droit ajoute le blinker
                        Vector2i mousePosition = Mouse::getPosition(window);
                        int y = mousePosition.x / cellSize;
                        int x = mousePosition.y / cellSize;

                        try {
                            vector<vector<int>> blinker = GestionDeFichier::lireFichier("blinker.txt");

                            //ajouter le blinker à la position de la souris
                            grid.ajouterMotif(blinker, x, y);
                            cout << "Blinker ajouté à (" << x << ", " << y << ")" << endl;
                        } catch (const std::exception& e) {
                            cerr << "Erreur : " << e.what() << endl;
                        }
                    } else if (event.mouseButton.button == Mouse::Left) {
                        //clic gauche ajoute une cellule vivante
                        Vector2i mousePosition = Mouse::getPosition(window); //position de la souris
                        int y = mousePosition.x / cellSize;  //conversion en coordonnées de grille
                        int x = mousePosition.y / cellSize;

                        try {
                            vector<vector<int>> cellule_vivante = GestionDeFichier::lireFichier("cellule_vivante.txt");

                            //ajoute une cellule vivante à la position de la souris
                            grid.ajouterMotif(cellule_vivante, x, y);
                            cout << "Cellule ajoutée à (" << x << ", " << y << ")" << endl;
                        } catch (const std::exception& e) {
                            cerr << "Erreur : " << e.what() << endl;
                        }
                    }
                }
            }

            //exécution de l'itération après que le délai soit écoulé
            if (clock.getElapsedTime().asSeconds() >= delay) {
                grid.iteration(); //MAJ de la grille
                clock.restart();
            }

            // affichage de l'interface graphique
            window.clear(Color::Black); //nettoyage de la fenêtre
            grid.graphique(window);    //dessin de la grille
            window.display();          //affichage dans la fenêtre
        }

        return 0; //fin du programme
    } else {
        cerr << "Mode non valide. Veuillez choisir 1 ou 2." << endl;
        return -1;
    }
}
