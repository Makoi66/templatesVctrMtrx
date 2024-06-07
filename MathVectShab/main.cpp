#include <iostream>
#include <cmath>
#include <string>
#include <typeinfo>
using namespace std;

template <typename T>
class Vector {
private:
    T* a;
    int size;
public:
    Vector(int size = 0) : size(size) {
        a = new T[size];
        for (int i = 0; i < size; i++) {
            a[i] = 0;
        }
    }

    Vector(const Vector& other) : size(other.size) {
        a = new T[size];
        for (int i = 0; i < size; ++i) {
            a[i] = other.a[i];
        }
    }

    ~Vector() {
        delete[] a;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] a;
            size = other.size;
            a = new T[size];
            for (int i = 0; i < size; ++i) {
                a[i] = other.a[i];
            }
        }
        return *this;
    }


    T& operator[](int i) {
        return a[i];
    }

    const T& operator[](int i) const {
        return a[i];
    }

    int getSize() const {
        return size;
    }

};

// матрица через агрегирование
template <typename T>
class MatrixAggregation {
private:
    Vector<T>* data;
    int rows;
    int cols;

public:
    MatrixAggregation(int r, int c) : rows(r), cols(c) {
        data = new Vector<T>[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = Vector<T>(cols);
        }
    }

    ~MatrixAggregation() {
        delete[] data;
    }

    Vector<T>& operator[](int i) {
        return data[i];
    }

    const Vector<T>& operator[](int i) const {
        return data[i];
    }

};

// матрица через наследование
template <typename T>
class MatrixInheritance : public Vector<Vector<T>> {
public:
    MatrixInheritance(int r, int c) : Vector<Vector<T>>(r) {
        for (int i = 0; i < r; ++i) {
            (*this)[i] = Vector<T>(c);
        }
    }
};

int main() {
    // тестирование MatrixAggregation
    MatrixAggregation<int> m1(3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            m1[i][j] = i * 4 + j;
        }
    }
    cout << "MatrixAggregation m1:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }


    // тестирование MatrixInheritance
    MatrixInheritance<double> m2(2, 3);
    m2[0][0] = 1.0;
    m2[0][1] = 2.0;
    m2[0][2] = 3.0;
    m2[1][0] = 4.0;
    m2[1][1] = 5.0;
    m2[1][2] = 6.0;
    cout << "MatrixInheritance m2:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << m2[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}