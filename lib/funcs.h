#ifndef FUNCS_H
#define FUNCS_H
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "math.h"
#include "list_manip.h"
#include "parser.h"
#include "helpers.h"

Polynome *f_LET(char *s, char nom);
void f_AFFECT(Polynome **, Polynome *, int);
void f_SET(Polynome *P, char *operant);
Polynome *f_DER(Polynome *P);
Polynome *f_INT(Polynome *P);
float f_EVAL(Polynome *P, float X);
Polynome *f_ADD(Polynome *P, Polynome *Q);
Polynome *f_SUB(Polynome *P, Polynome *Q);
Polynome *f_MUL(Polynome *P, Polynome *Q);
Polynome *f_POW(Polynome *P, int puiss);
void f_DISPLAY(Polynome P, int plusC);

#endif