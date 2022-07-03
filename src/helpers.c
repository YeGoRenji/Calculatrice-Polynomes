#include "../lib/helpers.h"

void Clear()
{
#ifdef _WIN32
    system("cls");
#endif
#ifdef linux
    system("clear");
#endif
}

int pgcd(int a, int b)
{
    if (a == 1 || a == -1 || b == 1)
        return 1;

    int temp;
    while (b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void simplifyFraction(int *num, int *denom)
{
    int nu = *num > 0 ? *num : -*num;
    int de = *denom > 0 ? *denom : -*denom;

    int d = pgcd(nu, de);

    *num /= d;
    *denom /= d;
}

void simplifyPoly(Polynome **R)
{
    int GrandDegre = (*R)->firstMonome->degre;
    Monome **ptr = calloc(GrandDegre + 1, sizeof(Monome *));

    Monome **tmp = &(*R)->firstMonome;
    int num = 0, denom = 1, deg = 1;

    Monome *tmp2 = NULL;

    while (*tmp != NULL)
    {
        deg = (*tmp)->degre;
        if (ptr[deg])
        {
            num = (*tmp)->coeffic.numerateur * ptr[deg]->coeffic.denominateur + (*tmp)->coeffic.denominateur * ptr[deg]->coeffic.numerateur;
            denom = ptr[deg]->coeffic.denominateur * (*tmp)->coeffic.denominateur;
            // Supprimer le Monome Supplimentaire.
            tmp2 = *tmp;
            *tmp = (*tmp)->next;
            free(tmp2);
            simplifyFraction(&num, &denom);
            // Mise a jour Monome.
            ptr[deg]->coeffic.numerateur = num;
            ptr[deg]->coeffic.denominateur = denom;
        }
        else
        {
            ptr[(*tmp)->degre] = *tmp;
            tmp = &(*tmp)->next;
        }
    }
    free(ptr);
}

void printMonome(Monome M, int first)
{
    int num = M.coeffic.numerateur;
    int denom = M.coeffic.denominateur;
    int deg = M.degre;
    int NumNegative = num < 0;
    const char *signe = (num > 0) ? " + " : " - ";

    // Affiche rien si numerateur nulle
    if (num == 0)
        return;

    // num = |num|
    num = num > 0 ? num : -num;

    // Affichage de signe :
    if (!first)
        printf("%s", signe);
    else if (NumNegative)
        printf("%s", signe);

    // Affichage de numerateur :
    if (denom == 1)
    {
        if (deg)
        {
            if (num != 1)
                printf("%d ", num);
        }
        else
            printf("%d ", num);
    }
    else
    {
        printf("%d", num);
        // Affichage de denominateur :
        printf("/%d ", denom);
    }

    // Affichage de degre :
    if (deg)
    {
        if (deg != 1)
            printf("X^%d", deg);
        else
            printf("X");
    }
}

