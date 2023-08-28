#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//define

typedef enum {
    TYPE_NULL,
    TYPE_INOT,
    TYPE_PNTR,
    TYPE_LOOP
}typtkn;

struct tree_tag {
    typtkn type;
    char ops;
    int nest;
    struct tree_tag *child;
    struct tree_tag *brother;
};
typedef struct tree_tag tree;

struct renketu_char {
    char code[17];
    struct renketu_char *next;
};
typedef struct renketu_char renketu;

struct jisho {
    typtkn type;
    char ops;
    struct jisho *next;
};
typedef struct jisho op_dict;

//tree.c
extern tree *load_last (tree* ki);
extern tree *load_child (tree* ki, int number);
extern tree *load_brother (tree* ki, int nest);
extern tree *load_loop(tree* ki, int nest);
extern void append_child (char opcode, typtkn type);
extern void append_brother (char opcode, typtkn type, int nest);
extern void print_tree(tree *ki, int nest);

//analyzer.c
extern typtkn decord_op(char ops[16], int size);
extern void init_opdict();

//interpter.c
extern void run_program(tree *ki);
extern void print_tape(void);

//main.c
extern tree *koubun;
extern renketu *code;
extern op_dict *token_dict;
extern unsigned char tape[300];
extern int pntr_tape;
extern int saidai_tape;
