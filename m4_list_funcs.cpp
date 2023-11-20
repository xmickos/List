















#include "listheader.h"

int ListCtor(List* Lst, int capacity, FILE* logfile){

    VERIFICATION_LOGFILE(logfile == nullptr, "logfile is nullptr!\nExiting...", -1);
    VERIFICATION(Lst == nullptr, "List pointer is nullptr!\nExiting...", -1);
    ECHO(logfile);
    VERIFICATION(capacity == 0, "Provided zero list capacity!\nExiting...", -1);

    Lst->data = (int*)calloc((size_t)capacity, sizeof(int));

    VERIFICATION(Lst->data == nullptr, "Failed to allocate enought memory for Lst->data!\nExiting...", -1);

    Lst->next = (int*)calloc((size_t)capacity, sizeof(int));
    Lst->capacity = capacity;

    VERIFICATION(Lst->next == nullptr, "Failed to allocate enought memory for Lst->next!\nExiting...", -1);

    Lst->prev = (int*)calloc((size_t)capacity, sizeof(int));

    VERIFICATION(Lst->prev == nullptr, "Failed to allocate enought memory for Lst->prev!\nExiting...", -1);


    Lst->free = 1;
    Lst->data[0] = (int)POISON;
    Lst->head = -1;
    Lst->tail = -1;
    Lst->size = 0;

    for(int i = 1; i < Lst->capacity - 1; i++){
        Lst->next[i] = i + 1;
        Lst->prev[i] = -1;
    }
    Lst->prev[Lst->capacity - 1] = -1;

    fprintf(logfile, "[%d, %s, %s] List created successfully!\n", __LINE__, __FUNCTION__, __FILE__);

    return Lst->free; // 0 - адрес первого свободного элемента
}


int ListInsert(List* Lst, int phys_ind, int value, FILE* logfile){    // Функция вставки возвращает физический индекс, по которому лежит вставленный элемент

    ECHO(logfile);
    GENERAL_VERIFICATION(Lst, logfile);

    int free_elem = Lst->free, stored_ind = -1;
    if(free_elem == 0) {
        printf("NEED TO RESIZE! \nExiting.\n");
        return -1;
    }

    fprintf(logfile, "\nInserting: %d, free_elem: %d\n", phys_ind, free_elem);

    // if(Lst->head == phys_ind && Lst->size != 1){         вставка в начало ?
    //     Lst->head = free_elem;
    // }

    stored_ind = Lst->next[phys_ind];

    if(stored_ind == 0){
        Lst->tail = Lst->free;
    }

    fprintf(logfile, "\nstored index: %d\n", stored_ind);

    Lst->free = Lst->next[Lst->free];

    Lst->data[free_elem]  = value;
    Lst->next[phys_ind]   = free_elem;
    Lst->next[free_elem]  = stored_ind;
    Lst->prev[stored_ind] = free_elem;
    Lst->prev[free_elem]  = phys_ind;

    if(Lst->head == -1){
        Lst->head = 1;
        Lst->next[free_elem] = 0;
        Lst->prev[free_elem] = 0;

        Lst->size = 1;
        Lst->tail = 1;
    }else{
        Lst->size += 1;
    }

    return free_elem;
}


int ListDelete(List* Lst, int phys_ind, FILE* logfile){

    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    int stored_ind = Lst->next[phys_ind];
    int stored_next = -1, stored_prev = -1;
    stored_prev = Lst->prev[phys_ind];
    stored_next = Lst->next[phys_ind];

    if(Lst->head == phys_ind){
        Lst->head = Lst->next[phys_ind];
    }

    if(Lst->tail == phys_ind){
        Lst->tail = Lst->prev[phys_ind];
    }

    Lst->next[stored_prev] = Lst->next[phys_ind];
    Lst->prev[stored_next] = Lst->prev[phys_ind];
    Lst->data[phys_ind] = 0;
    Lst->prev[phys_ind] = -1;

    Lst->next[phys_ind] = Lst->free;
    Lst->free = phys_ind;

    return 0;

}


int ListSearch(List* Lst, int logical_indx, FILE* logfile){
    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    if(logical_indx == 1) return logical_indx;



    for(int i = 1, next = Lst->head; i < Lst->size + 1; i++){
        // if(Lst->next[i] == logical_indx) return i;
        if(i == logical_indx) return next;
        next = Lst->next[next];
    }

    return -1;
}


