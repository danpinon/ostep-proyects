#include <stdio.h>
#include <string.h>

typedef struct {
    int count;
    char character; 
} CompressedBlock;

CompressedBlock parseBlock(char chunk[5]);

int main(int argc, char *argv[]) {
    if (argc < 2) { //no arguments passed to the program
        printf("%s", "wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *fileRoute = argv[i];
        FILE *file = fopen(fileRoute, "r");

        if (file == NULL) {
            fclose(file);
            continue;
        }
        
        char currentChunk[5];
        while(fread(&currentChunk, 5, 1, file) != 0) {
            CompressedBlock block = parseBlock(currentChunk);
            for (int n = 0; n < block.count; n++) {
                printf("%c", block.character);
            }
        }
    }

    return 0;
}

CompressedBlock parseBlock(char chunk[5]) {
    CompressedBlock output;
    memcpy(&output.count, chunk, sizeof(int));
    output.character = chunk[4];
    return output; 
}
