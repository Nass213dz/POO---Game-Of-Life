#ifndef CELLULE_H
#define CELLULE_H

#include <string>
#include <iostream>

class Cellule {
    protected:
    bool m_etat;
    public:
    virtual void changerEtat(bool m_etat)=0;          //Le même rôle qu'une porte NOT (si c'est true, il devient false et inversement)
    virtual bool getEtat()=0;                         //Récupère l'état actuelle de la cellule
    virtual ~Cellule()=default;
};

class CelluleVivante : public Cellule {
    protected:
    bool m_etat_vivant;
    public:
    void changerEtat(bool m_etat) override;
    bool getEtat() override;
};

class CelluleMorte : public Cellule {
    protected:
    bool m_etat_mort;
    public:
    void changerEtat(bool m_etat) override;
    bool getEtat() override;
};


#endif