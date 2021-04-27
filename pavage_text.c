#include "pavage.h"

int main(int argc, char* argv[]) {
    
    if(argc > 1){
        uint size = argc-1;
        char directions[size];
        for(uint i=0; i<size; i++){
            directions[i] = argv[i+1][0];
        }
        directions[size] = '\0';
        printf("String : %s\n", directions);
    }
    
    return EXIT_SUCCESS;
}