#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

#ifndef __HEAP_H__
#define __HEAP_H__

// Structure de tas binaire:
//
//  array = tableau de stockage des objets à partir de l'indice 1 (au lieu de 0)
//  n     = nombre d'objets (qui sont des int) stockés dans le tas
//  nmax  = nombre maximum d'objets stockables dans le tas
//
// Attention ! "heap" est défini comme un pointeur pour optimiser les
// appels (empilement d'un mot (= 1 pointeur) au lieu de 4 sinon).

typedef unsigned int uint;

typedef struct {
    cell_s **array;
    int index, size;
} heap_s;

// Crée un tas pouvant accueillir au plus k>0 objets avec une fonction
// de comparaison f() prédéfinie. NB: La taille d'un objet pointé par
// un pointeur h est sizeof(*h). Par exemple, si on déclare une
// variable T comme "double * T;" alors T est une variable de type
// "double*" (avec sizeof(T)=4) et *T est une variable de type
// "double" (avec sizeof(*T)=8).
heap_s *heap_new(const uint size);

// Renvoie l'objet en haut du tas h, c'est-à-dire l'élément minimal
// selon f(), sans le supprimer. On supposera h!=NULL. Renvoie NULL si
// le tas est vide.
cell_s *heap_top(const heap_s *heap);

// Comme heap_top() sauf que l'objet est en plus supprimé du
// tas. Renvoie NULL si le tas est vide.
cell_s *heap_pop(heap_s *heap);

// Ajoute un objet au tas h. On supposera h!=NULL. Renvoie vrai s'il
// n'y a pas assez de place, et faux sinon.
void heap_add(heap_s *heap, const cell_s *cell);

// Renvoie vrai si le tas h est vide, faux sinon. On supposera
// h!=NULL.
bool heap_empty(const heap_s *heap);

// Print heap
void heap_print(const heap_s *heap);

// Détruit le tas h. On supposera h!=NULL. Attention ! Il s'agit de
// libérer ce qui a été alloué par heap_create(). NB: Les objets
// stockés dans le tas n'ont pas à être libérés.
void heap_delete(heap_s *heap);

#endif  //__HEAP_H__