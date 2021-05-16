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

void set_scaled_point(Env* env, point_s* point, point_s* scaled_point){
    point_set_coordinates(scaled_point, env->base.x + (point->x - Xmin(env->hash_points))*env->multiplier, env->base.y + (Ymax(env->hash_points) - point->y)*env->multiplier);
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

    int xmax = Xmax(hash_points);
    int ymax = Ymax(hash_points);
    int xmin = Xmin(hash_points);
    int ymin = Ymin(hash_points);
    
    env->multiplier = min(w/(xmax-xmin+4), h/(ymax-ymin+4));

    env->base.w = (xmax-xmin)*env->multiplier;
    env->base.h = (ymax-ymin)*env->multiplier;
    env->base.x = w/2 - env->base.w/2;
    env->base.y = h/2 - env->base.h/2;
        
    heap_s* heap_points = heap_new((xmax-xmin+1)*(ymax-ymin+1));

    for(uint i=0; i<env->last_edge_point_index; i++){
        heap_add(heap_points, hash_points->p_cell[i]);
    }

    bool is_pavable = is_map_pavable(heap_points, hash_points, half_points, nb_half_points, xmax);
    if(is_pavable) printf("L'aire est pavable\n");

    point_print(env->hash_points->p_cell[1]->point);

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
    /*for(uint i=0; i<env->last_edge_point_index; i++){
        SDL_RenderDrawLine(ren, get_scaled_point(env, env->hash_points->p_cell[i]->point)->x, get_scaled_point(env, env->hash_points->p_cell[i]->point)->y, 
        get_scaled_point(env, env->hash_points->p_cell[(i+1)%env->last_edge_point_index]->point)->x, get_scaled_point(env, env->hash_points->p_cell[(i+1)%env->last_edge_point_index]->point)->y);
    }*/

    /*DESSINE LES DOMINOS*/
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
    point_s* E = point_new(0, 0);
    point_s* N = point_new(0, 0);
    point_s* scaled_point_i = point_new(0,0);
    point_s* scaled_point_f = point_new(0,0);
    for(uint i=0; i<env->nb_points; i++){
        point_set_coordinates(E, env->hash_points->p_cell[i]->point->x, env->hash_points->p_cell[i]->point->y);
        point_set_coordinates(N, env->hash_points->p_cell[i]->point->x, env->hash_points->p_cell[i]->point->y);
        next_point(E, EST);
        next_point(N, NORTH);
        
        if(is_inside(env->hash_points, E, env->half_points, env->nb_half_points, Xmax(env->hash_points))){
            if(abs(hash_search(env->hash_points, env->hash_points->p_cell[i]->point) - hash_search(env->hash_points, E)) == 1){
                if(hash_search(env->hash_points, E) != INT_MAX){
                    set_scaled_point(env, env->hash_points->p_cell[i]->point, scaled_point_i);
                    set_scaled_point(env, E, scaled_point_f);
                    SDL_RenderDrawLine(ren, scaled_point_i->x, scaled_point_i->y, scaled_point_f->x, scaled_point_f->y);
                }
            }
        }
        if(is_inside(env->hash_points, N, env->half_points, env->nb_half_points, Xmax(env->hash_points))){
            if(abs(hash_search(env->hash_points, env->hash_points->p_cell[i]->point) - hash_search(env->hash_points, N)) == 1){
                if(hash_search(env->hash_points, N) != INT_MAX){
                    set_scaled_point(env, env->hash_points->p_cell[i]->point, scaled_point_i);
                    set_scaled_point(env, N, scaled_point_f);
                    SDL_RenderDrawLine(ren, scaled_point_i->x, scaled_point_i->y, scaled_point_f->x, scaled_point_f->y);
                }
            }
        }
    }
    point_delete(scaled_point_i);
    point_delete(scaled_point_f);
    point_delete(E);
    point_delete(N);
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    
    if (e->type == SDL_QUIT) {
        return true;
    }/*
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
    }*/
    
    return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
    /* PUT YOUR CODE HERE TO CLEAN MEMORY */
    hash_delete(env->hash_points);
    for(uint i=0; i<env->nb_half_points; i++){
        point_delete(env->half_points[i]);
    }
    free(env->half_points);
    
    free(env);
}

/* **************************************************************** */
