/*
 * Realisé par :
 * Lyoussfi Youssef
 * Mjahed Mohammed
 *
 * Encadré par :
 * Abdelmajid Dargham
 *
 * Année : 2021/2022
 */

#include <stdio.h>
#include <string.h>
#include "../lib/structs.h"
#include "../lib/funcs.h"
#include "../lib/helpers.h"
#include "../lib/list_manip.h"
#include "../lib/parser.h"

int operation(char *cmd)
{
    const char commands[NB_CMDS][8] = {"LET", "SET", "DISPLAY", "ADD", "SUB", "MUL", "POW", "AFFECT", "DER", "INT", "EVAL", "HELP", "CLR", "EXIT"};
    int i = 0;
    for (i = 0; i < NB_CMDS; i++)
        if (strcmp(cmd, commands[i]) == 0)
            return i;

    return -1;
}

int main(void)
{
    Polynome *listPoly = NULL;
    int op = -1;
    char s[50];
    char *cmd = " ";
    char *operant = " ";
    Polynome *P = NULL, *R = NULL, *Q = NULL;
    char nom;
    float X;
    int valid;
    int puiss = 1;

    printf("-------------- Calculatrice Polynomes --------------\n");

    while (op != EXIT)
    {

        int taille = strlen(cmd) + strlen(operant) + 1;
        int i = 0;
        // Clear la commande Precedante
        for (i = 0; i < taille; i++)
            s[i] = '\0';

        printf("\ncmd> ");
        fgets(s,50,stdin);
        // gets(s);
        // Remove \n
        if(s[strlen(s)-1] == '\n')
           s[strlen(s)-1] = '\0';

        if (strlen(s) != 0)
        {
            // Command Ex : LET,SET ...
            cmd = strtok(s, " ");
            // Operant Apres la command Ex: P = X ^3 ...
            operant = s + strlen(cmd) + 1;
            // Effacez tous les Espaces d'operant.
            trim(operant);
        }

        switch (op = operation(cmd))
        {
        case LET:
            if (isalpha(operant[0]) && operant[1] == '=')
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P == NULL)
                {
                    printf(" Creation du polynome : %c \n", operant[0]);
                    // operant + 2 est la chaine de caractaire apres '='
                    P = f_LET(operant + 2, operant[0]);
                    if (P)
                    {
                        AjouterPoly(P, &listPoly);
                        printf(" Polynome %c cree !\n", P->nom);
                    }
                }
                else
                {
                    printf(" Polynome %c deja exist !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case SET:
            if (isalpha(operant[0]) && operant[1] == '=')
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P != NULL)
                {
                    // operant + 2 est la chaine de caractaire apres '='
                    f_SET(P, operant + 2);
                }
                else
                {
                    printf(" Polynome %c n'existe pas !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case DISPLAY:
            if (isalpha(operant[0]))
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P != NULL)
                {
                    f_DISPLAY(*P, 0);
                }
                else
                {
                    printf(" Polynome %c n'existe pas !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case ADD:
            if (isalpha(operant[0]) && isalpha(operant[2]))
            {
                P = ChercherPoly(operant[0], listPoly);
                Q = ChercherPoly(operant[2], listPoly);
                if (P != NULL && Q != NULL)
                {
                    R = f_ADD(P, Q);
                    f_DISPLAY(*R, 0);
                }
                else
                {
                    if (P == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[0]);
                    if (Q == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[2]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }

            break;
        case SUB:
            if (isalpha(operant[0]) && isalpha(operant[2]))
            {
                P = ChercherPoly(operant[0], listPoly);
                Q = ChercherPoly(operant[2], listPoly);
                if (P != NULL && Q != NULL)
                {
                    R = f_SUB(P, Q);
                    f_DISPLAY(*R, 0);
                }
                else
                {
                    if (P == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[0]);
                    if (Q == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[2]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case MUL:
            if (isalpha(operant[0]) && isalpha(operant[2]))
            {
                P = ChercherPoly(operant[0], listPoly);
                Q = ChercherPoly(operant[2], listPoly);
                if (P != NULL && Q != NULL)
                {
                    R = f_MUL(P, Q);
                    f_DISPLAY(*R, 0);
                }
                else
                {
                    if (P == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[0]);
                    if (Q == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[2]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case POW:
            valid = sscanf(operant, "%c,%d", &nom, &puiss);
            if (puiss < 0)
            {
                printf(" Impossible de traiter puissance negatif !\n");
                break;
            }
            if (isalpha(nom) && valid > 1)
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P != NULL)
                {
                    P = f_POW(P, puiss);
                    f_DISPLAY(*P, 0);
                }
                else
                {
                    printf(" Polynome %c n'exist pas !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            valid = 0;
            break;
        case AFFECT:
            if (isalpha(operant[0]) && isalpha(operant[2]))
            {
                P = ChercherPoly(operant[0], listPoly);
                Q = ChercherPoly(operant[2], listPoly);
                if (P != NULL && Q != NULL && P != Q)
                {
                    f_AFFECT(&P, Q, 0);
                    printf(" Polynome %c Modifie !\n", operant[0]);
                }
                else
                {
                    if (P == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[0]);
                    if (Q == NULL)
                        printf(" Polynome %c n'existe pas !\n", operant[2]);
                    if (P == Q && P != NULL)
                        printf(" Affectation du Polynome %c a lui meme !\n", operant[0]);
                }
            }
            break;
        case DER:
            if (isalpha(operant[0]))
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P != NULL)
                {
                    P = f_DER(P);
                    f_DISPLAY(*P, 0);
                }
                else
                {
                    printf(" Polynome %c n'existe pas !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case INT:
            if (isalpha(operant[0]))
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P != NULL)
                {
                    P = f_INT(P);
                    f_DISPLAY(*P, 1);
                }
                else
                {
                    printf(" Polynome %c n'exist pas !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            break;
        case EVAL:
            valid = sscanf(operant, "%cforX=%f", &nom, &X);
            if (isalpha(nom) && valid > 1)
            {
                P = ChercherPoly(operant[0], listPoly);
                if (P != NULL)
                {
                    X = f_EVAL(P, X);
                    printf(" P(X) = %.2f\n", X);
                }
                else
                {
                    printf(" Polynome %c n'exist pas !\n", operant[0]);
                    break;
                }
            }
            else
            {
                printf(" Erreur d'operant \n");
            }
            valid = 0;
            break;
        case HELP:
            puts("# Comment utiliser ?\n## LET\nCréation d'un nouveau polynôme :\n\nLET P = X + 1\n\n---\n## SET\nMise à jour d'un polynôme :\n\nSET P = X^2\n \n---\n## DER\nDérivée d'un polynôme :\n\nDER P\n\n---\n## INT\nIntégration d'un polynôme :\n\nINT P\n\n---\n## EVAL\nEvaluation d'un polynôme :\n\nEVAL P for X = 5\n\n---\n## ADD\nAddition de deux polynômes : \n\nADD P, Q\n\n---\n## SUB\nSoustraction de deux polynômes : \n\nSUB P, Q\n\n---\n## MUL\nMultiplication de deux polynômes : \n\nMUL P, Q\n\n---\n## POW\nPuissance n ème d'un polynôme :\n\nPOW P, 3\n\n---\n## AFFECT\nAffectation d'un polynôme à un autre :\n \nAFFECT P, Q\n\n---\n## DISPLAY\nAffichage d'un polynôme :\n\nDISPLAY P\n\n---\n## CLR\nNettoyage l'ecran :\n\nCLR\n\n---\n## HELP\nAffichage de manuel :\n\nHELP\n\n---\n## EXIT\nArrêt du programme :\n\nEXIT\n");
            break;
        case CLR:
            Clear();
            printf("-------------- Calculatrice Polynomes --------------\n");
            break;
        case EXIT:
            printf(" Fin du Programme, Merci ! \n");
            break;
        default:
            printf(" Operation inconnue !\n");
            break;
        }
    }
    return 0;
}
