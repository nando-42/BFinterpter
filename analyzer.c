#include "header.h"

void append_opdict(char ops, typtkn type){
    void *buffer = token_dict;
    while (1){
	if (token_dict->next == NULL) break;
	token_dict = token_dict->next;
    }
    token_dict->next = malloc(sizeof(op_dict));
    token_dict->ops = ops;
    token_dict->type = type;
    token_dict->next->next = NULL;
    token_dict = buffer;
    return;
}

void init_opdict(){
    token_dict = malloc(sizeof(op_dict));
    token_dict->next = NULL;
    append_opdict('+', TYPE_PNTR);
    append_opdict('-', TYPE_PNTR);
    append_opdict('<', TYPE_PNTR);
    append_opdict('>', TYPE_PNTR);
    append_opdict(',', TYPE_INOT);
    append_opdict('.', TYPE_INOT);
    append_opdict('[', TYPE_LOOP);
    append_opdict(']', TYPE_LOOP);
    return;
}

typtkn decord_op(char ops[16], int size){ //opcode wo suuji ni decord
    op_dict *tmp = token_dict;
    while (tmp->next != NULL){
	if (ops[size] == tmp->ops){
	    return tmp->type;
	}
	tmp = tmp->next;
    }
    return TYPE_NULL;
}
