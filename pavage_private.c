#include "pavage_private.h"

cell_s* cell_new(point_s* s, int height){
    cell_s* cell = (cell_s*)malloc(sizeof(cell_s));
    if(cell == NULL){
        fprintf(stderr, "Allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    cell->point = s;
    cell->height = height;
    return cell;
}

bool cell_is_equal(cell_s* cell1, cell_s* cell2){
    if(cell1 == NULL || cell2 == NULL){
        fprintf(stderr,"Invalid pointer adress!\n");
        exit(EXIT_FAILURE);
    }
    return (point_is_equal(cell1->point, cell2->point) && cell1->height == cell2->height);
}

void cell_delete(cell_s* cell){
    point_delete(cell->point);
    free(cell);
}

int get_height_from_cell(cell_s* *tab, point_s* p){
    
}