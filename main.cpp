#include "matrix.hpp"
#include "vector.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>


void sep() {
    std::cout << " - - - - - - - - - - - - - - - - - - - " << std::endl;
}

using namespace linear;

int main() {
    try {
        matrix m1 (1, 2.);
        vector v1 (1, 2.);

        matrix m21 = {{1, 2}, {3, 4}};
        matrix m22 = {{5, 6}, {7, 8}};

        matrix m35 = {{5, 6, 7, 8, 9}, 
                      {9, 8, 7, 6, 5},
                      {1, 2, 3, 4, 5}};

        matrix m51 = {{1},
                      {2},
                      {5},
                      {6},
                      {8}};

        matrix m5 = {{1, 2, 3, 4, 5}};

        vector v5  = {1, 1, 2, 3, 5};
        vector v3  = {5, 6, 7};

        sep();
        std::cout << std::setprecision(4);
        std::cout << std::setw (7) 
                  << m35
                  << std::endl;
        std::cout << std::setw (8) 
                  << std::setfill ('>') 
                  << v3
                  << std::endl
                  << std::setfill (' ');

        sep();
        std::cout << m1 * m1 << std::endl;

        sep();
        std::cout << m21 * m21 << std::endl;

        sep();
        std::cout << v3 * m35 << std::endl;

        sep();
        std::cout << m51 * v5 << std::endl;

        sep();
        std::cout << v1 * v1 << std::endl;

        sep();
        std::cout << v5 * 6 << std::endl;
        std::cout << m5 * 6 << std::endl;
        std::cout << 6 * v5 << std::endl;
        std::cout << 6 * m5 << std::endl;

        sep();
        std::cout << v5 + v5 << std::endl;

        sep();
        std::cout << m5 + v5 << std::endl;

        sep();
        std::cout << v5 + m5 << std::endl;

        sep();
        std::cout << m5 + m5 << std::endl;

        sep();
        std::cout << v5.to_normalize () << std::endl;
        std::cout << v5[2] << std::endl;
        v5[2] = 5;

        sep();
        std::cout << -v5 << std::endl;
        std::cout << v5 << std::endl;

        sep();
        std::cout << m35 << std::endl;
        std::cout << m35.to_transpose() << std::endl;
        std::cout << m35.get_transpose() << std::endl;

        sep();
        v3 = {5, 5, 0};
        vector v31 = {0, 1, 1};

        sep();
        std::cout << vect_mul (v3, v31) << std::endl;

        sep();
        std::cout << scal_mul (v3, v31) << std::endl;
            
        sep();
        std::cout << cos (v3, v31) << std::endl;

        sep();
        std::cout << sin (v3, v31) << std::endl;

        sep();
        std::cout << angle (v3, v31) << std::endl;

        sep();
    }
    catch (std::exception &exception) {
        std::cerr << "Standard exception: \x1B[1;31m" << exception.what() << "\x1B[0m" << std::endl;
    } catch (...) {
		std::cerr << "\x1B[1;31m" << "Undetermined exception" << "\x1B[31m" << std::endl;
    }
    return 0;
}

