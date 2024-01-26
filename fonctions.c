#include <stdlib.h>
#include <stdio.h>
#include "bib.h"
#include <time.h>
#include <string.h>


//fill the intire matrix withe zeros

void reset(int matrice [8][8],int nbrligne,int nbrcolomn)
{
    for (int i =0;i<nbrligne;i++)
    {
        for (int j=0;j<nbrcolomn;j++)
            {
            matrice[i][j]=0;
            }
    }

}

//affichage de matrice

void affich_matrice(int matrice[8][8],int nbrligne,int nbrcolomn)
{
    for (int i =0;i<nbrligne;i++)
    {
        for (int j=0;j<nbrcolomn;j++)
            {
            printf(" %d",matrice[i][j]);
            }
        printf("\n");
    }
}

//fill up the matrix with 1's and 2's (1=/;2=\)

void add_diagonals(int matrice[8][8],int nbrdiagonal,int nbrligne,int nbrcolomn)
{
    for (int k = 0; k < nbrdiagonal; k++) {
        int i, j;
        do {
            i = rand() % nbrligne;
            j = rand() % nbrcolomn;
        } while (matrice[i][j] != 0);

        matrice[i][j] = (rand() % 2) + 1;  // Generates 1 or 2
    }
}

void init_lvl(int *nbrdiagonal,int *size,pos* pos_insert,pos* pos_init,pos * pos_final,int matrice[8][8])
{
    (*nbrdiagonal)=3;(*size)=3;
    (*pos_insert).x=-10;
    reset(matrice,*size,*size);
    add_diagonals(matrice,nbrdiagonal,*size,*size);
    (*pos_init)=randomizePosInit(*size);
    (*pos_final)=NavigateMatrix(matrice,*pos_init,*size);
    printf("\n");
    affich_matrice(matrice,*size,*size);
    printf("pos_init.x:%d",(*pos_init).x);
    printf("pos_init.y:%d\n",(*pos_init).y);
    printf("pos_final.x:%d",(*pos_final).x);
    printf("pos_final.y:%d\n",(*pos_final).y);
}

pos randomizePosInit(int size)
{
    pos pos_init;
    int t;
    t= rand()%2;
    if (t==0) //x =-1 ou size
    {
        t=rand()%2;
        if (t==0)
        {
            pos_init.x=-1;
        }else
        {
            pos_init.x=size;
        }
        pos_init.y=rand()%size;
    }else
    {
        t=rand()%2;
        if (t==0)
        {
            pos_init.y=-1;
        }else
        {
            pos_init.y=size;
        }
        pos_init.x=rand()%size;
    }
return pos_init;
}



pos move_left(pos pos_final)
{
     pos_final.x = pos_final.x - 1;
     return pos_final;
}


pos move_right(pos pos_final)
{
    pos_final.x++;
    return pos_final;
}

pos move_up(pos pos_final)
{
    pos_final.y = pos_final.y - 1;
    return pos_final;
}

pos move_down(pos pos_final)
{
    pos_final.y = pos_final.y + 1;
    return pos_final;
}



pos NavigateMatrix(int matrice[8][8], pos pos_init, int size) {
    pos pos_final = pos_init;
    char direction=' ';

    // First step
    if (pos_init.x == -1) {
        pos_final = move_right(pos_final);
        direction = 'R';
    } else if (pos_init.x == size) {
        pos_final = move_left(pos_final);
        direction = 'L';
    } else if (pos_init.y == -1) {
        pos_final = move_down(pos_final);
        direction = 'D';
    } else if (pos_init.y == size) {
        pos_final = move_up(pos_final);
        direction = 'U';
    }

    while (pos_final.x >= 0 && pos_final.x < size && pos_final.y >= 0 && pos_final.y < size)

            {
                switch (direction)
                {
            case 'L':
                switch (matrice[pos_final.y][pos_final.x])
                {
                    case 0:pos_final=move_left(pos_final);break;
                    case 1:pos_final=move_down(pos_final);direction='D';break;
                    case 2:pos_final=move_up(pos_final);direction='U';break;
                }
                break;
            case 'D':
                        switch (matrice[pos_final.y][pos_final.x])
                {
                     case 0:pos_final=move_down(pos_final);break;
                    case 1:pos_final=move_left(pos_final);direction='L';break;
                    case 2:pos_final=move_right(pos_final);direction='R';break;
                }
                break;
            case 'R':
                switch (matrice[pos_final.y][pos_final.x])
                {
                     case 0:pos_final=move_right(pos_final);break;
                    case 1:pos_final=move_up(pos_final);direction='U';break;
                    case 2:pos_final=move_down(pos_final);direction='D';break;
                }
                break;
            case 'U':
                switch (matrice[pos_final.y][pos_final.x])
                {
                   case 0:pos_final=move_up(pos_final);break;
                    case 1:pos_final=move_right(pos_final);direction='R';break;
                    case 2:pos_final=move_left(pos_final);direction='L';break;
                }
                break;
                }
printf("mat[%d][%d]=%d",pos_final.y,pos_final.x,matrice[pos_final.y][pos_final.x]);
printf("direction:%c\n",direction);
            }
    return pos_final;
}

bool verif(pos pos_insert, pos pos_final)
{
    if(pos_insert.x==pos_final.x &&pos_insert.y==pos_final.y)return true;
    else return false;
}
bool pos_insert_valide(pos pos_insert,int size)
{
    if(pos_insert.x<=size && pos_insert.x>=-1 && pos_insert.y<=size && pos_insert.y>=-1)return true;
    else return false;
}

// Fonction de comparaison pour qsort
int comparaisonScores(const void *a, const void *b) {
    return ((Joueur*)b)->score - ((Joueur*)a)->score;
}

void remplir(FILE *f, Joueur *j){
    char buffer[80]; // Buffer pour la date formatée

    // Obtenir le temps actuel et le stocker dans j->timestamp
    time(&j->timestamp);

    // Convertir time_t en struct tm
    struct tm *timeinfo = localtime(&j->timestamp);

    // Formater la date et l'heure
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Ouvrir le fichier en mode append
    f = fopen("scores.txt", "a"); // 'a' pour append (ajouter à la fin du fichier)

    // Vérifier si le fichier est ouvert avec succès
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1); // Utiliser exit car nous sommes dans une fonction void
    }

    // Écrire les données dans le fichier
    fprintf(f, "%s %d %d %ld\n", j->nom, j->score, j->niveau, j->timestamp);

    // Fermer le fichier
    fclose(f);
}


