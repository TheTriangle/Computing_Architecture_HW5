#include "deque.h"

void deque::PushFront(number* n) {
    length++;
    if (leftmost == nullptr) {
        leftmost = new node();
        leftmost->value = n;
        rightmost = leftmost;
        return;
    }

    rightmost->right = new node();
    rightmost->right->value = n;
    rightmost->right->left = rightmost;
    rightmost = rightmost->right;
}

void deque::PushBack(number* n) {
    length++;
    if (leftmost == nullptr) {
        leftmost = new node();
        leftmost->value = n;
        rightmost = leftmost;
        return;
    }

    leftmost->left = new node();
    leftmost->left->value = n;
    leftmost->left->right = leftmost;
    leftmost = leftmost->left;
}

number* deque::PopFront() {
    number* ans = rightmost->value;
    if (length == 1) {
        // delete rightmost->value;
        delete rightmost;
        rightmost = nullptr;
        leftmost = nullptr;
        length--;
        return ans;
    }
    length--;
    node* newright = rightmost->left;
    // delete rightmost->value;
    delete rightmost;
    rightmost = newright;
    rightmost->right = nullptr;
    return ans;
}


number* deque::PopBack() {
    number* ans = leftmost->value;
    if (length == 1) {
        // delete leftmost->value;
        delete leftmost;
        rightmost = nullptr;
        leftmost = nullptr;
        length--;
        return ans;
    }
    length--;
    node* newleft = leftmost->right;

    // delete leftmost->value;
    delete leftmost;
    leftmost = newleft;
    leftmost->left = nullptr;
    return ans;
}

number* deque::Front() {
    return rightmost->value;
}

number* deque::Back() {
    return leftmost->value;
}

int deque::Size() {
    return length;
}

void deque::Clear() {
    if (length == 0)
        return;
    length = 0;
    while (leftmost != rightmost) {
        node* newleft = leftmost->right;
        // delete leftmost->value;
        delete leftmost;
        leftmost = newleft;
    }
    // delete leftmost->value;
    delete leftmost;
    leftmost = nullptr;
    rightmost = nullptr;
}

void SwapWithNext(deque::node* n) {
    deque::node* nextnode = n->right;
        //printf("UUUUU\n");

    if (n->left != nullptr)
        n->left->right = nextnode;
        //printf("AAAA\n");

    if (nextnode->right != nullptr)
        nextnode->right->left = n;
    nextnode->left = n->left;
    n->right = nextnode->right;

    n->left = nextnode;
    nextnode->right = n;
}

void deque::Print() {
    node* runningnode = leftmost;
    if (runningnode == nullptr) return;
    while (runningnode != rightmost) {
        printf("%f ", runningnode->value->ConvertToReal());
        runningnode = runningnode->right;
    }
}

void deque::BubbleSort() {
    if (length <= 1)
        return;
    node* runningnode = leftmost;
    for (int i = 0; i < Size() - 1; i++) {
        for (int j = 0; j < Size() - i - 1; j++) {
            if (runningnode->value->ConvertToReal() > runningnode->right->value->ConvertToReal()) {
                if (runningnode == leftmost)
                    leftmost = runningnode->right;
                if (runningnode->right == rightmost)
                    rightmost = runningnode;
                SwapWithNext(runningnode);
            }
            else
                runningnode = runningnode->right;
        }
        runningnode = leftmost;
    }
}