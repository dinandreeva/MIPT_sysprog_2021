#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <sys/stat.h>
#include "header.h"

int main(){
    ReadOnegin("onegin.txt")
}

int ReadOnegin(char path[]) {
    FILE *poem;
    poem = fopen(*path, "r");
    if (poem == NULL) {
        printf("Cannot open file.\n");
        return 0;
    } else {
        struct stat finfo;
        stat(*path, &finfo);
        
    }

}
