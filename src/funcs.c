#include "../lib/funcs.h"

Polynome *f_LET(char *s, char nom)
{
    int i = 0;

    // Polynome d'Expression Vide ?
    if (strlen(s) == 0)
    {
        printf(" Polynome Vide !\n");
        return NULL;
    }

    // Validation:
    while (s[i] != '\0')
    {
        if (!(isdigit(s[i]) || s[i] == '-' || s[i] == '+' || s[i] == 'X' || s[i] == '/' || s[i] == '^'))
        {
            printf(" Impossible de traiter le symbole \"%c\"\n", s[i]);
            return NULL;
        }

        if (s[i] == '/' && s[i + 1] == '0')
        {
            printf(" Division par 0 interdite !\n");
            return NULL;
        }
        i++;
    }

    int num = 1;
    int denom = 1;
    int exp = 0;

    i = 0;
    Polynome *P = newPoly(nom);

    Monome **ptrM = &P->firstMonome;

    // Traitement
    while (s[i] != '\0')
    {
        TraiterMonome(s, &i, &num, &denom, &exp);

        *ptrM = newMonome(num, denom, exp);
        ptrM = &(*ptrM)->next;
    }
    return P;
}

void f_SET(Polynome *P, char *operant)
{
    Polynome *Q = f_LET(operant, P->nom);
    f_AFFECT(&P, Q, 1);
    printf(" Polynome %c Modifie !\n", P->nom);
}

Polynome *f_DER(Polynome *P)
{
    Monome *tmp = P->firstMonome;
    if (tmp == NULL)
        return NULL;

    else
    {
        Polynome *D = newPoly('D');
        Monome **Dr = &D->firstMonome;
        if ((tmp->next == NULL) && (tmp->degre == 0))
        {
            *Dr = newMonome(0, 1, 0);
        }
        else
        {
            while (tmp != NULL && tmp->degre != 0)
            {
                *Dr = newMonome(tmp->degre * tmp->coeffic.numerateur, tmp->coeffic.denominateur, tmp->degre - 1);
                tmp = tmp->next;
                Dr = &(*Dr)->next;
            }
        }
        return D;
    }
}

Polynome *f_INT(Polynome *P)
{
    Monome *tmp = P->firstMonome;
    if (tmp == NULL)
        printf("I = c ");
    else
    {
        Polynome *I = newPoly('I');
        Monome **Ir = &I->firstMonome;
        while (tmp != NULL)
        {
            *Ir = newMonome(tmp->coeffic.numerateur, tmp->coeffic.denominateur * (tmp->degre + 1), tmp->degre + 1);
            tmp = tmp->next;
            Ir = &(*Ir)->next;
        }
        return I;
    }
    return NULL;
}

float f_EVAL(Polynome *P, float X)
{
    float E = 0;
    Monome *tmp = P->firstMonome;
    if (tmp == NULL)
        return 0;
    else
    {
        while (tmp != NULL)
        {
            E = E + ((tmp->coeffic.numerateur * pow(X, tmp->degre)) / tmp->coeffic.denominateur);
            tmp = tmp->next;
        }
        return E;
    }
}

