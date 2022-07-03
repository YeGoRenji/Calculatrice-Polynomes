#ifndef STRUCTS_H
#define STRUCTS_H

#define NB_CMDS 13

typedef enum PREFIX
{
    LET,
    SET,
    DISPLAY,
    ADD,
    SUB,
    MUL,
    POW,
    AFFECT,
    DER,
    INT,
    EVAL,
    CLR,
    EXIT
} PREFIX;

typedef struct Fraction
{
    int numerateur;
    int denominateur;
} Fraction;

typedef struct Monome
{
    Fraction coeffic;
    int degre;
    struct Monome *next;
} Monome;

typedef struct Polynome
{
    char nom;
    struct Polynome *next;
    struct Monome *firstMonome;
} Polynome;

#endif
