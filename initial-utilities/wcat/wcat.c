#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        char *fileRoute = argv[i];
        FILE *file = fopen(fileRoute, "r");
        if (file == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        } 
        char buffer[255];

        while(fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        fclose(file);
    }
    return 0;
}
