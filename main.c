#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "bib.h"
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>


int main(int argc, char* argv[]){


    srand(time(NULL));
    //declaration des vars
    bool quit=false,get_answer=false,nxtPartie=false,win;
    char game_state,playmode;
    int size,nbrdiagonal,matrice[8][8],lvl=1,partie=1,tries=0;
    SDL_Rect Record_tab=record_tab;
    SDL_Rect Back_tab=back_tab;
    SDL_Rect Player_tab=player_tab;
    SDL_Rect Machine_tab=machine_tab;
    SDL_Rect Pause_botton=pause_button;
    pos pos_final,pos_init,pos_insert;
    int score;
    int matrice1[8][8];

 atexit(Shutdown);
    //initialisation
    if (!Initialize()){exit(1);}
    SDL_Event event;
    SDL_Renderer* renderer;
    game_state='M';
    nbrdiagonal=3;
    size=3;
    pos_insert.x=-10;
    reset(matrice,size,size);
    add_diagonals(matrice,nbrdiagonal,size,size);
    pos_init=randomizePosInit(size);
    pos_final=NavigateMatrix(matrice,pos_init,size);

Uint32 startTime;
Uint32 currentTime;
Uint32 elapsedTime;
     while (!quit)
        {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
         {
             case SDL_QUIT:
              quit = true;


             case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                   {
                      quit=true;
                   } break;

                if(event.key.keysym.sym == SDLK_SPACE && game_state=='M')
                  {game_state = 'G';}break;

             case SDL_MOUSEBUTTONDOWN:
                if(game_state=='M' && withinrec(event,Player_tab))
                {
                    //printf("donnez le nom du joueur \n");
                    //scanf("%S",joueur.nom);
                    score=0;
                    game_state='G';
                    playmode='P';
                   startTime = SDL_GetTicks();
                }
                if(game_state=='M'&&withinrec(event,Machine_tab))
                {
                    game_state='G';
                    playmode='M';
                    startTime = SDL_GetTicks();
                }
                if(game_state=='M'&&withinrec(event,Record_tab))
                {
                    game_state='R';
                    startTime = SDL_GetTicks();
                }
                if(game_state=='M'&&withinrec(event,Back_tab))
                {
                    game_state='H';
                }

                 if (game_state=='G'&&withinrec(event,home))
                {
                    printf("mlkhu");
                    game_state='M';
                    //init_level
                    nbrdiagonal=3;
                    size=3;
                    pos_insert.x=-10;
                    reset(matrice,size,size);
                    add_diagonals(matrice,nbrdiagonal,size,size);
                    pos_init=randomizePosInit(size);
                    pos_final=NavigateMatrix(matrice,pos_init,size);
                    tries=0;
                }
                if (game_state=='R'&&withinrec(event,Back_tab))
                {
                    game_state='M';
                    //init_level
                   startTime=SDL_GetTicks();
                    nbrdiagonal=3;
                    size=3;
                    pos_insert.x=-10;
                    reset(matrice,size,size);
                    add_diagonals(matrice,nbrdiagonal,size,size);
                    pos_init=randomizePosInit(size);
                    pos_final=NavigateMatrix(matrice,pos_init,size);
                    tries=0;
                }
                if(game_state=='G'&& get_answer==true)
                {
                    pos_insert=Get_pos(event,size);
                    printf("inserted pos:x:%d,y:%d",pos_insert.x,pos_insert.y);
                }
                if(nxtPartie && withinrec(event ,continue_retry))
                {
                    load_lvl(&size,&nbrdiagonal,win,&tries,matrice,&pos_init,&pos_final,&startTime,&pos_insert,&score);
                    nxtPartie=false;
                }
                if (size<3||size>=8)
                {
                    game_state='E';
                }
                if (game_state=='E' && withinrec(event,end))
                {
                    Shutdown ();
                }
                if (game_state=='E' && withinrec(event,restart))
                {
                    game_state='G';
                    //init_lvl
                    startTime=SDL_GetTicks();
                    nbrdiagonal=3;
                    size=3;
                    pos_insert.x=-10;
                    reset(matrice,size,size);
                    add_diagonals(matrice,nbrdiagonal,size,size);
                    pos_init=randomizePosInit(size);
                    pos_final=NavigateMatrix(matrice,pos_init,size);
                    tries=0;
                }
                 if (game_state=='G' && withinrec(event,pause_button))
                {
                    game_state='A';
                }
                 if (game_state =='A' && withinrec(event,resume))
                {
                    game_state='G';
                }
                if (game_state =='A' && withinrec(event,back_to_menu))
                {
                    game_state='M';
                    //init_lvl
                    startTime=SDL_GetTicks();
                    nbrdiagonal=3;
                    size=3;
                    pos_insert.x=-10;
                    reset(matrice,size,size);
                    add_diagonals(matrice,nbrdiagonal,size,size);
                    pos_init=randomizePosInit(size);
                    pos_final=NavigateMatrix(matrice,pos_init,size);
                    tries=0;
                }
                if(game_state=='H'&&withinrec(event,Back_tab))
                {
                    game_state='M';
                }
                if (game_state=='M'&&withinrec(event,interro))
                {
                    game_state='H';
                }
                if (game_state == 'A' && withinrec(event,Exit))
                {
                    Shutdown();
                }

                break;
            }

         }
if(game_state=='G'){
        if (playmode=='P')
        {
    playmode_background(size);
    calcule_progress(size,nbrdiagonal,&lvl,&partie);
    affich_progress(lvl,partie,tries,2000-elapsedTime);
    player_score(score);
    currentTime = SDL_GetTicks();
        elapsedTime = currentTime - startTime;
        if (elapsedTime <= 2000)
                {
                    SDL_addiagonals(renderer,matrice,size);
                }

        else
            {

                //affich position initial
                 Render_pos(pos_init,size,0,0,0,255);
                //listen for answer position done in event loop

                if(!pos_insert_valide(pos_insert,size))get_answer=true;
                else//pos seccefully inserted
                {
                    get_answer=false;//stop listening for answers
                  Render_pos(pos_insert,size,255,0,0,255);//affich pos of the answer
                  win= verif(pos_insert,pos_final);
                  if (win==true)
                  {
                     Render_pos(pos_insert,size,46, 204, 113,255);
                     SDL_addiagonals(renderer,matrice,size);
                  }


                //if win test if better than one of the top 5 if yes listen for player info (name) add it where it belongs//function top_5()

                //affich replay button

                //listen for replay button
                nxtPartie=true;
                }
            }
        }
        if (playmode=='M')
        {
    playmode_background(size);
    currentTime = SDL_GetTicks();
        elapsedTime = currentTime - startTime;
        if (elapsedTime <= 1000)
                {
                    SDL_addiagonals(renderer,matrice,size);
                    machine_creat_matrice(matrice1,size);

                }
            else
            {
                //affich position initial
                Render_pos(pos_init,size,0,0,0,255);
                //affich answer position using navigate matrix & render_pos(answer_tab)
                pos_final=NavigateMatrix(matrice,pos_init,size);
                pos_insert=NavigateMatrix(matrice1,pos_init,size);
                Render_pos(pos_insert,size,46, 204, 113,255);
                SDL_addiagonals(renderer,matrice,size);
                //affich replay button
                nxtPartie=true;
                win= verif(pos_insert,pos_final);

            }

}
            SDL_RenderPresent(renderer);
    }
     if (game_state=='R')
        {
            record_tab_background(size);
        }
        if (game_state=='E')
        {
            restart_end(size);
        }
        if (game_state=='A')
        {
            continue_end();
        }
        if(game_state=='M')
        {
                menu();
        }
        if(game_state=='H')
        {
            help();
        }
    }
    return 0;

}
