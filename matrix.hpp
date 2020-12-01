#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <iostream>
#include <initializer_list>


namespace linear {
    class vector;

    class matrix { 
        private:
            static long unsigned int glob_id;

        protected:
            double* m_data;
            long unsigned int m_width;
            long unsigned int m_height;

        public:
            const long unsigned int id;
            explicit matrix (long unsigned int size = 1); // квадратная матрица
            explicit matrix (long unsigned int size, double def); // квадратная матрица со стандартным
            explicit matrix (long unsigned int width, long unsigned int height); // прямоугольная матрица
            explicit matrix (long unsigned int width, long unsigned int height, double def); // прямоугольная матрица со стандартным
            matrix (const matrix&); // копирование
            matrix (matrix&&);  // перемещение
            matrix (const std::initializer_list<std::initializer_list<double>> &list);
            ~matrix();

            // вспомогательные 
            long unsigned int get_width() const;
            long unsigned int get_height() const;
            bool is_isomeric (const matrix&) const; // согласованность
            bool is_proport (const matrix&) const;  // соразмерность
            double max() const;
            double min() const;
            matrix get_transpose() const;
            matrix& to_transpose();
            matrix operator+ () const;
            matrix operator- () const;

            // индексирование
            vector& operator[] (long unsigned int row);
            vector operator[] (long unsigned int row) const;

            // присваивание
            matrix& operator= (const matrix&);
            matrix& operator= (matrix&&);
            matrix& operator= (double);
            matrix& operator+= (const matrix&);
            matrix& operator-= (const matrix&);
            matrix& operator*= (const matrix&);

            matrix& operator*= (double);

            // внешние функции
            friend bool is_proport (const matrix&, const matrix&);
            friend bool is_isomeric (const matrix&, const matrix&);
            friend matrix operator+ (const matrix&, const matrix&);
            friend matrix operator- (const matrix&, const matrix&);
            friend matrix operator* (const matrix&, const matrix&);
            friend matrix operator* (const matrix&, double);
            friend matrix operator* (double, const matrix&);

            // стейтмент вывода
            friend std::ostream& operator<< (std::ostream&, const matrix&);
    };
}

#endif /* MATRIX_HPP */
