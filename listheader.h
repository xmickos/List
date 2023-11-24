#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define POISON -2

#define ECHO_ON

typedef int Elem_t;

struct List{
    int* data = nullptr;
    int* next = nullptr;
    int* prev = nullptr;
    size_t capacity = 0;
    int head = -1;          // Как же хочется везде здесь int поставить... изначально так и собирался сделать
    int tail = -1;
    int free = -1;
    int size = -1;
    size_t num_of_graph_dumps = 1;
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

#define GENERAL_VERIFICATION(Lst, logfile) do{     VERIFICATION_LOGFILE(logfile == nullptr, #logfile "is nullptr!\nExiting...", -1);     \
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

#define REALLOC_ME(ptr, message)     ptr = (int*)realloc(ptr, 2 * Lst->capacity * sizeof(int));                  \
    if(ptr == nullptr){                                                                                          \
        fprintf(logfile, "Failed to reallocate "#message" pointer!\nExiting...\n");                              \
        return -1;                                                                                               \
    }

#define CLOSE()    \n}

#define HTML_DEFAULT_BORDER_VALUE "1"

#define NODE_HEAD_INIT this text cant be executed, check readme.md if you see this

#define NODE_TAIL_INIT this text cant be executed, check readme.md if you see this

#define AUTOGEN_WARNING this text cant be executed, check readme.md if you see this

#define WATERMARK_NODE this text cant be executed, check readme.md if you see this

#define HTML_INIT "<html>\n\t<body>\n\t"

#define HTML_PUT_IMG(name) "\n\t<br>\n\t<img src = \"" name "\">\n\t<br>"

#define HTML_CLOSE "\n\t</body>\n</html>\n"

#define simple_safari_syscall "open -a Safari /Users/xmickos/Desktop/govno.jopa.kosmos/Ded_second_try/List/index.html"

#define HTML_TABLE_OPEN(border_value) "<table border=\"" border_value "\">\n"

#define HTML_TABLE_HEADER_OPEN "\t<thead>\n\t<tr>\n"

#define HTML_TABLE_MAIN_INIT "<tbody>\n"

#define HTML_TABLE_MAIN_ROW_OPEN "\t<tr>"

#define HTML_TABLE_MAIN_ROW_INFO(information) "\t<td>" information "</td>\n"

#define HTML_TABLE_MAIN_ROW_CLOSE "\t</tr>"

#define HTML_TABLE_MAIN_CLOSE "</tbody>\n"

#define HTML_TABLE_HEADER_CLOSE "\t</tr>\n</thead>\n"

#define HTML_TABLE_CLOSE "\t</table>\n"

#define HTML_EMPTY_TBL_ELEM "\t\t<td>&nbsp;</td>\n"

#define HTML_TABLE_HEADER_INFO(information) "\t\t<th>" information "</th>\n"

#define DUMP_CODE(delimiter)    do{fprintf(logfile, "\n\tLIST DUMP:\nSize: [%2d]\nHead: [%2d]\nTail: [%2d]\nFree: [%2d]", Lst->size, Lst->head, Lst->tail, Lst->free); \
        fprintf(logfile, "\nindx");                                                                                                                                 \
        for(size_t i = 0; i < Lst->capacity; i++){                                                                                                                  \
            fprintf(logfile, "%4zu", i);                                                                                                                            \
        }                                                                                                                                                           \
        fprintf(logfile, "\ndata");                                                                                                                                 \
        for(size_t i = 0; i < Lst->capacity; i++){                                                                                                                  \
            fprintf(logfile, "%4d", Lst->data[i]);                                                                                                                  \
        }                                                                                                                                                           \
        fprintf(logfile, "\nnext");                                                                                                                                 \
        for(size_t i = 0; i < Lst->capacity; i++){                                                                                                                  \
            fprintf(logfile, "%4d", Lst->next[i]);                                                                                                                  \
        }                                                                                                                                                           \
        fprintf(logfile, "\nprev");                                                                                                                                 \
        for(size_t i = 0; i < Lst->capacity; i++){                                                                                                                  \
            fprintf(logfile, "%4d", Lst->prev[i]);                                                                                                                  \
        }                                                                                                                                                           \
        fprintf(logfile, "\n\n");}while(0)                                                                                                                          \

#define HTML_LIST_PARAMS_TABLE "<table>\n                                                                                                                             \
  \t<tr>\n                                                                                                                                                              \
    \t\t<th>Size</th>\n                                                                                                                                                   \
    \t\t<th>Head</th>\n                                                                                                                                                   \
    \t\t<th>Tail</th>\n                                                                                                                                                   \
    \t\t<th>Free</th>\n                                                                                                                                                   \
  \t</tr>\n                                                                                                                                                             \
  \t<tr>\n                                                                                                                                                              \
    \t\t<td>%4d</td>\n                                                                                                                                                    \
    \t\t<td>%4d</td>\n                                                                                                                                                    \
    \t\t<td>%4d</td>\n                                                                                                                                                    \
    \t\t<td>%4d</td>\n                                                                                                                                                    \
  \t</tr>\n                                                                                                                                                             \
</table>"

int ListCtor(List* Lst, size_t capacity, FILE* logfile);

int ListInsert(List* Lst, int log_ind, int value, FILE* logfile);

int ListSearch(List* Lst, int logical_indx, FILE* logfile);

int ListOutput(List* Lst, FILE* logfile);

int ListVerificator(List* Lst, FILE* logfile);

int ListDump(List* Lst, FILE* logfile, bool is_html_flag);

int ListDelete(List* Lst, int phys_ind, FILE* logfile);

int ListDtor(List* Lst, FILE* logfile);

int ListResize(List* Lst, FILE* logfile);

int ListGraphDump(List* Lst, FILE* output, FILE* html_output, FILE* logfile);


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


    define(`NODE_CONNECT',`"$1":$3 -> "$2":$3 [\n                                                                        \
    id = 0\n                                                                                                        \
    ];                                                                                                               \
    \n\n')

*/
