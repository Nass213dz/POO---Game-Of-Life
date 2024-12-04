#ifndef CELLULE_H
#define CELLULE_H

#include <string>
#include <iostream>

class Cellule {
    protected:
    bool m_etat;
    public:
    virtual void changerEtat(bool m_etat)=0; //change l'état d'une cellule en fonction du booléen donné en paramètre
    virtual bool getEtat()=0; //récupère l'état actuelle de la cellule (méthode virtuelle pure)
    virtual ~Cellule()=default;
};

class CelluleVivante : public Cellule {
    protected:
    bool m_etat_vivant;
    public:
    CelluleVivante(); //constructeur cellule vivante
    void changerEtat(bool m_etat) override;
    bool getEtat() override;
};

class CelluleMorte : public Cellule {
    protected:
    bool m_etat_mort;
    public:
    CelluleMorte(); //constructeur cellule morte
    void changerEtat(bool m_etat) override;
    bool getEtat() override;
};


#endif