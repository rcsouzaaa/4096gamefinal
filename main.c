/********************************************************************************************************
*********************************************************************************************************
**************************************PROJETO FINAL PROGRAMAÇÃO******************************************
****************************************RAFAELA CANDIA SOUZA*********************************************
***********************************************4096GAME**************************************************
*********************************************************************************************************
********************************************************************************************************/
//BIBLIOTECAS//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
//CONSTANTES//
const int SCREEN_W = 450, SCREEN_H = 650, FPS = 10;
//!!Não usar y1 porque há uma função em math.h
//http://www.linuxhowtos.org/manpages/3/y0.htm
int linha=0,coluna=0, rlinha ,rcoluna, nt, x1,x2, y1r, y2, x1_ini, x2_ini, y1_ini, y2_ini,text2x_ini,text2y_ini,text1x_ini,text1y_ini,text2x,text2y, ql=0,qc=0,c1,c2,c3, score=0;
char teste=2, i=0;
float r;
enum teclas {key_up, key_down, key_left, key_right, key_esc, total_teclas};
int Keys[total_teclas];
bool doexit = false;
void randomrafa(int*, int*);
int matriz[5][5]=  {{0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};
//MAIN//
int main(int argc, char **argv)
{
    printf("\nSobre o Jogo:\nBaseado no classico 2048,  o jogo desenvolvido tem como objetivo \nalcancar o numero que da nome ao jogo somando numeros pares \ndentro de uma matriz quadrada. Requer habilidade para fazer \na maior pontuação possível sem preencher a tela toda.\n\nComo Jogar:\nUtilize as setas do teclado para mover os números da matriz de um lado para o outro ou de cima para baixo para realizar as jogadas. Para finalizar o jogo utilize o botão ESC e para recomecar o jogo clique com o mouse em New Game.");
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP  *image   = NULL, *image1  = NULL, *image2  = NULL, *image3  = NULL;
    ALLEGRO_FONT *font1 = NULL, *font2 = NULL;
    ALLEGRO_SAMPLE *sample=NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    if(!al_init())
    {
        return -1;
    }
    if(!al_install_keyboard())
    {
        return -1;
    }
    if(!al_install_audio())
    {
        return -1;
    }
    if(!al_init_acodec_addon())
    {
       return -1;
    }
    if (!al_reserve_samples(10))
    {
        return -1;
    }
    sample = al_load_sample("music.ogg");
    if (!sample)
    {
     printf("Problema ao carregar música music.ogg");  return -1;
    }

    al_play_sample(sample, 1,0,1,ALLEGRO_PLAYMODE_LOOP,NULL);

    if(!al_install_mouse())
    {
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        return -1;
    }
    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        return -1;
    }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    if(!al_init_image_addon())
    {
        return -1;
    }
    font1 = al_load_ttf_font("pirulen.ttf",12,0 );
    if (!font1)
    {
        return -1;
    }
    image = al_load_bitmap("iceblue2.png");
    if(!image)
    {
        return -1;
    }
    image1 = al_load_bitmap("IceBlue1.png");
    if(!image1)
    {
        return -1;
    }
    image2 = al_load_bitmap("NG.png");
    if(!image2)
    {
        return -1;
    }
    image3 = al_load_bitmap("retanrosa.png");
    if(!image2)
    {
        return -1;
    }
    al_draw_bitmap(image,0,0,0);
    al_draw_bitmap(image1,10,10,10);
    al_draw_bitmap(image2,180,45,15);
    al_draw_bitmap(image3,310,45,15);
//FUNÇÃO GERA RETANGULO//
    x1_ini=30.0, y1_ini=170.0, x2_ini=100.0, y2_ini=240;
    x1 = x1_ini,y1r= y1_ini,x2 = x2_ini,y2 = y2_ini;
    for(qc=0; qc<5; qc++)
    {
        for (ql=0; ql<5; ql++)
        {
            al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 211, 193));
            y1r=y1r+80;
            y2=y2+80;
        }
        y1r=y1_ini;
        y2=y2_ini;
        x1=x1+80;
        x2=x2+80;
    }
    font2 = al_load_ttf_font("pirulen.ttf",23,0 );
    if (!font2)
    {
        return -1;
    }
    al_flip_display();
