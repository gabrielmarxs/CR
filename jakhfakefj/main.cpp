#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#define tela_h 600
#define tela_w 800
#define FPS 10

SDL_Surface* tela;
SDL_Surface* telainicial;
SDL_Surface* fundo;
SDL_Surface* plataforma1;
SDL_Surface* plataforma2;
SDL_Surface* plataforma3;
SDL_Surface* plataforma4;
SDL_Surface* escada;
SDL_Surface* escada2;
SDL_Surface* escada3;
SDL_Surface* escada4;
SDL_Surface* personagem[2][7];
SDL_Surface* princesa;
SDL_Surface* vilao;
SDL_Surface* barril;
SDL_Surface* gameover;

SDL_Rect plataforma1_rect[32];
SDL_Rect plataforma2_rect[32];
SDL_Rect plataforma3_rect[32];
SDL_Rect plataforma4_rect[16];
SDL_Rect personagem_rect;
SDL_Rect fundo_rect;
SDL_Rect escada_rect;
SDL_Rect escada2_rect;
SDL_Rect escada3_rect;
SDL_Rect escada4_rect;
SDL_Rect princesa_rect;
SDL_Rect vilao_rect;
SDL_Rect barril_rect[5];
SDL_Rect gameover_rect;
SDL_Rect telainicial_rect;

int emovimento = 0;
int direcao = 1;
int j = 0;
int b=0;
bool teclaenter = 0;
Uint32 start;

void blit()
{
    int i;

    SDL_FillRect(tela,0,SDL_MapRGB(tela->format,0,0,0));

    SDL_BlitSurface(fundo,0,tela,&fundo_rect);

    SDL_BlitSurface(escada,0,tela,&escada_rect);
    SDL_BlitSurface(escada2,0,tela,&escada2_rect);
    SDL_BlitSurface(escada3,0,tela,&escada3_rect);
    SDL_BlitSurface(escada4,0,tela,&escada4_rect);

    for(i=0; i<16; i++)
    {
        SDL_BlitSurface(plataforma1,0,tela,&plataforma1_rect[i]);
    }
    for(i=16; i<31; i++)
    {
        SDL_BlitSurface(plataforma1,0,tela,&plataforma1_rect[i]);
    }

    for(i=0; i<16; i++)
    {
        SDL_BlitSurface(plataforma3,0,tela,&plataforma1_rect[i]);
    }
    for(i=16; i<31; i++)
    {
        SDL_BlitSurface(plataforma3,0,tela,&plataforma1_rect[i]);
    }

    for(i=16; i>=0; i--)
    {
        SDL_BlitSurface(plataforma2,0,tela,&plataforma2_rect[i]);
    }
    for(i=28; i>16; i--)
    {
        SDL_BlitSurface(plataforma2,0,tela,&plataforma2_rect[i]);
    }
    for(i=2; i<16; i++)
    {
        SDL_BlitSurface(plataforma3,0,tela,&plataforma3_rect[i]);
    }
    for(i=16; i<31; i++)
    {
        SDL_BlitSurface(plataforma3,0,tela,&plataforma3_rect[i]);
    }
    for(i=2; i<16; i++)
    {
        SDL_BlitSurface(plataforma4,0,tela,&plataforma4_rect[i]);
    }


    SDL_BlitSurface(personagem[direcao][j],0,tela,&personagem_rect);

    SDL_BlitSurface(princesa,0,tela,&princesa_rect);

    SDL_BlitSurface(vilao,0,tela,&vilao_rect);

    SDL_BlitSurface(barril,0,tela,&barril_rect[0]);

    SDL_BlitSurface(barril,0,tela,&barril_rect[1]);

    SDL_BlitSurface(barril,0,tela,&barril_rect[2]);

    SDL_BlitSurface(barril,0,tela,&barril_rect[3]);

    SDL_BlitSurface(barril,0,tela,&barril_rect[4]);

    SDL_Flip(tela);
}

