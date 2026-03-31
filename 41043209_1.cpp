#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class MinPQ{
    public:
    virtual ~MinPQ(){}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T>{
    private:
    T* heap;
    int capacity;
    int size;
    public:
    MinHeap(int theCapacity = 10);
    ~MinHeap();

    bool IsEmpty() const override;
    const T& Top() const override;
    void Push(const T& x) override;
    void Pop() override;
};

template <class T>
MinHeap<T>::MinHeap(int theCapacity){
    capacity = theCapacity;
    size = 0;
    heap = new T[capacity + 1];
}

template <class T>
MinHeap<T>::~MinHeap(){
    delete[] heap;
}

template <class T>
bool MinHeap<T>::IsEmpty() const{
    return size == 0;
}

template <class T>
const T& MinHeap<T>::Top() const{
    if(IsEmpty()){
        cout << "Heap is empty!" << endl;
        exit(1);
    }
    return heap[1];
}

template <class T>
void MinHeap<T>::Push(const T& x){
    if(size == capacity){
        cout << "Heap is full!" << endl;
        return;
    }
    int i = ++size;
    while(i != 1 && x < heap[i / 2]){
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = x;
}

template <class T>
void MinHeap<T>::Pop(){
    if(IsEmpty()){
        cerr << "Heap is empty!" << endl;
        return;
    }
    T lastElement = heap[size--];
    int current = 1;
    int child = 2;
    while(child <= size){
        if(child < size && heap[child + 1] < heap[child]){
            child++;
        }
        if(lastElement <= heap[child]){
            break;
        }
        heap[current] = heap[child];
        current = child;
        child = current * 2;
    }
    heap[current] = lastElement;
}

int main(){
    MinHeap<int> h(10);
    h.Push(10);
    h.Push(4);
    h.Push(15);
    h.Push(2);
    h.Push(8);
    for(int i = 0; i < 6; i++){
        cout << "Top = " << h.Top() << endl;
        h.Pop();
        cout << "Pop\n";
    }
    return 0;
}
