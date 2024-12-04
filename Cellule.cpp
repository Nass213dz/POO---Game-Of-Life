#include "Cellule.h"
#include <stdexcept>

CelluleVivante::CelluleVivante() : m_etat_vivant(1){} //constructeur pour une cellule vivante (initialisé à true ou 1 c'est pareil)
CelluleMorte::CelluleMorte() : m_etat_mort(0){} //constructeur pour une cellule morte (initialisé à false ou 0 c'est pareil)

void CelluleVivante::changerEtat(bool m_etat) {
    //change l'état d'une cellule en fonction du booléen donné en paramètre
    if (!m_etat) {
        m_etat_vivant = false;
    } else {
        m_etat_vivant = true;
    }
}


void CelluleMorte::changerEtat(bool m_etat) {
    //change l'état d'une cellule en fonction du booléen donné en paramètre
    if (m_etat) {
        m_etat_mort = false;
    } else {
        m_etat_mort = true;
    }
}


bool CelluleVivante::getEtat(){
    //récupère l'état actuelle de la cellule
    return m_etat_vivant;
}

bool CelluleMorte::getEtat(){
    //récupère l'état actuelle de la cellule
    return m_etat_mort;
}