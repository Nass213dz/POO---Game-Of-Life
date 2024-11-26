#include "GestionFichier.h"
#include <fstream>
#include <stdexcept>

using namespace std;

string lireFichier(const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier source.");
    }
    string contenu((istreambuf_iterator<char>(fichier)), istreambuf_iterator<char>());
    fichier.close();
    return contenu;
}

void ecrireFichier(const string& nomFichier, const string& contenu) {
    ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier de destination.");
    }
    fichier << contenu;
    fichier.close();
}
