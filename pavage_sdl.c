// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>

#include "model.h"

/* **************************************************************** */

int main(int argc, char* argv[]) {
    if (argc > 4) {
        uint size = argc - 1;
        char directions_char[size];
        for (uint i = 0; i < size; i++) {
            directions_char[i] = argv[i + 1][0];
        }
        directions_char[size] = '\0';
        direction directions[size];
        uint nb_N = 0, nb_S = 0, nb_E = 0, nb_W = 0;
        for (uint i = 0; i < size; i++) {
            switch (directions_char[i]) {
                case 'N':
                    nb_N++;
                    directions[i] = NORTH;
                    break;
                case 'S':
                    nb_S++;
                    directions[i] = SOUTH;
                    break;
                case 'E':
                    nb_E++;
                    directions[i] = EST;
                    break;
                case 'W':
                    nb_W++;
                    directions[i] = WEST;
                    break;
                default:
                    fprintf(stderr, "Unknown direction\n");
                    break;
            }
        }
        if (!(nb_N == nb_S && nb_E == nb_W)) {
            fprintf(stderr, "Le contour n'est pas correcte\n");
            exit(EXIT_FAILURE);
        }
		uint nb_points = (nb_N + 1) * (nb_W + 1);
		hash_s* hash_points = hash_new(nb_points);
		
		point_s* *half_points = (point_s**)malloc(size / 2 * sizeof(point_s));
		int nb_half_points = 0;
		state result = fill_map_edge_from_direction_list(directions, size, hash_points, &nb_half_points, half_points);
		switch (result) {
            case EDGE_IS_LOOPING:
                printf("Le contour forme une boucle\n");
                exit(EXIT_FAILURE);
                break;
            case EDGE_IS_DISCONNECTED:
                printf("Le contour ne se ferme pas\n");
                exit(EXIT_FAILURE);
                break;
            case EDGE_IS_CONNECTED:
                printf("Le contour est fermé\n");
                exit(EXIT_FAILURE);
                break;
            case AREA_IS_MAYBE_PAVABLE:
                printf("L'aire est peut être pavable\n");
                //Lancement de la fenêtre
                break;
            case AREA_IS_NOT_PAVABLE:
                printf("L'aire n'est pas pavable\n");
                exit(EXIT_FAILURE);
                break;
            case AREA_IS_PAVABLE:
                printf("L'aire est pavable\n");
                break;
            case ERROR_DIRECTION_TABLE:
                printf("Direction inconnue\n");
                exit(EXIT_FAILURE);
                break;
            case ERROR_MAP:
                printf("Table de hash incorrecte\n");
                exit(EXIT_FAILURE);
                break;
            default:
                printf("Erreur inconnue\n");
                exit(EXIT_FAILURE);
                break;
        }

    /* initialize SDL2 and some extensions */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) ERROR("Error: SDL_Init VIDEO (%s)", SDL_GetError());
    if (IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG) != IMG_INIT_PNG) ERROR("Error: IMG_Init PNG (%s)", SDL_GetError());
    if (TTF_Init() != 0) ERROR("Error: TTF_Init (%s)", SDL_GetError());

    /* create window and renderer */
    SDL_Window* win = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!win) ERROR("Error: SDL_CreateWindow (%s)", SDL_GetError());
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (!ren) ERROR("Error: SDL_CreateRenderer (%s)", SDL_GetError());
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    /* initialize your environment */
    Env* env = init(win, ren, argc, argv, hash_points, nb_points, half_points, nb_half_points);

    /* main render loop */
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        /* manage events */
        while (SDL_PollEvent(&e)) {
            /* process your events */
            quit = process(win, ren, env, &e);
            if (quit) break;
        }

        /* background in gray */
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
        SDL_RenderClear(ren);

        /* render all what you want */
        render(win, ren, env);
        SDL_RenderPresent(ren);
        SDL_Delay(DELAY);
    }

    /* clean your environment */
    clean(win, ren, env);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    }
    else{
        printf("Le nombre de coordonnées entrées au programme est insuffisant !\n");
    }

    return EXIT_SUCCESS;
}
