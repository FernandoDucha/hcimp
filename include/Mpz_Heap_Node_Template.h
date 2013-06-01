/* 
 * File:   Mpz_Heap_Node_Template.h
 * Author: fernando
 *
 * Created on 24 de Maio de 2013, 02:30
 */

#ifndef MPZ_HEAP_NODE_TEMPLATE_H
#define	MPZ_HEAP_NODE_TEMPLATE_H
#include "BasicTypes_heap.h"
#include "HeapStrctPtr.h"
#include "HeapStructure.h"
template <class heapType,class heapElement> class MpzHeapNodeTemplate{
private:
    heapType elements;
    MpzHeapNodeTemplate * parent;
    unsigned long int size_t;
    mpz_class nodeId;
    mpz_class sum;
public:
    MpzHeapNodeTemplate(MpzHeapNodeTemplate & node);
    MpzHeapNodeTemplate();
    
    ~MpzHeapNodeTemplate();
    MpzHeapNodeTemplate & operator=(MpzHeapNodeTemplate & rhs);
    unsigned long int size();
    void heaping();
    heapElement removeLargest();
//    heapElement removeLargestDelayHeapfy();
    void pushElem(heapElement elem);
//    void pushElemDelayed(heapElement elem);
    void print();
    void sort();
    heapType & data();
    mpz_class getNodeId() const;
    void setNodeId(mpz_class nodeId);
    bool prune(mpz_class & min,unsigned int part);
    void setParent(MpzHeapNodeTemplate* parent);
    MpzHeapNodeTemplate* getParent() const;
    mpz_class getSum() const;
};
template <class heapType,class heapElement>MpzHeapNodeTemplate<heapType,heapElement>::MpzHeapNodeTemplate(MpzHeapNodeTemplate & node):elements(node.data()){
    parent=NULL;
    this->size_t=node.size();
    this->nodeId=node.getNodeId();
    this->sum=node.getSum();
}
template <class heapType,class heapElement>MpzHeapNodeTemplate<heapType,heapElement>::MpzHeapNodeTemplate(){
    parent=NULL;
    nodeId=0;
    size_t=0;
    sum=0;
}
template <class heapType,class heapElement>MpzHeapNodeTemplate<heapType,heapElement>::~MpzHeapNodeTemplate(){

}
template <class heapType,class heapElement> MpzHeapNodeTemplate<heapType,heapElement> & MpzHeapNodeTemplate<heapType,heapElement>::operator=(MpzHeapNodeTemplate<heapType,heapElement> & rhs){
    this->elements= rhs.data();
    this->size_t=rhs.size();
    this->nodeId=rhs.getNodeId();
    this->sum=rhs.getSum();
    return *this;
}    
template <class heapType,class heapElement>inline mpz_class MpzHeapNodeTemplate<heapType,heapElement>::getSum() const {
    return sum;
}

template <class heapType,class heapElement>inline unsigned long int MpzHeapNodeTemplate<heapType,heapElement>::size(){
    return size_t;
}
template <class heapType,class heapElement>inline heapElement MpzHeapNodeTemplate<heapType,heapElement>::removeLargest(){
    sum-=elements.valueMax();
    heapElement max=elements.getMax();
    size_t--;
    return  max;
}
// template <class heapType,class heapElement>inline heapElement MpzHeapNodeTemplate<heapType,heapElement>::removeLargestDelayHeapfy(){
//    sum-=elements.valueMax();
//    heapElement max=elements.getMaxDelayed();
//    size_t--;
//    return  max;
// }
//void mpz_heap_node::addElem(mpz_heap_elem * elem){
//    elements.push_back(elem);
//}
template <class heapType,class heapElement>inline void MpzHeapNodeTemplate<heapType,heapElement>::pushElem(heapElement elem){
    
    size_t++;
    sum+=elements.Insert(elem);
}
//template <class heapType,class heapElement>inline void MpzHeapNodeTemplate<heapType,heapElement>::pushElemDelayed(heapElement elem){
//    size_t++;
//    sum+=elements.InsertDelayed(elem);
//}
template <class heapType,class heapElement>inline void MpzHeapNodeTemplate<heapType,heapElement>::print(){
    elements.print();
}
template <class heapType,class heapElement>inline heapType & MpzHeapNodeTemplate<heapType,heapElement>::data(){
    return elements;
}

template <class heapType,class heapElement>inline mpz_class  MpzHeapNodeTemplate<heapType,heapElement>::getNodeId() const {
    return nodeId;
}

template <class heapType,class heapElement>inline void MpzHeapNodeTemplate<heapType,heapElement>::setNodeId(mpz_class  nodeId) {
    this->nodeId = nodeId;
}
template <class heapType,class heapElement>inline bool MpzHeapNodeTemplate<heapType,heapElement>::prune(mpz_class & min, unsigned int part){
    mpz_class front;
    front=elements.valueMax();
    mpz_class factor=front-(sum-front)/(part-1);
    if(factor>=min){
        return true;
    }
    return false;
}

template <class heapType,class heapElement>inline void MpzHeapNodeTemplate<heapType,heapElement>::setParent(MpzHeapNodeTemplate* parent) {
    this->parent = parent;
}
typedef MpzHeapNodeTemplate<mpz_heap_ptr, mpz_heap_elem*> mpz_node_bfs;
typedef MpzHeapNodeTemplate<mpz_heap,mpz_class> mpz_node;
#endif	/* MPZ_HEAP_NODE_TEMPLATE_H */

