#include <stdio.h>

int main(int argc, char *argv[]) {
   if (argc < 2) {
        printf("%s", "wzip: file1 [file2 ...]\n");
        return 1;
    }
    
    int count = 0;
    char currentChar = '\0'; 
    for (int i = 1; i < argc; i++) {
        char *fileRoute = argv[i];
        FILE *file = fopen(fileRoute, "r");
        
        if (file == NULL) {
            perror("wzip: cannot open file");
            return 1;
        }
        
        if (currentChar == '\0') {
            currentChar = fgetc(file);
            count++;
        }
        
        if (currentChar == EOF) {
            fclose(file);
            continue;
        } 
        
        char nextChar; 
        while((nextChar = fgetc(file)) != EOF) {
            if (currentChar == nextChar) {
                count++;
            } else {
                fwrite(&count, 4, 1, stdout);
                fwrite(&currentChar, 1, 1, stdout);
                currentChar = nextChar;
                count = 1;
            }
        }
        fclose(file);
    }
    fwrite(&count, 4, 1, stdout);
    fwrite(&currentChar, 1, 1, stdout);
    return 0; 
}
