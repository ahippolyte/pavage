#include "pavage.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        uint size = argc - 1;
        char directions_char[size];
        for (uint i = 0; i < size; i++) {
            directions_char[i] = argv[i + 1][0];
        }
        directions_char[size] = '\0';
        direction directions[size];
        uint nb_N=0, nb_S=0, nb_E=0, nb_W=0;
        for(uint i=0; i<size; i++){
            switch (directions_char[i]) {
                case 'N' :
                    nb_N++;
                    directions[i] = NORTH;
                    break;
                case 'S' :
                    nb_S++;
                    directions[i] = SOUTH;
                    break;
                case 'E' :
                    nb_E++;
                    directions[i] = EST;
                    break;
                case 'W' :
                    nb_W++;
                    directions[i] = WEST;
                    break;
                default:
                    fprintf(stderr, "Unknown direction\n");
                    break;
            }
        }
        if(!(nb_N == nb_S && nb_E == nb_W)){
            fprintf(stderr, "Le contour n'est pas correcte");
            exit(EXIT_FAILURE);
        }
        hash_s* hash = hash_new((nb_N+1)*(nb_W+1));
        printf("%d\n",(nb_N+1)*(nb_W+1));
        
        point_s** inter_points = (point_s**)malloc(size / 2 * sizeof(point_s));
        int nb_inter_points = 0;

        state result = fill_map_edge_from_direction_list(directions, size, hash, &nb_inter_points, inter_points);
        switch (result) {
            case EDGE_IS_LOOPING:
                printf("Le contour forme une boucle\n");
                break;
            case EDGE_IS_DISCONNECTED:
                printf("Le contour ne se ferme pas\n");
                break;
            case EDGE_IS_CONNECTED:
                printf("Le contour est connecté\n");
                break;
            case AREA_IS_MAYBE_PAVABLE:
                printf("L'aire est peut être pavable\n");
                break;
            case AREA_IS_NOT_PAVABLE:
                printf("L'aire n'est pas pavable\n");
                break;
            case AREA_IS_PAVABLE:
                printf("L'aire est pavable\n");
                break;
            case ERROR_DIRECTION_TABLE:
                printf("Direction inconnue\n");
                break;
            case ERROR_MAP:
                printf("Table de hash incorrecte\n");
                break;
            default:
                printf("Erreur inconnue\n");
                break;
        }

        for(uint i=0; i<nb_inter_points; i++){
            point_print(inter_points[i]);
        }
    }

    return EXIT_SUCCESS;
}