//LOGICA//
    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                for (coluna=0; coluna<5; coluna++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (linha=4; linha>=1; linha--)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha-1][coluna]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha-1][coluna];
                                matriz[linha-1][coluna]=nt;
                            }
                        }
                    }
                }
                for (coluna=0; coluna<5; coluna++)
                {
                    for (linha=0; linha<4; linha++)
                    {
                        if ((matriz[linha][coluna]==matriz[linha+1][coluna])&&(matriz[linha][coluna]!=0))
                        {
                            matriz[linha+1][coluna]+=matriz[linha][coluna];
                            matriz[linha][coluna]=0;
                            linha++;
                        }
                    }
                }
                for (coluna=0; coluna<5; coluna++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (linha=4; linha>=1; linha--)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha-1][coluna]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha-1][coluna];
                                matriz[linha-1][coluna]=nt;
                            }
                        }
                    }
                }
                break;
            case ALLEGRO_KEY_DOWN:
                for (coluna=0; coluna<5; coluna++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (linha=0; linha<4; linha++)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha+1][coluna]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha+1][coluna];
                                matriz[linha+1][coluna]=nt;
                            }
                        }
                    }
                }
                for (coluna=0; coluna<5; coluna++)
                {
                    for (linha=4; linha>=1; linha--)
                    {
                        if ((matriz[linha][coluna]==matriz[linha-1][coluna])&&(matriz[linha][coluna]!=0))
                        {
                            matriz[linha][coluna]+=matriz[linha-1][coluna];
                            matriz[linha-1][coluna]=0;
                            linha--;
                        }
                    }
                }
                for (coluna=0; coluna<5; coluna++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (linha=0; linha<4; linha++)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha+1][coluna]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha+1][coluna];
                                matriz[linha+1][coluna]=nt;
                            }
                        }
                    }
                }
                break;
            case ALLEGRO_KEY_LEFT:
                for (linha=0; linha<5; linha++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (coluna=4; coluna>=1; coluna--)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha][coluna-1]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha][coluna-1];
                                matriz[linha][coluna-1]=nt;
                            }
                        }
                    }
                }
                for (linha=0; linha<5; linha++)
                {
                    for (coluna=0; coluna<4; coluna++)
                    {
                        if ((matriz[linha][coluna]==matriz[linha][coluna+1])&&(matriz[linha][coluna]!=0))
                        {
                            matriz[linha][coluna+1]+=matriz[linha][coluna];
                            matriz[linha][coluna]=0;
                            coluna++;
                        }
                    }
                }
                for (linha=0; linha<5; linha++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (coluna=4; coluna>=1; coluna--)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha][coluna-1]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha][coluna-1];
                                matriz[linha][coluna-1]=nt;
                            }
                        }
                    }
                }
                break;
            case ALLEGRO_KEY_RIGHT:
                for (linha=0; linha<5; linha++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (coluna=0; coluna<4; coluna++)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha][coluna+1]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha][coluna+1];
                                matriz[linha][coluna+1]=nt;
                            }
                        }
                    }
                }
                for (linha=0; linha<5; linha++)
                {
                    for (coluna=4; coluna>=1; coluna--)
                    {
                        if ((matriz[linha][coluna]==matriz[linha][coluna-1])&&(matriz[linha][coluna]!=0))
                        {
                            matriz[linha][coluna-1]+=matriz[linha][coluna];
                            matriz[linha][coluna]=0;
                            coluna--;
                        }
                    }
                }
                for (linha=0; linha<5; linha++)
                {
                    for (i=3; i>=0; i--)
                    {
                        for (coluna=0; coluna<4; coluna++)
                        {
                            if ((matriz[linha][coluna]!=0) && (matriz[linha][coluna+1]==0))
                            {
                                nt=matriz[linha][coluna];
                                matriz[linha][coluna]=matriz[linha][coluna+1];
                                matriz[linha][coluna+1]=nt;
                            }
                        }
                    }
                }
                break;
            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
            }
//GERADOR randomrafa//
            randomrafa(&rcoluna,&rlinha);
            while (matriz[rlinha][rcoluna]!=0)
            {
                randomrafa(&rcoluna,&rlinha);
            }
            matriz[rlinha][rcoluna]=  (rand()%4 == 3)? 4 : 2;

            for (linha=0; linha<=4; linha++)
            {
                for (coluna=0; coluna<=4; coluna++)
                {
                    if (matriz[linha][coluna]!=0)
                        i++;
                }
            }
            if (i==25) {doexit = true;}
//SCORE//
            al_draw_bitmap(image3,310,45,15);
            score=0;
            for(qc=0; qc<5; qc++)
            {
                for (ql=0; ql<5; ql++)
                {
                    score+=matriz[ql][qc];
                }
            }
            al_draw_textf(font1, al_map_rgb(255,255,255),365,68,ALLEGRO_ALIGN_CENTRE,"%i",score);
        }
