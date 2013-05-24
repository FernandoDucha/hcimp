/* 
 * File:   node_list_struct.h
 * Author: fernando
 *
 * Created on 8 de Outubro de 2011, 19:45
 */

#ifndef NODE_LIST_STRUCT_H
#define	NODE_LIST_STRUCT_H
template <class TipoChave>struct node_list_struct {
    TipoChave element;
    node_list_struct * next;
    node_list_struct * prev;
};
//static int NNEWS=0;
//static int NDELS=0;


#endif	/* NODE_LIST_STRUCT_H */