int main(int argc,char ** argv)
{
    int i;
    int jota=0;
    int subindo = 0;
    SDL_Event evento;
    tela = SDL_SetVideoMode(tela_w,tela_h,16,SDL_HWSURFACE || SDL_DOUBLEBUF);
    int espaco_ant = 0;
    if(!tela)
    {
        printf("Deu erro na tela: %s\n",SDL_GetError());
        return 1;
    }

    personagem[0][0] = IMG_Load("aluno01.png");
    personagem[0][1] = IMG_Load("aluno02.png");
    personagem[0][2] = IMG_Load("aluno03.png");
    personagem[0][3] = IMG_Load("aluno04.png");
    personagem[0][4] = IMG_Load("aluno05.png");
    personagem[0][5] = IMG_Load("aluno06.png");
    personagem[0][6] = IMG_Load("aluno00.png");
    personagem[1][0] = IMG_Load("aluno11.png");
    personagem[1][1] = IMG_Load("aluno12.png");
    personagem[1][2] = IMG_Load("aluno13.png");
    personagem[1][3] = IMG_Load("aluno14.png");
    personagem[1][4] = IMG_Load("aluno15.png");
    personagem[1][5] = IMG_Load("aluno16.png");
    personagem[1][6] = IMG_Load("aluno10.png");

    fundo = SDL_LoadBMP("rural.bmp");

    if(!fundo)
    {
        printf("DEU ERRO no background:%s\n",SDL_GetError());
        return 1;
    }

    plataforma1 = SDL_LoadBMP("plataforma1.bmp");
    if(!plataforma1)
    {
        printf("DEU ERRO na plataforma1: %s \n",SDL_GetError());
        return 1;
    }

    plataforma2 = SDL_LoadBMP("plataforma1.bmp");
    if(!plataforma2)
    {
        printf("DEU ERRO na plataforma2: %s \n",SDL_GetError());
        return 1;
    }

    plataforma3 = SDL_LoadBMP("plataforma1.bmp");
    if(!plataforma3)
    {
        printf("Deu erro na plataforma3: %s \n",SDL_GetError());
        return 1;
    }

    plataforma4 = SDL_LoadBMP("plataforma1.bmp");
    if(!plataforma4)
    {
        printf("Deu erro na plataforma4: %s \n",SDL_GetError());
        return 1;
    }

    escada = IMG_Load("escada.png");
    if(!escada)
    {
        printf("Deu erro na escada: %s \n",SDL_GetError());
        return 1;
    }

    escada2 = IMG_Load("escada.png");
    if(!escada2)
    {
        printf("Deu erro na escada2: %s \n",SDL_GetError());
        return 1;
    }
    escada3 = IMG_Load("escada.png");
    if(!escada3)
    {
        printf("Deu erro na escada3: %s \n",SDL_GetError());
        return 1;
    }
    escada4 = IMG_Load("escada.png");
    if(!escada4)
    {
        printf("Deu erro na escada4: %s \n",SDL_GetError());
        return 1;
    }

    princesa = SDL_LoadBMP("princesa.bmp");
    if(!princesa)
    {
        printf("Deu erro na princesa: %s \n",SDL_GetError());
        return 1;
    }

    vilao = IMG_Load("vilao.png");
    if(!vilao)
    {
        printf("Deu erro no vilao: %s \n",SDL_GetError());
        return 1;
    }

    barril = IMG_Load("barril.png");
    if(!barril)
    {
        printf("Deu erro no barril: %s \n",SDL_GetError());
        return 1;
    }

    gameover = IMG_Load("gameover.png");
    telainicial = IMG_Load("telainicial.png");

    Mix_Music *music = NULL;
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    music = Mix_LoadMUS("anotherworld.mp3");
    Mix_PlayMusic(music,1);


    escada_rect.w = escada->w;
    escada_rect.h = escada->h;
    escada_rect.x = 640;
    escada_rect.y = 431;

    escada2_rect.w = escada2->w;
    escada2_rect.h = escada2->h;
    escada2_rect.x = 94;
    escada2_rect.y = 269;

    escada3_rect.w = escada3->w;
    escada3_rect.h = escada3->h;
    escada3_rect.x = 553;
    escada3_rect.y = 107;

    escada4_rect.w = escada4->w;
    escada4_rect.h = escada4->h;
    escada4_rect.x = 650;
    escada4_rect.y = 107;

    fundo_rect.w = fundo->w;
    fundo_rect.h = fundo->h;
    fundo_rect.x = 0;
    fundo_rect.y = 0;

    plataforma1_rect[0].w = plataforma1->w;
    plataforma1_rect[0].h = plataforma1->h;
    for(i=0; i<16; i++)
    {
        plataforma1_rect[i].x = i*25;
        plataforma1_rect[i].y = 585-i;
    }
    for(i=16; i<31; i++)
    {
        plataforma1_rect[i].x = i*25;
        plataforma1_rect[i].y = 592-(i*1.5);
    }

    plataforma2_rect[0].w = plataforma2->w;
    plataforma2_rect[0].h = plataforma2->h;
    for(i=16; i>=0; i--)
    {
        plataforma2_rect[i].x = i*25;
        plataforma2_rect[i].y = 385 + (i*1.5);
    }
    for(i=28; i>16; i--)
    {
        plataforma2_rect[i].x = i*25;
        plataforma2_rect[i].y = 392 + i;
    }

    plataforma3_rect[0].w = plataforma3->w;
    plataforma3_rect[0].h = plataforma3->h;
    for(i=2; i<16; i++)
    {
        plataforma3_rect[i].x = i*25;
        plataforma3_rect[i].y = 258-i;
    }
    for(i=16; i<31; i++)
    {
        plataforma3_rect[i].x = i*25;
        plataforma3_rect[i].y = 265-(i*1.5);
    }

    plataforma4_rect[0].w = plataforma4->w;
    plataforma4_rect[0].h = plataforma4->h;
    for(i=2; i<16; i++)
    {
        plataforma4_rect[i].x = 294 + i*25;
        plataforma4_rect[i].y = 92;
    }

    personagem_rect.w = personagem[0][0]->w;

    personagem_rect.h = personagem[0][0]->h;

    personagem_rect.x = 0;

    personagem_rect.y = (tela_h)-(personagem[0][0]->h)-(plataforma1->h)+5;

    princesa_rect.w = princesa->w;
    princesa_rect.h = princesa->h;
    princesa_rect.x = 440;
    princesa_rect.y = 10;

    vilao_rect.w = vilao->w;
    vilao_rect.h = vilao->h;
    vilao_rect.x = 600;
    vilao_rect.y = 16;

    barril_rect[0].w = barril->w;
    barril_rect[0].h = barril->h;
    barril_rect[0].x = 650;
    barril_rect[0].y = 49;

    barril_rect[1].w = barril->w;
    barril_rect[1].h = barril->h;
    barril_rect[1].x = 850;
    barril_rect[1].y = 49;

    barril_rect[2].w = barril->w;
    barril_rect[2].h = barril->h;
    barril_rect[2].x = 850;
    barril_rect[2].y = 49;

    barril_rect[3].w = barril->w;
    barril_rect[3].h = barril->h;
    barril_rect[3].x = 850;
    barril_rect[3].y = 49;

    barril_rect[4].w = barril->w;
    barril_rect[4].h = barril->h;
    barril_rect[4].x = 850;
    barril_rect[4].y = 49;

    int saida = 0;

    bool tecladireita = 0;

    bool teclaesquerda = 0;

    bool teclabaixo = 0;

    bool teclacima = 0;

    bool teclaespaco = 0;


    while(saida!=1)
    {
        start = SDL_GetTicks();

        while(SDL_PollEvent(&evento))
        {
            if(evento.type==SDL_QUIT)
                saida = 1;

            if(evento.type==SDL_KEYDOWN)
            {
                if(evento.key.keysym.sym==SDLK_RIGHT)
                {
                    tecladireita = 1;
                    direcao=1;
                    emovimento=1;
                }
                if(evento.key.keysym.sym==SDLK_LEFT)
                {
                    teclaesquerda = 1;
                    direcao=0;
                    emovimento=1;
                }
                if(evento.key.keysym.sym==SDLK_UP)
                    teclacima = 1;
                if(evento.key.keysym.sym==SDLK_DOWN)
                    teclabaixo = 1;
                if(evento.key.keysym.sym==SDLK_ESCAPE)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    teclaenter = 1;
                if(evento.key.keysym.sym==SDLK_SPACE)
                    teclaespaco = 1;
            }

            if(evento.type==SDL_KEYUP)
            {
                emovimento=0;
                if(evento.key.keysym.sym==SDLK_RIGHT)
                    tecladireita = 0;
                if(evento.key.keysym.sym==SDLK_LEFT)
                    teclaesquerda = 0;
                if(evento.key.keysym.sym==SDLK_UP)
                    teclacima = 0;
                if(evento.key.keysym.sym==SDLK_DOWN)
                    teclabaixo = 0;
            }
        }
        if(!teclaenter)
        {
            SDL_BlitSurface(telainicial,0,tela,&telainicial_rect);
            SDL_Flip(tela);
        }
        else
        {

        if(emovimento && !teclaespaco)
        {
            jota++;
            j = (jota/10)%6;
        }

        if(jota==120)
            jota=60;
        if(!emovimento)
        {
            j=6;
        }

        if(tecladireita && personagem_rect.y >= escada_rect.y+35 && !teclaespaco)
        {
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[0].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[0].x+10)
            {
                personagem_rect.y = plataforma1_rect[0].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[1].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[1].x+10)
            {
                personagem_rect.y = plataforma1_rect[1].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[2].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[2].x+10)
            {
                personagem_rect.y = plataforma1_rect[2].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[3].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[3].x+10)
            {
                personagem_rect.y = plataforma1_rect[3].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[4].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[4].x+10)
            {
                personagem_rect.y = plataforma1_rect[4].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[5].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[5].x+10)
            {
                personagem_rect.y = plataforma1_rect[5].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[6].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[6].x+10)
            {
                personagem_rect.y = plataforma1_rect[6].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[7].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[7].x+10)
            {
                personagem_rect.y = plataforma1_rect[7].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[8].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[8].x+10)
            {
                personagem_rect.y = plataforma1_rect[8].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[9].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[9].x+10)
            {
                personagem_rect.y = plataforma1_rect[9].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[10].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[10].x+10)
            {
                personagem_rect.y = plataforma1_rect[10].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[11].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[11].x+10)
            {
                personagem_rect.y = plataforma1_rect[11].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[12].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[12].x+10)
            {
                personagem_rect.y = plataforma1_rect[12].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[13].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[13].x+10)
            {
                personagem_rect.y = plataforma1_rect[13].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[14].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[14].x+10)
            {
                personagem_rect.y = plataforma1_rect[14].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[17].x+10)
            {
                personagem_rect.y = plataforma1_rect[17].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[16].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[16].x+10)
            {
                personagem_rect.y = plataforma1_rect[16].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[17].x+10)
            {
                personagem_rect.y = plataforma1_rect[17].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[18].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[18].x+10)
            {
                personagem_rect.y = plataforma1_rect[18].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[19].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[19].x+10)
            {
                personagem_rect.y = plataforma1_rect[19].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[20].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[20].x+10)
            {
                personagem_rect.y = plataforma1_rect[20].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[21].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[21].x+10)
            {
                personagem_rect.y = plataforma1_rect[21].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[22].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[22].x+10)
            {
                personagem_rect.y = plataforma1_rect[22].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[23].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[23].x+10)
            {
                personagem_rect.y = plataforma1_rect[23].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[24].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[24].x+10)
            {
                personagem_rect.y = plataforma1_rect[24].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[27].x+10)
            {
                personagem_rect.y = plataforma1_rect[27].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[26].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[26].x+10)
            {
                personagem_rect.y = plataforma1_rect[26].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[27].x+10)
            {
                personagem_rect.y = plataforma1_rect[27].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[28].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[28].x+10)
            {
                personagem_rect.y = plataforma1_rect[28].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[29].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[29].x+10)
            {
                personagem_rect.y = plataforma1_rect[29].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[30].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[30].x+10)
            {
                personagem_rect.y = plataforma1_rect[30].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[31].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[31].x+10)
            {
                personagem_rect.y = plataforma1_rect[31].y - personagem[0][0]->h+7;
            }


            personagem_rect.x = personagem_rect.x + 1.8;
        }
        if(teclaesquerda && personagem_rect.y >= escada_rect.y+35 && !teclaespaco)
        {
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[0].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[0].x+10)
            {
                personagem_rect.y = plataforma1_rect[0].y - personagem[0][0]->h + 8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[1].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[1].x+10)
            {
                personagem_rect.y = plataforma1_rect[1].y - personagem[0][0]->h + 8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[2].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[2].x+10)
            {
                personagem_rect.y = plataforma1_rect[2].y - personagem[0][0]->h + 8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[3].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[3].x+10)
            {
                personagem_rect.y = plataforma1_rect[3].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[4].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[4].x+10)
            {
                personagem_rect.y = plataforma1_rect[4].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[5].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[5].x+10)
            {
                personagem_rect.y = plataforma1_rect[5].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[6].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[6].x+10)
            {
                personagem_rect.y = plataforma1_rect[6].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[7].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[7].x+10)
            {
                personagem_rect.y = plataforma1_rect[7].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[8].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[8].x+10)
            {
                personagem_rect.y = plataforma1_rect[8].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[9].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[9].x+10)
            {
                personagem_rect.y = plataforma1_rect[9].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[10].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[10].x+10)
            {
                personagem_rect.y = plataforma1_rect[10].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[11].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[11].x+10)
            {
                personagem_rect.y = plataforma1_rect[11].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[12].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[12].x+10)
            {
                personagem_rect.y = plataforma1_rect[12].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[13].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[13].x+10)
            {
                personagem_rect.y = plataforma1_rect[13].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[14].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[14].x+10)
            {
                personagem_rect.y = plataforma1_rect[14].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[15].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[15].x+10)
            {
                personagem_rect.y = plataforma1_rect[15].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[16].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[16].x+10)
            {
                personagem_rect.y = plataforma1_rect[16].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[17].x+10)
            {
                personagem_rect.y = plataforma1_rect[17].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[18].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[18].x+10)
            {
                personagem_rect.y = plataforma1_rect[18].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[19].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[19].x+10)
            {
                personagem_rect.y = plataforma1_rect[19].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[20].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[20].x+10)
            {
                personagem_rect.y = plataforma1_rect[20].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[21].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[21].x+10)
            {
                personagem_rect.y = plataforma1_rect[21].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[22].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[22].x+10)
            {
                personagem_rect.y = plataforma1_rect[22].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[23].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[23].x+10)
            {
                personagem_rect.y = plataforma1_rect[23].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[24].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[24].x+10)
            {
                personagem_rect.y = plataforma1_rect[24].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[25].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[25].x+10)
            {
                personagem_rect.y = plataforma1_rect[25].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[26].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[26].x+10)
            {
                personagem_rect.y = plataforma1_rect[26].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[27].x+10)
            {
                personagem_rect.y = plataforma1_rect[27].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[28].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[28].x+10)
            {
                personagem_rect.y = plataforma1_rect[28].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[29].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[29].x+10)
            {
                personagem_rect.y = plataforma1_rect[29].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[30].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[30].x+10)
            {
                personagem_rect.y = plataforma1_rect[30].y - personagem[0][0]->h+8;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma1_rect[31].x && personagem_rect.x + personagem[0][0]->w <= plataforma1_rect[31].x+10)
            {
                personagem_rect.y = plataforma1_rect[31].y - personagem[0][0]->h+8;
            }
            personagem_rect.x -= 1;
        }
        if(teclacima && personagem_rect.x >= escada_rect.x-10 && personagem_rect.x <= escada_rect.x+25 && personagem_rect.y >= escada_rect.y-83 && personagem_rect.y <= escada_rect.y+70)
        {
            personagem_rect.y -= 1;
        }
        if(tecladireita && personagem_rect.y <= escada_rect.y-75 && personagem_rect.y >= escada2_rect.y+35 && !teclaespaco)
        {
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[0].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[0].x+10)
            {
                personagem_rect.y = plataforma2_rect[0].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[1].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[1].x+10)
            {
                personagem_rect.y = plataforma2_rect[1].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[2].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[2].x+10)
            {
                personagem_rect.y = plataforma2_rect[2].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[3].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[3].x+10)
            {
                personagem_rect.y = plataforma2_rect[3].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[4].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[4].x+10)
            {
                personagem_rect.y = plataforma2_rect[4].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[5].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[5].x+10)
            {
                personagem_rect.y = plataforma2_rect[5].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[6].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[6].x+10)
            {
                personagem_rect.y = plataforma2_rect[6].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[7].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[7].x+10)
            {
                personagem_rect.y = plataforma2_rect[7].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[8].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[8].x+10)
            {
                personagem_rect.y = plataforma2_rect[8].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[9].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[9].x+10)
            {
                personagem_rect.y = plataforma2_rect[9].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[10].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[10].x+10)
            {
                personagem_rect.y = plataforma2_rect[10].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[11].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[11].x+10)
            {
                personagem_rect.y = plataforma2_rect[11].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[12].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[12].x+10)
            {
                personagem_rect.y = plataforma2_rect[12].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[13].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[13].x+10)
            {
                personagem_rect.y = plataforma2_rect[13].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[14].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[14].x+10)
            {
                personagem_rect.y = plataforma2_rect[14].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[15].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[15].x+10)
            {
                personagem_rect.y = plataforma2_rect[15].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[16].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[16].x+10)
            {
                personagem_rect.y = plataforma2_rect[16].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[17].x+10)
            {
                personagem_rect.y = plataforma2_rect[17].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[18].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[18].x+10)
            {
                personagem_rect.y = plataforma2_rect[18].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[19].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[19].x+10)
            {
                personagem_rect.y = plataforma2_rect[19].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[20].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[20].x+10)
            {
                personagem_rect.y = plataforma2_rect[20].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[21].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[21].x+10)
            {
                personagem_rect.y = plataforma2_rect[21].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[22].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[22].x+10)
            {
                personagem_rect.y = plataforma2_rect[22].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[23].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[23].x+10)
            {
                personagem_rect.y = plataforma2_rect[23].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[24].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[24].x+10)
            {
                personagem_rect.y = plataforma2_rect[24].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[25].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[25].x+10)
            {
                personagem_rect.y = plataforma2_rect[25].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[26].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[26].x+10)
            {
                personagem_rect.y = plataforma2_rect[26].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[27].x+10)
            {
                personagem_rect.y = plataforma2_rect[27].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[28].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[28].x+10)
            {
                personagem_rect.y = plataforma2_rect[28].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[29].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[29].x+10)
            {
                personagem_rect.y = plataforma2_rect[29].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[30].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[30].x+10)
            {
                personagem_rect.y = plataforma2_rect[30].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[31].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[31].x+10)
            {
                personagem_rect.y = plataforma2_rect[31].y - personagem[0][0]->h+7;
            }
            personagem_rect.x += 1.8;
        }
        if(teclaesquerda && personagem_rect.y <= escada_rect.y-75 && personagem_rect.y >= escada2_rect.y+35 && !teclaespaco)
        {
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[0].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[0].x+10)
            {
                personagem_rect.y = plataforma2_rect[0].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[1].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[1].x+10)
            {
                personagem_rect.y = plataforma2_rect[1].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[2].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[2].x+10)
            {
                personagem_rect.y = plataforma2_rect[2].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[3].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[3].x+10)
            {
                personagem_rect.y = plataforma2_rect[3].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[4].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[4].x+10)
            {
                personagem_rect.y = plataforma2_rect[4].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[5].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[5].x+10)
            {
                personagem_rect.y = plataforma2_rect[5].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[6].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[6].x+10)
            {
                personagem_rect.y = plataforma2_rect[6].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[7].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[7].x+10)
            {
                personagem_rect.y = plataforma2_rect[7].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[8].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[8].x+10)
            {
                personagem_rect.y = plataforma2_rect[8].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[9].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[9].x+10)
            {
                personagem_rect.y = plataforma2_rect[9].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[10].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[10].x+10)
            {
                personagem_rect.y = plataforma2_rect[10].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[11].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[11].x+10)
            {
                personagem_rect.y = plataforma2_rect[11].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[12].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[12].x+10)
            {
                personagem_rect.y = plataforma2_rect[12].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[13].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[13].x+10)
            {
                personagem_rect.y = plataforma2_rect[13].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[14].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[14].x+10)
            {
                personagem_rect.y = plataforma2_rect[14].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[15].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[15].x+10)
            {
                personagem_rect.y = plataforma2_rect[15].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[16].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[16].x+10)
            {
                personagem_rect.y = plataforma2_rect[16].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[17].x+10)
            {
                personagem_rect.y = plataforma2_rect[17].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[18].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[18].x+10)
            {
                personagem_rect.y = plataforma2_rect[18].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[19].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[19].x+10)
            {
                personagem_rect.y = plataforma2_rect[19].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[20].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[20].x+10)
            {
                personagem_rect.y = plataforma2_rect[20].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[21].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[21].x+10)
            {
                personagem_rect.y = plataforma2_rect[21].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[22].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[22].x+10)
            {
                personagem_rect.y = plataforma2_rect[22].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[23].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[23].x+10)
            {
                personagem_rect.y = plataforma2_rect[23].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[24].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[24].x+10)
            {
                personagem_rect.y = plataforma2_rect[24].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[25].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[25].x+10)
            {
                personagem_rect.y = plataforma2_rect[25].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[26].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[26].x+10)
            {
                personagem_rect.y = plataforma2_rect[26].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[27].x+10)
            {
                personagem_rect.y = plataforma2_rect[27].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[28].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[28].x+10)
            {
                personagem_rect.y = plataforma2_rect[28].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[29].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[29].x+10)
            {
                personagem_rect.y = plataforma2_rect[29].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[30].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[30].x+10)
            {
                personagem_rect.y = plataforma2_rect[30].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma2_rect[31].x && personagem_rect.x + personagem[0][0]->w <= plataforma2_rect[31].x+10)
            {
                personagem_rect.y = plataforma2_rect[31].y - personagem[0][0]->h+6;
            }

            personagem_rect.x -= 1;
        }
        if(tecladireita && personagem_rect.y <= escada2_rect.y-75 && !teclaespaco)
        {
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[0].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[0].x+10)
            {
                personagem_rect.y = plataforma3_rect[0].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[1].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[1].x+10)
            {
                personagem_rect.y = plataforma3_rect[1].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[2].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[2].x+10)
            {
                personagem_rect.y = plataforma3_rect[2].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[3].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[3].x+10)
            {
                personagem_rect.y = plataforma3_rect[3].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[4].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[4].x+10)
            {
                personagem_rect.y = plataforma3_rect[4].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[5].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[5].x+10)
            {
                personagem_rect.y = plataforma3_rect[5].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[6].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[6].x+10)
            {
                personagem_rect.y = plataforma3_rect[6].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[7].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[7].x+10)
            {
                personagem_rect.y = plataforma3_rect[7].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[8].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[8].x+10)
            {
                personagem_rect.y = plataforma3_rect[8].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[9].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[9].x+10)
            {
                personagem_rect.y = plataforma3_rect[9].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[10].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[10].x+10)
            {
                personagem_rect.y = plataforma3_rect[10].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[11].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[11].x+10)
            {
                personagem_rect.y = plataforma3_rect[11].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[12].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[12].x+10)
            {
                personagem_rect.y = plataforma3_rect[12].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[13].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[13].x+10)
            {
                personagem_rect.y = plataforma3_rect[13].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[14].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[14].x+10)
            {
                personagem_rect.y = plataforma3_rect[14].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[15].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[15].x+10)
            {
                personagem_rect.y = plataforma3_rect[15].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[16].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[16].x+10)
            {
                personagem_rect.y = plataforma3_rect[16].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[17].x+10)
            {
                personagem_rect.y = plataforma3_rect[17].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[18].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[18].x+10)
            {
                personagem_rect.y = plataforma3_rect[18].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[19].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[19].x+10)
            {
                personagem_rect.y = plataforma3_rect[19].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[20].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[20].x+10)
            {
                personagem_rect.y = plataforma3_rect[20].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[21].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[21].x+10)
            {
                personagem_rect.y = plataforma3_rect[21].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[22].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[22].x+10)
            {
                personagem_rect.y = plataforma3_rect[22].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[23].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[23].x+10)
            {
                personagem_rect.y = plataforma3_rect[23].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[24].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[24].x+10)
            {
                personagem_rect.y = plataforma3_rect[24].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[25].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[25].x+10)
            {
                personagem_rect.y = plataforma3_rect[25].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[26].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[26].x+10)
            {
                personagem_rect.y = plataforma3_rect[26].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[27].x+10)
            {
                personagem_rect.y = plataforma3_rect[27].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[28].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[28].x+10)
            {
                personagem_rect.y = plataforma3_rect[28].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[29].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[29].x+10)
            {
                personagem_rect.y = plataforma3_rect[29].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[30].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[30].x+10)
            {
                personagem_rect.y = plataforma3_rect[30].y - personagem[0][0]->h+7;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[31].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[31].x+10)
            {
                personagem_rect.y = plataforma3_rect[31].y - personagem[0][0]->h+7;
            }
            personagem_rect.x += 1.8;
        }
        if(teclaesquerda && personagem_rect.y <= escada2_rect.y-75 && !teclaespaco)
        {
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[0].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[0].x+10)
            {
                personagem_rect.y = plataforma3_rect[0].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[1].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[1].x+10)
            {
                personagem_rect.y = plataforma3_rect[1].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[2].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[2].x+10)
            {
                personagem_rect.y = plataforma3_rect[2].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[3].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[3].x+10)
            {
                personagem_rect.y = plataforma3_rect[3].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[4].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[4].x+10)
            {
                personagem_rect.y = plataforma3_rect[4].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[5].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[5].x+10)
            {
                personagem_rect.y = plataforma3_rect[5].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[6].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[6].x+10)
            {
                personagem_rect.y = plataforma3_rect[6].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[7].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[7].x+10)
            {
                personagem_rect.y = plataforma3_rect[7].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[8].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[8].x+10)
            {
                personagem_rect.y = plataforma3_rect[8].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[9].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[9].x+10)
            {
                personagem_rect.y = plataforma3_rect[9].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[10].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[10].x+10)
            {
                personagem_rect.y = plataforma3_rect[10].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[11].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[11].x+10)
            {
                personagem_rect.y = plataforma3_rect[11].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[12].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[12].x+10)
            {
                personagem_rect.y = plataforma3_rect[12].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[13].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[13].x+10)
            {
                personagem_rect.y = plataforma3_rect[13].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[14].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[14].x+10)
            {
                personagem_rect.y = plataforma3_rect[14].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[15].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[15].x+10)
            {
                personagem_rect.y = plataforma3_rect[15].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[16].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[16].x+10)
            {
                personagem_rect.y = plataforma3_rect[16].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[17].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[17].x+10)
            {
                personagem_rect.y = plataforma3_rect[17].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[18].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[18].x+10)
            {
                personagem_rect.y = plataforma3_rect[18].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[19].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[19].x+10)
            {
                personagem_rect.y = plataforma3_rect[19].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[20].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[20].x+10)
            {
                personagem_rect.y = plataforma3_rect[20].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[21].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[21].x+10)
            {
                personagem_rect.y = plataforma3_rect[21].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[22].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[22].x+10)
            {
                personagem_rect.y = plataforma3_rect[22].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[23].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[23].x+10)
            {
                personagem_rect.y = plataforma3_rect[23].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[24].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[24].x+10)
            {
                personagem_rect.y = plataforma3_rect[24].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[25].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[25].x+10)
            {
                personagem_rect.y = plataforma3_rect[25].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[26].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[26].x+10)
            {
                personagem_rect.y = plataforma3_rect[26].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[27].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[27].x+10)
            {
                personagem_rect.y = plataforma3_rect[27].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[28].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[28].x+10)
            {
                personagem_rect.y = plataforma3_rect[28].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[29].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[29].x+10)
            {
                personagem_rect.y = plataforma3_rect[29].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[30].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[30].x+10)
            {
                personagem_rect.y = plataforma3_rect[30].y - personagem[0][0]->h+6;
            }
            if(personagem_rect.x + personagem[0][0]->w >= plataforma3_rect[31].x && personagem_rect.x + personagem[0][0]->w <= plataforma3_rect[31].x+10)
            {
                personagem_rect.y = plataforma3_rect[31].y - personagem[0][0]->h+6;
            }

            personagem_rect.x -= 1;
        }
        if(teclabaixo && personagem_rect.x >= escada_rect.x-10 && personagem_rect.x <= escada_rect.x+25 && personagem_rect.y <= escada_rect.y+45)
        {
            personagem_rect.y += 1.8;
        }
        if(teclacima && personagem_rect.x >= escada2_rect.x-10 && personagem_rect.x <= escada2_rect.x+25 && personagem_rect.y >= escada2_rect.y-83 && personagem_rect.y <= escada2_rect.y+70)
        {
            personagem_rect.y -= 1;
        }
        if(teclabaixo && personagem_rect.x >= escada2_rect.x-10 && personagem_rect.x <= escada2_rect.x+25 && personagem_rect.y <= escada2_rect.y+45)
        {
            personagem_rect.y += 1.8;
        }
        if(teclacima && personagem_rect.x >= escada3_rect.x-10 && personagem_rect.x <= escada3_rect.x+25 && personagem_rect.y >= escada3_rect.y-83 && personagem_rect.y <= escada3_rect.y+70)
        {
            personagem_rect.y -= 1;
        }
        if(teclabaixo && personagem_rect.x >= escada3_rect.x-10 && personagem_rect.x <= escada3_rect.x+25 && personagem_rect.y <= escada3_rect.y+45)
        {
            personagem_rect.y += 1.8;
        }
        if(teclacima && personagem_rect.x >= escada4_rect.x-10 && personagem_rect.x <= escada4_rect.x+25 && personagem_rect.y >= escada4_rect.y-83 && personagem_rect.y <= escada4_rect.y+70)
        {
            personagem_rect.y -= 1;
        }
        if(teclabaixo && personagem_rect.x >= escada4_rect.x-10 && personagem_rect.x <= escada4_rect.x+25 && personagem_rect.y <= escada4_rect.y+45)
        {
            personagem_rect.y += 1.8;
        }