//FUNÇÃO GERA RETANGULO//
        x1_ini=30.0, y1_ini=170.0, x2_ini=100.0, y2_ini=240;
        x1 = x1_ini,y1r= y1_ini,x2 = x2_ini,y2 = y2_ini;
        for(qc=0; qc<5; qc++)
        {
            for (ql=0; ql<5; ql++)
            {
                if(matriz[ql][qc]==0)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 211, 193));
                }
                else if(matriz[ql][qc]==2)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 182, 151));
                }
                else if(matriz[ql][qc]==4)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 141, 132));
                }
                else if(matriz[ql][qc]==8)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 211, 100));
                }
                else if(matriz[ql][qc]==16)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 128, 1));
                }
                else if(matriz[ql][qc]==32)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 0, 128));
                }
                else if(matriz[ql][qc]==64)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 0, 30));
                }
                else if(matriz[ql][qc]==128)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(108, 128, 255));
                }
                else if(matriz[ql][qc]==256)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(108, 188, 255));
                }
                else if(matriz[ql][qc]==512)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(15, 203, 80));
                }
                else if(matriz[ql][qc]==1024)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(140, 255, 198));
                }
                else if(matriz[ql][qc]==2048)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 255, 26));
                }
                else if(matriz[ql][qc]==4069)
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 0, 0));
                }
                else
                {
                    al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 225, 255));
                }
                y1r=y1r+80;
                y2=y2+80;
            }
            y1r=y1_ini;
            y2=y2_ini;
            x1=x1+80;
            x2=x2+80;
        }
//FUNÇÃO GERA MATRIZ//
        text2x_ini=64, text2y_ini=192;
        text2x=text2x_ini, text2y=text2y_ini;
        for(qc=0; qc<5; qc++)
        {
            for (ql=0; ql<5; ql++)
            {
                if (matriz[ql][qc]==0)
                {
                    c1=255, c2=211, c3=193;
                }
                else
                {
                    c1=255, c2=255, c3=255;
                }
                al_draw_textf(font2, al_map_rgb(c1,c2,c3),text2x,text2y,ALLEGRO_ALIGN_CENTRE, "%i",matriz[ql][qc]);
                text2y=text2y+80;
            }
            text2y=text2y_ini;
            text2x=text2x+80;
            al_flip_display();
        }
//MOUSE EVENT//
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(ev.mouse.x >= al_get_bitmap_width(image2) &&
                    ev.mouse.x <= SCREEN_W -10 && ev.mouse.y <= SCREEN_H - 10 &&
                    ev.mouse.y >= al_get_bitmap_height(image2) - 10)
            {
                al_draw_bitmap(image3,310,45,15);
                score=0;
                text2x_ini=64, text2y_ini=192;
                text2x=text2x_ini, text2y=text2y_ini;

                for(qc=0; qc<5; qc++)
                {
                    for (ql=0; ql<5; ql++)
                    {
                        c1=255, c2=211, c3=193;
                        matriz[ql][qc]=0;
                        al_draw_textf(font2, al_map_rgb(c1,c2,c3),text2x,text2y,ALLEGRO_ALIGN_CENTRE, "%i",matriz[ql][qc]);
                        text2y=text2y+80;
                    }
                    text2y=text2y_ini;
                    text2x=text2x+80;
                }

                x1_ini=30.0, y1_ini=170.0, x2_ini=100.0, y2_ini=240;
                x1 = x1_ini,y1r= y1_ini,x2 = x2_ini,y2 = y2_ini;
                for(qc=0; qc<5; qc++)
                {
                    for (ql=0; ql<5; ql++)
                    {
                        al_draw_filled_rectangle(x1, y1r, x2, y2, al_map_rgb(255, 211, 193));
                        y1r=y1r+80;
                        y2=y2+80;
                    }
                    y1r=y1_ini;
                    y2=y2_ini;
                    x1=x1+80;
                    x2=x2+80;
                }
                al_flip_display();
            }
        }
    }
    system("cls");
    printf("GAME OVER!");
    al_destroy_event_queue(event_queue);
    al_destroy_sample(sample);
    al_destroy_display(display);
    return 0;
}
//GERA  NÚMEROS ALEATÓRIOS PARA A MATRIZ//
void randomrafa(int *c, int *l)
{
    int r;
    r = rand() % 99;
    *c = (r%10)%5;
    *l = (r/10)%5;
}
