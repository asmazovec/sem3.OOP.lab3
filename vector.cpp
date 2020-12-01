#ifndef VECTOR_CPP
#define VECTOR_CPP


#include "vector.hpp"
#include <stdexcept>
#include <iomanip>
#include <cmath>


#ifdef DEBUG

#if defined (__linux) || defined (__gnu_linux__) || defined (linux) || defined (__linux__)

#define NCOL "\x1b[0m"  // normal color
#define GCOL "\x1B[32m" // green color

#else  /* OPERATING SYSTEM */

#define NCOL "" 
#define GCOL ""

#endif /* OPERATING SYSTEM */

#endif /* DEBUG */


namespace linear {
    vector::vector (long unsigned int width) 
    : matrix (width, 1UL) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3) 
                  << id   << " vector "
                  << NCOL << std::endl;
#endif /* DEBUG */

    }

    vector::vector (long unsigned int width, double def)
    : matrix (width, 1UL) { 

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3) 
                  << id   << " vector with default " 
                  << NCOL << std::endl;
#endif /* DEBUG */

        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] = def;
    }

    vector::vector (const vector& refer)
    : matrix (refer.m_width, 1UL) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector copy from " << std::setw (3)
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        for (long unsigned int i = 0; i < m_width; i++)
            m_data[i] = refer.m_data[i];
    }

    vector::vector (vector&& refer)
    : matrix () {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector move from " << std::setw (3)
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        m_width = refer.m_width;
        delete[] m_data;
        m_data = refer.m_data;
        refer.m_width = 0;
        refer.m_data = nullptr;
    }

    vector::vector (const std::initializer_list<double> &list)
    : matrix (list.size(), 1UL) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K"
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector initializer list "
                  << NCOL << std::endl;
