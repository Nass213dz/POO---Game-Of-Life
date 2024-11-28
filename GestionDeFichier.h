#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include <string>

class GestionDeFichier{
    public:
        static std::vector<std::vector<int>> lireFichier(const std::string& nomFichier);
        void ecrireFichier(const std::string& nomFichier, const std::string& contenu);
};


#endif