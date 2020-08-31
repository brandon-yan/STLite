#include <iostream>
#include "deque.hpp"
using namespace sjtu;
int main() {
    deque <int> a;
    for (int i = 0; i < 10005; ++i) {
        a.push_back(i);
        std::cout << i << "a" << std::endl;
        std::cout << a[i] << std::endl;
    }
    if (pos >= it->length + 1 || pos <= 0) throw index_out_of_bound();
    int count = 0, ret = 0;
    block *p = it->head->next;
    while (count < pos) {
        if (count + p->len < pos) {
            count += p->len;
            p = p->next;
        }
        else {
            ret = pos - count - 1;
            return p->data[ret];
        }
    }
    return 0;
    if (pos < 0 || pos >= length) throw index_out_of_bound();
    int count = 0, ret = 0, start = pos + 1;
    block *p = head->next;
    while (count < start) {
        if (count + p->len < start) {
            count += p->len;
            p = p->next;
        }
        else {
            ret = start - count;
            return p->data[ret - 1];
        }
    }
}
