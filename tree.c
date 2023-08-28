#include "header.h"

//sitei no child ga nai baai saigonowo shuturyoku
tree *load_last (tree* ki){
    if (ki->brother != NULL){
	ki = load_last(ki->brother);
    }
    if (ki->child != NULL && ki->brother == NULL){
	ki = load_last(ki->child);
    }
    return ki;
}

tree *load_child(tree* ki, int number){
    for (int i = 0; i<= number; i++){
	if (ki->child == NULL) break;
	ki = ki->child;
    }
    return ki;
}

tree *load_brother(tree* ki, int nest){
    for (int i = 0; ; i++){
	if (ki->child != NULL && nest>0 && ki->brother == NULL){
	    ki = ki->child;
	    nest--;
	}
	if (ki->brother == NULL) break;
	ki = ki->brother;
    }
    return ki;
}

tree *load_loop(tree* ki, int nest){
    if (ki->ops == ']'){
	nest--;
	if (nest == 0){
	    return ki->brother;
	}
    }
    if (ki->child != NULL){
	nest++;
	load_loop(ki->child, nest);
    }
    if (ki->brother != NULL){
	load_loop(ki->brother, nest);
    }
}

//edani kid wo tuika
void append_child (char opcode, typtkn type){
    void *buffer = koubun;
    koubun = load_last(koubun);
    koubun->child = malloc(sizeof(tree));
    koubun->child->brother = NULL;
    koubun->child->child = NULL;
    koubun->child->ops = opcode;
    koubun->child->type = type;
    koubun = buffer;
    return;
}

void append_brother (char opcode, typtkn type, int nest){ 
    void *buffer = koubun;
    koubun = load_brother(koubun, nest);
    koubun->brother = malloc(sizeof(tree));
    koubun->brother->brother = NULL;
    koubun->brother->child = NULL;
    koubun->brother->ops = opcode;
    koubun->brother->type = type;
    koubun = buffer;
    return;
}

void print_tree(tree *ki, int nest){
    if (ki->ops == NULL){
	printf("op ga nai! or comment!\n");
    }
    else{
	printf("|");
	printf("%c\n", ki->ops);
    }
    if (ki->child != NULL){
	printf("child ");
	nest++;
	printf("nest = %d\n", nest);
        print_tree(ki->child, nest);
	printf("parent\n");
	nest--;
    }
    if (ki->brother != NULL){
	printf("brother ");
	printf("nest = %d\n", nest);
	print_tree(ki->brother, nest);
    }
    return;
}
