#include "poly.hpp"

#include <iostream>
#include <cstdlib>

using std::copy;
using std::max;
using std::min;
using std::swap;

bool poly_linked_test() {
    // std::cout << "poly was linked" << std::endl;
    return true;
}

// explicit impl
template class Poly<short>;
template class Poly<int>;
template class Poly<long>;
template class Poly<long long>;
template class Poly<float>;
template class Poly<double>;
template class Poly<long double>;






template <class T>
Poly<T>::Poly() 
: size{1}, degree{-1}, coeffs{(T*) malloc(sizeof(T))} {
    coeffs[0] = zero;
}


template <class T>
Poly<T>::Poly(int degree_)
: size{degree_ + 1}, degree{degree_}, coeffs{(T*) malloc(size * sizeof(T))} {
    for(int i = 0; i < degree; i++) {
        coeffs[i] = zero;
    }
    coeffs[degree] = (T)1;
}


template <class T>
Poly<T>::Poly(int degree_, T k)
: degree{degree_}, size{degree + 1}, coeffs{(T*) malloc(size * sizeof(T))} {
    for(int i = 0; i < degree; i++) {
        coeffs[i] = zero;
    }
    coeffs[degree] = k;
}


template <class T>
Poly<T>::Poly(int degree_, T* poly)
: degree{degree_}, size{degree + 1} {
    coeffs = (T*) malloc(size * sizeof(T));
    copy(poly, poly + size, coeffs);
}


template <class T>
Poly<T>::Poly(const Poly<T>& poly)
: degree{poly.degree}, size{degree + 1} {
    coeffs = (T*) malloc(size * sizeof(T));
    copy(poly.coeffs, poly.coeffs + size, coeffs);
}

template <class T>
Poly<T>::~Poly() { free(coeffs); }







template <class T>
void Poly<T>::push(T k) {
    if (degree++ >= size) {
        size *= 2; 
        coeffs = (T*) realloc(coeffs, size * sizeof(T));
    }
    coeffs[degree] = k;
}

template <class T>
void Poly<T>::remove_trailing_zeros() {
    while (coeffs[degree] == zero && degree >= 0) { degree--; }
    size = degree + 1 + (int)(degree == -1);
    coeffs = (T*) realloc(coeffs, size * sizeof(T));
}

template <class T>
T Poly<T>::high_coeff() const {
    return (*this)[degree];
}






template <class T>
T& Poly<T>::operator[] (int idx) {
    if (0 <= idx && idx <= degree) {
        return coeffs[idx];
    }
    return zero;
}

template <class T>
T Poly<T>::operator[] (int idx) const {
    if (0 <= idx && idx <= degree) {
        return coeffs[idx];
    }
    return zero;
}

template <class T>
bool Poly<T>::operator== (const Poly<T>& poly) {
    if (degree == poly.degree) {
        for (int i = 0; i <= degree; i++) {
            if (coeffs[i] != poly[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}






template <class T>
Poly<T> Poly<T>::operator+ (const Poly<T>& poly) const {
    Poly<T> out;
    for (int i = 0; i <= max(degree, poly.degree); i++) {
        out.push((*this)[i] + poly[i]);
    }
    return out;
}

template <class T>
Poly<T> Poly<T>::operator- (const Poly<T>& poly) const {
    Poly<T> out;
    for (int i = 0; i <= max(degree, poly.degree); i++) {
        out.push((*this)[i] - poly[i]);
    }
    out.remove_trailing_zeros();
    return out;
}

template <class T>
Poly<T> Poly<T>::operator* (const Poly<T>& poly) const {
    Poly<T> out;
    for (int coeff = 0; coeff <= degree + poly.degree; coeff++) {
        out.push(0);
        for (int i = 0; i <= min(coeff, degree); i++) {
            out[coeff] += (*this)[i] * poly[coeff - i];
        }
    }
    return out;
}

template <class T>
Poly<T> Poly<T>::operator/ (const Poly<T>& poly) const {
    Poly<T> rem(*this);
    Poly<T> quot;
    for (int i = rem.degree - poly.degree; i >= 0; i--) {
        T k = rem.high_coeff() / poly.high_coeff();
        Poly<T> k_x(i, k);
        rem -= poly * k_x;
        quot += k_x;
    }
    return quot;
}

template <class T>
Poly<T> Poly<T>::operator% (const Poly<T>& poly) const {
    Poly<T> rem(*this);
    for (int i = rem.degree - poly.degree; i >= 0; i--) {
        Poly<T> k(i, rem.high_coeff() / poly.high_coeff());
        rem -= poly * k;
    }
    return rem;
}


template <class T>
void Poly<T>::operator+= (const Poly<T>& poly) {
    for (int i = 0; i <= degree; i++) {
        (*this)[i] += poly[i];
    }
    for (int i = degree + 1; i <= poly.degree; i++) {
        push(poly[i]);
    }
}

template <class T>
void Poly<T>::operator-= (const Poly<T>& poly) {
    for (int i = 0; i <= degree; i++) {
        (*this)[i] -= poly[i];
    }
    for (int i = degree + 1; i <= poly.degree; i++) {
        push(-poly[i]);
    }
    remove_trailing_zeros();
}

template <class T>
void Poly<T>::operator*= (const Poly<T>& poly) {
    T* c_s = (T*) malloc((degree + poly.degree) * sizeof(T));
    for (int c = 0; c <= degree + poly.degree; c++) { c_s[c] = (T)0; }
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= poly.degree; j++) {
            c_s[i + j] += coeffs[i] * poly.coeffs[j]; 
        }
    }
    coeffs = c_s;
    degree += poly.degree;
    size = degree + 1;
}

template <class T>
void Poly<T>::operator/= (const Poly<T>& poly) {
    Poly<T> rem(*this);
    (*this) -= (*this);
    for (int i = rem.degree - poly.degree; i >= 0; i--) {
        T k = rem.high_coeff() / poly.high_coeff();
        Poly<T> k_x(i, k);
        rem -= poly * k_x;
        (*this) += k_x;
    }
}

template <class T>
void Poly<T>::operator%= (const Poly<T>& poly) {
    for (int i = degree - poly.degree; i >= 0; i--) {
        Poly<T> k(i, high_coeff() / poly.high_coeff());
        (*this) -= poly * k;
    }
}