Polynome *f_ADD(Polynome *P, Polynome *Q)
{
    int num, denom, degre;
    Monome *tmp1 = P->firstMonome, *tmp2 = Q->firstMonome;
    Polynome *R = newPoly('R');
    Monome **Res = &R->firstMonome;
    while ((tmp1 != NULL) && (tmp2 != NULL))
    {
        if (tmp1->degre < tmp2->degre)
        {
            num = tmp2->coeffic.numerateur;
            denom = tmp2->coeffic.denominateur;
            degre = tmp2->degre;
            tmp2 = tmp2->next;
        }
        else if (tmp1->degre > tmp2->degre)
        {
            num = tmp1->coeffic.numerateur;
            denom = tmp1->coeffic.denominateur;
            degre = tmp1->degre;
            tmp1 = tmp1->next;
        }
        else if (tmp1->degre == tmp2->degre)
        {
            if (tmp1->coeffic.denominateur == tmp2->coeffic.denominateur) // les deux nombres ont le meme d�nominateur.
            {
                num = tmp1->coeffic.numerateur + tmp2->coeffic.numerateur;
                denom = tmp1->coeffic.denominateur; // Car tmp1->coeffic.denominateur = tmp2->coeffic.denominateur
            }
            else // les deux nombres ont des denominateurs differents .
            {
                num = tmp1->coeffic.numerateur * tmp2->coeffic.denominateur + tmp2->coeffic.numerateur * tmp1->coeffic.denominateur;
                denom = tmp1->coeffic.denominateur * tmp2->coeffic.denominateur;
            }
            degre = tmp1->degre; // Car tmp1->degre = tmp2->degre
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        if (num != 0)
        {
            *Res = newMonome(num, denom, degre);
            Res = &(*Res)->next;
        }
    }

    // Le reste Dans tmp1 ou tmp2
    tmp1 = tmp1 != NULL ? tmp1 : tmp2;
    while (tmp1 != NULL)
    {
        num = tmp1->coeffic.numerateur;
        denom = tmp1->coeffic.denominateur;
        degre = tmp1->degre;
        *Res = newMonome(num, denom, degre);
        tmp1 = tmp1->next;
        Res = &(*Res)->next;
    }
    if (R->firstMonome)
        return R;
    else
    {
        R->firstMonome = newMonome(0, 1, 0);
        return R;
    }
}

Polynome *f_SUB(Polynome *P, Polynome *Q)
{
    int num, denom, degre;
    Monome *tmp1 = P->firstMonome, *tmp2 = Q->firstMonome;
    Polynome *R = newPoly('R');
    Monome **Res = &R->firstMonome;
    while ((tmp1 != NULL) && (tmp2 != NULL))
    {
        if (tmp1->degre < tmp2->degre)
        {
            num = -(tmp2->coeffic.numerateur);
            denom = tmp2->coeffic.denominateur;
            degre = tmp2->degre;
            tmp2 = tmp2->next;
        }
        else if (tmp1->degre > tmp2->degre)
        {
            num = tmp1->coeffic.numerateur;
            denom = tmp1->coeffic.denominateur;
            degre = tmp1->degre;
            tmp1 = tmp1->next;
        }
        else if (tmp1->degre == tmp2->degre)
        {
            if (tmp1->coeffic.denominateur == tmp2->coeffic.denominateur) // les deux nombres ont le meme d�nominateur.
            {
                num = tmp1->coeffic.numerateur - tmp2->coeffic.numerateur;
                denom = tmp1->coeffic.denominateur; // Car tmp1->coeffic.denominateur = tmp2->coeffic.denominateur
            }
            else // les deux nombres ont des denominateurs differents .
            {
                num = tmp1->coeffic.numerateur * tmp2->coeffic.denominateur - tmp2->coeffic.numerateur * tmp1->coeffic.denominateur;
                denom = tmp1->coeffic.denominateur * tmp2->coeffic.denominateur;
            }
            degre = tmp1->degre; // Car tmp1->degre = tmp2->degre
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        if (num != 0)
        {
            *Res = newMonome(num, denom, degre);
            Res = &(*Res)->next;
        }
    }

    // Le reste Dans tmp1 ou tmp2
    tmp1 = tmp1 != NULL ? tmp1 : tmp2;
    while (tmp1 != NULL)
    {
        num = tmp1->coeffic.numerateur;
        if (tmp2)
            num *= -1;
        denom = tmp1->coeffic.denominateur;
        degre = tmp1->degre;
        *Res = newMonome(num, denom, degre);
        tmp1 = tmp1->next;
        Res = &(*Res)->next;
    }
    if (R->firstMonome)
        return R;
    else
    {
        R->firstMonome = newMonome(0, 1, 0);
        return R;
    }
}

Polynome *f_MUL(Polynome *P, Polynome *Q)
{
    int num, denom, degre;
    Monome *tmp1 = P->firstMonome, *tmp2 = Q->firstMonome;
    Polynome *R = newPoly('R');
    Monome **Res = &R->firstMonome;
    if (tmp1 != NULL && tmp2 != NULL)
    {
        while (tmp1 != NULL)
        {
            while (tmp2 != NULL)
            {
                num = tmp1->coeffic.numerateur * tmp2->coeffic.numerateur;
                denom = tmp1->coeffic.denominateur * tmp2->coeffic.denominateur;
                degre = tmp1->degre + tmp2->degre;
                *Res = newMonome(num, denom, degre);
                Res = &(*Res)->next;
                tmp2 = tmp2->next;
            }
            tmp2 = Q->firstMonome;
            tmp1 = tmp1->next;
        }
        simplifyPoly(&R);
        return R;
    }
    return NULL;
}

Polynome *f_POW(Polynome *P, int puiss)
{
    Polynome *R = newPoly('R');
    R->firstMonome = newMonome(1, 1, 0);

    if (puiss == 0)
    {
        return R;
    }

    while (puiss-- > 0)
        R = f_MUL(P, R);

    return R;
}

void f_AFFECT(Polynome **P, Polynome *Q, int utiliserQ)
{
    Monome **ptr = &(*P)->firstMonome;
    Monome *source = Q->firstMonome;
    Monome *tmp = NULL;

    while (source != NULL && (*ptr) != NULL)
    {
        if (source->degre > (*ptr)->degre)
        {
            // Inserer Avant
            if (utiliserQ)
            {
                tmp = source->next;
                source->next = *ptr;
                *ptr = source;
                ptr = &source->next;
                source = tmp;
            }
            else
            {
                tmp = newMonome(source->coeffic.numerateur, source->coeffic.denominateur, source->degre);
                tmp->next = *ptr;
                *ptr = tmp;
                source = source->next;
                ptr = &(*ptr)->next;
            }
        }
        else if (source->degre == (*ptr)->degre)
        {
            // Remplacer par le nouveau coeffic
            (*ptr)->coeffic = source->coeffic;
            tmp = source;
            source = source->next;
            ptr = &(*ptr)->next;
            // Supprimer la source
            if (utiliserQ)
                free(tmp);
        }
        else if (source->degre < (*ptr)->degre)
        {
            // Suprrimer le monome -> le monome n'exist pas dans le nouveau poly
            tmp = *ptr;
            *ptr = (*ptr)->next;
            free(tmp);
        }
    }

    if (source != NULL && (*ptr) == NULL)
    {
        if (utiliserQ)
            *ptr = source;
        else
        {
            while (source != NULL)
            {
                *ptr = newMonome(source->coeffic.numerateur, source->coeffic.denominateur, source->degre);
                source = source->next;
                ptr = &(*ptr)->next;
            }
        }
    }
    else if (source == NULL && (*ptr) != NULL)
    {
        // Si l'ancien polynome avait assez des monomes -> Les supprimer
        Monome *prev = *ptr;
        *ptr = NULL;
        Monome *current = prev->next;
        do
        {
            free(prev);
            prev = current;
            if (current != NULL)
                current = current->next;
        } while (current != NULL);
    }
}

void f_DISPLAY(Polynome P, int plusC)
{
    Monome *tmp = P.firstMonome;

    printf(" %c = ", P.nom);

    if (!tmp || (tmp->coeffic.numerateur == 0 && tmp->next == NULL && !plusC))
    {
        printf("0\n");
        return;
    }

    printMonome(*tmp, 1);

    tmp = tmp->next;
    while (tmp != NULL)
    {
        if (tmp->coeffic.numerateur != 0)
            printMonome(*tmp, 0);
        tmp = tmp->next;
    }
    if (plusC)
        printf(" + c");
    printf("\n");
}

