#ifndef MATRIX_CPP
#define MATRIX_CPP


#include "matrix.hpp"
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
    unsigned long int matrix::glob_id = 0;
    
    _row::_row (double* list, unsigned long int width)
    : m_data (list), m_width (width) {
        if (width < 1)
            throw std::invalid_argument ("Invalid _row size ");
    }

    double& _row::operator[] (long unsigned int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }

    double _row::operator[] (long unsigned int index) const {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }


    /// Constructor square matrix { size * size }
    matrix::matrix (unsigned long int size)
    : m_width (size), m_height (size), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix square " 
                  << NCOL << std::endl;
#endif /* DEBUG */

        if (size < 1)
            throw std::invalid_argument ("Invalid matrix size ");
        m_data = new double[size * size];
    }


    /// Constructor square matrix with default { size * size }
    matrix::matrix (unsigned long int size, double def)
    : m_width (size), m_height (size), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix square with default "
                  << NCOL << std::endl;
#endif /* DEBUG */
        
        if (size < 1)
            throw std::invalid_argument ("Invalid matrix size ");
        m_data = new double[size * size];
        for (unsigned long int i = 0; i < size * size; i++) 
            m_data[i] = def;
    }


    /// Constructor matrix { width * height }
    matrix::matrix (unsigned long int width, unsigned long int height)
    : m_width (width), m_height (height), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix "
                  << NCOL << std::endl;
#endif /* DEBUG */

        if (height < 1)
            throw std::invalid_argument ("Invalid matrix height ");
        if (width < 1)
            throw std::invalid_argument ("Invalid matrix width ");
        m_data = new double[width * height];
    }


    /// Constructor matrix with default { width * height }
    matrix::matrix (unsigned long int width, unsigned long int height, double def)
    : m_width (width), m_height (height), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix with default "
                  << NCOL << std::endl;
#endif /* DEBUG */

        if (height < 1)
            throw std::invalid_argument ("Invalid matrix height ");
        if (width < 1)
            throw std::invalid_argument ("Invalid matrix width ");
        m_data = new double[width * height];
        for (unsigned long int i = 0; i < width * height; i++) 
            m_data[i] = def;
    }


    /// Copy constructor
    matrix::matrix (const matrix& refer)
    : m_width (refer.m_width), m_height (refer.m_height), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix copy from " << std::setw (3)
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        m_data = new double[m_width * m_height];
        for (unsigned long int i = 0; i < m_width * m_height; i++) 
            m_data[i] = refer.m_data[i];
    }


    /// Move constructor
    matrix::matrix (matrix&& refer)
    : m_data (refer.m_data), m_width (refer.m_width), m_height (refer.m_height), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix move from " << std::setw (3)
                  << refer.id << NCOL << std::endl << std::endl << std::endl;
