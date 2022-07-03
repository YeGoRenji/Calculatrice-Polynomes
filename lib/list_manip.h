#ifndef LIST_MANIP_H
#define LIST_MANIP_H
#include <stdlib.h>
#include "structs.h"
#include "helpers.h"

Monome *newMonome(int num, int denom, int degre);
Polynome *newPoly(char nom);
void AjouterPoly(Polynome *P, Polynome **List);
Polynome *ChercherPoly(char nom, Polynome *List);

#endif