#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

class BinaryHeap
{
    protected:
    int* heap;
    double* pr;
    int* loc;
    int size;


    public:
        BinaryHeap(const double* priorities, int numItems);
        ~BinaryHeap();
        int getMin() const;
        void popMin();
        bool contains(int item) const;
        double getPriority(int item) const;
        void decreasePriority(int item, double newPriority);
        int getSize() const;
        int getItem(int pos) const;
        int getPos(int item) const;

        int getLeft(int pos);
		int getRight(int pos);
        int getParent(int pos);
        void heapify(int pos);
        
        void printHeap();
};

#endif