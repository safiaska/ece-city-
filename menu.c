void menu()
{
    initialisation_allegro();
    show_mouse (screen);
    int quitter = 0;
    BITMAP* imagemenu = create_bitmap (SCREEN_H, SCREEN_W);
    imagemenu = load_bitmap ("fondmenu.bmp", NULL);
    while (quitter != 1)
    {
        blit (imagemenu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        while (mouse_x >=275 &  mouse_x <= 520 && mouse_y >= 200 && mouse_y <= 250)
        {
            rect(screen, 300, 200, 520, 270, makecol (255, 255, 255));

            if (mouse_b & 1)
            {
                nbjoueur ();
            }
        }

        while (mouse_x >=275 &  mouse_x <= 520 && mouse_y >= 290 && mouse_y <= 340)
        {
            rect(screen, 300, 290, 520, 350, makecol (255, 255, 255));

            if (mouse_b & 1)
            {
                ///sauvegarde ();
            }
        }

        while (mouse_x >=275 &  mouse_x <= 520 && mouse_y >= 390 && mouse_y <= 440)
        {
            rect(screen, 300, 390, 520, 440, makecol (255, 255, 255));

            if (mouse_b & 1)
            {
                quitter = 1;
            }
        }
    }
    return 0;

    fclose (imagemenu);
    imagemenu = NULL;
}
