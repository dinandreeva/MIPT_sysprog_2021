#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <sys/stat.h>
#include "header.h"

typedef enum C_DETECT {
    WHITESPACE = 0,
    POEM = 1,
    POEM_END = 2,
    UNDEFINED = -1
};

int main () {
    ReadOnegin ("onegin.txt")
}

FILE* ReadFile (char path[], FILE* data) {
    data = fopen (path, "r");
    assert (data != NULL);
    return data;
}

FILE* WriteToFile ()

int CountLines (char* path[], int* max_length) {
    
    return lines;
}

int CleanOnegin (char raw_path[]) {
    FILE* raw_poem = NULL;
    raw_poem = ReadFile(raw_path, raw_poem);


    char ch = "";
    int n_lines = 0;
    int line_length = 1; // How to check if file is empty?
    int max_lenth = 1;

    CHAR_TYPE c_type = UNDEFINED;

    while ((ch = getc (raw_poem)) != EOF) {
        switch (ch) {
            case ' ':
            case '\t':
                if (c_type == POEM) {
                    c
                }
                c_type = WHITESPACE;

        }

        // Подготовка к переходу на следующую строку
        ++line_length;
        if (ch == "\n") {
            n_lines++;
            if (max_length < line_length) {
                max_length = line_length;
            }
            line_length = 1; // \n also counts
        }
    }

}
int ReadOnegin (char path[]) {
    // Открываем файл
    FILE *poem;
    poem = ReadFile(path, poem);

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
        *onegin = buff;
        index[j] = onegin;
}