#endif /* DEBUG */

        refer.m_width = 0;
        refer.m_height = 0;
        refer.m_data = nullptr;

    }


    /// Initializer list constructor
    matrix::matrix (const std::initializer_list<std::initializer_list<double>> &list)
    : m_width (0), m_height (list.size()), id (glob_id++) {

#ifdef DEBUG
        std::cerr << GCOL << " + " << std::setw (3)
                  << id   << " matrix initializer list "
                  << NCOL << std::endl;
#endif /* DEGUB */

        m_width = list.begin()->size();
        for (auto &_row : list)
            if (_row.size() != m_width)
                throw std::length_error ("Invalid initialiser list ");
        if (m_width < 1)
            throw std::length_error ("Invalid initialiser list ");
        if (m_height < 1)
            throw std::length_error ("Invalid initialiser list ");
        m_data = new double[m_width * m_height];
        unsigned long int count = 0;
        for (auto &_row : list)
           for (auto &element : _row) 
               m_data[count++] = element;
    }


    /// Destructor matrix
    matrix::~matrix() {

#ifdef DEBUG
        std::cerr << GCOL << " - " << std::setw (3) 
                  << id   << " obj " 
                  << NCOL << std::endl;
#endif /* DEBUG */

        delete[] m_data;
    }


    // вспомогательные
    unsigned long int matrix::get_width() const {
        return m_width;
    }

    unsigned long int matrix::get_height() const {
        return m_height;
    }

    bool matrix::is_isomeric (const matrix& B) const {
        return m_width == B.m_height;
    }

    bool matrix::is_proport (const matrix& B) const {
        return (m_height == B.m_height) && (m_width == B.m_width);
    }

    double matrix::max() const {
        double max = m_data[0];
        for (unsigned long int i = 1; i < m_height * m_width; i++) 
            if (max < m_data[i])
                max = m_data[i];
        return max;
    }

    double matrix::min() const {
        double min = m_data[0];
        for (unsigned long int i = 1; i < m_height * m_width; i++) 
            if (min > m_data[i])
                min = m_data[i];
        return min;
    }

    matrix matrix::get_transpose() const {
        return matrix (*this).to_transpose();
    }

    matrix& matrix::to_transpose() {
        if (m_height == 1UL) {
            m_height = m_width;
            m_width = 1UL;
        } else if (m_width == 1UL) {
            m_width = m_height;
            m_height = 1UL;
        } else {
            double* new_data = new double[m_width * m_height];
            for (unsigned long int i = 0; i < m_height; i++)
                for (unsigned long int j = 0; j < m_width; j++) 
                    new_data[j * m_height + i] = m_data[i * m_width + j];
            delete[] m_data;
            unsigned long int old_height = m_height;
            m_height = m_width;
            m_width = old_height;
            m_data = new_data;
        }
        return *this;
    }

    matrix& matrix::operator+ () {
        return *this;
    }

    matrix& matrix::operator- () {
        for (unsigned long int i = 0; i < m_width; i++)
            m_data[i] = -m_data[i];
        return *this;
    }


    // индексирование
    _row matrix::operator[] (unsigned long int __row) const {
        if (__row < 0)
            throw std::invalid_argument ("Invalid index ");
        if (__row >= m_height) 
            throw std::out_of_range ("Index is out of range ");
        _row line (m_data, m_width);
        for (unsigned long int i = 0; i < m_width; i++)
            line.m_data[i] = m_data[i];
        return line;
    }


    // присваивание
    matrix& matrix::operator= (const matrix& refer) {
         
#ifdef DEBUG
        std::cerr << GCOL     << "    op = [copy matrix] " 
                  << std::setw (3)
                  << id       << " <- " 
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        if (m_width * m_height != refer.m_width * refer.m_height) {
            delete[] m_data;
            m_width = refer.m_width;
            m_height = refer.m_height;
            m_data = new double[m_width * m_height];
        }
        for (unsigned long int i = 0; i < m_width * m_height; i++) 
            m_data[i] = refer.m_data[i];
        return *this;
    }

    matrix& matrix::operator= (matrix&& refer) {

#ifdef DEBUG
        std::cerr << GCOL     << "    op = [move matrix] " 
                  << std::setw (3)
                  << id       << " <- "
                  << refer.id << NCOL << std::endl;
#endif /* DEBUG */

        if (&refer == this)
            return *this;
        delete[] m_data;
        m_data = refer.m_data;
        m_width = refer.m_width;
        m_height = refer.m_height;
        refer.m_width = 0;
        refer.m_height = 0;
        refer.m_data = nullptr;
        return *this;
    }

    matrix& matrix::operator= (double def) {
        for (unsigned long int i = 0; i < m_width * m_height; i++)
            m_data[i] *= def;
        return *this;
    }

    matrix& matrix::operator+= (const matrix& B) {
        if (!is_proport (B))
            throw std::length_error ("Matrix's sizes are different ");
        for (unsigned long int i = 0; i < m_width * m_height; i++)
            m_data[i] += B.m_data[i];
        return *this;
    }

    matrix& matrix::operator-= (const matrix& B) {
        if (!is_proport (B))
            throw std::length_error ("Matrix's sizes are different ");
        for (unsigned long int i = 0; i < m_width * m_height; i++)
            m_data[i] -= B.m_data[i];
        return *this;
    }

    matrix& matrix::operator*= (const matrix& B) {
        if (!is_isomeric (B))
            throw std::length_error ("Matrixs are not isomeric ");
        double* new_data = new double [m_height * B.m_width];
        for (unsigned long int i = 0; i < m_height; i++)
            for (unsigned long int j = 0; j < B.m_width; j++) {
                new_data[i * B.m_width + j] = 0.;
                for (unsigned long int r = 0; r < m_width; r++) 
                   new_data[i * B.m_width + j] += m_data[i * m_width + r] * B.m_data[r * B.m_width + j];
            }
        delete[] m_data;
        m_data = new_data;
        m_width = B.m_width;
        return *this;
    }

    matrix& matrix::operator*= (double B) {
        for (unsigned long int i = 0; i < m_width * m_height; i++)
            m_data[i] *= B;
        return *this;
    }


    // внешние функции
    bool is_proport (const matrix& A, const matrix& B) {
        return (A.m_width == B.m_width) && (A.m_height == B.m_height);
    }

    bool is_isomeric (const matrix& A, const matrix& B) {
        return A.m_width == B.m_height;
    }

    matrix operator+ (const matrix& A, const matrix& B) {
        return matrix (A) += B;
    }

    matrix operator- (const matrix& A, const matrix& B) {
        return matrix (A) -= B;
    }

    matrix operator* (const matrix& A, const matrix& B) {
        return matrix (A) *= B;
    }

    matrix operator* (const matrix& A, double B) {
        return matrix (A) *= B;
    }

    matrix operator* (double A, const matrix& B) {
        return matrix (B) *= A;
    }


    // стейтмент вывода
    std::ostream& operator<< (std::ostream& out, const matrix& M) {
        std::ios state (nullptr);
        state.copyfmt(std::cout);
        state.setf (std::ios_base::showpoint);
        for (unsigned long int i = 0; i < M.m_height; i++) {
            out << std::setw (0) << ((i == 0)?"{{":" {");
            for (unsigned long int j = 0; j < M.m_width; j++) {
                out.copyfmt (state);
                out << M.m_data[i * M.m_width + j] 
                    << std::setw (0)
                    << ((j == M.m_width - 1)? ((i == M.m_height - 1)?"}}":"}\n"): ", ");
            }
        }
        return out;
    }
}


#endif /* MATRIX_CPP */
