#include "asciiart.h"

void cutecat(){
    printf("  /\\_/\\   \n");
    printf(" ( ^w^ )  \n");
    printf("  > ^ <   \n");
    printf(" /     \\ \n");
    printf(" \\__|__/  \n");
}


void grumpycat(){
    printf(" /\\_/\\\n");
    printf("( =.= )\n");
    printf("  ----\n");
    printf("/     \\ \n");
    printf("\\__|__/  \n");
}


void dumbcat(){
    printf(" /\\_/\\\n");
    printf("( o o )\n");
    printf("==_Y_==\n");
    printf("/     \\ \n");
    printf("\\__|__/  \n");
}


// Random cat generator
void randomCat(){
    srand(time(NULL));

    // Generate number from 1 to 3
    int number = rand() % 3 + 1;

    // Random cats
    switch (number) {
        case 1:
            cutecat();
            break;
        case 2:
            grumpycat();
            break;
        case 3:
            dumbcat();
            break;
        default:
            printf("An error has occured when generating random cat.\n");
    }
}