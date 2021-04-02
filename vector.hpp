#ifndef VECTOR_HPP
#define VECTOR_HPP


#include "matrix.hpp"
#include <iostream>
#include <initializer_list>


namespace linear {
    class vector: public matrix {
        // внешние функции
        friend vector operator+ (const vector&, const vector&);
        friend vector operator+ (const vector&, const matrix&);
        friend vector operator- (const vector&, const matrix&);
        friend vector operator- (const vector&, const vector&);
        friend vector operator* (const vector&, double); 
        friend vector operator* (double, const vector&); 
        friend vector operator* (const vector&, const matrix&);
        friend vector vect_mul (const vector&, const vector&); // векторное произведение
        friend double scal_mul (const vector&, const vector&); // скалярное произведение

        // стейтмент вывода
        friend std::ostream& operator<< (std::ostream&, const vector&);

        public:
            explicit vector (long unsigned int width = 1);
            explicit vector (long unsigned int width, double def);
            vector (const _row&);
            vector (const vector&); // копирование
            vector (vector&&); // перемещение
            vector (const std::initializer_list<double> &list);
            
            // вспомогательные
            double abs() const;
            vector get_normalize() const;
            vector& to_normalize();
            vector get_transpose() const;
            vector& to_transpose();
            vector& operator+ ();
            vector& operator- ();

            // индексирование
            double& operator[] (long unsigned int index);
            double operator[] (long unsigned int index) const;

            // присваивание
            vector& operator= (const vector&); // оператор копирования
            vector& operator= (vector&&); // оператор перемещения
            vector& operator= (double);
            vector& operator+= (const vector&);
            vector& operator+= (const matrix&);
            vector& operator-= (const vector&);
            vector& operator-= (const matrix&);
            vector& operator*= (const matrix&);

            vector& operator*= (double); // произведение со скаляром
    };

    double cos (const vector&, const vector&);
    double sin (const vector&, const vector&);
    double angle (const vector&, const vector&);
}


#endif /* VECTOR_HPP */
