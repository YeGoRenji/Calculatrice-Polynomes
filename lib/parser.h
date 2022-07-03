#ifndef PARSER_H
#define PARSER_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim(char *s);
int evalNombre(int debut, int fin, char const *s);
void TraiterMonome(char *s, int *i, int *num, int *denom, int *deg);

#endif