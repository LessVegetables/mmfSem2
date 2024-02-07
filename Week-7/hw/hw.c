#include <stdio.h>

int main()
{
    FILE *in, *out;
    in = fopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-2-NSU/Week-7/hw/input.txt", "r");
    out = fopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-2-NSU/Week-7/hw/output.txt", "w");
    
    int const BASIC = 0, COMMENT = 1, QUOTES = 2;
    int mode = 0;
    char c;

    while(fscanf(in, "%c", &c) != EOF){
        if(mode == BASIC){
            if(c == '/'){
                if(fscanf(in, "%c", &c) == EOF){fprintf(out, "/"); break;}
                if(c == '*')mode = COMMENT;
                else fprintf(out, "/");
            }
            else if(c == '\"'){
                mode = QUOTES;
                fprintf(out, "\"");
            }
            else fprintf(out, "%c", c);
        }
        else if(mode == COMMENT){
            if(c == '*'){
                if(fscanf(in, "%c", &c) == EOF){break;}
                if(c == '/')mode = BASIC;
            }
        }
        else if(mode == QUOTES){
            if(c == '\"'){
                mode = BASIC;
                fprintf(out, "\"");
            }
            else fprintf(out, "%c", c);
        }
    }
    fclose(in);
    fclose(out);

    return 0;
}