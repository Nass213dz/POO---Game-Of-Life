#include <fstream>
#include <stdexcept>
#include "GestionDeFichier.h"

using namespace std;

string GestionDeFichier::lireFichier(const string& nomFichier) {
    string premiereLigne;
    string ligne;
    ifstream lireMessage(nomFichier);
    if (!lireMessage.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier source.");
    }

    getline(lireMessage, premiereLigne);
    for (int i(0); i < premiereLigne.size(); )

    while(getline(lireMessage, ligne)){
        message.append(ligne + "\n");
    }
    lireMessage.ignore();
    return contenu;
}

void GestionDeFichier::ecrireFichier(const string& nomFichier, const string& contenu) {
    ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier de destination.");
    }
    fichier << contenu;
    fichier.close();
}