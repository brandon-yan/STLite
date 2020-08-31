#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>
#include <cassert>

namespace sjtu {

    template<class T>
    class deque {
    public:
        struct block {
            block *last, *next;
            T *data;
            int size, len;
            block(): size(1024), len(0), last(nullptr), next(nullptr) {
                data = (T*) (operator new (size * sizeof(T)));
            }
            block(const block &other): size(other.size), len(other.len), last(nullptr), next(nullptr) {
                data = (T*) (operator new (size * sizeof(T)));
                for (int i = 0; i < len; ++i) {
                    new(data + i) T(other.data[i]);
                }
            }
            ~block() {
                for (int i = 0; i < len; ++i)
                    data[i].~T();
                operator delete (data);
                len = 0;
            }
        };
        block *head, *tail;
        int length, blocknum;
        class const_iterator;
        class iterator {
        private:
            friend const_iterator;
        public:
            int pos;
            deque *it;
            iterator (int obj1 = 0, deque *obj2 = nullptr) {
                pos = obj1;
                it = obj2;
            }
            iterator operator+(const int &n) const {
                return iterator(pos + n, it);
            }
            iterator operator-(const int &n) const {
                return iterator(pos - n, it);
            }
            int operator-(const iterator &rhs) const {
                if (it != rhs.it) throw invalid_iterator();
                return (pos - rhs.pos);
            }
            iterator& operator+=(const int &n) {
                pos += n;
                return *this;
            }
            iterator& operator-=(const int &n) {
                pos -= n;
                return *this;
            }
            iterator operator++(int) {
                iterator tmp = *this;
                ++pos;
                return tmp;
            }
            iterator& operator++() {
                ++pos;
                return *this;
            }
            iterator operator--(int) {
                iterator tmp = *this;
                --pos;
                return tmp;
            }
            iterator& operator--() {
                --pos;
                return *this;
            }
            T& operator*() const {
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
            }
            T* operator->() const noexcept {
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
                        return &p->data[ret];
                    }
                }
            }
            bool operator==(const iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return true;
                else return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return true;
                else return false;
            }
            bool operator!=(const iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return false;
                else return true;
            }
            bool operator!=(const const_iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return false;
                else return true;
            }
        };
        class const_iterator {
        private:
            friend iterator;
        public:
            int pos;
            const deque *it;
            const_iterator (int obj1 = 0, const deque *obj2 = nullptr) {
                pos = obj1;
                it = obj2;
            }
            const_iterator(const const_iterator &other) {
                pos = other.pos;
                it = other.it;
            }
            const_iterator(const iterator &other) {
                pos = other.pos;
                it = other.it;
            }
            const_iterator operator+(const int &n) const {
                return const_iterator(pos + n, it);
            }
            const_iterator operator-(const int &n) const {
                return const_iterator(pos - n, it);
            }
            int operator-(const const_iterator &rhs) const {
                if (it != rhs.it) throw invalid_iterator();
                return (pos - rhs.pos);
            }
            const_iterator& operator+=(const int &n) {
                pos += n;
                return *this;
            }
            const_iterator& operator-=(const int &n) {
                pos -= n;
                return *this;
            }
            const_iterator operator++(int) {
                const_iterator tmp = *this;
                ++pos;
                return tmp;
            }
            const_iterator& operator++() {
                ++pos;
                return *this;
            }
            const_iterator operator--(int) {
                const_iterator tmp = *this;
                --pos;
                return tmp;
            }
            const_iterator& operator--() {
                --pos;
                return *this;
            }
            const T& operator*() const {
                if (pos >= it->length + 1 || pos <= 0) throw index_out_of_bound();
                int count = 0, ret = 0;
                block *p = it->head->next;
                while (count < pos) {
                    if (count + p->len < pos) {
                        count += p->len;
                        p = p->next;
                    }
                    else {
                        ret = pos - count;
                        return p->data[ret - 1];
                    }
                }
            }
            const T* operator->() const noexcept {
                if (pos >= it->length + 1 || pos <= 0) throw index_out_of_bound();
                int count = 0, ret = 0;
                block *p = it->head->next;
                while (count < pos) {
                    if (count + p->len < pos) {
                        count += p->len;
                        p = p->next;
                    }
                    else {
                        ret = pos - count;
                        return &p->data[ret - 1];
                    }
                }
            }
            bool operator==(const iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return true;
                else return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return true;
                else return false;
            }
            bool operator!=(const iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return false;
                else return true;
            }
            bool operator!=(const const_iterator &rhs) const {
                if (rhs.pos == pos && rhs.it == it) return false;
                else return true;
            }
        };
        deque() {
            length = 0;
            blocknum = 0;
            head = new block;
            tail = new block;
            head->next = tail;
            tail->last = head;
        }
        deque(const deque &other) {
	        length = other.length;
	        blocknum = other.blocknum;
            if (length == 0) {
                head = new block;
                tail = new block;
                head->next = tail;
                tail->last = head;
            }
            else {
                head = new block;
                block *p = head, *q = other.head->next;
                while (q != other.tail) {
                    block *tmp;
                    tmp = new block(*q);
                    tmp->last = p;
                    p->next = tmp;
                    p = p->next;
                    q = q->next;
                }
                tail = new block;
                tail->last = p;
                p->next = tail;
            }
        }
        ~deque() {
            clear();
            delete head;
            delete tail;
        }
        deque &operator=(const deque &other) {
            if (this == &other) return *this;
            clear();
            length = other.length;
            blocknum = other.blocknum;
            if (length == 0) {
                head->next = tail;
                tail->last = head;
            }
            else {
                block *p = head, *q = other.head->next;
                while (q != other.tail) {
                    block *tmp;
                    tmp = new block(*q);
                    tmp->last = p;
                    p->next = tmp;
                    p = p->next;
                    q = q->next;
                }
                tail->last = p;
                p->next = tail;
            }
            return *this;
        }
        void findPos(int start, int &pos, block *&p) const{
            int count = 0;
            p = head->next;
            while (count < start) {
                if (count + p->len < start) {
                    count += p->len;
                    p = p->next;
                }
                else {
                    pos = start - count;
                    return;
                }
            }
        }
        void split(block *p, int pos) {
            block *tmp;
            tmp = new block;
            block *nextp = p->next;
            tmp->next = nextp;
            nextp->last = tmp;
            p->next = tmp;
            tmp->last = p;
            int i;
            for (i = pos; i < p->len; ++i)
                new(tmp->data + i -pos) T(p->data[i]);
            for (int j = pos; j < p->len; ++j)
                p->data[j].~T();
            tmp->len = i - pos;
            p->len = pos;
            ++blocknum;
        }
        void merge(block *p) {
            block *nextp = p->next;
            if (p->len + nextp->len <= p->size && nextp != tail && p != head) {
                for (int pos = 0; pos < nextp->len; ++pos, ++p->len)
                    new(p->data + p->len) T(nextp->data[pos]);
                p->next = nextp->next;
                nextp->next->last = p;
                delete nextp;
                --blocknum;
            }
        }
        T & at(const size_t &pos) {
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
        const T & at(const size_t &pos) const {
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
        T & operator[](const size_t &pos) {
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
        const T & operator[](const size_t &pos) const {
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
        const T & front() const {
            if (length == 0) throw container_is_empty();
            block *p = head->next;
            return p->data[0];
        }
        const T & back() const {
            if (length == 0) throw container_is_empty();
            block *p = tail->last;
            return p->data[p->len - 1];
        }
        iterator begin() {
            return iterator(1, this);
        }
        const_iterator cbegin() const {
            return const_iterator(1, this);
        }
        iterator end() {
            return iterator(length + 1, this);
        }
        const_iterator cend() const {
            return const_iterator(length + 1, this);
        }
        bool empty() const {
            if (length == 0) return true;
            else return false;
        }
        size_t size() const {
            return length;
        }
        void clear() {
            block *p = head->next;
            block *q = p;
            while (p != tail) {
                p = p->next;
                delete q;
                q = p;
            }
            length = 0;
            blocknum = 0;
            delete head;
            delete tail;
            head = new block;
            tail = new block;
            head->next = tail;
            tail->last = head;
        }
        iterator insert(iterator pos, const T &value) {
            int start = pos.pos, n;
            if (pos.it != this) throw invalid_iterator();
            if (start == length + 1) {
                push_back(value);
                return iterator(start, this);
            }
            else if (start == 1) {
                push_front(value);
                return iterator(start, this);
            }
            else {
                if (start <= 0 || start > length + 1) throw index_out_of_bound();
                block *p;
                findPos(start, n, p);
                split(p, n - 1);
                block *tmp;
                tmp = new block;
                ++blocknum;
                block *nextp = p->next;
                tmp->next = nextp;
                nextp->last = tmp;
                tmp->last = p;
                p->next = tmp;
                new(tmp->data) T(value);
                ++length;
                ++tmp->len;
                merge(tmp);
                merge(p);
                return iterator(start, this);
            }
        }
        iterator erase(iterator pos) {
            if (pos.it != this) throw invalid_iterator();
            int start = pos.pos, n;
            if (start <= 0 || start > length) throw index_out_of_bound();
            block *p;
            findPos(start, n, p);
            split(p, n);
            p->data[p->len - 1].~T();
            --p->len;
            --length;
            merge(p);
            return iterator(start, this);
        }
        void push_back(const T &value) {
            block *tmp;
            tmp = new block;
            ++blocknum;
            block *p = tail->last;
            tmp->next = tail;
            tail->last = tmp;
            tmp->last = p;
            p->next = tmp;
            new(tmp->data) T(value);
            ++length;
            ++tmp->len;
            merge(p);
        }
        void pop_back() {
            if (length == 0) throw container_is_empty();
            block *p = tail->last;
            p->data[p->len - 1].~T();
            --p->len;
            --length;
            if (p->last != head) merge(p->last);
        }
        void push_front(const T &value) {
            block *tmp;
            tmp = new block;
            ++blocknum;
            block *p = head->next;
            tmp->next = p;
            p->last = tmp;
            head->next = tmp;
            tmp->last = head;
            new(tmp->data) T(value);
            ++length;
            ++tmp->len;
            merge(tmp);
        }
        void pop_front() {
            if (length == 0) throw container_is_empty();
            block *p = head->next;
            for (int i = 0; i < p->len - 1; ++i)
                p->data[i] = p->data[i + 1];
            p->data[p->len - 1].~T();
            --p->len;
            --length;
            merge(p);
        }
    };

}

#endif
