#ifndef __deque__
#define __deque__

class deque {
public:
    class node {
    public:
        number* value;
        node* left = nullptr;
        node* right = nullptr;
    };
    node* rightmost = nullptr;
    node* leftmost = nullptr;

    int length = 0;

    void PushFront(number* n);

    void PushBack(number* n);

    number* PopFront();

    number* PopBack();

    number* Front();

    number* Back();

    int Size();

    void Clear();

    void BubbleSort();

    void Swap(node* n);

    void Print();

    ~deque() {
        Clear();
    }
};

#endif // __deque__