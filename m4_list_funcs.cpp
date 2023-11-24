

























/*

!!!
    THIS FILE WAS GENERATED AUTOMATICALLY, PLEASE DONT TRY TO EDIT OR FIX
!!!

    GENERATED FROM SOURCE: list_funcs.cpp USING M4 PREPROCESSOR

*/

#include "listheader.h"

int ListCtor(List* Lst, size_t capacity, FILE* logfile){

    VERIFICATION_LOGFILE(logfile == nullptr, "logfile is nullptr!\nExiting...", -1);
    VERIFICATION(Lst == nullptr, "List pointer is nullptr!\nExiting...", -1);
    ECHO(logfile);
    VERIFICATION(capacity == 0, "Provided zero list capacity!\nExiting...", -1);

    Lst->data = (int*)calloc(capacity, sizeof(int));

    VERIFICATION(Lst->data == nullptr, "Failed to allocate enought memory for Lst->data!\nExiting...", -1);

    Lst->next = (int*)calloc(capacity, sizeof(int));

    VERIFICATION(Lst->next == nullptr, "Failed to allocate enought memory for Lst->next!\nExiting...", -1);

    Lst->prev = (int*)calloc(capacity, sizeof(int));

    VERIFICATION(Lst->prev == nullptr, "Failed to allocate enought memory for Lst->prev!\nExiting...", -1);

    Lst->capacity = capacity;
    Lst->free = 1;
    Lst->data[0] = (int)POISON;
    Lst->head = -1;
    Lst->tail = -1;
    Lst->size = 0;

    for(size_t i = 1; i < Lst->capacity - 1; i++){
        Lst->next[i] = (int)i + 1;
        Lst->prev[i] = -1;
    }
    Lst->prev[Lst->capacity - 1] = -1;

    fprintf(logfile, "[%d, %s, %s] List created successfully!\n", __LINE__, __FUNCTION__, __FILE__);

    return Lst->free; // 1 - адрес первого свободного элемента
}


int ListInsert(List* Lst, int phys_ind, int value, FILE* logfile){
// Функция вставки возвращает физический индекс, по которому лежит вставленный элемент, и принимает физический индекс, по которому
// нужно вставить новый элемент – таким образом, её можно вызывать раз за разом без посторонних команд.

    ECHO(logfile);
    GENERAL_VERIFICATION(Lst, logfile);

    int free_elem = Lst->free, stored_ind = -1;

    if(free_elem == 0) {
        fprintf(logfile, "NEED TO RESIZE!.\n");
        ListResize(Lst, logfile);
        fprintf(logfile, "Resized list dump:\n");
        ListDump(Lst, logfile, 0);
        free_elem = Lst->free;
    }


    stored_ind = Lst->next[phys_ind];

    fprintf(logfile, "Input: phys_ind = %d, value = %d\n", phys_ind, value);
    fprintf(logfile, "Insterting position: %d, Lst->next[phys_ind] = %d\n",
            free_elem, stored_ind);

    if(stored_ind == 0){
        Lst->tail = Lst->free;
    }else{
        Lst->prev[stored_ind] = free_elem;
    }

    Lst->free = Lst->next[Lst->free];

    Lst->data[free_elem]  = value;
    Lst->next[phys_ind]   = free_elem;
    Lst->next[free_elem]  = stored_ind;
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
    Lst->size--;

    return 0;

}


int ListSearch(List* Lst, int logical_indx, FILE* logfile){
// logical_indx - порядковый номер элемента, следующий за которым необходимо найти
// Функция возвращает физический индекс элемента, следующего за тем, который имеет логический индекс logical_indx

    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    if(logical_indx == 1) return logical_indx;

    for(int i = 1, next = Lst->head; i < Lst->size + 1; i++){
        if(i == logical_indx) return next;
        next = Lst->next[next];
    }

    return -1;
}


