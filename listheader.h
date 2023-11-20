#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define POISON -2

// #define ECHO_ON

typedef int Elem_t;

struct List{
    int* data = nullptr;
    int* next = nullptr;
    int* prev = nullptr;
    int capacity = -1;
    int head = -1;          // Как же хочется везде здесь int поставить... изначально так и собирался сделать
    int tail = -1;
    int free = -1;
    int size = -1;
};

#define STRINGIFY(name) #name

#define VERIFICATION(condition, message, retvalue)     do {if(condition){                                                                \
        fprintf(logfile, "[%s][line: %d] " #message "\n", __FUNCTION__, __LINE__);                                                       \
        printf("Error:  [%s][Line: %d] " #message "\n", __FUNCTION__, __LINE__);                                                         \
        return retvalue;                                                                                                                 \
    }                                                                                                                                    \
}while(0)

#define VERIFICATION_LOGFILE(condition, message, retvalue)     if(condition){                                                            \
        printf("Error:  [%s][Line: %d] " #message "\n", __FUNCTION__, __LINE__);                                                         \
        return retvalue;                                                                                                                 \
    }

#define GENERAL_VERIFICATION(Lst, logfile) do{     VERIFICATION_LOGFILE(logfile == nullptr, "logfile is nullptr!\nExiting...", -1);      \
    VERIFICATION(Lst == nullptr, "List pointer is nullptr!\nExiting...", -1);                                                            \
    VERIFICATION_LOGFILE(logfile == nullptr, "logfile is nullptr!\nExiting...", -1);                                                     \
    VERIFICATION(Lst->data == nullptr, "List data pointer is nullptr!\nExiting...", -1);                                                 \
    VERIFICATION(Lst->next == nullptr, "List next pointer is nullptr!\nExiting...", -1);                                                 \
    }while(0)

#ifdef ECHO_ON
#define ECHO(logfile) do{ fprintf(logfile, "[%s, %s, %d]\n", __FILE__, __FUNCTION__, __LINE__); }while(0)
#else
#define ECHO(logfile) do{ } while(0)
#endif

#define GRAPH_INIT  digraph g {   \n                                                                             \
fontname="Helvetica,Arial,sans-serif"\n                                                                          \
node [fontname="Helvetica,Arial,sans-serif"]\n                                                                   \
edge [fontname="Helvetica,Arial,sans-serif"]\n                                                                   \
graph [\n                                                                                                        \
rankdir = "LR"\n                                                                                                 \
];

#define NODE_CONNECT(first_node, second_node, cell, i) #first_node:#cell -> #second_node:#cell [                 \
id = i                                                                                                           \
];                                                                                                               \

#define NODE_SETTINGS() node [                                                                                   \
fontsize = "16"                                                                                                  \
shape = "square"                                                                                                 \
];

#define EDGE_SETTINGS() edge [                                                                                   \
style="solid"                                                                                                    \
arrowhead="vee"                                                                                                  \
penwidth=2                                                                                                       \
];                                                                                                               \

#define NODE_INIT(name, first_label, second_label, third_label) #name [                                          \
label = "<f0> " #first_label "| " #second_label " | " #third_label                                               \
shape = "record"                                                                                                 \
];                                                                                                               \

#define CLOSE()    \n}


int ListCtor(List* Lst, int capacity, FILE* logfile);

int ListInsert(List* Lst, int log_ind, int value, FILE* logfile);

int ListSearch(List* Lst, int logical_indx, FILE* logfile);

int ListOutput(List* Lst, FILE* logfile);

int ListVerificator(List* Lst, FILE* logfile);

int ListDump(List* Lst, FILE* logfile);

int ListDelete(List* Lst, int phys_ind, FILE* logfile);

int ListDtor(List* Lst, FILE* logfile);

int ListResize(List* Lst, FILE* logfile);

int ListGraphDump(List* Lst, FILE* output, FILE* logfile);


/*

    # define(`STRINGIFY(name)',`#name')

    define(`VERIFICATION',`do {if($1){                                                                \
            fprintf(logfile, "[%s][line: %d] " #$1 "\n", __FUNCTION__, __LINE__);                                                       \
            printf("Error:  [%s][Line: %d] " #$1 "\n", __FUNCTION__, __LINE__);                                                         \
            return $1;                                                                                                                 \
        }                                                                                                                                    \
    }while(0)
    ')


    define(`VERIFICATION_LOGFILE',`if($1){                                                            \
            printf("Error:  [%s][Line: %d] " #$2 "\n", __FUNCTION__, __LINE__);                                                         \
            return $3;                                                                                                                 \
        }
    ')

    define(`GENERAL_VERIFICATION',`do{     VERIFICATION_LOGFILE($2 == nullptr, "$2 is nullptr!\nExiting...", -1);      \
        VERIFICATION($1 == nullptr, "List pointer is nullptr!\nExiting...", -1);                                                            \
        VERIFICATION_LOGFILE($2 == nullptr, "$2 is nullptr!\nExiting...", -1);                                                     \
        VERIFICATION($1->data == nullptr, "List data pointer is nullptr!\nExiting...", -1);                                                 \
        VERIFICATION($1->next == nullptr, "List next pointer is nullptr!\nExiting...", -1);                                                 \
        }while(0)
    ')

*/
