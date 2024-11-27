#include "Cellule.h"
#include <stdexcept>

CelluleVivante::CelluleVivante() : m_etat_vivant(1){}
CelluleMorte::CelluleMorte() : m_etat_mort(0){}

void CelluleVivante::changerEtat(bool m_etat){
    m_etat_vivant!=m_etat_vivant;
}

void CelluleMorte::changerEtat(bool m_etat){
    m_etat_mort!=m_etat_mort;
}

bool CelluleVivante::getEtat(){
    return m_etat_vivant;
}

bool CelluleMorte::getEtat(){
    return m_etat_mort;
}