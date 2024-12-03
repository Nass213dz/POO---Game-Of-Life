#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include <string>
#include <vector>
#include "Cellule.h"

class GestionDeFichier{
    public:
        static std::vector<std::vector<int>> lireFichier(const std::string& nomFichier);
        static void ecrireFichier(const std::string& nomFichier, const std::vector<std::vector<int>>& grille, const std::string& dossier);
        static std::vector<std::vector<int>> convertirGrille(const std::vector<std::vector<Cellule*>>& grille);
        static bool comparerGrilles(const std::vector<std::vector<int>>& grille1, const std::vector<std::vector<int>>& grille2);
        static void supprimerFichiersTxt(const std::string& dossier);
        static std::vector<std::vector<int>> lireMotifDepuisFichier(const std::string& nomFichier);
};


#endif