//SALTO.
        if(espaco_ant==0 && teclaespaco==1)
        {
            i = personagem_rect.y;
            subindo = 1;
        }
        espaco_ant = teclaespaco;

        if(teclaespaco)
        {
            if(personagem_rect.y > i - 45 && subindo)
            {
                personagem_rect.y -= 1.3;
                if(tecladireita)
                {
                    personagem_rect.x += 1.8;
                    emovimento = 1;
                }
                if(teclaesquerda)
                {
                    personagem_rect.x -= 1;
                    emovimento = 1;
                }
            }
            else if(personagem_rect.y < i)
            {
                personagem_rect.y += 1.9;
                if(tecladireita)
                    personagem_rect.x += 1.8;
                if(teclaesquerda)
                    personagem_rect.x -= 1;
                subindo = 0;
            }
            else
            {
                teclaespaco = 0;
            }


        }

        if(barril_rect[0].y <= escada4_rect.y && barril_rect[0].x <= escada4_rect.x+68)
            barril_rect[0].x+=2;
        else if(barril_rect[0].y <= escada2_rect.y-75)
            barril_rect[0].y+=2;
        else if(barril_rect[0].x >= escada2_rect.x-75 && barril_rect[0].y <= escada2_rect.y)
        {
            barril_rect[0].x-=2;
            if(barril_rect[0].x + barril->w >= plataforma3_rect[0].x && barril_rect[0].x + barril->w <= plataforma3_rect[0].x+10)
            {
                barril_rect[0].y = plataforma3_rect[0].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[1].x && barril_rect[0].x + barril->w <= plataforma3_rect[1].x+10)
            {
                barril_rect[0].y = plataforma3_rect[1].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[2].x && barril_rect[0].x + barril->w <= plataforma3_rect[2].x+10)
            {
                barril_rect[0].y = plataforma3_rect[2].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[3].x && barril_rect[0].x + barril->w <= plataforma3_rect[3].x+10)
            {
                barril_rect[0].y = plataforma3_rect[3].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[4].x && barril_rect[0].x + barril->w <= plataforma3_rect[4].x+10)
            {
                barril_rect[0].y = plataforma3_rect[4].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[5].x && barril_rect[0].x + barril->w <= plataforma3_rect[5].x+10)
            {
                barril_rect[0].y = plataforma3_rect[5].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[6].x && barril_rect[0].x + barril->w <= plataforma3_rect[6].x+10)
            {
                barril_rect[0].y = plataforma3_rect[6].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[7].x && barril_rect[0].x + barril->w <= plataforma3_rect[7].x+10)
            {
                barril_rect[0].y = plataforma3_rect[7].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[8].x && barril_rect[0].x + barril->w <= plataforma3_rect[8].x+10)
            {
                barril_rect[0].y = plataforma3_rect[8].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[9].x && barril_rect[0].x + barril->w <= plataforma3_rect[9].x+10)
            {
                barril_rect[0].y = plataforma3_rect[9].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[10].x && barril_rect[0].x + barril->w <= plataforma3_rect[10].x+10)
            {
                barril_rect[0].y = plataforma3_rect[10].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[11].x && barril_rect[0].x + barril->w <= plataforma3_rect[11].x+10)
            {
                barril_rect[0].y = plataforma3_rect[11].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[12].x && barril_rect[0].x + barril->w <= plataforma3_rect[12].x+10)
            {
                barril_rect[0].y = plataforma3_rect[12].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[13].x && barril_rect[0].x + barril->w <= plataforma3_rect[13].x+10)
            {
                barril_rect[0].y = plataforma3_rect[13].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[14].x && barril_rect[0].x + barril->w <= plataforma3_rect[14].x+10)
            {
                barril_rect[0].y = plataforma3_rect[14].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[15].x && barril_rect[0].x + barril->w <= plataforma3_rect[15].x+10)
            {
                barril_rect[0].y = plataforma3_rect[15].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[16].x && barril_rect[0].x + barril->w <= plataforma3_rect[16].x+10)
            {
                barril_rect[0].y = plataforma3_rect[16].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[17].x && barril_rect[0].x + barril->w <= plataforma3_rect[17].x+10)
            {
                barril_rect[0].y = plataforma3_rect[17].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[18].x && barril_rect[0].x + barril->w <= plataforma3_rect[18].x+10)
            {
                barril_rect[0].y = plataforma3_rect[18].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[19].x && barril_rect[0].x + barril->w <= plataforma3_rect[19].x+10)
            {
                barril_rect[0].y = plataforma3_rect[19].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[20].x && barril_rect[0].x + barril->w <= plataforma3_rect[20].x+10)
            {
                barril_rect[0].y = plataforma3_rect[20].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[21].x && barril_rect[0].x + barril->w <= plataforma3_rect[21].x+10)
            {
                barril_rect[0].y = plataforma3_rect[21].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[22].x && barril_rect[0].x + barril->w <= plataforma3_rect[22].x+10)
            {
                barril_rect[0].y = plataforma3_rect[22].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[23].x && barril_rect[0].x + barril->w <= plataforma3_rect[23].x+10)
            {
                barril_rect[0].y = plataforma3_rect[23].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[24].x && barril_rect[0].x + barril->w <= plataforma3_rect[24].x+10)
            {
                barril_rect[0].y = plataforma3_rect[24].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[25].x && barril_rect[0].x + barril->w <= plataforma3_rect[25].x+10)
            {
                barril_rect[0].y = plataforma3_rect[25].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[26].x && barril_rect[0].x + barril->w <= plataforma3_rect[26].x+10)
            {
                barril_rect[0].y = plataforma3_rect[26].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[27].x && barril_rect[0].x + barril->w <= plataforma3_rect[27].x-2)
            {
                barril_rect[0].y = plataforma3_rect[27].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[28].x && barril_rect[0].x + barril->w <= plataforma3_rect[28].x-2)
            {
                barril_rect[0].y = plataforma3_rect[28].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[29].x && barril_rect[0].x + barril->w <= plataforma3_rect[29].x-2)
            {
                barril_rect[0].y = plataforma3_rect[29].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[30].x && barril_rect[0].x + barril->w <= plataforma3_rect[30].x-2)
            {
                barril_rect[0].y = plataforma3_rect[30].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma3_rect[31].x && barril_rect[0].x + barril->w <= plataforma3_rect[31].x-2)
            {
                barril_rect[0].y = plataforma3_rect[31].y - barril->h+2;
            }
        }
        else if(barril_rect[0].y <= escada_rect.y-75)
            barril_rect[0].y+=2;
        else if(barril_rect[0].y <= escada_rect.y && barril_rect[0].x <= escada_rect.x+92)
        {
            barril_rect[0].x+=2;
            if(barril_rect[0].x + barril->w >= plataforma2_rect[0].x && barril_rect[0].x + barril->w <= plataforma2_rect[0].x+10)
            {
                barril_rect[0].y = plataforma2_rect[0].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[1].x && barril_rect[0].x + barril->w <= plataforma2_rect[1].x+10)
            {
                barril_rect[0].y = plataforma2_rect[1].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[2].x && barril_rect[0].x + barril->w <= plataforma2_rect[2].x+10)
            {
                barril_rect[0].y = plataforma2_rect[2].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[3].x && barril_rect[0].x + barril->w <= plataforma2_rect[3].x+10)
            {
                barril_rect[0].y = plataforma2_rect[3].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[4].x && barril_rect[0].x + barril->w <= plataforma2_rect[4].x+10)
            {
                barril_rect[0].y = plataforma2_rect[4].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[5].x && barril_rect[0].x + barril->w <= plataforma2_rect[5].x+10)
            {
                barril_rect[0].y = plataforma2_rect[5].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[6].x && barril_rect[0].x + barril->w <= plataforma2_rect[6].x+10)
            {
                barril_rect[0].y = plataforma2_rect[6].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[7].x && barril_rect[0].x + barril->w <= plataforma2_rect[7].x+10)
            {
                barril_rect[0].y = plataforma2_rect[7].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[8].x && barril_rect[0].x + barril->w <= plataforma2_rect[8].x+10)
            {
                barril_rect[0].y = plataforma2_rect[8].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[9].x && barril_rect[0].x + barril->w <= plataforma2_rect[9].x+10)
            {
                barril_rect[0].y = plataforma2_rect[9].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[10].x && barril_rect[0].x + barril->w <= plataforma2_rect[10].x+10)
            {
                barril_rect[0].y = plataforma2_rect[10].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[11].x && barril_rect[0].x + barril->w <= plataforma2_rect[11].x+10)
            {
                barril_rect[0].y = plataforma2_rect[11].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[12].x && barril_rect[0].x + barril->w <= plataforma2_rect[12].x+10)
            {
                barril_rect[0].y = plataforma2_rect[12].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[13].x && barril_rect[0].x + barril->w <= plataforma2_rect[13].x+10)
            {
                barril_rect[0].y = plataforma2_rect[13].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[14].x && barril_rect[0].x + barril->w <= plataforma2_rect[14].x+10)
            {
                barril_rect[0].y = plataforma2_rect[14].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[15].x && barril_rect[0].x + barril->w <= plataforma2_rect[15].x+10)
            {
                barril_rect[0].y = plataforma2_rect[15].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[16].x && barril_rect[0].x + barril->w <= plataforma2_rect[16].x+10)
            {
                barril_rect[0].y = plataforma2_rect[16].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[17].x && barril_rect[0].x + barril->w <= plataforma2_rect[17].x+10)
            {
                barril_rect[0].y = plataforma2_rect[17].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[18].x && barril_rect[0].x + barril->w <= plataforma2_rect[18].x+10)
            {
                barril_rect[0].y = plataforma2_rect[18].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[19].x && barril_rect[0].x + barril->w <= plataforma2_rect[19].x+10)
            {
                barril_rect[0].y = plataforma2_rect[19].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[20].x && barril_rect[0].x + barril->w <= plataforma2_rect[20].x+10)
            {
                barril_rect[0].y = plataforma2_rect[20].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[21].x && barril_rect[0].x + barril->w <= plataforma2_rect[21].x+10)
            {
                barril_rect[0].y = plataforma2_rect[21].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[22].x && barril_rect[0].x + barril->w <= plataforma2_rect[22].x+10)
            {
                barril_rect[0].y = plataforma2_rect[22].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[23].x && barril_rect[0].x + barril->w <= plataforma2_rect[23].x+10)
            {
                barril_rect[0].y = plataforma2_rect[23].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[24].x && barril_rect[0].x + barril->w <= plataforma2_rect[24].x+10)
            {
                barril_rect[0].y = plataforma2_rect[24].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[25].x && barril_rect[0].x + barril->w <= plataforma2_rect[25].x+10)
            {
                barril_rect[0].y = plataforma2_rect[25].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[26].x && barril_rect[0].x + barril->w <= plataforma2_rect[26].x+10)
            {
                barril_rect[0].y = plataforma2_rect[26].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[27].x && barril_rect[0].x + barril->w <= plataforma2_rect[27].x+10)
            {
                barril_rect[0].y = plataforma2_rect[27].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[28].x && barril_rect[0].x + barril->w <= plataforma2_rect[28].x+10)
            {
                barril_rect[0].y = plataforma2_rect[28].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[29].x && barril_rect[0].x + barril->w <= plataforma2_rect[29].x+10)
            {
                barril_rect[0].y = plataforma2_rect[29].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[30].x && barril_rect[0].x + barril->w <= plataforma2_rect[30].x+10)
            {
                barril_rect[0].y = plataforma2_rect[30].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma2_rect[31].x && barril_rect[0].x + barril->w <= plataforma2_rect[31].x+10)
            {
                barril_rect[0].y = plataforma2_rect[31].y - barril->h+2;
            }
        }
        else if(barril_rect[0].y <= escada_rect.y+90)
            barril_rect[0].y+=2;
        else if(barril_rect[0].y <= escada_rect.y+220)
        {
            barril_rect[0].x-=2;
            if(barril_rect[0].x + barril->w >= plataforma1_rect[0].x && barril_rect[0].x + barril->w <= plataforma1_rect[0].x+10)
            {
                barril_rect[0].y = plataforma1_rect[0].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[1].x && barril_rect[0].x + barril->w <= plataforma1_rect[1].x+10)
            {
                barril_rect[0].y = plataforma1_rect[1].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[2].x && barril_rect[0].x + barril->w <= plataforma1_rect[2].x+10)
            {
                barril_rect[0].y = plataforma1_rect[2].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[3].x && barril_rect[0].x + barril->w <= plataforma1_rect[3].x+10)
            {
                barril_rect[0].y = plataforma1_rect[3].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[4].x && barril_rect[0].x + barril->w <= plataforma1_rect[4].x+10)
            {
                barril_rect[0].y = plataforma1_rect[4].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[5].x && barril_rect[0].x + barril->w <= plataforma1_rect[5].x+10)
            {
                barril_rect[0].y = plataforma1_rect[5].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[6].x && barril_rect[0].x + barril->w <= plataforma1_rect[6].x+10)
            {
                barril_rect[0].y = plataforma1_rect[6].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[7].x && barril_rect[0].x + barril->w <= plataforma1_rect[7].x+10)
            {
                barril_rect[0].y = plataforma1_rect[7].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[8].x && barril_rect[0].x + barril->w <= plataforma1_rect[8].x+10)
            {
                barril_rect[0].y = plataforma1_rect[8].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[9].x && barril_rect[0].x + barril->w <= plataforma1_rect[9].x+10)
            {
                barril_rect[0].y = plataforma1_rect[9].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[10].x && barril_rect[0].x + barril->w <= plataforma1_rect[10].x+10)
            {
                barril_rect[0].y = plataforma1_rect[10].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[11].x && barril_rect[0].x + barril->w <= plataforma1_rect[11].x+10)
            {
                barril_rect[0].y = plataforma1_rect[11].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[12].x && barril_rect[0].x + barril->w <= plataforma1_rect[12].x+10)
            {
                barril_rect[0].y = plataforma1_rect[12].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[13].x && barril_rect[0].x + barril->w <= plataforma1_rect[13].x+10)
            {
                barril_rect[0].y = plataforma1_rect[13].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[14].x && barril_rect[0].x + barril->w <= plataforma1_rect[14].x+10)
            {
                barril_rect[0].y = plataforma1_rect[14].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[15].x && barril_rect[0].x + barril->w <= plataforma1_rect[15].x+10)
            {
                barril_rect[0].y = plataforma1_rect[15].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[16].x && barril_rect[0].x + barril->w <= plataforma1_rect[16].x+10)
            {
                barril_rect[0].y = plataforma1_rect[16].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[17].x && barril_rect[0].x + barril->w <= plataforma1_rect[17].x+10)
            {
                barril_rect[0].y = plataforma1_rect[17].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[18].x && barril_rect[0].x + barril->w <= plataforma1_rect[18].x+10)
            {
                barril_rect[0].y = plataforma1_rect[18].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[19].x && barril_rect[0].x + barril->w <= plataforma1_rect[19].x+10)
            {
                barril_rect[0].y = plataforma1_rect[19].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[20].x && barril_rect[0].x + barril->w <= plataforma1_rect[20].x+10)
            {
                barril_rect[0].y = plataforma1_rect[20].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[21].x && barril_rect[0].x + barril->w <= plataforma1_rect[21].x+10)
            {
                barril_rect[0].y = plataforma1_rect[21].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[22].x && barril_rect[0].x + barril->w <= plataforma1_rect[22].x+10)
            {
                barril_rect[0].y = plataforma1_rect[22].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[23].x && barril_rect[0].x + barril->w <= plataforma1_rect[23].x+10)
            {
                barril_rect[0].y = plataforma1_rect[23].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[24].x && barril_rect[0].x + barril->w <= plataforma1_rect[24].x+10)
            {
                barril_rect[0].y = plataforma1_rect[24].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[25].x && barril_rect[0].x + barril->w <= plataforma1_rect[25].x+10)
            {
                barril_rect[0].y = plataforma1_rect[25].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[26].x && barril_rect[0].x + barril->w <= plataforma1_rect[26].x+10)
            {
                barril_rect[0].y = plataforma1_rect[26].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[27].x && barril_rect[0].x + barril->w <= plataforma1_rect[27].x+10)
            {
                barril_rect[0].y = plataforma1_rect[27].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[28].x && barril_rect[0].x + barril->w <= plataforma1_rect[28].x+10)
            {
                barril_rect[0].y = plataforma1_rect[28].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[29].x && barril_rect[0].x + barril->w <= plataforma1_rect[29].x+10)
            {
                barril_rect[0].y = plataforma1_rect[29].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[30].x && barril_rect[0].x + barril->w <= plataforma1_rect[30].x+10)
            {
                barril_rect[0].y = plataforma1_rect[30].y - barril->h+2;
            }
            if(barril_rect[0].x + barril->w >= plataforma1_rect[31].x && barril_rect[0].x + barril->w <= plataforma1_rect[31].x+10)
            {
                barril_rect[0].y = plataforma1_rect[31].y - barril->h+2;
            }

        }

        if(barril_rect[0].y>=218 || barril_rect[1].y>=218)
        {
            if(barril_rect[1].y <= escada4_rect.y && barril_rect[1].x <= escada4_rect.x+68)
                barril_rect[1].x+=2;
            else if(barril_rect[1].y <= escada2_rect.y-75)
                barril_rect[1].y+=2;
            else if(barril_rect[1].x >= escada2_rect.x-75 && barril_rect[1].y <= escada2_rect.y)
            {
                barril_rect[1].x-=2;
                if(barril_rect[1].x + barril->w >= plataforma3_rect[1].x && barril_rect[1].x + barril->w <= plataforma3_rect[1].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[1].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[1].x && barril_rect[1].x + barril->w <= plataforma3_rect[1].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[1].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[2].x && barril_rect[1].x + barril->w <= plataforma3_rect[2].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[2].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[3].x && barril_rect[1].x + barril->w <= plataforma3_rect[3].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[3].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[4].x && barril_rect[1].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[5].x && barril_rect[1].x + barril->w <= plataforma3_rect[5].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[5].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[6].x && barril_rect[1].x + barril->w <= plataforma3_rect[6].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[6].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[7].x && barril_rect[1].x + barril->w <= plataforma3_rect[7].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[7].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[8].x && barril_rect[1].x + barril->w <= plataforma3_rect[8].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[8].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[9].x && barril_rect[1].x + barril->w <= plataforma3_rect[9].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[9].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[10].x && barril_rect[1].x + barril->w <= plataforma3_rect[10].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[10].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[11].x && barril_rect[1].x + barril->w <= plataforma3_rect[11].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[11].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[12].x && barril_rect[1].x + barril->w <= plataforma3_rect[12].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[12].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[13].x && barril_rect[1].x + barril->w <= plataforma3_rect[13].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[13].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[14].x && barril_rect[1].x + barril->w <= plataforma3_rect[14].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[14].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[15].x && barril_rect[1].x + barril->w <= plataforma3_rect[15].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[15].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[16].x && barril_rect[1].x + barril->w <= plataforma3_rect[16].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[16].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[17].x && barril_rect[1].x + barril->w <= plataforma3_rect[17].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[17].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[18].x && barril_rect[1].x + barril->w <= plataforma3_rect[18].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[18].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[19].x && barril_rect[1].x + barril->w <= plataforma3_rect[19].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[19].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[20].x && barril_rect[1].x + barril->w <= plataforma3_rect[20].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[20].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[21].x && barril_rect[1].x + barril->w <= plataforma3_rect[21].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[21].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[22].x && barril_rect[1].x + barril->w <= plataforma3_rect[22].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[22].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[23].x && barril_rect[1].x + barril->w <= plataforma3_rect[23].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[23].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[24].x && barril_rect[1].x + barril->w <= plataforma3_rect[24].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[24].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[25].x && barril_rect[1].x + barril->w <= plataforma3_rect[25].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[25].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[26].x && barril_rect[1].x + barril->w <= plataforma3_rect[26].x+10)
                {
                    barril_rect[1].y = plataforma3_rect[26].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[27].x && barril_rect[1].x + barril->w <= plataforma3_rect[27].x-2)
                {
                    barril_rect[1].y = plataforma3_rect[27].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[28].x && barril_rect[1].x + barril->w <= plataforma3_rect[28].x-2)
                {
                    barril_rect[1].y = plataforma3_rect[28].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[29].x && barril_rect[1].x + barril->w <= plataforma3_rect[29].x-2)
                {
                    barril_rect[1].y = plataforma3_rect[29].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[30].x && barril_rect[1].x + barril->w <= plataforma3_rect[30].x-2)
                {
                    barril_rect[1].y = plataforma3_rect[30].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma3_rect[31].x && barril_rect[1].x + barril->w <= plataforma3_rect[31].x-2)
                {
                    barril_rect[1].y = plataforma3_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[1].y <= escada_rect.y-75)
                barril_rect[1].y+=2;
            else if(barril_rect[1].y <= escada_rect.y && barril_rect[1].x <= escada_rect.x+92)
            {
                barril_rect[1].x+=2;
                if(barril_rect[1].x + barril->w >= plataforma2_rect[1].x && barril_rect[1].x + barril->w <= plataforma2_rect[1].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[1].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[1].x && barril_rect[1].x + barril->w <= plataforma2_rect[1].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[1].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[2].x && barril_rect[1].x + barril->w <= plataforma2_rect[2].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[2].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[3].x && barril_rect[1].x + barril->w <= plataforma2_rect[3].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[3].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[4].x && barril_rect[1].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[5].x && barril_rect[1].x + barril->w <= plataforma2_rect[5].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[5].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[6].x && barril_rect[1].x + barril->w <= plataforma2_rect[6].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[6].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[7].x && barril_rect[1].x + barril->w <= plataforma2_rect[7].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[7].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[8].x && barril_rect[1].x + barril->w <= plataforma2_rect[8].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[8].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[9].x && barril_rect[1].x + barril->w <= plataforma2_rect[9].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[9].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[10].x && barril_rect[1].x + barril->w <= plataforma2_rect[10].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[10].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[11].x && barril_rect[1].x + barril->w <= plataforma2_rect[11].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[11].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[12].x && barril_rect[1].x + barril->w <= plataforma2_rect[12].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[12].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[13].x && barril_rect[1].x + barril->w <= plataforma2_rect[13].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[13].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[14].x && barril_rect[1].x + barril->w <= plataforma2_rect[14].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[14].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[15].x && barril_rect[1].x + barril->w <= plataforma2_rect[15].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[15].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[16].x && barril_rect[1].x + barril->w <= plataforma2_rect[16].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[16].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[17].x && barril_rect[1].x + barril->w <= plataforma2_rect[17].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[17].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[18].x && barril_rect[1].x + barril->w <= plataforma2_rect[18].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[18].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[19].x && barril_rect[1].x + barril->w <= plataforma2_rect[19].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[19].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[20].x && barril_rect[1].x + barril->w <= plataforma2_rect[20].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[20].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[21].x && barril_rect[1].x + barril->w <= plataforma2_rect[21].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[21].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[22].x && barril_rect[1].x + barril->w <= plataforma2_rect[22].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[22].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[23].x && barril_rect[1].x + barril->w <= plataforma2_rect[23].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[23].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[24].x && barril_rect[1].x + barril->w <= plataforma2_rect[24].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[24].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[25].x && barril_rect[1].x + barril->w <= plataforma2_rect[25].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[25].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[26].x && barril_rect[1].x + barril->w <= plataforma2_rect[26].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[26].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[27].x && barril_rect[1].x + barril->w <= plataforma2_rect[27].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[27].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[28].x && barril_rect[1].x + barril->w <= plataforma2_rect[28].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[28].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[29].x && barril_rect[1].x + barril->w <= plataforma2_rect[29].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[29].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[30].x && barril_rect[1].x + barril->w <= plataforma2_rect[30].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[30].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma2_rect[31].x && barril_rect[1].x + barril->w <= plataforma2_rect[31].x+10)
                {
                    barril_rect[1].y = plataforma2_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[1].y <= escada_rect.y+90)
                barril_rect[1].y+=2;
            else if(barril_rect[1].y <= escada_rect.y+220)
            {
                barril_rect[1].x-=2;
                if(barril_rect[1].x + barril->w >= plataforma1_rect[1].x && barril_rect[1].x + barril->w <= plataforma1_rect[1].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[1].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[1].x && barril_rect[1].x + barril->w <= plataforma1_rect[1].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[1].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[2].x && barril_rect[1].x + barril->w <= plataforma1_rect[2].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[2].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[3].x && barril_rect[1].x + barril->w <= plataforma1_rect[3].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[3].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[4].x && barril_rect[1].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[5].x && barril_rect[1].x + barril->w <= plataforma1_rect[5].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[5].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[6].x && barril_rect[1].x + barril->w <= plataforma1_rect[6].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[6].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[7].x && barril_rect[1].x + barril->w <= plataforma1_rect[7].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[7].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[8].x && barril_rect[1].x + barril->w <= plataforma1_rect[8].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[8].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[9].x && barril_rect[1].x + barril->w <= plataforma1_rect[9].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[9].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[10].x && barril_rect[1].x + barril->w <= plataforma1_rect[10].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[10].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[11].x && barril_rect[1].x + barril->w <= plataforma1_rect[11].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[11].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[12].x && barril_rect[1].x + barril->w <= plataforma1_rect[12].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[12].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[13].x && barril_rect[1].x + barril->w <= plataforma1_rect[13].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[13].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[14].x && barril_rect[1].x + barril->w <= plataforma1_rect[14].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[14].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[15].x && barril_rect[1].x + barril->w <= plataforma1_rect[15].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[15].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[16].x && barril_rect[1].x + barril->w <= plataforma1_rect[16].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[16].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[17].x && barril_rect[1].x + barril->w <= plataforma1_rect[17].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[17].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[18].x && barril_rect[1].x + barril->w <= plataforma1_rect[18].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[18].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[19].x && barril_rect[1].x + barril->w <= plataforma1_rect[19].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[19].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[20].x && barril_rect[1].x + barril->w <= plataforma1_rect[20].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[20].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[21].x && barril_rect[1].x + barril->w <= plataforma1_rect[21].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[21].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[22].x && barril_rect[1].x + barril->w <= plataforma1_rect[22].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[22].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[23].x && barril_rect[1].x + barril->w <= plataforma1_rect[23].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[23].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[24].x && barril_rect[1].x + barril->w <= plataforma1_rect[24].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[24].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[25].x && barril_rect[1].x + barril->w <= plataforma1_rect[25].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[25].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[26].x && barril_rect[1].x + barril->w <= plataforma1_rect[26].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[26].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[27].x && barril_rect[1].x + barril->w <= plataforma1_rect[27].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[27].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[28].x && barril_rect[1].x + barril->w <= plataforma1_rect[28].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[28].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[29].x && barril_rect[1].x + barril->w <= plataforma1_rect[29].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[29].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[30].x && barril_rect[1].x + barril->w <= plataforma1_rect[30].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[30].y - barril->h+2;
                }
                if(barril_rect[1].x + barril->w >= plataforma1_rect[31].x && barril_rect[1].x + barril->w <= plataforma1_rect[31].x+10)
                {
                    barril_rect[1].y = plataforma1_rect[31].y - barril->h+2;
                }

            }


        }

        if(barril_rect[1].y>=218 || barril_rect[2].y>=218)
        {
            if(barril_rect[2].y <= escada4_rect.y && barril_rect[2].x <= escada4_rect.x+68)
                barril_rect[2].x+=2;
            else if(barril_rect[2].y <= escada2_rect.y-75)
                barril_rect[2].y+=2;
            else if(barril_rect[2].x >= escada2_rect.x-75 && barril_rect[2].y <= escada2_rect.y)
            {
                barril_rect[2].x-=2;
                if(barril_rect[2].x + barril->w >= plataforma3_rect[2].x && barril_rect[2].x + barril->w <= plataforma3_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[2].x && barril_rect[2].x + barril->w <= plataforma3_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[2].x && barril_rect[2].x + barril->w <= plataforma3_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[3].x && barril_rect[2].x + barril->w <= plataforma3_rect[3].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[3].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[4].x && barril_rect[2].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[5].x && barril_rect[2].x + barril->w <= plataforma3_rect[5].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[5].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[6].x && barril_rect[2].x + barril->w <= plataforma3_rect[6].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[6].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[7].x && barril_rect[2].x + barril->w <= plataforma3_rect[7].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[7].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[8].x && barril_rect[2].x + barril->w <= plataforma3_rect[8].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[8].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[9].x && barril_rect[2].x + barril->w <= plataforma3_rect[9].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[9].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[10].x && barril_rect[2].x + barril->w <= plataforma3_rect[10].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[10].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[11].x && barril_rect[2].x + barril->w <= plataforma3_rect[11].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[11].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[12].x && barril_rect[2].x + barril->w <= plataforma3_rect[12].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[12].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[13].x && barril_rect[2].x + barril->w <= plataforma3_rect[13].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[13].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[14].x && barril_rect[2].x + barril->w <= plataforma3_rect[14].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[14].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[15].x && barril_rect[2].x + barril->w <= plataforma3_rect[15].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[15].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[16].x && barril_rect[2].x + barril->w <= plataforma3_rect[16].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[16].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[17].x && barril_rect[2].x + barril->w <= plataforma3_rect[17].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[17].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[18].x && barril_rect[2].x + barril->w <= plataforma3_rect[18].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[18].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[19].x && barril_rect[2].x + barril->w <= plataforma3_rect[19].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[19].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[20].x && barril_rect[2].x + barril->w <= plataforma3_rect[20].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[20].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[21].x && barril_rect[2].x + barril->w <= plataforma3_rect[21].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[21].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[22].x && barril_rect[2].x + barril->w <= plataforma3_rect[22].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[22].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[23].x && barril_rect[2].x + barril->w <= plataforma3_rect[23].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[23].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[24].x && barril_rect[2].x + barril->w <= plataforma3_rect[24].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[24].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[25].x && barril_rect[2].x + barril->w <= plataforma3_rect[25].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[25].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[26].x && barril_rect[2].x + barril->w <= plataforma3_rect[26].x+10)
                {
                    barril_rect[2].y = plataforma3_rect[26].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[27].x && barril_rect[2].x + barril->w <= plataforma3_rect[27].x-2)
                {
                    barril_rect[2].y = plataforma3_rect[27].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[28].x && barril_rect[2].x + barril->w <= plataforma3_rect[28].x-2)
                {
                    barril_rect[2].y = plataforma3_rect[28].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[29].x && barril_rect[2].x + barril->w <= plataforma3_rect[29].x-2)
                {
                    barril_rect[2].y = plataforma3_rect[29].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[30].x && barril_rect[2].x + barril->w <= plataforma3_rect[30].x-2)
                {
                    barril_rect[2].y = plataforma3_rect[30].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma3_rect[31].x && barril_rect[2].x + barril->w <= plataforma3_rect[31].x-2)
                {
                    barril_rect[2].y = plataforma3_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[2].y <= escada_rect.y-75)
                barril_rect[2].y+=2;
            else if(barril_rect[2].y <= escada_rect.y && barril_rect[2].x <= escada_rect.x+92)
            {
                barril_rect[2].x+=2;
                if(barril_rect[2].x + barril->w >= plataforma2_rect[2].x && barril_rect[2].x + barril->w <= plataforma2_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[2].x && barril_rect[2].x + barril->w <= plataforma2_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[2].x && barril_rect[2].x + barril->w <= plataforma2_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[3].x && barril_rect[2].x + barril->w <= plataforma2_rect[3].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[3].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[4].x && barril_rect[2].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[5].x && barril_rect[2].x + barril->w <= plataforma2_rect[5].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[5].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[6].x && barril_rect[2].x + barril->w <= plataforma2_rect[6].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[6].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[7].x && barril_rect[2].x + barril->w <= plataforma2_rect[7].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[7].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[8].x && barril_rect[2].x + barril->w <= plataforma2_rect[8].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[8].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[9].x && barril_rect[2].x + barril->w <= plataforma2_rect[9].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[9].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[10].x && barril_rect[2].x + barril->w <= plataforma2_rect[10].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[10].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[11].x && barril_rect[2].x + barril->w <= plataforma2_rect[11].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[11].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[12].x && barril_rect[2].x + barril->w <= plataforma2_rect[12].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[12].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[13].x && barril_rect[2].x + barril->w <= plataforma2_rect[13].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[13].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[14].x && barril_rect[2].x + barril->w <= plataforma2_rect[14].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[14].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[15].x && barril_rect[2].x + barril->w <= plataforma2_rect[15].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[15].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[16].x && barril_rect[2].x + barril->w <= plataforma2_rect[16].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[16].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[17].x && barril_rect[2].x + barril->w <= plataforma2_rect[17].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[17].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[18].x && barril_rect[2].x + barril->w <= plataforma2_rect[18].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[18].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[19].x && barril_rect[2].x + barril->w <= plataforma2_rect[19].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[19].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[20].x && barril_rect[2].x + barril->w <= plataforma2_rect[20].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[20].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[21].x && barril_rect[2].x + barril->w <= plataforma2_rect[21].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[21].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[22].x && barril_rect[2].x + barril->w <= plataforma2_rect[22].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[22].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[23].x && barril_rect[2].x + barril->w <= plataforma2_rect[23].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[23].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[24].x && barril_rect[2].x + barril->w <= plataforma2_rect[24].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[24].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[25].x && barril_rect[2].x + barril->w <= plataforma2_rect[25].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[25].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[26].x && barril_rect[2].x + barril->w <= plataforma2_rect[26].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[26].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[27].x && barril_rect[2].x + barril->w <= plataforma2_rect[27].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[27].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[28].x && barril_rect[2].x + barril->w <= plataforma2_rect[28].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[28].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[29].x && barril_rect[2].x + barril->w <= plataforma2_rect[29].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[29].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[30].x && barril_rect[2].x + barril->w <= plataforma2_rect[30].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[30].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma2_rect[31].x && barril_rect[2].x + barril->w <= plataforma2_rect[31].x+10)
                {
                    barril_rect[2].y = plataforma2_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[2].y <= escada_rect.y+90)
                barril_rect[2].y+=2;
            else if(barril_rect[2].y <= escada_rect.y+220)
            {
                barril_rect[2].x-=2;
                if(barril_rect[2].x + barril->w >= plataforma1_rect[2].x && barril_rect[2].x + barril->w <= plataforma1_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[2].x && barril_rect[2].x + barril->w <= plataforma1_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[2].x && barril_rect[2].x + barril->w <= plataforma1_rect[2].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[2].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[3].x && barril_rect[2].x + barril->w <= plataforma1_rect[3].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[3].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[4].x && barril_rect[2].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[5].x && barril_rect[2].x + barril->w <= plataforma1_rect[5].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[5].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[6].x && barril_rect[2].x + barril->w <= plataforma1_rect[6].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[6].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[7].x && barril_rect[2].x + barril->w <= plataforma1_rect[7].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[7].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[8].x && barril_rect[2].x + barril->w <= plataforma1_rect[8].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[8].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[9].x && barril_rect[2].x + barril->w <= plataforma1_rect[9].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[9].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[10].x && barril_rect[2].x + barril->w <= plataforma1_rect[10].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[10].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[11].x && barril_rect[2].x + barril->w <= plataforma1_rect[11].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[11].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[12].x && barril_rect[2].x + barril->w <= plataforma1_rect[12].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[12].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[13].x && barril_rect[2].x + barril->w <= plataforma1_rect[13].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[13].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[14].x && barril_rect[2].x + barril->w <= plataforma1_rect[14].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[14].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[15].x && barril_rect[2].x + barril->w <= plataforma1_rect[15].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[15].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[16].x && barril_rect[2].x + barril->w <= plataforma1_rect[16].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[16].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[17].x && barril_rect[2].x + barril->w <= plataforma1_rect[17].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[17].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[18].x && barril_rect[2].x + barril->w <= plataforma1_rect[18].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[18].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[19].x && barril_rect[2].x + barril->w <= plataforma1_rect[19].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[19].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[20].x && barril_rect[2].x + barril->w <= plataforma1_rect[20].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[20].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[21].x && barril_rect[2].x + barril->w <= plataforma1_rect[21].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[21].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[22].x && barril_rect[2].x + barril->w <= plataforma1_rect[22].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[22].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[23].x && barril_rect[2].x + barril->w <= plataforma1_rect[23].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[23].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[24].x && barril_rect[2].x + barril->w <= plataforma1_rect[24].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[24].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[25].x && barril_rect[2].x + barril->w <= plataforma1_rect[25].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[25].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[26].x && barril_rect[2].x + barril->w <= plataforma1_rect[26].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[26].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[27].x && barril_rect[2].x + barril->w <= plataforma1_rect[27].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[27].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[28].x && barril_rect[2].x + barril->w <= plataforma1_rect[28].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[28].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[29].x && barril_rect[2].x + barril->w <= plataforma1_rect[29].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[29].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[30].x && barril_rect[2].x + barril->w <= plataforma1_rect[30].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[30].y - barril->h+2;
                }
                if(barril_rect[2].x + barril->w >= plataforma1_rect[31].x && barril_rect[2].x + barril->w <= plataforma1_rect[31].x+10)
                {
                    barril_rect[2].y = plataforma1_rect[31].y - barril->h+2;
                }

            }


        }

        if(barril_rect[2].y>=218 || barril_rect[3].y>=218)
        {
            if(barril_rect[3].y <= escada4_rect.y && barril_rect[3].x <= escada4_rect.x+68)
                barril_rect[3].x+=2;
            else if(barril_rect[3].y <= escada2_rect.y-75)
                barril_rect[3].y+=2;
            else if(barril_rect[3].x >= escada2_rect.x-75 && barril_rect[3].y <= escada2_rect.y)
            {
                barril_rect[3].x-=2;
                if(barril_rect[3].x + barril->w >= plataforma3_rect[3].x && barril_rect[3].x + barril->w <= plataforma3_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[3].x && barril_rect[3].x + barril->w <= plataforma3_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[3].x && barril_rect[3].x + barril->w <= plataforma3_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[3].x && barril_rect[3].x + barril->w <= plataforma3_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[4].x && barril_rect[3].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[5].x && barril_rect[3].x + barril->w <= plataforma3_rect[5].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[5].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[6].x && barril_rect[3].x + barril->w <= plataforma3_rect[6].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[6].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[7].x && barril_rect[3].x + barril->w <= plataforma3_rect[7].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[7].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[8].x && barril_rect[3].x + barril->w <= plataforma3_rect[8].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[8].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[9].x && barril_rect[3].x + barril->w <= plataforma3_rect[9].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[9].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[10].x && barril_rect[3].x + barril->w <= plataforma3_rect[10].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[10].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[11].x && barril_rect[3].x + barril->w <= plataforma3_rect[11].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[11].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[12].x && barril_rect[3].x + barril->w <= plataforma3_rect[12].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[12].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[13].x && barril_rect[3].x + barril->w <= plataforma3_rect[13].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[13].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[14].x && barril_rect[3].x + barril->w <= plataforma3_rect[14].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[14].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[15].x && barril_rect[3].x + barril->w <= plataforma3_rect[15].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[15].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[16].x && barril_rect[3].x + barril->w <= plataforma3_rect[16].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[16].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[17].x && barril_rect[3].x + barril->w <= plataforma3_rect[17].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[17].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[18].x && barril_rect[3].x + barril->w <= plataforma3_rect[18].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[18].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[19].x && barril_rect[3].x + barril->w <= plataforma3_rect[19].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[19].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[20].x && barril_rect[3].x + barril->w <= plataforma3_rect[20].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[20].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[21].x && barril_rect[3].x + barril->w <= plataforma3_rect[21].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[21].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[22].x && barril_rect[3].x + barril->w <= plataforma3_rect[22].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[22].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[23].x && barril_rect[3].x + barril->w <= plataforma3_rect[23].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[23].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[24].x && barril_rect[3].x + barril->w <= plataforma3_rect[24].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[24].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[25].x && barril_rect[3].x + barril->w <= plataforma3_rect[25].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[25].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[26].x && barril_rect[3].x + barril->w <= plataforma3_rect[26].x+10)
                {
                    barril_rect[3].y = plataforma3_rect[26].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[27].x && barril_rect[3].x + barril->w <= plataforma3_rect[27].x-2)
                {
                    barril_rect[3].y = plataforma3_rect[27].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[28].x && barril_rect[3].x + barril->w <= plataforma3_rect[28].x-2)
                {
                    barril_rect[3].y = plataforma3_rect[28].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[29].x && barril_rect[3].x + barril->w <= plataforma3_rect[29].x-2)
                {
                    barril_rect[3].y = plataforma3_rect[29].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[30].x && barril_rect[3].x + barril->w <= plataforma3_rect[30].x-2)
                {
                    barril_rect[3].y = plataforma3_rect[30].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma3_rect[31].x && barril_rect[3].x + barril->w <= plataforma3_rect[31].x-2)
                {
                    barril_rect[3].y = plataforma3_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[3].y <= escada_rect.y-75)
                barril_rect[3].y+=2;
            else if(barril_rect[3].y <= escada_rect.y && barril_rect[3].x <= escada_rect.x+92)
            {
                barril_rect[3].x+=2;
                if(barril_rect[3].x + barril->w >= plataforma2_rect[3].x && barril_rect[3].x + barril->w <= plataforma2_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[3].x && barril_rect[3].x + barril->w <= plataforma2_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[3].x && barril_rect[3].x + barril->w <= plataforma2_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[3].x && barril_rect[3].x + barril->w <= plataforma2_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[4].x && barril_rect[3].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[5].x && barril_rect[3].x + barril->w <= plataforma2_rect[5].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[5].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[6].x && barril_rect[3].x + barril->w <= plataforma2_rect[6].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[6].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[7].x && barril_rect[3].x + barril->w <= plataforma2_rect[7].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[7].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[8].x && barril_rect[3].x + barril->w <= plataforma2_rect[8].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[8].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[9].x && barril_rect[3].x + barril->w <= plataforma2_rect[9].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[9].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[10].x && barril_rect[3].x + barril->w <= plataforma2_rect[10].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[10].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[11].x && barril_rect[3].x + barril->w <= plataforma2_rect[11].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[11].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[12].x && barril_rect[3].x + barril->w <= plataforma2_rect[12].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[12].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[13].x && barril_rect[3].x + barril->w <= plataforma2_rect[13].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[13].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[14].x && barril_rect[3].x + barril->w <= plataforma2_rect[14].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[14].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[15].x && barril_rect[3].x + barril->w <= plataforma2_rect[15].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[15].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[16].x && barril_rect[3].x + barril->w <= plataforma2_rect[16].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[16].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[17].x && barril_rect[3].x + barril->w <= plataforma2_rect[17].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[17].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[18].x && barril_rect[3].x + barril->w <= plataforma2_rect[18].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[18].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[19].x && barril_rect[3].x + barril->w <= plataforma2_rect[19].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[19].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[20].x && barril_rect[3].x + barril->w <= plataforma2_rect[20].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[20].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[21].x && barril_rect[3].x + barril->w <= plataforma2_rect[21].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[21].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[22].x && barril_rect[3].x + barril->w <= plataforma2_rect[22].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[22].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[23].x && barril_rect[3].x + barril->w <= plataforma2_rect[23].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[23].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[24].x && barril_rect[3].x + barril->w <= plataforma2_rect[24].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[24].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[25].x && barril_rect[3].x + barril->w <= plataforma2_rect[25].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[25].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[26].x && barril_rect[3].x + barril->w <= plataforma2_rect[26].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[26].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[27].x && barril_rect[3].x + barril->w <= plataforma2_rect[27].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[27].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[28].x && barril_rect[3].x + barril->w <= plataforma2_rect[28].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[28].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[29].x && barril_rect[3].x + barril->w <= plataforma2_rect[29].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[29].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[30].x && barril_rect[3].x + barril->w <= plataforma2_rect[30].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[30].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma2_rect[31].x && barril_rect[3].x + barril->w <= plataforma2_rect[31].x+10)
                {
                    barril_rect[3].y = plataforma2_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[3].y <= escada_rect.y+90)
                barril_rect[3].y+=2;
            else if(barril_rect[3].y <= escada_rect.y+220)
            {
                barril_rect[3].x-=2;
                if(barril_rect[3].x + barril->w >= plataforma1_rect[3].x && barril_rect[3].x + barril->w <= plataforma1_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[3].x && barril_rect[3].x + barril->w <= plataforma1_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[3].x && barril_rect[3].x + barril->w <= plataforma1_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[3].x && barril_rect[3].x + barril->w <= plataforma1_rect[3].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[3].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[4].x && barril_rect[3].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[5].x && barril_rect[3].x + barril->w <= plataforma1_rect[5].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[5].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[6].x && barril_rect[3].x + barril->w <= plataforma1_rect[6].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[6].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[7].x && barril_rect[3].x + barril->w <= plataforma1_rect[7].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[7].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[8].x && barril_rect[3].x + barril->w <= plataforma1_rect[8].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[8].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[9].x && barril_rect[3].x + barril->w <= plataforma1_rect[9].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[9].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[10].x && barril_rect[3].x + barril->w <= plataforma1_rect[10].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[10].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[11].x && barril_rect[3].x + barril->w <= plataforma1_rect[11].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[11].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[12].x && barril_rect[3].x + barril->w <= plataforma1_rect[12].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[12].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[13].x && barril_rect[3].x + barril->w <= plataforma1_rect[13].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[13].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[14].x && barril_rect[3].x + barril->w <= plataforma1_rect[14].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[14].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[15].x && barril_rect[3].x + barril->w <= plataforma1_rect[15].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[15].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[16].x && barril_rect[3].x + barril->w <= plataforma1_rect[16].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[16].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[17].x && barril_rect[3].x + barril->w <= plataforma1_rect[17].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[17].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[18].x && barril_rect[3].x + barril->w <= plataforma1_rect[18].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[18].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[19].x && barril_rect[3].x + barril->w <= plataforma1_rect[19].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[19].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[20].x && barril_rect[3].x + barril->w <= plataforma1_rect[20].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[20].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[21].x && barril_rect[3].x + barril->w <= plataforma1_rect[21].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[21].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[22].x && barril_rect[3].x + barril->w <= plataforma1_rect[22].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[22].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[23].x && barril_rect[3].x + barril->w <= plataforma1_rect[23].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[23].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[24].x && barril_rect[3].x + barril->w <= plataforma1_rect[24].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[24].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[25].x && barril_rect[3].x + barril->w <= plataforma1_rect[25].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[25].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[26].x && barril_rect[3].x + barril->w <= plataforma1_rect[26].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[26].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[27].x && barril_rect[3].x + barril->w <= plataforma1_rect[27].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[27].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[28].x && barril_rect[3].x + barril->w <= plataforma1_rect[28].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[28].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[29].x && barril_rect[3].x + barril->w <= plataforma1_rect[29].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[29].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[30].x && barril_rect[3].x + barril->w <= plataforma1_rect[30].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[30].y - barril->h+2;
                }
                if(barril_rect[3].x + barril->w >= plataforma1_rect[31].x && barril_rect[3].x + barril->w <= plataforma1_rect[31].x+10)
                {
                    barril_rect[3].y = plataforma1_rect[31].y - barril->h+2;
                }

            }


        }

        if(barril_rect[3].y>=218 || barril_rect[4].y>=218)
        {
            if(barril_rect[4].y <= escada4_rect.y && barril_rect[4].x <= escada4_rect.x+68)
                barril_rect[4].x+=2;
            else if(barril_rect[4].y <= escada2_rect.y-75)
                barril_rect[4].y+=2;
            else if(barril_rect[4].x >= escada2_rect.x-75 && barril_rect[4].y <= escada2_rect.y)
            {
                barril_rect[4].x-=2;
                if(barril_rect[4].x + barril->w >= plataforma3_rect[4].x && barril_rect[4].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[4].x && barril_rect[4].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[4].x && barril_rect[4].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[4].x && barril_rect[4].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[4].x && barril_rect[4].x + barril->w <= plataforma3_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[5].x && barril_rect[4].x + barril->w <= plataforma3_rect[5].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[5].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[6].x && barril_rect[4].x + barril->w <= plataforma3_rect[6].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[6].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[7].x && barril_rect[4].x + barril->w <= plataforma3_rect[7].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[7].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[8].x && barril_rect[4].x + barril->w <= plataforma3_rect[8].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[8].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[9].x && barril_rect[4].x + barril->w <= plataforma3_rect[9].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[9].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[10].x && barril_rect[4].x + barril->w <= plataforma3_rect[10].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[10].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[11].x && barril_rect[4].x + barril->w <= plataforma3_rect[11].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[11].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[12].x && barril_rect[4].x + barril->w <= plataforma3_rect[12].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[12].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[13].x && barril_rect[4].x + barril->w <= plataforma3_rect[13].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[13].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[14].x && barril_rect[4].x + barril->w <= plataforma3_rect[14].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[14].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[15].x && barril_rect[4].x + barril->w <= plataforma3_rect[15].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[15].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[16].x && barril_rect[4].x + barril->w <= plataforma3_rect[16].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[16].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[17].x && barril_rect[4].x + barril->w <= plataforma3_rect[17].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[17].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[18].x && barril_rect[4].x + barril->w <= plataforma3_rect[18].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[18].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[19].x && barril_rect[4].x + barril->w <= plataforma3_rect[19].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[19].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[20].x && barril_rect[4].x + barril->w <= plataforma3_rect[20].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[20].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[21].x && barril_rect[4].x + barril->w <= plataforma3_rect[21].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[21].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[22].x && barril_rect[4].x + barril->w <= plataforma3_rect[22].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[22].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[23].x && barril_rect[4].x + barril->w <= plataforma3_rect[23].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[23].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[24].x && barril_rect[4].x + barril->w <= plataforma3_rect[24].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[24].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[25].x && barril_rect[4].x + barril->w <= plataforma3_rect[25].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[25].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[26].x && barril_rect[4].x + barril->w <= plataforma3_rect[26].x+10)
                {
                    barril_rect[4].y = plataforma3_rect[26].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[27].x && barril_rect[4].x + barril->w <= plataforma3_rect[27].x-2)
                {
                    barril_rect[4].y = plataforma3_rect[27].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[28].x && barril_rect[4].x + barril->w <= plataforma3_rect[28].x-2)
                {
                    barril_rect[4].y = plataforma3_rect[28].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[29].x && barril_rect[4].x + barril->w <= plataforma3_rect[29].x-2)
                {
                    barril_rect[4].y = plataforma3_rect[29].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[30].x && barril_rect[4].x + barril->w <= plataforma3_rect[30].x-2)
                {
                    barril_rect[4].y = plataforma3_rect[30].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma3_rect[31].x && barril_rect[4].x + barril->w <= plataforma3_rect[31].x-2)
                {
                    barril_rect[4].y = plataforma3_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[4].y <= escada_rect.y-75)
                barril_rect[4].y+=2;
            else if(barril_rect[4].y <= escada_rect.y && barril_rect[4].x <= escada_rect.x+92)
            {
                barril_rect[4].x+=2;
                if(barril_rect[4].x + barril->w >= plataforma2_rect[4].x && barril_rect[4].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[4].x && barril_rect[4].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[4].x && barril_rect[4].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[4].x && barril_rect[4].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[4].x && barril_rect[4].x + barril->w <= plataforma2_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[5].x && barril_rect[4].x + barril->w <= plataforma2_rect[5].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[5].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[6].x && barril_rect[4].x + barril->w <= plataforma2_rect[6].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[6].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[7].x && barril_rect[4].x + barril->w <= plataforma2_rect[7].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[7].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[8].x && barril_rect[4].x + barril->w <= plataforma2_rect[8].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[8].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[9].x && barril_rect[4].x + barril->w <= plataforma2_rect[9].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[9].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[10].x && barril_rect[4].x + barril->w <= plataforma2_rect[10].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[10].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[11].x && barril_rect[4].x + barril->w <= plataforma2_rect[11].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[11].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[12].x && barril_rect[4].x + barril->w <= plataforma2_rect[12].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[12].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[13].x && barril_rect[4].x + barril->w <= plataforma2_rect[13].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[13].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[14].x && barril_rect[4].x + barril->w <= plataforma2_rect[14].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[14].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[15].x && barril_rect[4].x + barril->w <= plataforma2_rect[15].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[15].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[16].x && barril_rect[4].x + barril->w <= plataforma2_rect[16].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[16].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[17].x && barril_rect[4].x + barril->w <= plataforma2_rect[17].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[17].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[18].x && barril_rect[4].x + barril->w <= plataforma2_rect[18].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[18].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[19].x && barril_rect[4].x + barril->w <= plataforma2_rect[19].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[19].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[20].x && barril_rect[4].x + barril->w <= plataforma2_rect[20].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[20].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[21].x && barril_rect[4].x + barril->w <= plataforma2_rect[21].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[21].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[22].x && barril_rect[4].x + barril->w <= plataforma2_rect[22].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[22].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[23].x && barril_rect[4].x + barril->w <= plataforma2_rect[23].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[23].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[24].x && barril_rect[4].x + barril->w <= plataforma2_rect[24].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[24].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[25].x && barril_rect[4].x + barril->w <= plataforma2_rect[25].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[25].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[26].x && barril_rect[4].x + barril->w <= plataforma2_rect[26].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[26].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[27].x && barril_rect[4].x + barril->w <= plataforma2_rect[27].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[27].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[28].x && barril_rect[4].x + barril->w <= plataforma2_rect[28].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[28].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[29].x && barril_rect[4].x + barril->w <= plataforma2_rect[29].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[29].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[30].x && barril_rect[4].x + barril->w <= plataforma2_rect[30].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[30].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma2_rect[31].x && barril_rect[4].x + barril->w <= plataforma2_rect[31].x+10)
                {
                    barril_rect[4].y = plataforma2_rect[31].y - barril->h+2;
                }
            }
            else if(barril_rect[4].y <= escada_rect.y+90)
                barril_rect[4].y+=2;
            else if(barril_rect[4].y <= escada_rect.y+220)
            {
                barril_rect[4].x-=2;
                if(barril_rect[4].x + barril->w >= plataforma1_rect[4].x && barril_rect[4].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[4].x && barril_rect[4].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[4].x && barril_rect[4].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[4].x && barril_rect[4].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[4].x && barril_rect[4].x + barril->w <= plataforma1_rect[4].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[4].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[5].x && barril_rect[4].x + barril->w <= plataforma1_rect[5].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[5].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[6].x && barril_rect[4].x + barril->w <= plataforma1_rect[6].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[6].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[7].x && barril_rect[4].x + barril->w <= plataforma1_rect[7].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[7].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[8].x && barril_rect[4].x + barril->w <= plataforma1_rect[8].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[8].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[9].x && barril_rect[4].x + barril->w <= plataforma1_rect[9].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[9].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[10].x && barril_rect[4].x + barril->w <= plataforma1_rect[10].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[10].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[11].x && barril_rect[4].x + barril->w <= plataforma1_rect[11].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[11].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[12].x && barril_rect[4].x + barril->w <= plataforma1_rect[12].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[12].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[13].x && barril_rect[4].x + barril->w <= plataforma1_rect[13].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[13].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[14].x && barril_rect[4].x + barril->w <= plataforma1_rect[14].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[14].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[15].x && barril_rect[4].x + barril->w <= plataforma1_rect[15].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[15].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[16].x && barril_rect[4].x + barril->w <= plataforma1_rect[16].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[16].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[17].x && barril_rect[4].x + barril->w <= plataforma1_rect[17].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[17].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[18].x && barril_rect[4].x + barril->w <= plataforma1_rect[18].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[18].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[19].x && barril_rect[4].x + barril->w <= plataforma1_rect[19].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[19].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[20].x && barril_rect[4].x + barril->w <= plataforma1_rect[20].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[20].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[21].x && barril_rect[4].x + barril->w <= plataforma1_rect[21].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[21].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[22].x && barril_rect[4].x + barril->w <= plataforma1_rect[22].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[22].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[23].x && barril_rect[4].x + barril->w <= plataforma1_rect[23].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[23].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[24].x && barril_rect[4].x + barril->w <= plataforma1_rect[24].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[24].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[25].x && barril_rect[4].x + barril->w <= plataforma1_rect[25].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[25].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[26].x && barril_rect[4].x + barril->w <= plataforma1_rect[26].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[26].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[27].x && barril_rect[4].x + barril->w <= plataforma1_rect[27].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[27].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[28].x && barril_rect[4].x + barril->w <= plataforma1_rect[28].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[28].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[29].x && barril_rect[4].x + barril->w <= plataforma1_rect[29].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[29].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[30].x && barril_rect[4].x + barril->w <= plataforma1_rect[30].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[30].y - barril->h+2;
                }
                if(barril_rect[4].x + barril->w >= plataforma1_rect[31].x && barril_rect[4].x + barril->w <= plataforma1_rect[31].x+10)
                {
                    barril_rect[4].y = plataforma1_rect[31].y - barril->h+2;
                }

            }


        }

        if(barril_rect[4].y==218)
        {
            barril_rect[0].x = 650;
            barril_rect[0].y = 49;
        }

        if(barril_rect[0].y==218)
        {
            barril_rect[1].x = 650;
            barril_rect[1].y = 49;
        }

        if(barril_rect[1].y==218)
        {
            barril_rect[2].x = 650;
            barril_rect[2].y = 49;
        }

        if(barril_rect[2].y==218)
        {
            barril_rect[3].x = 650;
            barril_rect[3].y = 49;
        }

        if(barril_rect[3].y==218)
        {
            barril_rect[4].x = 650;
            barril_rect[4].y = 49;
        }

        while(barril_rect[0].y>=personagem_rect.y && barril_rect[0].y<=personagem_rect.y+76 && barril_rect[0].x<=personagem_rect.x+25 && barril_rect[0].x>=personagem_rect.x+3)
        {
            barril_rect[0].y=personagem_rect.y+4;
            barril_rect[0].x=personagem_rect.x+4;

            SDL_BlitSurface(gameover,0,tela,&gameover_rect);
            SDL_Flip(tela);
            while(SDL_PollEvent(&evento))
            {
                if(evento.type==SDL_QUIT)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    SDL_Quit();
            }

        }

        while(barril_rect[1].y>=personagem_rect.y && barril_rect[1].y<=personagem_rect.y+76 && barril_rect[1].x<=personagem_rect.x+23 && barril_rect[1].x>=personagem_rect.x+3)
        {
            barril_rect[1].y=personagem_rect.y+4;
            barril_rect[1].x=personagem_rect.x+4;

            SDL_BlitSurface(gameover,0,tela,&gameover_rect);
            SDL_Flip(tela);
            while(SDL_PollEvent(&evento))
            {
                if(evento.type==SDL_QUIT)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    SDL_Quit();
            }

        }

        while(barril_rect[2].y>=personagem_rect.y && barril_rect[2].y<=personagem_rect.y+76 && barril_rect[2].x<=personagem_rect.x+23 && barril_rect[2].x>=personagem_rect.x+3)
        {
            barril_rect[2].y=personagem_rect.y+4;
            barril_rect[2].x=personagem_rect.x+4;

            SDL_BlitSurface(gameover,0,tela,&gameover_rect);
            SDL_Flip(tela);
            while(SDL_PollEvent(&evento))
            {
                if(evento.type==SDL_QUIT)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    SDL_Quit();
            }

        }

        while(barril_rect[3].y>=personagem_rect.y && barril_rect[3].y<=personagem_rect.y+76 && barril_rect[3].x<=personagem_rect.x+23 && barril_rect[3].x>=personagem_rect.x+3)
        {
            barril_rect[3].y=personagem_rect.y+4;
            barril_rect[3].x=personagem_rect.x+4;

            SDL_BlitSurface(gameover,0,tela,&gameover_rect);
            SDL_Flip(tela);
            while(SDL_PollEvent(&evento))
            {
                if(evento.type==SDL_QUIT)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    SDL_Quit();
            }

        }

        while(barril_rect[4].y>=personagem_rect.y && barril_rect[4].y<=personagem_rect.y+76 && barril_rect[4].x<=personagem_rect.x+23 && barril_rect[4].x>=personagem_rect.x+3)
        {
            barril_rect[4].y=personagem_rect.y+4;
            barril_rect[4].x=personagem_rect.x+4;

            SDL_BlitSurface(gameover,0,tela,&gameover_rect);
            SDL_Flip(tela);
            while(SDL_PollEvent(&evento))
            {
                if(evento.type==SDL_QUIT)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    SDL_Quit();
            }

        }
        while(personagem_rect.x<=princesa_rect.x+105 && personagem_rect.y<=princesa_rect.y+74)
        {
            SDL_BlitSurface(gameover,0,tela,&gameover_rect);
            SDL_Flip(tela);
            while(SDL_PollEvent(&evento))
            {
                if(evento.type==SDL_QUIT)
                    saida = 1;
                if(evento.key.keysym.sym==SDLK_RETURN)
                    SDL_Quit();
            }
        }

        blit();
        }
    }

    Mix_FreeMusic(music);
    music = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
