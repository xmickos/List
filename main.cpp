#include "listheader.h"

int main(){

    FILE* logfile = fopen("logfile.txt", "w");

    List Lst = {};
    int free_elem = -1, phys_ind = -1, insert_output = -1;

    free_elem = ListCtor(&Lst, 20, logfile);
    printf("free_elem = %d\n", free_elem);

    insert_output = ListInsert(&Lst, free_elem, 10, logfile);

    ListDump(&Lst, logfile);

    insert_output = ListInsert(&Lst, insert_output, 20, logfile);

    ListDump(&Lst, logfile);

    insert_output = ListInsert(&Lst, insert_output, 30, logfile);

    ListDump(&Lst, logfile);

    ListOutput(&Lst, logfile);

    phys_ind = ListSearch(&Lst, 3, logfile);            // найти физический индекс третьего элемента и вставить третьим по счёту число 40

    insert_output = ListInsert(&Lst, phys_ind, 40, logfile);

    ListOutput(&Lst, logfile);

    ListDump(&Lst, logfile);

    phys_ind = ListSearch(&Lst, 1, logfile);

    insert_output = ListInsert(&Lst, phys_ind, -20, logfile);       // вставить -20 после элемента, которому отвечает phys_ind (вставить вторым)

    ListDump(&Lst, logfile);

    ListOutput(&Lst, logfile);

    phys_ind = ListSearch(&Lst, 2, logfile);

    ListDelete(&Lst, phys_ind, logfile);        // удалить элемент после того, которому отвечает phys_ind (удалить третий)

    ListDump(&Lst, logfile);

    ListOutput(&Lst, logfile);

    phys_ind = ListSearch(&Lst, 2, logfile);

    ListDelete(&Lst, phys_ind, logfile);

    ListDump(&Lst, logfile);

    ListOutput(&Lst, logfile);

    ListDtor(&Lst, logfile);
    return 0;
}
