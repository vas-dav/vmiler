#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

enum TokenType {
    _EXIT_KEY = 1,
    _END,
    _NUMERIC_VAL,
};

struct Lines {
    char lines[30][100];
    unsigned int count;
};

struct Token {
    enum TokenType type;
    bool arg_needed;
    bool used;
    size_t num_value;
};


static struct Token get_digit_token(const char* buff) {
    if (buff == NULL) {
        exit(1);
    }
    struct Token t = {0};
    t.num_value = strtol(buff, NULL, 10);
    t.type = _NUMERIC_VAL;
    t.used = true;
    return t;
}

static struct Token get_alpha_token(const char* buff) {
    if (buff == NULL) {
        exit(1);
    }
    struct Token t = {0};
    uint8_t hash = 0;
    for (int i = 0;buff[i];i++) {
      hash ^= buff[i]<< i;
    }
    t.type = hash % 3;
    t.used = true;
    printf("hash: %d, type: %d", hash, t.type);
    if (hash == _EXIT_KEY) {
        t.arg_needed = true;
    }
    return t;
}

static void assemble_tokens(struct Token* t) {
    FILE* obj = fopen("main.asm", "w");
    assert(obj != NULL);
    fprintf(obj, "global _start\n_start:\n");
    for(int i = 0; t[i].used; i++) {
        if (t[i].type == _EXIT_KEY) {
            assert(t[i+1].type == _NUMERIC_VAL && t[i+2].type == _END);
            const char exit_fmt[] = 
            "\tmov rax, 60\n"
            "\tmov edi, %lu\n"
            "\tsyscall\n";
            fprintf(obj, exit_fmt, t[i + 1].num_value);
        }
    }
    fclose(obj);
}

int main (int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: vmi <source.vmi>\n");
        exit(1);
    }

    FILE* src_file = fopen(argv[1], "r");
    struct Lines lines = {0};
    char* line = NULL;
    size_t line_size = 0;
    size_t char_read = 0;
    while ((char_read = getline(&line, &line_size, src_file)) != -1) {
       strncpy(lines.lines[lines.count++], line, char_read);
    }
    
    struct Token tokens[30] = {0};
    int token_count = 0;
    for (int i = 0; i < lines.count; i++) {
        printf("Line %u: %s\n", i + 1, lines.lines[i]);
        for(int j = 0; lines.lines[i][j];) {
            char current = lines.lines[i][j];
            char token_buffer[100] = {0};
            size_t tbc = 0;
            printf("Current char: %c\n", lines.lines[i][j]);
            if (isalpha(current) || current == ';') {
                while(isalpha(lines.lines[i][j]) || lines.lines[i][j] == ';') {
                    token_buffer[tbc++]= lines.lines[i][j];
                    j++;
                }
                printf("Tokenizing alpha: %s\n", token_buffer);
                tokens[token_count++] = get_alpha_token(token_buffer);
            } else if(isdigit(current)) {
                while(isdigit(lines.lines[i][j])) {
                    token_buffer[tbc++] = lines.lines[i][j];
                    j++;
                }
                printf("Tokenizing digit: %s\n", token_buffer);
                tokens[token_count++] = get_digit_token(token_buffer);
            } else {
                j++;
            }
        }
    }

    for (int i = 0; i < token_count; i++) {
        printf("[type: %d, arg: %d, value: %zu] ",
                tokens[i].type, tokens[i].arg_needed, tokens[i].num_value);
    }
    fflush(stdout);

    assemble_tokens(tokens);
    system("nasm -f elf64 -o main.o main.asm");
    system("ld main.o");
    return 0;
}
