//
//  vector.hpp
//  MSTL
//
//  Created by 오민호 on 2017. 3. 22..
//  Copyright © 2017년 오민호. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <iostream>

namespace omh {
    template<typename T>
    class vector {
        T* base; // start pointer
        int bsize; // count of item;
        size_t bcapacity; //
    public:
        class iterator {
            T* pos;
        public:
            iterator(T* pos = 0);
            T& operator*();
            size_t operator-(const iterator& iter);
            iterator& operator++() {
                pos++;
                return (*this);
            }
            const iterator operator++(int);
            bool operator!=(const iterator& iter) const;
            bool operator==(const iterator& iter) const;
        };
        vector(size_t init_cnt = 0, T t = 0);
        void reserve(size_t capacity);
        void resize(size_t nsize, T t = 0);
        void push_back(T t);
        void insert(iterator at, T t);
        void erase(iterator at);
        size_t size() const;
        size_t capacity() const;
        iterator begin() const;
        iterator end() const;
        T& operator[](size_t index);
    };
}
using namespace omh;

template<typename T>
vector<T>::vector(size_t init_cnt, T t) {
    base = 0;
    bcapacity = 0;
    reserve(init_cnt);
    for(int i = 0 ; i < init_cnt; ++i)
        push_back(t);
}

template<typename T>
vector<T>::iterator::iterator(T* pos) :pos(pos){}

template<typename T>
T& vector<T>::iterator::operator*() {
    return *pos;
}

template<typename T>
size_t vector<T>::iterator::operator-(const iterator& iter) {
    return pos - iter.pos;
}

//template<typename T>
//typename vector<T>::iterator& vector<T>::iterator::operator++() {
//    pos++;
//    return *this;
//}

template<typename T>
const typename vector<T>::iterator vector<T>::iterator::operator++(int) {
    iterator iter(*this);
    pos++;
    return iter;
}

template<typename T>
bool vector<T>::iterator::operator!=(const iterator& iter) const {
    return pos != iter.pos;
}

template<typename T>
bool vector<T>::iterator::operator==(const iterator& iter) const {
    return pos == iter.pos;
}

template<typename T>
void vector<T>::reserve(size_t capacity) {
    T* tmp = new T[capacity];
    if(bsize) {
        for(size_t i = 0 ; i < bsize ; ++i) {
            tmp[i] = base[i];
        }
        delete[] base;
    }
    base = tmp;
    bcapacity = capacity;
}

template<typename T>
void vector<T>::resize(size_t nsize, T t) {
    if(bsize < nsize) {
        for(size_t i = bsize; i < nsize ; ++i)
            push_back(t);
    } else {
        for(size_t i = nsize; i < bsize;)
            erase(base + i);
    }
}
template<typename T>
void vector<T>::push_back(T t) {
    insert(end(), t);
}

template<typename T>
void vector<T>::insert(vector<T>::iterator at, T t) {
    size_t index = at - base;
    if(bsize == bcapacity) {
        reserve(bcapacity + 10);
    }
    for(size_t i = bsize ; i > index ; --i) {
        base[i] = base[i - 1];
    }
    base[index] = t;
    bsize++;
}

template<typename T>
void vector<T>::erase(vector<T>::iterator at) {
    size_t index = at - base;
    for(size_t i = index + 1 ; i < bsize ; ++i)
        base[i - 1] = base[i];
    bsize--;
}

template<typename T>
size_t vector<T>::size() const {
    return bsize;
}

template<typename T>
size_t vector<T>::capacity() const {
    return bcapacity;
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() const {
    return base;
}

template<typename T>
typename vector<T>::iterator vector<T>::end() const {
    return base + bsize;
}

template<typename T>
T& vector<T>::operator[](size_t index) {
    if(index >= 0 && index < bsize) return base[index];
    throw "wrong index";
}





#endif /* vector_hpp */
