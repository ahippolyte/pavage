#include "pavage.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        uint size = argc - 1;
        char directions[size];
        for (uint i = 0; i < size; i++) {
            directions[i] = argv[i + 1][0];
        }
        directions[size] = '\0';
        hash_s* hash = hash_new(size);
        queue_s* queue = queue_new(size);
        for (uint i = 0; i < size; i++) {
            switch (directions[i]) {
                case 'N':
                    queue_enqueue(queue, NORTH);
                    break;
                case 'S':
                    queue_enqueue(queue, SOUTH);
                    break;
                case 'E':
                    queue_enqueue(queue, EST);
                    break;
                case 'W':
                    queue_enqueue(queue, WEST);
                    break;
                default:
                    fprintf(stderr, "Unknown direction\n");
                    break;
            }
        }
        point_s** inter_points = (point_s**)malloc(size / 2 * sizeof(point_s));
        uint nb_inter_points = 0;
        state result = get_edge_from_direction_list(queue, hash, inter_points, &nb_inter_points);
        switch (result) {
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
                break;
        }

        hash_print(hash);
    }

    return EXIT_SUCCESS;
}