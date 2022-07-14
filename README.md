# Description :
Projet d'un Mini-shell Calculatrice des polynomes.

**04 Janvier 2022** \
Projet d'études à l'ENSA khouribga ( 1er Année Cycle d'ingénieur Genie informatique ).

Réaliser par : **Youssef LYOUSSFI** et **Mohammed MJAHED**.

Encadré par : **PR. Abdelmajid DARGHAM**

# Comment configuré ?
- Executer le bash script `init.sh`. (pour créer les dossier necessaires)
    - `bin/` et `obj/`.
- Démarrer `make` pour compiler.
- Démarrer `make run` pour démarrer le program.
# Comment utiliser ?
## LET
Création d'un nouveau polynôme :
```
LET P = X + 1
```
---
## SET
Mise à jour d'un polynôme :
```
SET P = X^2
``` 
---
## DER
Dérivée d'un polynôme :
```
DER P
```
---
## INT
Intégration d'un polynôme :
```
INT P
```
---
## EVAL
Evaluation d'un polynôme :
```
EVAL P for X = 5
```
---
## ADD
Addition de deux polynômes : 
```
ADD P, Q
```
---
## SUB
Soustraction de deux polynômes : 
```
SUB P, Q
```
---
## MUL
Multiplication de deux polynômes : 
```
MUL P, Q
```
---
## POW
Puissance n ème d'un polynôme :
```
POW P, 3
```
---
## AFFECT
Affectation d'un polynôme à un autre :
``` 
AFFECT P, Q
```
---
## DISPLAY
Affichage d'un polynôme :
```
DISPLAY P
```
---
## CLR
Nettoyage l'ecran :
```
CLR
```
---
## HELP
Affichage de manuel :
```
HELP
```
---
## EXIT
Arrêt du programme :
```
EXIT
```
