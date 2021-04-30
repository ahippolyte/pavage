#include "pavage.h"

int main(int argc, char* argv[]) {
    
    if(argc > 1){
        uint size = argc-1;
        char directions[size];
        for(uint i=0; i<size; i++){
            directions[i] = argv[i+1][0];
        }
        directions[size] = '\0';
        hash_s * hash = hash_new();
        queue_s * queue = queue_new(size);
        for(uint i=0; i<size; i++){
            switch(directions[i]){
                case 'N' :
                    queue_enqueue(queue, NORTH);
                    break;
                case 'S' :
                    queue_enqueue(queue, SOUTH);
                    break;
                case 'E' :
                    queue_enqueue(queue, EST);
                    break;
                case 'W' :
                    queue_enqueue(queue, WEST);
                    break;
                default :
                    fprintf(stderr, "Unknown direction\n");
                    break;
            }
        }
        how_fill_fonction_worked state = fill_map_edge_from_direction_list(queue, hash);
        switch (state){
        case SHAPE_IS_MAYBE_PAVABLE:
            printf("Le contour est peut-être pavable\n");
            break;
        case SHAPE_IS_NOT_PAVABLE:
            printf("Le contour n'est pas pavable\n");
            break;
        case EDGE_IS_DISCONNECTED:
            printf("Le contour est ouvert\n");
            break;
        case ERROR_DIRECTION_TABLE:
            printf("Erreur dans la liste des directions\n");
            break;
        case ERROR_MAP:
            printf("Erreur dans la table de hash\n");
            break;
        default:
            break;
        }

        hash_print(hash);
    }
    
    return EXIT_SUCCESS;
}