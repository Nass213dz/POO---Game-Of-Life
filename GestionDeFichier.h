#ifndef GESTIONFICHIER_H
#define GESTIONFICHIER_H

#include <string>

class GestionDeFichier{
    public:
        int lireFichier(const std::string& nomFichier);
        void ecrireFichier(const std::string& nomFichier, const std::string& contenu);
};


#endif