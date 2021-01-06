#include "BinaryHeap.hpp"
#include <iostream>
#include <ostream>
#include <limits>

using namespace std;

BinaryHeap::BinaryHeap(const double* priorities, int numItems){
    
    heap = new int[numItems];
    loc = new int[numItems];
    pr = new double[numItems];
    size = numItems;

    for(int i = 0; i < numItems; i++){
		heap[i] = i;
		pr[i] = priorities[i];
		loc[i] = i;
	}
	for(int i=(size-1); i>=0; i--){
		this->heapify(i);
	}
}

BinaryHeap::~BinaryHeap(){
    delete[] pr;
	delete[] this->heap;
	delete[] this->loc;
}

int BinaryHeap::getLeft(int pos){
	return 2*(pos)+1;
}

int BinaryHeap::getRight(int pos){
	return (2*(pos))+2;
}

int BinaryHeap::getParent(int pos){
 	return (pos-1)/2;
}

void BinaryHeap::heapify(int pos){

	int lChild=this->getLeft(pos);
	int rChild=this->getRight(pos);
	int min;
	if(lChild<(size-1) && (pr[heap[lChild]] < pr[heap[pos]])){
		min = lChild;
	} else{
		min=pos;
	}
	if(rChild<(size-1) && (pr[heap[rChild]] < pr[heap[min]])){
		min=rChild;
	}
	if(min!=pos){
 		loc[heap[min]]=pos;
		loc[heap[pos]] = min;
		int pos1 = heap[min];
		int lpos = heap[pos];
		heap[min]=lpos;
		heap[pos]=pos1;
		
		this->heapify(min);
	}
 }

 int BinaryHeap::getMin() const{
	return this->heap[0];
}

void BinaryHeap::popMin(){

	loc[heap[size-1]] = loc[heap[0]];
	loc[heap[0]]=std::numeric_limits<int>::max();

	int p1=heap[0];
	int p2=heap[size-1];

	heap[0]=p2;
	heap[size-1]=p1;
	size-=1;

	this->heapify(0);
}

bool BinaryHeap::contains(int item) const{
	if(this->loc[item]==(numeric_limits<int>::max())){
		return false;
	} else{
		return true;
	}
 }

 double BinaryHeap::getPriority(int item) const{
	return pr[item];
}

void BinaryHeap::decreasePriority(int item, double newPriority){

    int i = this->getPos(item);
	if(newPriority < pr[item]){
		pr[item]=newPriority;
		while(i>0 && pr[heap[this->getParent(i)]] > pr[heap[i]]){
			pr[heap[i]]=this->getParent(i);
			pr[heap[this->getParent(i)]]=i;
			int p1=heap[i];
			int p2=heap[this->getParent(i)];
			heap[i]=p2;
			heap[this->getParent(i)]=p1;
		
			i=this->getParent(i);
		}
	}
}

int BinaryHeap::getSize() const{
	return size;
}

int BinaryHeap::getItem(int pos) const{
	return heap[pos];
}

int BinaryHeap::getPos(int item) const{
	return loc[item];
	
}

void BinaryHeap::printHeap(){
	for(int i =0; i < this->size; i++){
		cout<<heap[i]<<"  "<< i << "  l  " << loc[heap[i]] <<endl;
	}
	
}








    