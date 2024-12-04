#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GestionDeFichier.h"
#include "Cellule.h"
#include "Grille.h"

using namespace std;
using namespace sf;

const int cellSize = 10; //taille d'une cellule
bool pause = false;

int main() {
    int mode;

    cout << "Quel mode souhaitez-vous exécuter ?\n{1} Mode console\n{2} Mode graphique\n{3} Mode Test" << endl; //laisse le choix du mode à l'utilisateur
    cin >> mode; //récupération du choix de l'utilisateur

    if (mode == 1) {
        //mode console
        vector<vector<Cellule*>> grille_cell; //création d'un vecteur de pointeur cellule appelé grille_cell
        vector<vector<int>> grille; //création d'un vecteur int appelé grille
        int nbIterations; //initialisation de l'entier nombre d'itération
        const string iterationPrefix = "Iteration_"; //nom des fichiers d'itération (qui seront complétés par le nombre d'itération)
        const string outputFolder = "fichier_iteration"; //nom du dossier qui va stocker les itérations

        //fichier source prédéfini
        string nomFichier = "test.txt"; //nom du fichier source

        try {
            grille = GestionDeFichier::lireFichier(nomFichier); //remplissage du vecteur grille avec les informations de test.txt
        } catch (const exception& e) {
            cerr << "Erreur lors de la lecture du fichier : " << e.what() << endl; //si le fichier n'est pas trouvé ou impossible à lire
            return -1;
        }

        int largeur = grille.size(); //taille de la grille (nombre de lignes)
        int longueur = grille[0].size(); //pareil (nombre de colonnes)

        Grille grid(longueur, largeur); //création de l'objet grid avec les paramètres longueur et largeur récupérés dans le fichier source
        grid.clearGrille(); //libère la mémoire pour toute la grille
        GestionDeFichier::supprimerFichiersTxt(outputFolder); //supprime tous les fichiers du dossier qui stocke les itérations

        cout << "Entrez le nombre d'itérations que vous souhaitez effectuer : ";
        cin >> nbIterations; //récupération du nombre d'itérations

        for (int i = 0; i < nbIterations; i++) {
            //pour chaque itération
            grid.initialisationGrille(grille); //initialisation de la grille
            grille_cell = grid.iteration(); //génération de la prochaine itération
            grille = GestionDeFichier::convertirGrille(grille_cell); //conversion de la grille vers int

            static vector<vector<int>> grillePrecedente; //vecteur statique d'entier qui stocke la grille precedente
            if (grillePrecedente.empty() || !GestionDeFichier::comparerGrilles(grillePrecedente, grille)) {
                //si il y a une différence entre la grille précédente et la nouvelle
                GestionDeFichier::ecrireFichier(iterationPrefix + to_string(i + 1), grille, outputFolder); //écriture de la nouvelle grille dans le fichier
                grillePrecedente = grille;
            } else {
                //sinon le programme s'arrête (break) et renvoie un message disant qu'il n'y a plus de changements en précisant à partir de quelle itération
                cout << "Aucune différence entre l'itération " << i + 1 << " et l'itération précédente. Arrêt de l'écriture des fichiers.\n";
                break;
            }
        }
        grid.clearGrille(); //libération de la mémoire
        return 0;

    } else if (mode == 2) {
        //mode graphique
        string nomFichier = "test.txt"; //pareil qu'en mode console
        vector<vector<int>> grille;

        try {
            grille = GestionDeFichier::lireFichier(nomFichier); //pareil qu'en mode console
        } catch (const exception& e) {
            cerr << "Erreur lors de la lecture du fichier : " << e.what() << endl;
            return -1;
        }

        int largeur = grille.size();
        int longueur = grille[0].size();

        Grille grid(longueur, largeur);

        const int gridWidth = grid.getLargeur(); //largeur de la grille
        const int gridHeight = grid.getLongueur(); //hauteur de la grille

        RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life"); //création de la fenêtre graphique

        grid.initialisationGrille(grille); //initialisation de la grille

        //variables pour gérer le temps entre chaque itération
        Clock clock;
        float delay = 0.5f; //delai initial en secondes (0,5 secondes par défaut)

        while (window.isOpen()) {
            //gestion des événements clavier et souris
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    //si la fenêtre est fermée
                    grid.clearGrille(); //libération de la mémoire
                    window.close();
                } else if (event.type == Event::KeyPressed) {
                    //augmenter ou diminuer le délai avec les flèches du clavier
                    if (event.key.code == Keyboard::Up) {
                        delay = max(0.1f, delay - 0.1f); //diminution du délai (avec un minimum de 0.1s)
                        cout << "Délai réduit : " << delay << "s" << endl;
                    } else if (event.key.code == Keyboard::Down) {
                        delay += 0.1f; //augmentation du délai (pas de maximum)
                        cout << "Délai augmenté : " << delay << "s" << endl;
                    } else if(event.key.code == Keyboard::Space){
                        //appui sur la barre espace met pause ou reprend le jeu de la vie
                        pause = !pause; //changement de l'état de pause (il devient true si il était false et inversement)
                        cout << (pause ? "Jeu en Pause" : "Jeu en Cours") << endl; //condition ternaire qui montre dans la console si le jeu est en pause ou en cours
                    }
                } else if (event.type == Event::MouseButtonPressed) {
                    //bouton de souris appuyé
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
                        } catch (const exception& e) {
                            cerr << "Erreur : " << e.what() << endl;
                        }
                    } else if (event.mouseButton.button == Mouse::Right) {
                        //clic droit ajoute le blinker
                        Vector2i mousePosition = Mouse::getPosition(window);
                        int y = mousePosition.x / cellSize;
                        int x = mousePosition.y / cellSize;

                        try {
                            vector<vector<int>> blinker = GestionDeFichier::lireFichier("blinker.txt"); //récupération du fichier blinker

                            //ajouter le blinker à la position de la souris
                            grid.ajouterMotif(blinker, x, y);
                            cout << "Blinker ajouté à (" << x << ", " << y << ")" << endl;
                        } catch (const exception& e) {
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
                        } catch (const exception& e) {
                            cerr << "Erreur : " << e.what() << endl;
                        }
                    }else if (event.mouseButton.button == Mouse::XButton1){
                        //touche latérale ajoute un canon
                        Vector2i mousePosition = Mouse::getPosition(window);
                        int y = mousePosition.x / cellSize;
                        int x = mousePosition.y / cellSize;

                        try{
                            vector<vector<int>> canon = GestionDeFichier::lireFichier("canon.txt");

                            //ajoute un canon à la position de la souris
                            grid.ajouterMotif(canon, x, y);
                            cout << "Canon ajouté à (" << x << ", " << y << ")" << endl;
                        } catch(const exception& e){
                            cerr <<"Erreur : " << e.what() << endl;
                        }
                    } 
                }
            }

            //exécution de l'itération après que le délai soit écoulé
            if (!pause && clock.getElapsedTime().asSeconds() >= delay) {
                grid.iteration(); //MAJ de la grille
                clock.restart();
            }
            
            // affichage de l'interface graphique
            window.clear(Color(20, 20, 20)); //nettoyage de la fenêtre avec couleur de fond en gris
            grid.graphique(window);    //dessin de la grille
            window.display();          //affichage dans la fenêtre
        }

        return 0; //fin du programme
    } else if (mode == 3) {
        // Mode test unitaire
        string fichierDepart = "grille_depart.txt";  // fichier de la grille initiale
        string fichierAttendu = "grille_arrivee.txt"; // fichier de la grille attendue
        vector<vector<int>> grilleDepart;
        vector<vector<int>> grilleAttendue;

        try {
            //lecture des fichiers
            grilleDepart = GestionDeFichier::lireFichier(fichierDepart);
            grilleAttendue = GestionDeFichier::lireFichier(fichierAttendu);
        } catch (const exception& e) {
            cerr << "Erreur lors de la lecture des fichiers : " << e.what() << endl;
            return -1;
        }

        // inititlisation de la grille à partir des dimensions du fichier de départ
        int largeur = grilleDepart.size();
        int longueur = grilleDepart[0].size();
        Grille grid(longueur, largeur);

        // chargement la grille de départ
        grid.initialisationGrille(grilleDepart);

        //5 itérations
        vector<vector<Cellule*>> grille_cell;
        for (int i = 0; i < 5; i++) {
            grille_cell = grid.iteration(); //une itération
        }

        //convertir la grille finale en vecteur d'int
        vector<vector<int>> grilleResultat = GestionDeFichier::convertirGrille(grille_cell);

        //comparaison de la grille obtenue avec la grille attendue
        if (!GestionDeFichier::comparerGrilles(grilleResultat, grilleAttendue)) {
            //si il n'y a pas de différence entre la grille résultante et la grille
            cout << "Test unitaire réussi : La grille obtenue après 5 itérations correspond à la grille attendue." << endl;
        } else {
            cout << "Test unitaire échoué : La grille obtenue après 5 itérations ne correspond pas à la grille attendue." << endl;
        }
     } else {
        cerr << "Mode non valide. Veuillez choisir 1, 2 ou 3." << endl;
        return -1;
    }
}