#endif /* DEBUG */

        int count = 0;
        for (auto &element : list) 
			m_data[count++] = element;
    }

    vector::vector (double* list, long unsigned int width)
    : matrix () {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector pointer "
                  << NCOL << std::endl;
#endif /* DEBUG */
        
        m_width = width;
        delete[] m_data;
        m_data = list;
    }

    // вспомогательные
    long unsigned int vector::get_width() const {
        return m_width;
    }

    double vector::abs() const {
        int abs = 0;
        for (long unsigned int i = 0; i < m_width; i++)
            abs += m_data[i] * m_data[i];
        return sqrt(abs);
    }

    vector& vector::get_normalize() const {
        double len = abs();
        vector* tmp = new vector (m_width);
        for (long unsigned int i = 0; i < m_width; i++) 
            (*tmp)[i] = m_data[i] / len;
        return *tmp;
    }

    vector& vector::to_normalize() {
        double len = abs();
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] = m_data[i] / len;
        return *this;
    }

    vector vector::operator+ () { 
        vector C (*this);
        return C;
    }

    vector vector::operator- () {
        vector C (m_width);
        for (long unsigned int i = 0; i < m_width; i++) 
            C.m_data[i] = -m_data[i];
        return C;
    }


    // индексирование
    double& vector::operator[] (long unsigned int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }

    double vector::operator[] (long unsigned int index) const {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }


    // присваивания
    vector& vector::operator= (const vector& refer) {

#ifdef DEBUG
        std::cerr << GCOL     << "    op = [copy vector] " 
                  << std::setw (3)
                  << id       << " <- " 
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        delete m_data;
        m_width = refer.m_width;
        m_data = new double[m_width];
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] = refer.m_data[i];
        return *this;
    }

    vector& vector::operator= (vector&& refer) {

#ifdef DEBUG
        std::cerr << GCOL     << "    op = [move vector] " 
                  << std::setw (3)
                  << id       << " <- " 
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        if (&refer == this)
            return *this;
        delete m_data;
        m_width = refer.m_width;
        m_data = refer.m_data;
        refer.m_width = 0;
        refer.m_data = nullptr;
        return *this;
    }

    vector& vector::operator= (double def) {
        for (long unsigned int i = 0; i < m_width; i++)
            m_data[i] = def;
        return *this;
    }

    vector& vector::operator+= (const vector& B) {
        if (!is_proport (B)) 
            throw std::length_error ("Vectors are not proportionate ");
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] += B.m_data[i];
        return *this;
    }

    vector& vector::operator+= (const matrix& B) {
        if (!is_proport (B))
            throw std::length_error ("Objects are not proportionate ");
        // приведение к базовому (повышающее приведение)
        dynamic_cast <matrix&> (*this) += B;
        return *this;
    }

    vector& vector::operator-= (const vector& B) { 
        if (!is_proport (B)) 
            throw std::length_error ("Vectors are not proportionate ");
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] -= B.m_data[i];
        return *this;
    }

    vector& vector::operator-= (const matrix& B) {
        if (!is_proport (B))
            throw std::length_error ("Objects are not proportionate ");
        // приведение к базовому (повышающее приведение)
        dynamic_cast <matrix&> (*this) -= B;
        return *this;
    }

    vector& vector::operator*= (const matrix& B) {
        if (!is_isomeric (B))
            throw std::length_error ("Objects are not isomeric ");
        // приведение к базовому (повышающее приведение)
        dynamic_cast <matrix&> (*this) *= B;
        return *this;
    }

    vector& vector::operator*= (double B) {
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] *= B;
        return *this;
    }


    // внешние функции
    bool is_proport (const vector& A, const vector& B) {
        return A.m_width == B.m_width; 
    }

    vector operator+ (const vector& A, const vector& B) {
        vector C (A);
        C += B;
        return C;
    }
  
    vector operator+ (const vector& A, const matrix& B) {
        vector C (A);
        C += B;
        return C;
    }

    vector operator- (const vector& A, const vector& B) {
        vector C (A);
        C -= B;
        return C;
    }

    vector operator- (const vector& A, const matrix& B) {
        vector C (A);
        C -= B;
        return C;
    }

    vector operator* (const vector& A, double B) {
        vector C (A);
        C *= B;
        return C;
    }

    vector operator* (double A, const vector& B) {
        vector C (B);
        C *= A;
        return C;
    }

    vector operator* (const vector& A, const matrix& B) {
        /*
        if (!is_isomeric (A, B))
            throw std::length_error ("Objects are not isomeric ");
        double* new_data = new double [B.m_width];
        for (long unsigned int j = 0; j < B.m_width; j++) {
            new_data[j] = 0.;
            for (long unsigned int r = 0; r < A.m_width; r++)
                new_data[j] += A.m_data[r] * B.m_data[r*B.m_width + j];
        }
        vector C (new_data, B.m_width);
        return C;
        */
        vector C (A);
        C *= B;
        return C;
    }

    /* векторное произведение */
    vector vect_mul (const vector& A, const vector& B) {
        if (A.m_width != 3 || B.m_width != 3) 
            throw std::invalid_argument ("Invalid vectors ");
        vector C = { A.m_data[1] * B.m_data[2] - A.m_data[2] * B.m_data[1], 
                     A.m_data[2] * B.m_data[0] - A.m_data[0] * B.m_data[2], 
                     A.m_data[0] * B.m_data[1] - A.m_data[1] * B.m_data[0]};
        return C;
    }

    /* скалярное произведение */
    double scal_mul (const vector& A, const vector& B) {
        if (A.m_width != B.m_width)
            throw std::invalid_argument ("Invalid vectors ");
        double result = 0.;
        for (long unsigned int i = 0; i < A.m_width; i++) 
            result += A.m_data[i] * B.m_data[i];
        return result;
    }


    // стейтмент вывода
    std::ostream& operator<< (std::ostream& out, const vector& V) {
        std::ios state (nullptr);
        state.copyfmt(std::cout);
        state.setf (std::ios_base::showpoint);
        out << std::setw (0) << "(";
        for (long unsigned int i = 0; i < V.m_width; i++) {
            out.copyfmt (state);
            out << V.m_data[i]
                << std::setw (0)
                << ((i == V.m_width - 1)?")":", ");
        }
        return out;
    }


    double cos (const vector& A, const vector& B) {
        return scal_mul (A, B) / (A.abs() * B.abs());
    }

    double sin (const vector& A, const vector& B) {
        return vect_mul (A, B).abs() / (A.abs() * B.abs());
    }

    double angle (const vector& A, const vector& B) {
        return (atan2 (vect_mul (A, B).abs(), scal_mul (A, B)) * 180 / M_PI);
    }
}
 

#endif /* VECTOR_CPP */
