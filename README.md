MP2I CPGE Project in C

# Structure

## Cette vilaine grille
Structure position couple (x,y) tout sera stoque comme ca et jamais en valeur relative (numero d'entree)
Structure case {}

Structure board qui contient un tableau (ref) de struct blocs, puis une grille (ref) generee en focntion des blocs. Sera stoquee dans la pile
 - Tableau sur le tas -> Struc bloc avec {couleur = 'Y', pos = struct pos, orientation voir doc} 
 - grille matrice applatie (y*q + x) en fonction de la position xy sur le tas -> pointer vers case sur static ex:
    (static) Blue = [[e1,e2,e3],  et chaque element sera une structure {couleur, le triangle orient }
                     [e4,e5,e6]]  le pointeur sera vers un element


## ce vilain rayon

pos de depart et on prend une orientation determinee par le cote d'ou on viens (fonction qui traduit int input vers pos absolue + orientation)
puis un tableau de couleur dans le contexte (pile) de la fonction de simu du rayon, avec une taille fixe du nombre de couleur max du jeu (4 je crois)
chaque frame on avance d'une case en fonction de la direction

# Outdated