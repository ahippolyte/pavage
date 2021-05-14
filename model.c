// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include "model.h"
#include "pavage.h"

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* **************************************************************** */

struct Env_t {
    hash_s *hash_points;
	uint nb_points;
    uint last_edge_point_index;
    point_s* *half_points;
    int nb_half_points;
    SDL_Rect base;
    int multiplier;
    point_s* *scaled_points;
};

/* **************************************************************** */


int x_min(point_s* *tab, uint size){
    int x_min = (int)tab[0]->x;
    for(uint i=1; i<size; i++){
        if((int)tab[i]->x < x_min){
            x_min = (int)tab[i]->x;
        }
    }
    return x_min;
}

int y_min(point_s* *tab, uint size){
    int y_min = (int)tab[0]->y;
    for(uint i=1; i<size; i++){
        if((int)tab[i]->y < y_min){
            y_min = (int)tab[i]->y;
        }
    }
    return y_min;
}

int x_max(point_s* *tab, uint size){
    int x_max = (int)tab[0]->x;
    for(uint i=1; i<size; i++){
        if((int)tab[i]->x > x_max){
            x_max = (int)tab[i]->x;
        }
    }
    return x_max;
}

int y_max(point_s* *tab, uint size){
    int y_max = (int)tab[0]->y;
    for(uint i=1; i<size; i++){
        if((int)tab[i]->y > y_max){
            y_max = (int)tab[i]->y;
        }
    }
    return y_max;
}

int min(int a, int b){
    if(a>b) return b;
    return a;
}

int get_point_index_in_tab(point_s* point, point_s* *tab, uint size){
    for(uint i=0; i<size; i++){
        if(point_is_equal(tab[i], point)){
            return i;
        }
    }
    return -1;
}

point_s * get_scaled_point(Env* env, point_s* point){
    return point_new(env->base.x + (point->x - Xmin(env->hash_points))*env->multiplier, env->base.y + (Ymax(env->hash_points) - point->y)*env->multiplier);
}

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[], hash_s* hash_points, uint nb_points, point_s* *half_points, int nb_half_points) {
    Env *env = malloc(sizeof(struct Env_t));

    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    env->hash_points = hash_points;
    env->nb_points = nb_points;
    env->half_points = half_points;
    env->nb_half_points = nb_half_points;

    env->last_edge_point_index = argc-1;
    
    env->multiplier = min(w/(Xmax(hash_points)-Xmin(hash_points)+4), h/(Ymax(hash_points)-Ymin(hash_points)+4));

    env->base.w = (Xmax(hash_points)-Xmin(hash_points))*env->multiplier;
    env->base.h = (Ymax(hash_points)-Ymin(hash_points))*env->multiplier;
    env->base.x = w/2 - env->base.w/2;
    env->base.y = h/2 - env->base.h/2;
        
    heap_s* heap_points = heap_new((Xmax(hash_points)-Xmin(hash_points)+1)*(Ymax(hash_points)-Ymin(hash_points)+1));
    for(uint i=0; i<env->last_edge_point_index; i++){
        heap_add(heap_points, hash_points->p_cell[i]);
    }

    bool is_pavable = is_map_pavable(heap_points, hash_points, half_points, nb_half_points, Xmax(hash_points));
    if(is_pavable) printf("L'aire est pavable\n");

    /**env->scaled_points = (point_s**)malloc(nb_points*sizeof(point_s*));
    
    for(uint i=0; i<env->nb_points; i++){
        env->scaled_points[i] = point_copy(hash_get_point(hash_points, i));
        env->scaled_points[i]->x = (int)env->scaled_points[i]->x*env->multiplier;
        env->scaled_points[i]->y = (int)env->scaled_points[i]->y*env->multiplier;
    }**/
    
    /*
    int xmin = x_min(env->scaled_points, env->nb_points);
    int ymin = y_min(env->scaled_points, env->nb_points);
    for(uint i=0; i<env->nb_points; i++){
        if(xmin < 0){
            point_set_x(env->scaled_points[i], env->scaled_points[i]->x + abs(xmin));
        }
        if(ymin < 0){
            point_set_y(env->scaled_points[i], env->scaled_points[i]->y + abs(ymin));
        }
    }
    */

    return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    /*RECTANGLE DES FRONTIERES*/
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderFillRect(ren, &env->base);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 50);
    SDL_RenderDrawRect(ren, &env->base);

    /*DESSINE LE CONTOUR UNIQUEMENT*/
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    for(uint i=0; i<env->last_edge_point_index; i++){
        SDL_RenderDrawLine(ren, get_scaled_point(env, env->hash_points->p_cell[i]->point)->x, get_scaled_point(env, env->hash_points->p_cell[i]->point)->y, get_scaled_point(env, env->hash_points->p_cell[(i+1)%env->last_edge_point_index]->point)->x, get_scaled_point(env, env->hash_points->p_cell[(i+1)%env->last_edge_point_index]->point)->y);
    }

    /*DESSINE LES DOMINOS*/
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
    point_s* E;
    point_s* N;
    for(uint i=0; i<env->nb_points; i++){
        E = next_point(env->hash_points->p_cell[i]->point, EST);
        N = next_point(env->hash_points->p_cell[i]->point, NORTH);
        
        if(is_inside(env->hash_points, E, env->half_points, env->nb_half_points, Xmax(env->hash_points))){
            if(abs(hash_search(env->hash_points, env->hash_points->p_cell[i]->point) - hash_search(env->hash_points, E)) == 1){
                if(hash_search(env->hash_points, E) != INT_MAX){
                    SDL_RenderDrawLine(ren, get_scaled_point(env, env->hash_points->p_cell[i]->point)->x, get_scaled_point(env, env->hash_points->p_cell[i]->point)->y, get_scaled_point(env, E)->x, get_scaled_point(env, E)->y);
                }
            }
        }
        if(is_inside(env->hash_points, N, env->half_points, env->nb_half_points, Xmax(env->hash_points))){
            if(abs(hash_search(env->hash_points, env->hash_points->p_cell[i]->point) - hash_search(env->hash_points, N)) == 1){
                if(hash_search(env->hash_points, N) != INT_MAX){
                    SDL_RenderDrawLine(ren, get_scaled_point(env, env->hash_points->p_cell[i]->point)->x, get_scaled_point(env, env->hash_points->p_cell[i]->point)->y, get_scaled_point(env, N)->x, get_scaled_point(env, N)->y);
                }
            }
        }
    }
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    
    if (e->type == SDL_QUIT) {
        return true;
    }
    if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED){
        env->multiplier = min(w,h)/env->last_edge_point_index;

        env->base.w = env->multiplier * (Xmax(env->hash_points) - Xmin(env->hash_points));
        env->base.h = env->multiplier * (Ymax(env->hash_points) - Ymin(env->hash_points));
        env->base.x = w/2 - env->base.w/2;
        env->base.y = h/2 - env->base.h/2;

        for(uint i=0; i<env->nb_points; i++){
            env->scaled_points[i]->x = (int)env->scaled_points[i]->x*env->multiplier;
            env->scaled_points[i]->y = (int)env->scaled_points[i]->y*env->multiplier;
        }
    }
    
    return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
    /* PUT YOUR CODE HERE TO CLEAN MEMORY */
    hash_delete(env->hash_points);
    for(uint i=0; i<env->nb_points; i++){
        point_delete(env->scaled_points[i]);
    }
    free(env);
}

/* **************************************************************** */
