#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include <string>
#include <vector>
#include "Cellule.h"

class GestionDeFichier{
    public:
        static std::vector<std::vector<int>> lireFichier(const std::string& nomFichier);
        static void ecrireFichier(const std::string& nomFichier, const std::vector<std::vector<int>>& grille);
        static std::vector<std::vector<int>> convertirGrille(const std::vector<std::vector<Cellule*>>& grille);
};


#endif