int ListDump(List* Lst, FILE* logfile, bool is_html_flag){
    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    if(is_html_flag == 0){
        DUMP_CODE("\n");
    }else{
        DUMP_CODE("<br>\n");
    }

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

    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    REALLOC_ME(Lst->data, data);
    REALLOC_ME(Lst->prev, prev);
    REALLOC_ME(Lst->next, next);
    Lst->capacity *= 2;

    for(int i = Lst->size + 1; i < (int)Lst->capacity; i++){
        Lst->data[i] = 0;
        Lst->prev[i] = -1;
        Lst->next[i] = i + 1;
    }
    Lst->next[Lst->capacity - 1] = 0;
    Lst->free = Lst->size + 1;

    return 0;
}

int ListGraphDump(List* Lst, FILE* output, FILE* html_output, FILE* logfile){

    GENERAL_VERIFICATION(Lst, logfile);
    ECHO(logfile);

    int curr_ind = Lst->head;
    fprintf(logfile, "list head is %d\n", Lst->head);

        // Creating .dot file

    fprintf(output, STRINGIFY(digraph g {   \n
fontname="Helvetica,Arial,sans-serif"\n
node [fontname="Helvetica,Arial,sans-serif"]\n
edge [fontname="Helvetica,Arial,sans-serif"]\n
graph [\n
rankdir = "LR"\n
];
) STRINGIFY(\nnode [\n
fontsize = "16"\n
shape = "square"\n
];\n\n) STRINGIFY(edge [\n
style="solid"\n
arrowhead="vee"\n
penwidth=2\n
];
\n\n));
    fprintf(output, STRINGIFY(\n"watermark node" [ label = "dump %zu"\nshape=record];\n\n), Lst->num_of_graph_dumps);

    while(curr_ind != 0){
    if(curr_ind == Lst->head){
        fprintf(output, STRINGIFY(\n"node %d" [\n
   label=<\n
     <table border="0" cellborder="1" cellspacing="0">\n
       <tr><td bgcolor="#581845"><font color="#FF5733">Head</font></td></tr>\n
       <tr><td bgcolor="#f57777">data %d</td></tr>\n
       <tr><td bgcolor="lightblue"><font color="#0000ff">next: %d</font></td></tr>\n
       <tr><td bgcolor="#f0e3ff"><font color="#ff1020">prev: %d</font></td></tr>\n
     </table>>\n
  ];\n\n), curr_ind,
                Lst->data[curr_ind], Lst->next[curr_ind], Lst->prev[curr_ind]);
    }else if(curr_ind == Lst->tail){
        fprintf(output, STRINGIFY(\n"node %d" [\n
   label=<\n
     <table border="0" cellborder="1" cellspacing="0">\n
       <tr><td bgcolor="#581845"><font color="#FF5733">Tail</font></td></tr>\n
       <tr><td bgcolor="#f57777">data %d</td></tr>\n
       <tr><td bgcolor="lightblue"><font color="#0000ff">next: %d</font></td></tr>\n
       <tr><td bgcolor="#f0e3ff"><font color="#ff1020">prev: %d</font></td></tr>\n
     </table>>\n
  ];\n\n), curr_ind,
                Lst->data[curr_ind], Lst->next[curr_ind], Lst->prev[curr_ind]);
    }
    else{
        fprintf(output, STRINGIFY(\n"node %d" [\n
   label=<\n
     <table border="0" cellborder="1" cellspacing="0">\n
       <tr><td bgcolor="#f57777">data: %d</td></tr>\n
       <tr><td bgcolor="lightblue"><font color="#0000ff">next: %d</font></td></tr>\n
       <tr><td bgcolor="#f0e3ff"><font color="#ff1020">prev: %d</font></td></tr>\n
     </table>>\n
  ];\n\n), curr_ind,
                Lst->data[curr_ind], Lst->next[curr_ind], Lst->prev[curr_ind]);
    }

        fprintf(logfile, "next: %d, data: %d\n", Lst->next[curr_ind], Lst->data[curr_ind]);
        curr_ind = Lst->next[curr_ind];
    }

    curr_ind = Lst->head;

    while(Lst->next[curr_ind] != 0){
        fprintf(output, STRINGIFY("node %d" -> "node %d"\n\n), curr_ind, Lst->next[curr_ind]);
        fprintf(logfile, "!!!prev: %d, next: %d, data: %d\n", Lst->prev[curr_ind], Lst->next[curr_ind], Lst->data[curr_ind]);


        curr_ind = Lst->next[curr_ind];
    }

    curr_ind = Lst->head;

    while(Lst->next[curr_ind] != 0){
        fprintf(output, STRINGIFY("node %d" -> "node %d"\n\n), Lst->next[curr_ind], curr_ind);
        fprintf(logfile, "prev: %d, next: %d, data: %d\n", Lst->prev[curr_ind], Lst->next[curr_ind], Lst->data[curr_ind]);

        curr_ind = Lst->next[curr_ind];
    }

    fprintf(output, STRINGIFY(\n}\n\n));

        // Creating .html file

    fprintf(html_output, HTML_INIT);
    if(Lst->num_of_graph_dumps == 1){
        fprintf(html_output, HTML_PUT_IMG("dot_example.dot.png"));
    }else{
        fprintf(html_output, HTML_PUT_IMG("dot_example.dot.%zu.png"), Lst->num_of_graph_dumps);
    }

    fprintf(html_output, HTML_LIST_PARAMS_TABLE, Lst->size, Lst->tail, Lst->head, Lst->free);
    fprintf(html_output, HTML_TABLE_OPEN(HTML_DEFAULT_BORDER_VALUE));
    fprintf(html_output, HTML_TABLE_HEADER_OPEN);

    fprintf(html_output, HTML_TABLE_HEADER_INFO("indx"));
    for(size_t i = 0; i < Lst->capacity; i++){
        fprintf(html_output, HTML_TABLE_HEADER_INFO("%4zu"), i);
    }

    fprintf(html_output, HTML_TABLE_MAIN_INIT);

    fprintf(html_output, HTML_TABLE_MAIN_ROW_OPEN);

    fprintf(html_output, HTML_TABLE_MAIN_ROW_INFO("data"));
    for(size_t i = 0; i < Lst->capacity; i++){
        fprintf(html_output, HTML_TABLE_MAIN_ROW_INFO("%4d"), Lst->data[i]);
    }
    fprintf(html_output, HTML_TABLE_MAIN_ROW_CLOSE);
    fprintf(html_output, HTML_TABLE_MAIN_ROW_OPEN);
    fprintf(html_output, HTML_TABLE_MAIN_ROW_INFO("next"));
    for(size_t i = 0; i < Lst->capacity; i++){
        fprintf(html_output, HTML_TABLE_MAIN_ROW_INFO("%4d"), Lst->next[i]);
    }
    fprintf(html_output, HTML_TABLE_MAIN_ROW_CLOSE);
    fprintf(html_output, HTML_TABLE_MAIN_ROW_OPEN);
    fprintf(html_output, HTML_TABLE_MAIN_ROW_INFO("prev"));
    for(size_t i = 0; i < Lst->capacity; i++){
        fprintf(html_output, HTML_TABLE_MAIN_ROW_INFO("%4d"), Lst->prev[i]);
    }
    fprintf(html_output, HTML_TABLE_MAIN_ROW_CLOSE);

    fprintf(html_output, HTML_TABLE_MAIN_CLOSE);

    fprintf(html_output, HTML_TABLE_HEADER_CLOSE);

    fprintf(html_output, HTML_TABLE_CLOSE);
    fprintf(html_output, HTML_CLOSE);

    Lst->num_of_graph_dumps++;

    system(simple_safari_syscall);
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
