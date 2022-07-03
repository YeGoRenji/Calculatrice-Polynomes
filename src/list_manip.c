#include "../lib/list_manip.h"

Monome *newMonome(int num, int denom, int degre)
{
    Monome *M = (Monome *)malloc(sizeof(Monome));
    if (M != NULL)
    {
        simplifyFraction(&num, &denom);
        M->coeffic.numerateur = num;
        M->coeffic.denominateur = denom;
        M->degre = degre;
        M->next = NULL;
    }
    return M;
}

Polynome *newPoly(char nom)
{
    Polynome *P = (Polynome *)malloc(sizeof(Polynome));
    if (P != NULL)
    {
        P->nom = nom;
        P->next = NULL;
        P->firstMonome = NULL;
    }
    return P;
}

void AjouterPoly(Polynome *P, Polynome **List)
{
    Polynome *tmp = *List;
    *List = P;
    P->next = tmp;
}

Polynome *ChercherPoly(char nom, Polynome *List)
{
    Polynome *tmp = List;

    while (tmp != NULL)
    {
        if (tmp->nom == nom)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}

