#include "../lib/parser.h"

void trim(char *s)
{
    unsigned int i = 0, j = 0;

    while (s[i] != '\0')
    {
        if (isspace(s[i]))
        {
            for (j = i; j < strlen(s); j++)
                s[j] = s[j + 1];
        }
        else
            i++;
    }
}

int evalNombre(int debut, int fin, char const *s)
{
    // Cas particulier pour Les exponant
    if (debut == -1 && fin == -1)
        return 0;
    if (debut == fin)
        return 1;

    int k = 0;
    int res = 0;

    for (k = debut; k < fin; k++)
        res = res * 10 + (s[k] - '0');

    return res;
}

void TraiterMonome(char *s, int *i, int *num, int *denom, int *deg)
{
    // Indices Numerateur
    int num_debut = 0;
    int num_fin = 0;

    // Indices Denominateur
    int denom_debut = 0;
    int denom_fin = 0;

    // Indices Exponant (ou Degre)
    int exp_debut = -1;
    int exp_fin = -1;

    int negatif = 0;
    // Traitement de Signe
    if (s[*i] == '-' || s[*i] == '+')
    {
        negatif = s[*i] == '-' ? 1 : 0;
        *i = *i + 1;
    }

    // Numerateur
    if (isdigit(s[*i]))
    {
        num_debut = *i;
        while (isdigit(s[*i]))
        {
            num_fin = *i + 1;
            *i = *i + 1;
        }
    }

    // Denominateur
    if (s[*i] == '/')
    {
        *i = *i + 1;
        denom_debut = *i;
        while (isdigit(s[*i]))
        {
            denom_fin = *i + 1;
            *i = *i + 1;
        }
    }

    // X
    if (s[*i] == 'X')
    {
        exp_debut = 1;
        exp_fin = 1;
        *i = *i + 1;
    }

    if (s[*i] == '^' || isdigit(s[*i]))
    {
        if (!isdigit(s[*i]))
            *i = *i + 1;
        exp_debut = *i;
        while (isdigit(s[*i]))
        {
            exp_fin = *i + 1;
            *i = *i + 1;
        }
    }

    *num = evalNombre(num_debut, num_fin, s);
    if (negatif)
        *num *= -1;
    *denom = evalNombre(denom_debut, denom_fin, s);
    *deg = evalNombre(exp_debut, exp_fin, s);
}

