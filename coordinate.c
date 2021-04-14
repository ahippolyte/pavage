#include "coordinate.h"

coordinate_s *coordinate_new(int x, int y){
    coordinate_s *coordinate = NULL;
    coordinate = malloc(sizeof(*coordinate));
    if (coordinate != NULL)
    {
        coordinate->x = x;
        coordinate->y = y;
    }
    else
    {
        fprintf(stderr, "Memoire insufisante\n");
        exit(EXIT_FAILURE);
    }
    return (coordinate);
}