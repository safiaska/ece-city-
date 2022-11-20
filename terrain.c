#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

typedef struct Case
{
    int matricechoix;
    int coord_x;
    int coord_y;
    int blind;
}Case;

void PlateauVierge(BITMAP * buffer)
{
    int i,j=0;
    //plateau vierge
    j=52;
    for(i=0;i<35;i++)
    {
        rectfill(buffer,72,37,972,737,makecol(0,171,100));
    }

    //cadrillage 35x45
    for(i=0;i<45+1;i++)
    {
        vline(buffer, 20+j, 38,737, makecol(0,151,80));
        j=j+20;
    }

    j=17;

    for(i=0;i<35+1;i++)
    {
        hline(buffer, 72, 20+j, 972, makecol(0,151,80));
        j=j+20;
    }
}



int ChoixItem(int choix, BITMAP * buffer, BITMAP ** tab_image)
{
    //choix du bitmap a mettre
    rectfill(buffer,1100,200,1160,260, makecol(3,103,53));
    rectfill(buffer,1100,500,1160,560, makecol(3,103,53));
    masked_blit(tab_image[1],buffer, 0, 0, 1100, 200,tab_image[1]->w,tab_image[1]->h);
    masked_blit(tab_image[2],buffer, 0, 0, 1100, 500,tab_image[2]->w,tab_image[2]->h);

    //choix maison
    if(mouse_x>1100 && mouse_x<11600 && mouse_y>200 && mouse_y<260)
        if(mouse_b & 1)
            choix=1;

    //choix gratteciel
    if(mouse_x>1100 && mouse_x<11600 && mouse_y>500 && mouse_y<560)
        if(mouse_b & 1)
            choix=2;

    return choix;
}

void SurbrillancedeCase(BITMAP * buffer, Case tableauCase[45][35], int choix)
{
    int i,j=0;
    //surbrillance des cases
    for(i=0;i<45;i++)
        for(j=0;j<35;j++)
        if (mouse_x > 72 + 20 * i && mouse_x < 92 + 20 * i && mouse_y > 37+20*j && mouse_y < 57+20*j && tableauCase[i][j].blind!=1)
            {
                rectfill(buffer, 72 + 20 * i, 37+20*j, 92 + 20 * i, 57+20*j, makecol(255, 255, 0));

                if(tableauCase[i][j].matricechoix>0)
                    rectfill(buffer,72 + 20 * i, 37+20*j, 92 + 20 *i, 57+20*j, makecol(255, 0, 0));

                if(mouse_b & 1)
                    {
                        tableauCase[i][j].matricechoix=choix;
                        tableauCase[i][j].coord_x=72 + 20 * i;
                        tableauCase[i][j].coord_y=37+20*j;
                    }
            }
}

void PlacementItem(BITMAP ** tab_image, BITMAP * buffer, Case tableauCase[45][35]) {

    //placement de cases
    for(int i=0;i<45;i++) {
        for (int j = 0; j < 35; j++) {
            if (tableauCase[i][j].matricechoix == 1) {
                masked_blit(tab_image[1], buffer, 0, 0, tableauCase[i][j].coord_x,
                            tableauCase[i][j].coord_y,
                            tab_image[1]->w, tab_image[1]->h);
                //blindage des cases
                tableauCase[i][j].blind=1;
                tableauCase[i][j+1].blind=1;
                tableauCase[i][j+2].blind=1;
                tableauCase[i+1][j].blind=1;
                tableauCase[i+1][j+1].blind=1;
                tableauCase[i+1][j+2].blind=1;
                tableauCase[i+2][j].blind=1;
                tableauCase[i+2][j+1].blind=1;
                tableauCase[i+2][j+2].blind=1;
            }
            if(tableauCase[i][j].matricechoix==2) {
                masked_blit(tab_image[2], buffer, 0, 0, tableauCase[i][j].coord_x, tableauCase[i][j].coord_y,
                            tab_image[2]->w, tab_image[2]->h);
                tableauCase[i][j].blind=1;
                tableauCase[i][j+1].blind=1;
                tableauCase[i][j+2].blind=1;
                tableauCase[i+1][j].blind=1;
                tableauCase[i+1][j+1].blind=1;
                tableauCase[i+1][j+2].blind=1;
                tableauCase[i+2][j].blind=1;
                tableauCase[i+2][j+1].blind=1;
                tableauCase[i+2][j+2].blind=1;
            }

        }
    }
}

int main()
{
    int i, j, choix = 1;

    struct Case tableauCase[45][35];

    for(i=0;i<45;i++)
        for(j=0;j<35;j++)
            tableauCase[i][j].matricechoix=0;

    for(i=0;i<45;i++)
        for(j=0;j<35;j++)
            tableauCase[i][j].blind=0;

    //coordonnées de la souris
    extern volatile int mouse_x;
    extern volatile int mouse_y;
    extern volatile int mouse_z;
    extern volatile int mouse_b;

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1300,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_W,SCREEN_H,0,0))!=0)
    {
        allegro_message("Pb de mode graphique");
        allegro_exit();        exit(EXIT_FAILURE);
    }

    //buffers
    BITMAP * buffer;
    BITMAP * doublebuffer;
    buffer=create_bitmap(1300,768);
    doublebuffer=create_bitmap(1300,768);

    //images
    BITMAP * tab_image[3];

    //maison
    tab_image[1]= load_bitmap("MaisonChampi.bmp", NULL);
    //gratte ciel
    tab_image[2]= load_bitmap("GratteCielChampi.bmp",NULL);
    //route 1
    tab_image[3]= load_bitmap("route1.bmp", NULL);


    ///cadrillage centré 45x35 (pixels 20x20)

    while(!key[KEY_ESC])
    {
        show_mouse(buffer);
        clear(buffer);
        clear(doublebuffer);

        PlateauVierge(buffer);
        choix= ChoixItem(choix,buffer,tab_image);
        SurbrillancedeCase(buffer,tableauCase,choix);
        PlacementItem(tab_image,buffer,tableauCase);

        /* Maintenant, il faut copier le contenu de notre buffer dans l’écran */
            blit(buffer, doublebuffer, 0, 0, 0, 0, 1300, 768) ;

        blit(doublebuffer,screen,0,0,0,0,1300,768);

    }

    readkey();

    return 0;
}
END_OF_MAIN();
