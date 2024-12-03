#include "Cellule.h"
#include <stdexcept>

CelluleVivante::CelluleVivante() : m_etat_vivant(1){}
CelluleMorte::CelluleMorte() : m_etat_mort(0){}

void CelluleVivante::changerEtat(bool m_etat) {
    if (!m_etat) {
        m_etat_vivant = false;
    } else {
        m_etat_vivant = true;
    }
}


void CelluleMorte::changerEtat(bool m_etat) {
    if (m_etat) {
        m_etat_mort = false;
    } else {
        m_etat_mort = true;
    }
}


bool CelluleVivante::getEtat(){
    return m_etat_vivant;
}

bool CelluleMorte::getEtat(){
    return m_etat_mort;
}