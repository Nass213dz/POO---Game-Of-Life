#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include <string>

class GestionDeFichier{
    public:
        static std::vector<std::vector<int>> lireFichier(const std::string& nomFichier);
        static void ecrireFichier(const std::string& nomFichier, const std::vector<std::vector<int>>& grille);
};


#endif