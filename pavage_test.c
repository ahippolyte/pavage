#include "tools.h"
#include "coordinate.h"
#include "hash_table.h"

<<<<<<< HEAD
int main(int argc, char* argv[]) {
=======
/*---------------- COORDINATE ---------------*/

/**     test_coordinate_new    **/

bool test_coordinate_new()
{
    coordinate_s *coordinate = coordinate_new(1, 1);
    if (coordinate->x != 1 || coordinate->y != 1)
    {
        coordinate_delete(coordinate);
        return false;
    }
    coordinate_delete(coordinate);
    return true;
}

/**     test_coordinate_compare    **/

bool test_coordinate_compare()
{
    coordinate_s *coordinate_1 = coordinate_new(1, 1);
    coordinate_s *coordinate_2 = coordinate_new(1, 1);
    coordinate_s *coordinate_3 = coordinate_new(1, 2);

    if (coordinate_compare(coordinate_1, coordinate_2) != true)
    {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_2);
        return false;
    }

    if (coordinate_compare(coordinate_1, coordinate_3) != false)
    {
        coordinate_delete(coordinate_1);
        coordinate_delete(coordinate_3);
        return false;
    }
    coordinate_delete(coordinate_1);
    coordinate_delete(coordinate_2);
    coordinate_delete(coordinate_3);
    return true;
}

/*---------------- HASH_TABLE ---------------*/

/**     test_hash_new    **/

bool test_hash_new()
{

    return true;
}

/**     test_hash_add    **/

bool test_hash_add()
{
    return true;
}

/**     test_hash_search    **/

bool test_hash_search()
{
    return true;
}

/**     test_hash_delete   **/

bool test_hash_delete()
{

    return true;
}

/*-------------- fonction usage --------------*/

void usage(int argc, char *argv[])
{
    fprintf(stderr, "Usage: %s <nom du test>\n", argv[0]);
    exit(EXIT_FAILURE);
}

/*-------------- fonction main --------------*/

int main(int argc, char *argv[])
{
>>>>>>> 71e4d98d8a6e8aff83ea33519816c21c68bcfc6e
    printf("Beginning tests...\n");
    return EXIT_SUCCESS;
}