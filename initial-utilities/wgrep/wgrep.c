#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int hasPipeInput = !isatty(fileno(stdin));

    if (argc < 2) {
        printf("%s", "wgrep: searchterm [file ...]\n");
        return 1;
    }    

    char *pattern = argv[1];
    FILE *file;
    if (hasPipeInput) {
        argc++;
        file = stdin;
    }
    for (int i = 2; i < argc; i++) {
        if (!hasPipeInput) {
            char *fileRoute = argv[i];
            file = fopen(fileRoute, "r");
        }

        if (file == NULL) {
            printf("%s", "wgrep: cannot open file\n");
            return 1;
        }

        char buffer[255];

        while(fgets(buffer, sizeof(buffer), hasPipeInput ? stdin : file)) {
           if(strstr(buffer, pattern)) {
               printf("%s", buffer);
            } 
        }
        
        fclose(file);
        return 0;
    } 
}
