#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix
{
    private:
        unsigned int row;
        unsigned int col;
        double **data;
        double fill;

    public:
        Matrix(const Matrix &m);
        Matrix(unsigned int row = 0, unsigned int col = 0, double fill = 0.0);
        ~Matrix();

        int num_rows() const; //get row
        int num_cols() const; //get col
        void clear(); //clear

        bool get(int row, int col, double &num) const;
        bool set(int row, int col, double num);
        
        void multiply_by_coefficent(double coefficent);
        bool swap_row(unsigned int sourceRow, unsigned int targetRow);
        void transpose();

        bool add(Matrix &m2); //return true if dimensions match
        bool subtract(Matrix &m2); //return true if dimension match
        
        double* get_row(unsigned int numRow) const;
        double* get_col(unsigned int numCol) const;

        Matrix* quarter();
};

bool operator==(const Matrix &m1, const Matrix &m2);
bool operator!=(const Matrix &m1, const Matrix &m2);
std::ostream &operator<<(std::ostream &out_str, const Matrix &m);

#endif