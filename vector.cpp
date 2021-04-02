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
    vector::vector (unsigned long int width) 
    : matrix (width, 1UL) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3) 
                  << id   << " vector "
                  << NCOL << std::endl;
#endif /* DEBUG */

    }

    vector::vector (unsigned long int width, double def)
    : matrix (width, 1UL) { 

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3) 
                  << id   << " vector with default " 
                  << NCOL << std::endl;
#endif /* DEBUG */

        for (unsigned long int i = 0; i < m_width; i++) 
            m_data[i] = def;
    }

    vector::vector (const _row& refer) 
    : matrix (refer.m_width, 1UL) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector copy from row " 
                  << NCOL << std::endl;
#endif /* DEBUG */

        for (unsigned long int i = 0; i < m_width; i++)
            m_data[i] = refer.m_data[i];
    }

    vector::vector (const vector& refer)
    : matrix (refer.m_width, 1UL) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector copy from " << std::setw (3)
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        for (unsigned long int i = 0; i < m_width; i++)
            m_data[i] = refer.m_data[i];
    }

    vector::vector (vector&& refer)
    : matrix (refer) {

#ifdef DEBUG
        std::cerr << "\033[1A\033[2K" 
                  << GCOL << " + " << std::setw (3)
                  << id   << " vector move from " << std::setw (3)
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

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


    // вспомогательные
    double vector::abs() const {
        double abs = 0;
        for (unsigned long int i = 0; i < m_width; i++)
            abs += m_data[i] * m_data[i];
        return sqrt(abs);
    }

    vector vector::get_transpose() const {
        return vector (*this).to_transpose();
    }

    vector& vector::to_transpose() {
        unsigned long int m_tmp = m_height;
        m_height = m_width;
        m_width = m_tmp;
        return *this;
    }

    vector vector::get_normalize() const {
        return vector (*this).to_normalize();
    }

    vector& vector::to_normalize() {
        double len = abs();
        for (unsigned long int i = 0; i < m_width; i++) 
            m_data[i] = m_data[i] / len;
        return *this;
    }

    vector& vector::operator+ () { 
        matrix::operator+();
        return *this;
    }

    vector& vector::operator- () {
        matrix::operator-();
        return *this;
    }


    // индексирование
    double& vector::operator[] (unsigned long int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }

    double vector::operator[] (unsigned long int index) const {
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

        matrix::operator=(refer);
        return *this;
    }

    vector& vector::operator= (vector&& refer) {
        matrix::operator=(refer);
        return *this;
    }

    vector& vector::operator= (double def) {
        matrix::operator=(def);
        return *this;
    }

    vector& vector::operator+= (const vector& B) {
        matrix::operator+=(B);
        return *this;
    }

    vector& vector::operator+= (const matrix& B) {
        matrix::operator+=(B);
        return *this;
    }

    vector& vector::operator-= (const vector& B) { 
        matrix::operator-=(B);
        return *this;
    }

    vector& vector::operator-= (const matrix& B) {
        matrix::operator-=(B);
        return *this;
    }

    vector& vector::operator*= (const matrix& B) {
        matrix::operator*=(B);
        return *this;
    }

    vector& vector::operator*= (double B) {
        matrix::operator*=(B);
        return *this;
    }


    // внешние функции

    vector operator+ (const vector& A, const vector& B) {
        return vector (A) += B;
    }
  
    vector operator+ (const vector& A, const matrix& B) {
        return vector (A) += B;
    }

    vector operator- (const vector& A, const vector& B) {
        return vector (A) -= B;
    }

    vector operator- (const vector& A, const matrix& B) {
        return vector (A) -= B;
    }

    vector operator* (const vector& A, double B) {
        return vector (A) *= B;
    }

    vector operator* (double A, const vector& B) {
        return vector (B) *= A ;
    }

    vector operator* (const vector& A, const matrix& B) {
        return vector (A) *= B;
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
        for (unsigned long int i = 0; i < A.m_width; i++) 
            result += A.m_data[i] * B.m_data[i];
        return result;
    }


    // стейтмент вывода
    std::ostream& operator<< (std::ostream& out, const vector& V) {
        std::ios state (nullptr);
        state.copyfmt(std::cout);
        state.setf (std::ios_base::showpoint);
        out << std::setw (0) << "(";
        for (unsigned long int i = 0; i < V.m_width*V.m_height; i++) {
            out.copyfmt (state);
            out << V.m_data[i]
                << std::setw (0)
                << ((i == V.m_width*V.m_height - 1)?")":", ");
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