int ListDump(List* Lst, FILE* logfile){
    ECHO(logfile);
    GENERAL_VERIFICATION(Lst, logfile);

    fprintf(logfile, "\n\tLIST DUMP:\nSize: [%2d]\nHead: [%2d]\nTail: [%2d]\nFree: [%2d]", Lst->size, Lst->head, Lst->tail, Lst->free);
    fprintf(logfile, "\nindx");
    for(int i = 0; i < Lst->capacity; i++){
        fprintf(logfile, "%4d", i);
    }
    fprintf(logfile, "\ndata");
    for(int i = 0; i < Lst->capacity; i++){
        fprintf(logfile, "%4d", Lst->data[i]);
    }
    fprintf(logfile, "\nnext");
    for(int i = 0; i < Lst->capacity; i++){
        fprintf(logfile, "%4d", Lst->next[i]);
    }
    fprintf(logfile, "\nprev");
    for(int i = 0; i < Lst->capacity; i++){
        fprintf(logfile, "%4d", Lst->prev[i]);
    }

    fprintf(logfile, "\n\n");

    return 0;
}


int ListOutput(List* Lst, FILE* logfile){

    ECHO(logfile);

    int ind = Lst->head;

    fprintf(logfile, "\nList output:");
    for(int i = 0; i < Lst->size; i++){
        fprintf(logfile, "%4d", Lst->data[ind]);
        ind = Lst->next[ind];
        if(ind == 0) break;
    }
    fprintf(logfile, "\n\n");

    return 0;

}


int ListDtor(List* Lst, FILE* logfile){
    ECHO(logfile);
    GENERAL_VERIFICATION(Lst, logfile);


    free(Lst->data);
    free(Lst->next);

    Lst->data = nullptr;
    Lst->next = nullptr;

    return 0;
}

int ListResize(List* Lst, FILE* logfile){

    return 0;
}

int ListGraphDump(List* Lst, FILE* output, FILE* logfile){

    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    int curr_ind = Lst->head;
    printf("list head is %d\n", Lst->head);

    fprintf(output, STRINGIFY(digraph g {   \n                                                                            \
fontname="Helvetica,Arial,sans-serif"\n                                                                          \
node [fontname="Helvetica,Arial,sans-serif"]\n                                                                   \
edge [fontname="Helvetica,Arial,sans-serif"]\n                                                                   \
graph [\n                                                                                                        \
rankdir = "LR"\n                                                                                                 \
];
) STRINGIFY(node [\n                                                                                 \
fontsize = "16"\n                                                                                                \
shape = "square"\n                                                                                               \
];\n\n) STRINGIFY(edge [\n                                                                                 \
style="solid"\n                                                                                                  \
arrowhead="vee"\n                                                                                                \
penwidth=2\n                                                                                                     \
];                                                                                                               \
\n\n));

    while(Lst->data[curr_ind] != -2){
        fprintf(output, STRINGIFY("node %d" [\n
   label=<\n
     <table border="0" cellborder="1" cellspacing="0">\n
       <tr><td bgcolor="#f57777">data: %d</td></tr>\n
       <tr><td bgcolor="lightblue"><font color="#0000ff">next: %d</font></td></tr>\n
       <tr><td bgcolor="#f0e3ff"><font color="#ff1020">prev: %d</font></td></tr>\n
     </table>>\n
  ];), curr_ind,
                Lst->data[curr_ind], Lst->next[curr_ind], Lst->prev[curr_ind]);

        printf("next: %d, data: %d\n", Lst->next[curr_ind], Lst->data[curr_ind]);
        curr_ind = Lst->next[curr_ind];
    }

    curr_ind = Lst->head;

    while(Lst->data[curr_ind] != -2){
        fprintf(output, STRINGIFY("node %d":f0 -> "node %d":f0 [\n                                                                        \
id = 0\n                                                                                                        \
];                                                                                                               \
\n\n), curr_ind, Lst->next[curr_ind]);
        curr_ind = Lst->next[curr_ind];
    }

    curr_ind = Lst->head;

    while(Lst->data[curr_ind] != -2){
        fprintf(output, STRINGIFY("node %d":f2 -> "node %d":f2 [\n                                                                        \
id = 0\n                                                                                                        \
];                                                                                                               \
\n\n), Lst->next[curr_ind], curr_ind);
        curr_ind = Lst->next[curr_ind];
        printf("prev: %d, next: %d, data: %d\n", Lst->prev[curr_ind], Lst->next[curr_ind], Lst->data[curr_ind]);
    }

    fprintf(output, STRINGIFY(\n}));

    return 0;
}

int ListVerificator(List* Lst, FILE* logfile){

    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    int test_next = Lst->head, test_prev = Lst->tail;

    for(int i = 1; i < Lst->size - 1; i++){
        test_next = Lst->next[test_next];
        test_prev = Lst->prev[test_prev];
    }

    if(test_next == Lst->tail && test_prev == Lst->head){
        fprintf(logfile, "List verificated succesfully!\n");
    }else{
        fprintf(logfile, "The list is inconsistent!\nExiting...");
        return -1;
    }

    return 0;
}
