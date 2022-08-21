//
// Created by Xiaodong Liu on 8/21/22.
//

#ifndef CUSTOMVECTOR_CUSTOMVECTOR_H
#define CUSTOMVECTOR_CUSTOMVECTOR_H
#include <iostream>
#include <initializer_list>
#include <algorithm>
using namespace std;
namespace ns{
    template<typename T>
    class vector{
    private:
        size_t n, cap;
        T* arr;
        void incCapacity(){
            size_t k = 1;
            while(k <= cap){
                k <<= 1;
            }
            T* newArr = new T[k];
            copy(arr, arr+cap, newArr);
            delete [] arr;
            arr = newArr;
            cap = k;
        }


        void initCapacity(){
            cap = 1;
            while(cap <= n){
                cap <<= 1;
            }
            arr = new T[cap];
        }

    public:
        class iterator{
        private:
            T* p;
        public:
            //default
            iterator(T* _p= nullptr):p(_p){}


            //assignment operator
            iterator& operator=(const iterator& other){
                this->p = other.p;
                return *this;
            }

            //==
            bool operator==(const iterator& other) const{
                return this->p == other.p;
            }

            //* !=
            bool operator!=(const iterator& other) const{
                return !(*this == other);
            }

            //dereference
            T operator*() const{
                return *p;
            }

            //pre-increment
            iterator& operator++(){
                ++p;
                return *this;
            }

            //post-increment
            iterator operator++(int){
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

        };

        //default
        vector(size_t _n = 0, T val = 0):n(_n){
            initCapacity();
            for(int i = 0; i < n; ++i){
                arr[i] = val;
            }
        }

        //destructor
        ~vector(){
            delete [] arr;
        }

        //initializer list
        vector(initializer_list<T> li): n(li.size()){
            initCapacity();
            auto it = li.begin();
            int i = 0;
            while(it != li.end()){
                arr[i++] = *it++;
            }
        }

        //range constructor
        vector(iterator first, iterator last):n(0){
            initCapacity();
            while(first != last){
                push_back(*first++);
            }
        }

        //copy constructor
        vector(const vector<T>& other): n(other.n), cap(other.cap), arr(new T[cap]){
            copy(other.arr, other.arr+n, arr);
        }
        //copy assignment operator
        vector<T>& operator=(const vector<T>& other){
            if(this != &other){
                this->n = other.n;
                this->cap = other.cap;
                delete [] arr;
                arr = new T[cap];
                copy(other.arr, other.arr+n, arr);
            }
            return *this;
        }
        //move constructor
        vector(vector<T>&& other){
            if(this != &other){
                n = other.n;
                cap = other.cap;
                arr = other.arr;
                other.arr = nullptr;
            }
        }
        //push back
        void push_back(const T& val){
            if(n+1 > cap){
                incCapacity();
            }
            arr[n++] = val;
        }
        //pop back
        void pop_back(){
            if(n == 0){
                return;
            }
            --n;
        }

        //resize
        void resize(size_t _n, const T& val = 0){
            if(n != _n){
                swap(n, _n);
                if(n > cap){
                    incCapacity();
                }
                for(size_t i = _n; i < n; ++i){
                    arr[i] = val;
                }
            }
        }

        //reserve
        void reserve(size_t _cap){
            if(_cap >= n){
                T* newArr = new T[_cap];
                copy(arr, arr+min(_cap, cap), newArr);
                delete [] arr;
                arr = newArr;
                cap = _cap;
            }
        }

        //size
        size_t size() const noexcept{
            return n;
        }

        //capacity
        size_t capacity() const noexcept{
            return cap;
        }

        //[]
        T& operator[](size_t pos){
            if(pos >= n || arr == nullptr){
                throw out_of_range("Exceed valid range");
            }
            return arr[pos];
        }

        //begin
        iterator begin() const{
            return iterator(arr);
        }
        //end
        iterator end() const{
            return iterator(arr+n);
        }
    };

}
#endif //CUSTOMVECTOR_CUSTOMVECTOR_H
