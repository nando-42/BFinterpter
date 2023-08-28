#include "header.h"
int pcntr;

void run_program(tree *ki){
    if (ki->type == TYPE_LOOP){
	if (ki->ops == '['){
	    while (1){
		    if (tape[pntr_tape] == 0){
			return;
		    }
		    else{
			if (ki->child != NULL) run_program(ki->child);
			if (ki->brother != NULL)run_program(ki->brother);
		    }
	    }
	}
	else if (ki->ops == ']'){
	    return;
	}
    }
    else if (ki->type == TYPE_PNTR){
	    if (ki->ops == '+'){
		tape[pntr_tape] += 1;
	    }
	    else if (ki->ops == '-'){
		tape[pntr_tape] -= 1;
	    }
	    else if (ki->ops == '<'){
		if (pntr_tape == 0){
		    printf("error! invalid pntr!\n");
		    exit(1);
		}
		pntr_tape--;
	    }
	    else if (ki->ops == '>'){
		pntr_tape++;
		if (saidai_tape < pntr_tape){
		    saidai_tape = pntr_tape;
		}
	    }
	}
    else if (ki->type == TYPE_INOT){
	    if (ki->ops == ','){
		tape[pntr_tape] = getchar();
	    }
	    if (ki->ops == '.'){
		printf("%c", tape[pntr_tape]);
	    }
    }
end:
    if (ki->child != NULL){
	run_program(ki->child);
    }
    if (ki->brother != NULL){
	run_program(ki->brother);
    }
    return;
}

void print_tape(void){
    printf("tape:");
    int i = 0;
    while (1){
	printf("%d ", tape[i]);
	if (i >= saidai_tape) break;
	i++;
    }
    printf("\n");
    return;
}
