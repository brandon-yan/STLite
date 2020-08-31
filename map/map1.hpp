/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

    template<
            class Key,
            class T,
            class Compare = std::less<Key>
    > class map {
    public:
        typedef pair<const Key, T> value_type;
        struct node {
            value_type data;
            node* left;
            node* right;
            node* father;
            node (node *other, node *f):data(other->data) {
                if (other->left != nullptr) left = new node (other->left, this);
                else left = nullptr;
                if (other->right != nullptr) right = new node (other->right, this);
                else right = nullptr;
                father = f;
            }
            node (Key k, T t, node *f):data(k, t) {
                left = nullptr;
                right = nullptr;
                father = f;
            }
            node (const value_type &val, node *f):data(val){
                left = nullptr;
                right = nullptr;
                father = f;
            }
        };
        node *root;
        int len;
        Compare com;
        void del(node *tmp) {
            if (tmp == nullptr) return;
            if (tmp->left != nullptr) del(tmp->left);
            if (tmp->right != nullptr) del(tmp->right);
            delete tmp;
        }
        node *search (const Key &k) const {
            if (len == 0) return nullptr;
            node *tmp = root;
            while (tmp != nullptr) {
                if (com(k, tmp->data.first)) tmp = tmp->left;
                else if (com(tmp->data.first, k)) tmp = tmp->right;
                else break;
            }
            return tmp;
        }
        node *findnext (node *p) const {
            if (p == nullptr) throw invalid_iterator();
            if (p->right != nullptr) {
                p = p->right;
                while (p->left != nullptr) p = p->left;
                return p;
            }
            while (p->father != nullptr) {
                if (p == p->father->left) return p->father;
                p = p->father;
            }
            return nullptr;
        }
        node *findlast (node *p) const {
            if (p == nullptr) {
                p = root;
                if (p == nullptr) throw invalid_iterator();
                while (p->right != nullptr) p = p->right;
                return p;
            }
            else if (p->left != nullptr) {
                p = p->left;
                while (p->right != nullptr) p = p->right;
                return p;
            }
            while (p->father != nullptr) {
                if (p == p->father->right) return p->father;
                p = p->father;
            }
            throw invalid_iterator();
        }
        class const_iterator;
        class iterator {
        private:
            friend const_iterator;
        public:
            node *pos;
            map *it;
            iterator() {
                pos = nullptr;
                it = nullptr;
            }
            iterator(const iterator &other) {
                pos = other.pos;
                it = other.it;
            }
            iterator(node *obj1, map *obj2) {
                pos = obj1;
                it = obj2;
            }
            iterator operator++(int) {
                node *tmp = pos;
                pos = it->findnext(pos);
                return iterator(tmp, it);
            }
            iterator & operator++() {
                pos = it->findnext(pos);
                return *this;
            }
            iterator operator--(int) {
                node *tmp = pos;
                pos = it->findlast(pos);
                return iterator(tmp, it);
            }
            iterator & operator--() {
                pos = it->findlast(pos);
                return *this;
            }
            value_type & operator*() const {
                return pos->data;
            }
            bool operator==(const iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return true;
                else return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return true;
                else return false;
            }
            bool operator!=(const iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return false;
                else return true;
            }
            bool operator!=(const const_iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return false;
                else return true;
            }
            value_type* operator->() const noexcept {
                return &(pos->data);
            }
        };
        class const_iterator {
        private:
            friend iterator;
        public:
            node *pos;
            const map *it;
            const_iterator() {
                pos = nullptr;
                it = nullptr;
            }
            const_iterator(const const_iterator &other) {
                pos = other.pos;
                it = other.it;
            }
            const_iterator(const iterator &other) {
                pos = other.pos;
                it = other.it;
            }
            const_iterator(node *obj1, const map *obj2) {
                pos = obj1;
                it = obj2;
            }
            const_iterator operator++(int) {
                node *tmp = pos;
                pos = it->findnext(pos);
                return const_iterator(tmp, it);
            }
            const_iterator & operator++() {
                pos = it->findnext(pos);
                return *this;
            }
            const_iterator operator--(int) {
                node *tmp = pos;
                pos = it->findlast(pos);
                return const_iterator(tmp, it);
            }
            const_iterator & operator--() {
                pos = it->findlast(pos);
                return *this;
            }
            value_type & operator*() const {
                return pos->data;
            }
            bool operator==(const iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return true;
                else return false;
            }
            bool operator==(const const_iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return true;
                else return false;
            }
            bool operator!=(const iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return false;
                else return true;
            }
            bool operator!=(const const_iterator &rhs) const {
                if (pos == rhs.pos && it == rhs.it) return false;
                else return true;
            }
            value_type* operator->() const noexcept {
                return &(pos->data);
            }
        };
        map() {
            root = nullptr;
            len = 0;
        }
        map(const map &other) {
            len = other.len;
            node *tmp;
            if (other.root != nullptr) tmp = new node (other.root, nullptr);
            else tmp = nullptr;
            root = tmp;
            tmp = nullptr;
        }
        map & operator=(const map &other) {
            if (this == &other) return *this;
            clear();
            len = other.len;
            node *tmp;
            if (other.root != nullptr) tmp = new node (other.root, nullptr);
            else tmp = nullptr;
            root = tmp;
            tmp = nullptr;
        }
        ~map() {
            clear();
        }
        T & at(const Key &key) {
            node *tmp = search(key);
            if (tmp == nullptr) throw index_out_of_bound();
            return tmp->data.second;
        }
        const T & at(const Key &key) const {
            node *tmp = search(key);
            if (tmp == nullptr) throw index_out_of_bound();
            return tmp->data.second;
        }
        T & operator[](const Key &key) {
            node *tmp = search(key);
            if (tmp == nullptr) {
                ++len;
                value_type t(key, T());
                if (root == nullptr) {
                    root = new node(t, nullptr);
                    return root->data.second;
                }
                tmp = root;
                node *fa;
                while (tmp != nullptr) {
                    fa = tmp;
                    if (com(key, tmp->data.first)) tmp = tmp->left;
                    else if (com(tmp->data.first, key)) tmp = tmp->right;
                }
                node *ret = new node(t, fa);
                ret->father = fa;
                if (com(key, fa->data.first)) fa->left = ret;
                else fa->right = ret;
                return ret->data.second;
            }
            return tmp->data.second;
        }
        const T & operator[](const Key &key) const {
            node *tmp = search(key);
            if (tmp == nullptr) throw index_out_of_bound();
            return tmp->data.second;
        }
        iterator begin() {
            if (len == 0) return iterator(nullptr, this);
            node *tmp = root;
            while (tmp->left != nullptr) tmp = tmp->left;
            return iterator(tmp, this);
        }
        const_iterator cbegin() const {
            if (len == 0) return const_iterator(nullptr, this);
            node *tmp = root;
            while (tmp->left != nullptr) tmp = tmp->left;
            return const_iterator(tmp, this);
        }
        iterator end() {
            return iterator(nullptr, this);
        }
        const_iterator cend() const {
            return const_iterator(nullptr, this);
        }
        bool empty() const {
            if (len == 0) return true;
            else return false;
        }
        size_t size() const {
            return len;
        }
        void clear() {
            del(root);
            len = 0;
            root = nullptr;
        }
        pair<iterator, bool> insert(const value_type &value) {
            node *tmp = search(value.first);
            iterator ret1;
            bool ret2;
            if (tmp == nullptr) {
                if (len == 0) {
                    root = new node(value, nullptr);
                    ret1.pos = root;
                    ret1.it = this;
                    ret2 = true;
                    ++len;
                    return pair<iterator, bool>(ret1, ret2);
                }
                tmp = root;
                node *fa;
                while (tmp != nullptr) {
                    fa = tmp;
                    if (com(value.first, tmp->data.first)) tmp = tmp->left;
                    else if (com(tmp->data.first, value.first)) tmp = tmp->right;
                }
                node *ret = new node(value, fa);
                ret->father = fa;
                if (com(value.first, fa->data.first)) fa->left = ret;
                else fa->right = ret;
                ret1.pos = ret;
                ret1.it = this;
                ret2 = true;
                ++len;
                return pair<iterator, bool>(ret1, ret2);
            }
            else {
                ret1.pos = tmp;
                ret1.it = this;
                ret2 = false;
                return pair<iterator, bool>(ret1, ret2);
            }
        }
        void erase(iterator pos) {
            node *tmp = pos.pos;
            if (tmp == nullptr || this != pos.it) throw index_out_of_bound();
            if (tmp->left == nullptr) {
                if (tmp == root) root = tmp->right;
                else if (tmp == tmp->father->left) tmp->father->left = tmp->right;
                else tmp->father->right = tmp->right;
                if (tmp->right != nullptr) tmp->right->father = tmp->father;
            }
            else if (tmp->right == nullptr) {
                if (tmp == root) root = tmp->left;
                else if (tmp == tmp->father->left) tmp->father->left = tmp->left;
                else tmp->father->right = tmp->left;
                if (tmp->left != nullptr) tmp->left->father = tmp->father;
            }
            else {
                node *rep = tmp->right;
                while (rep->left != nullptr) rep = rep->left;
                rep->left = tmp->left;
                rep->left->father = rep;
                if (tmp == root) root = tmp->right;
                else if (tmp == tmp->father->left) tmp->father->left = tmp->right;
                else tmp->father->right = tmp->right;
                if (tmp->right != nullptr) tmp->right->father = tmp->father;
            }
            delete tmp;
            --len;
        }
        size_t count(const Key &key) const {
            node *tmp = search(key);
            if (tmp == nullptr) return 0;
            else return 1;
        }
        iterator find(const Key &key) {
            node *tmp = search(key);
            if (tmp == nullptr) return iterator(nullptr, this);
            else return iterator(tmp, this);
        }
        const_iterator find(const Key &key) const {
            node *tmp = search(key);
            if (tmp == nullptr) return const_iterator(nullptr, this);
            else return const_iterator(tmp, this);
        }
    };

}

#endif

