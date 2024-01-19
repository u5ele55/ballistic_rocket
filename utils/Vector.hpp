#pragma once
#include <vector>
#include <ostream>

class Vector {
private:
    int n;
    double * data;
public:
    Vector(int n);

    Vector(std::initializer_list<double> list);

    Vector(std::vector<double> l);

    Vector(const Vector &other);
    Vector(Vector &&other);

    int size() const;

    double &at(int y);
    double at(int y) const;

    double &operator[](int n);
    double operator[](int n) const;

    explicit operator bool() const;

    Vector operator+(const Vector &other) const;

    Vector operator-() const;

    Vector operator-(const Vector &other) const;

    Vector operator*(double val) const;

    Vector operator/(double val) const;

    Vector &operator+=(const Vector &other);

    Vector &operator=(const Vector &other);

    Vector &operator=(Vector &&other);

    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

    /**
     * @return is current vector lower then other lexicographically
     * */
    bool operator<(const Vector &other) const;

    /**
     * @return dot product of the vectors
     * */
    double dot(const Vector &other) const;

    Vector cross(const Vector &other) const;

    double norm() const;

    void resize(int newN);

    friend std::ostream &operator<<(std::ostream &stream, const Vector &vec);
};

std::ostream &operator<<(std::ostream &stream, const Vector &vec);