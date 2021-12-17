#ifndef __deque__
#define __deque__

class Array {
    number **innerArr;
    int len = 0;

    struct ThreadParams {
        int j;
        int len;
        number **innerArr;
        bool *sorted;
    };

public:
    number* operator[] (int i) {
        return innerArr[i];
    }

    Array() {
        innerArr = new number*[10000];
        len = 0;
    }

    void push_back(number *x) {
        innerArr[len++] = x;
    }

    int size() {
        return len;
    }

    ~Array() {
        for (int i = 0; i < len; i++) {
            delete innerArr[i];
        }
        delete[] innerArr;
    }

    void parallelBubbleSort() {
        bool sorted = false;
        int len = this->len;
        number **innerArr = this->innerArr;
        std::thread threads[len + 1];
        ThreadParams params[len + 1];
        for (int i = 0; i < len - 1; i++) {
            for (int j = 0; j < (len + 1) / 2; j++) {
                params[j].j = 2 * j;
                params[j].len = len;
                params[j].innerArr = innerArr;
                params[j].sorted = &sorted;
                threads[j] = std::thread(parallelExchange, (&params[j]));
            }
            for(int j = 0; j < (len + 1) / 2; j++) {
                threads[j].join();
            }
            for (int j = 0; j < (len + 1) / 2; j++) {
                params[j + (len + 1)/2].j = 2 * j + 1;
                params[j + (len + 1)/2].len = len;
                params[j + (len + 1)/2].innerArr = innerArr;
                params[j + (len + 1)/2].sorted = &sorted;
                threads[j + (len + 1)/2] = std::thread(parallelExchange, (&params[j + (len + 1)/2]));
            }
            for(int j = (len + 1) / 2; j < (len + (len % 2)); j++) {
             // int f;
             // std::cin >> f;
             // std::cout<<j;
                threads[j].join();
            }
            // if (sorted) {
            //     break;
            // }
        }
    }

    static void *parallelExchange (ThreadParams *params) {
        ThreadParams *parameters = (ThreadParams*) params;
        if (parameters->j >= (parameters->len - 1)) return nullptr;
        if (parameters->innerArr[parameters->j]->ConvertToReal() > parameters->innerArr[parameters->j + 1]->ConvertToReal()) {
            number *h = parameters->innerArr[parameters->j + 1];
            parameters->innerArr[parameters->j + 1] = parameters->innerArr[parameters->j];
            parameters->innerArr[parameters->j] = h;

            bool notsorted = false;
            parameters->sorted = &notsorted;
        }
        return nullptr;
    }
};

#endif // __deque__