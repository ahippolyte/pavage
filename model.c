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

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[], hash_s* hash_points, uint nb_points, point_s* *half_points, int nb_half_points) {
    Env *env = malloc(sizeof(struct Env_t));

    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    env->hash_points = hash_points;
    env->nb_points = nb_points;
    env->half_points = half_points;
    env->nb_half_points = nb_half_points;

    env->last_edge_point_index = argc-1;
    
    env->multiplier = 40;

    env->base.w = env->multiplier * (Xmax(hash_points) - Xmin(hash_points));
    env->base.h = env->multiplier * (Ymax(hash_points) - Ymin(hash_points));
    env->base.x = w/2 - env->base.w/2;
    env->base.y = h/2 - env->base.h/2;
        
    heap_s* heap_points = heap_new((Xmax(hash_points)-Xmin(hash_points)+1)*(Ymax(hash_points)-Ymin(hash_points)+1));
    for(uint i=0; i<env->last_edge_point_index; i++){
        heap_add(heap_points, hash_points->p_cell[i]);
    }

    bool is_pavable = is_map_pavable(heap_points, hash_points, half_points, nb_half_points, Xmax(hash_points));
    if(is_pavable) printf("L'aire est pavable\n");

    env->scaled_points = (point_s**)malloc(nb_points*sizeof(point_s*));
    
    for(uint i=0; i<env->nb_points; i++){
        env->scaled_points[i] = point_copy(hash_get_point(hash_points, i));
        env->scaled_points[i]->x = (int)env->scaled_points[i]->x*env->multiplier;
        env->scaled_points[i]->y = (int)env->scaled_points[i]->y*env->multiplier;
    }
    
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
        SDL_RenderDrawLine(ren, env->base.x+env->scaled_points[i]->x, env->base.y+env->scaled_points[i]->y, env->base.x+env->scaled_points[(i+1)%env->last_edge_point_index]->x, env->base.y+env->scaled_points[(i+1)%env->last_edge_point_index]->y);
    }

    /*DESSINE LES DOMINOS*/
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    point_s* iter = point_new(Xmin(env->hash_points), Ymin(env->hash_points));
    for(uint x=Xmin(env->hash_points); x<Xmax(env->hash_points); x++){
        for(uint y=Ymin(env->hash_points); y<Ymax(env->hash_points); y++){
            point_set_x(iter, x);
            point_set_y(iter, y);
            if(is_inside(env->hash_points, iter, env->half_points, env->nb_half_points, Xmax(env->hash_points))){
                if(is_inside(env->hash_points, next_point(iter, EST), env->half_points, env->nb_half_points, Xmax(env->hash_points))){
                    if(abs( hash_search(env->hash_points, iter) - hash_search(env->hash_points, next_point(iter, EST)) ) == 1 ){
                        SDL_RenderDrawLine(ren, env->base.x+( (int)iter->x-Xmin(env->hash_points) )*env->multiplier, env->base.y+( (int)iter->y-Ymin(env->hash_points) )*env->multiplier, env->base.x+( (int)next_point(iter, EST)->x-Xmin(env->hash_points) )*env->multiplier, env->base.y+( (int)next_point(iter, EST)->y-Ymin(env->hash_points) )*env->multiplier);
                    }
                }


                if(is_inside(env->hash_points, next_point(iter, NORTH), env->half_points, env->nb_half_points, Xmax(env->hash_points))){  
                    if(abs( hash_search(env->hash_points, iter) - hash_search(env->hash_points, next_point(iter, NORTH)) ) == 1 ){
                        SDL_RenderDrawLine(ren, env->base.x+( (int)iter->x-Xmin(env->hash_points) )*env->multiplier, env->base.y+( (int)iter->y-Ymin(env->hash_points) )*env->multiplier, env->base.x+( (int)next_point(iter, NORTH)->x-Xmin(env->hash_points) )*env->multiplier, env->base.y+( (int)next_point(iter, NORTH)->y-Ymin(env->hash_points) )*env->multiplier);
                    }
                }

            }
            
        }
    }

}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
    if (e->type == SDL_QUIT) {
        return true;
    }

    /* PUT YOUR CODE HERE TO PROCESS EVENTS */

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
