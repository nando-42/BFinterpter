#include "header.h"

tree *koubun;
renketu *code;
op_dict *token_dict;
unsigned char tape[300];
int pntr_tape;
int saidai_tape;

int main(int argc, char** argv){
    saidai_tape = 0;
    pntr_tape = 0;
    for (int i = 0; i<=300; i++){
	tape[i] = 0;
    }
    init_opdict();
    koubun = malloc(sizeof(tree)); //set the pointer
    koubun->brother = NULL;
    koubun->child = NULL;
    if (argc<2){
	printf("error! no arg!\n");
	return 1; //mosi hikisuuga tarinainara
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
	printf("error! no file! file:%s\n", argv[1]);
	return 1; //file ga sonzai sinai nara
    }
    char tmp_op[16];
    int nest = 0;
    int filelengh = 0;
    int i=0;
    while (1){ //meirei decord
	i++;
	tmp_op[i] = fgetc(file);
	filelengh++;
	if (tmp_op[i] == EOF) break; //file ga owatte itara
	if (decord_op(tmp_op, i) == TYPE_INOT){
	    append_brother(tmp_op[i], TYPE_INOT, nest);
	}
	else if (decord_op(tmp_op, i) == TYPE_PNTR){
	    append_brother(tmp_op[i], TYPE_PNTR, nest);
	}
	else if (decord_op(tmp_op, i) == TYPE_LOOP){
	    if (tmp_op[i] == '['){
		nest++;
		append_child(tmp_op[i], TYPE_LOOP);
	    }
	    else if(tmp_op[i] == ']'){
		if (nest == 0){
		    printf("error! invalid loop!\n");
		    return 1;
		}
		append_brother(tmp_op[i], TYPE_LOOP, nest);
		nest--;
		append_brother(NULL, TYPE_NULL, nest);
	    }
	}
	if(1) i = 0; //token ga shuuryou sita ra i wo shokika
    }
    fclose(file);
    if (nest != 0){
	printf("error! invalid loop!\n");
	return 1;
    }
    print_tree(koubun, 0);
    run_program(koubun);
    printf("\n");
    print_tape();
    return 0;
}
