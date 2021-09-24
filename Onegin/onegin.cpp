#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <sys/stat.h>
#include "header.h"

int main () {
    ReadOnegin ("onegin.txt")
}

int CountLines (char* path[], int* max_length) {
    char ch = "";
    int lines = 1;  // last line counts
    int line_length = 1; // How to check if file is empty?

    while ((ch = getc (poem)) != EOF) {
        ++line_length;
        if (ch == "\n") {
            lines++;
            line_length = 1; // \n also counts
            if (*max_length < line_length) {
                *max_length = line_length;
            }
        }
    }
    return lines;
}

int ReadOnegin (char* path[]) {
    FILE *poem;
    poem = fopen (path, "r");
    if (poem == NULL) {
        printf ("Cannot open file.\n");
        return -1;
    } else {
        (int* max_length = calloc ()) == NULL
        CountLines(poem)
        char* index[lines];
        // struct stat finfo;
        // stat(*path, &finfo);
        char buff [];
        int i = 0;
        while ((ch = getc (poem)) != "\n") {
            *(buff + i) = ch;
            ++i;
        }
        int j = 0;
        if (char* onegin = calloc (sizeof(buff)/sizeof(buff[0]), sizeof(buff[0])) == NULL) {
            printf("No memory available. \n");
            return -1;
        } else {
            // 
            *onegin = buff;
            index[j] = onegin;
    }
}
