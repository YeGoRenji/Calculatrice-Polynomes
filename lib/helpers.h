#ifndef HELPERS_H
#define HELPERS_H
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void Clear();
int pgcd(int a, int b);
void simplifyFraction(int *num, int *denom);
void simplifyPoly(Polynome **R);
void printMonome(Monome M, int first);

#endif