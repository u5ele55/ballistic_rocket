#include "Vector.hpp"

#include <stdexcept>
#include <cmath>

Vector::Vector(int n) : n(n) {
    this->data = new double[n];
    for (int i = 0; i < n; i++) {
        at(i) = 0;
    }
}


double &Vector::at(int y) {
    return this->data[y];
}

double Vector::at(int y) const {
    return this->data[y];
}

Vector::Vector(std::initializer_list<double> list)
        : Vector(list.size()) {
    int i = 0;
    for (auto p = list.begin(); p != list.end(); p++) {
        at(i) = *p;
        i++;
    }
}

Vector::Vector(std::vector<double> l)
        : Vector(l.size()) {
    for (int i = 0; i < (int)l.size(); i++) {
        at(i) = l[i];
    }
}

Vector::Vector(const Vector &other) 
        : Vector(other.n) {
    for (int i = 0; i < other.n; i++) {
        at(i) = other.at(i);
    }
}

Vector::Vector(Vector &&other) 
        : Vector(other.n) {
    for (int i = 0; i < other.n; i++) {
        at(i) = other.at(i);
    }
}

int Vector::size() const {
    return n;
}

double &Vector::operator[](int n) {
    return at(n);
}

double Vector::operator[](int n) const {
    return at(n);
}

Vector::operator bool() const {
    return n;
}

double Vector::dot(const Vector &other) const {
    double res = 0;
    for (int i = 0; i < n; i ++) {
        res += other.at(i) * at(i);
    }
    return res;
}

Vector Vector::cross(const Vector &other) const
{
    if (size() != 3) {
        throw std::runtime_error("Vector::cross: Only 3-dim vectors allowed");
    } 
    double ax = at(0), ay = at(1), az = at(2);
    double bx = other.at(0), by = other.at(1), bz = other.at(2);

    return {
        ay*bz - by*az,
        az*bx - bz*ax,
        ax*by - bx*ay
    };
}

double Vector::norm() const
{
    return sqrt((*this).dot(*this));
}

void Vector::resize(int newN){
    auto *newData = new double[newN];
    for (int i = 0; i < this->n; i++) {
        newData[i] = at(i);
    }

    delete[] data;
    data = newData;

    this->n = n;
}

Vector Vector::operator-(const Vector &other) const {
    return *this + (-other);
}

Vector Vector::operator*(double val) const {
    Vector res(n);
    for (int i = 0; i < n; i++) {
        res[i] = at(i) * val;
    }
    return res;
}

Vector Vector::operator+(const Vector &other) const {
    if (n != other.n) {
        throw std::invalid_argument("Vector::operator+: Wrong sizes");
    }
    Vector result = Vector(n);

    for (int i = 0; i < n; i++) {
        result.at(i) = at(i) + other.at(i);
    }

    return result;
}

Vector Vector::operator-() const {
    Vector result = Vector(n);

    for (int i = 0; i < n; i++) {
        result.at(i) = -at(i);
    }

    return result;
}

Vector &Vector::operator+=(const Vector &other) {
    if (n != other.n) {
        throw std::invalid_argument("Vector::operator+=: Wrong sizes");
    }

    for (int i = 0; i < n; i++) {
        at(i) += other.at(i);
    }

    return *this;
}

Vector &Vector::operator=(const Vector &other) {
    resize(other.n);
    for (int i = 0; i < other.n; i++) {
        at(i) = other.at(i);
    }
    return *this;
}

Vector &Vector::operator=(Vector &&other)
{
    resize(other.n);
    for (int i = 0; i < other.n; i++) {
        at(i) = other.at(i);
    }
    return *this;
}

bool Vector::operator==(const Vector &other) const
{
    if (other.n != n) {
        return false;
    }
    for (int i = 0; i < n; i ++) {
        if (other[i] != at(i)) {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector &other) const
{
    return !(*this == other);
}

bool Vector::operator<(const Vector &other) const {
    if (other.n != n) {
        return other.n < n;
    }
    for (int i = 0; i < n; i ++) {
        if (at(i) < other[i]) {
            return true;
        }
        if (at(i) > other[i]) {
            return false;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const Vector &vec) {
    stream << "[";
    for (int i = 0; i < vec.n; i++) {
        stream << vec.at(i) << ((i == vec.n - 1) ? "" : " ");
    }
    stream << "]";

    return stream;
}