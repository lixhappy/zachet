#ifdef tests
bool poly_linked_test();
#endif

#ifndef POLY_HPP
#define POLY_HPP

#include <cstdlib>
#include <iostream>

template <class T>
class Poly {
    private:
        T* coeffs;
        int degree;
        int size;
        T zero = (T)0;

        void remove_trailing_zeros();

    public:

        Poly();
        Poly(int);
        Poly(int, T);
        Poly(int, T*);
        Poly(const Poly<T>&);
        ~Poly();

        void push(T);
        T high_coeff() const;
        int deg() const { return degree; }
        T& operator[] (int);
        T operator[] (int) const;
        bool operator== (const Poly<T>&);

        Poly<T> operator+ (const Poly<T>&) const;
        Poly<T> operator- (const Poly<T>&) const;
        Poly<T> operator* (const Poly<T>&) const;
        Poly<T> operator/ (const Poly<T>&) const;
        Poly<T> operator% (const Poly<T>&) const;

        void operator+= (const Poly<T>&);
        void operator-= (const Poly<T>&);
        void operator*= (const Poly<T>&);
        void operator/= (const Poly<T>&);
        void operator%= (const Poly<T>&);
};


#endif