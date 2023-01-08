#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE "10000*sizeof(int)"
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage:\n%s <Source File>", argv[0]);
        return -1;
    }
    FILE *in = fopen(argv[1], "r"), *out = fopen("temp.c", "w");
    fputs("#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n"
          "int main(){int*p=malloc(" MAX_SIZE ");memset(p,0," MAX_SIZE ");",
          out);
    char c;
    while ((c = fgetc(in)) != EOF)
        switch (c) {
        case '+':
            fputs("++*p;", out);
            break;
        case '-':
            fputs("--*p;", out);
            break;
        case '>':
            fputs("++p;", out);
            break;
        case '<':
            fputs("--p;", out);
            break;
        case '[':
            fputs("while(*p){", out);
            break;
        case ']':
            fputs("}", out);
            break;
        case '.':
            fputs("putchar(*p);", out);
            break;
        case ',':
            fputs("*p=getchar();", out);
            break;
        }
    fputs("return 0;}", out);
    fclose(in);
    fclose(out);
    char cmd[1000];
    sprintf(cmd, "gcc temp.c -o %s.exe&del temp.c", argv[1]);
    system(cmd);
    return 0;
}