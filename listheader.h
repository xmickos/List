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

int ListCtor(List* Lst, int capacity, FILE* logfile);

int ListInsert(List* Lst, int log_ind, int value, FILE* logfile);

int ListSearch(List* Lst, int logical_indx, FILE* logfile);

int ListOutput(List* Lst, FILE* logfile);

int ListVerificator(List* Lst, FILE* logfile);

int ListDump(List* Lst, FILE* logfile);

int ListDelete(List* Lst, int phys_ind, FILE* logfile);

int ListDtor(List* Lst, FILE* logfile);