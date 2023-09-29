#include "Matrix.h"
#include <iostream>

//copy constuctor
Matrix::Matrix(const Matrix &m)
{
    //copy row and col
    row = m.row;
    col = m.col;
    
    data = new double*[row];
    for(unsigned x = 0; x < row; x++)
    {
        //create row
        data[x] = new double[col];
        for(unsigned y = 0; y < col; y++)
        {
            //allocate data[row][col]
            data[x][y] = m.data[x][y];
        }
    }
}
//default constuctor
Matrix::Matrix(unsigned int aRow, unsigned int aCol, double aFill)
{
    row = aRow;
    col = aCol;
    fill = aFill;

    data = new double*[row];
    for(unsigned int x = 0; x < row; x++)
    {
        //create row
        data[x] = new double[col];
        for(unsigned int y = 0; y < col; y++)
        {
            //allocate data[row][col]
            data[x][y] = fill;
        }
    }
}
//destuctor
Matrix::~Matrix()
{
    clear();
}
void Matrix::clear()
{
    for(unsigned int x = 0; x < row; x++)
    {
        //delete col
        delete[] data[x];
    }
    //delete row
    delete[] data;
    //reset data, row, col
    data = NULL;
    row = 0;
    col = 0;
}
int Matrix::num_rows() const
{
    return row;
}
int Matrix::num_cols() const
{
    return col;
}
bool Matrix::get(int aRow, int aCol, double &num) const
{
    //checks in bound
    if(!((int)row > aRow && (int)col > aCol))
       return false;

    num = data[aRow][aCol];
    return true;
}
bool Matrix::set(const int aRow, const int aCol, const double num)
{
    //checks in bound
    if(!((int)row > aRow && (int)col > aCol))
       return false;
    
    data[aRow][aCol] = num; 
    return true;
}
double* Matrix::get_row(unsigned int numRow) const
{
    //check bound of input
    if(row > numRow)
    {
        //creates a pointer of doubles length col to store data from row
        double* output = new double[col];
        for(unsigned int x = 0; x < col; x++)
        {
            //set data of each col from row into output
            output[x] = data[numRow][x];
        }
        return output;
    }
    return NULL;

}
double* Matrix::get_col(unsigned int numCol) const
{
    //check bound of input
    if(col > numCol)
    {
        //creates a pointer of doubles length row to store data from col
        double *output = new double(row);
        for(unsigned int x = 0; x < row; x++)
        {
            //set data of each row from col into output
            output[x] = data[x][col];
        }
        return output;
    }
    return NULL;
}
bool Matrix::swap_row(unsigned int sourceRow, unsigned int targetRow)
{

    //checks in bound
    if(!(row > sourceRow && row > targetRow))
       return false;
    
    //swap rows
    double *temp = data[sourceRow];
    data[sourceRow] = data[targetRow];
    data[targetRow] = temp;
    return true;
}
void Matrix::multiply_by_coefficent(double coefficent)
{
    //loops through pointer pointer to multiply each element
    for(unsigned int x = 0; x < row; x++)
    {
        for(unsigned int y = 0; y < col; y++)
        {
            data[x][y] *= coefficent;
        }
    }
}
bool Matrix::add(Matrix &m2)
{
    //check bounds of array 
    if(m2.num_rows() == (int)row && m2.num_cols() == (int)col)
    {
        //loops through pointer pointer to add to each element
        for(unsigned int x = 0; x < row; x++)
        {
            for(unsigned int y = 0; y < col; y++)
            {
                data[x][y] += m2.data[x][y];
            }
        }
        return true;
    }
    return false;
}
bool Matrix::subtract(Matrix &m2)
{
    //check bounds of array 
    if(m2.num_rows() == (int)row && m2.num_cols() == (int)col)
    {
        //loops through pointer pointer to subtract from each element
        for(unsigned int x = 0; x < row; x++)
        {
            for(unsigned int y = 0; y < col; y++)
            {
                data[x][y] -= m2.data[x][y];
            }
        }
        return true;
    }
    return false;
}
Matrix* Matrix::quarter()
{
    //creates size of each quarter
    int qRow = (int)(0.5 + row/2.0);
    int qCol = (int)(0.5 + col/2.0);
    Matrix* output = new Matrix[4];
    for(int x = 0; x < 4; x++)
    {
        //set size for each quarter
        output[x] = Matrix(qRow, qCol, 0.0);
        int rStart = 0;
        int cStart = 0;
        //sets the start location of row and col for each iteration
        if(x == 0)
        {
            rStart = 0;
            cStart = 0;
        }
        if(x == 1)
        {
            rStart = 0;
            cStart = qCol;
            if(col % 2 != 0) cStart = qCol - 1;

        }
        if(x == 2)
        {
            rStart = qRow;
            if(row % 2 != 0) rStart = qRow - 1;
            cStart = 0;
        }
        if(x == 3)
        {
            rStart = qRow;
            if(row % 2 != 0) rStart = qRow - 1;
            cStart = qCol;
            if(col % 2 != 0) cStart = qCol - 1;
        }

        //loops through each quarter
        for(int r = 0; r < qRow; r++)
        {
            for(int c = 0; c < qCol; c++)
            {
                output[x].set(r, c, data[r + rStart][c + cStart]);
            }
        }
    }
    return output;
}
void Matrix::transpose()
{
    //saves length row before transpose
    int oldRow = row;
    //swap size of row and col;
    int temp = row;
    row = col;
    col = temp;
    //creates new double pointer with size of transposed data
    double **output = new double*[row];
    for(unsigned int x = 0; x < row; x++)
    {
        output[x] = new double[col];
        for(unsigned int y = 0; y < col; y++)
        {
            //tranpose data 
            output[x][y] = data[y][x];
        }
    }
    //clear memory in data
    for(int y = 0; y < oldRow; y++)
    {
        delete[] data[y];
    }
    delete[] data;
    //set data as output which has the transposed data
    data = output;
}
void Matrix::operator=(const Matrix &m1)
{
    //clears and sets size
    clear();
    row = m1.num_rows();
    col = m1.num_cols();
    
    data = new double*[row];
    for(unsigned int x = 0; x < row; x++)
    {
        //create row
        data[x] = new double[col];
        for(unsigned int y = 0; y < col; y++)
        {
            //allocate data[row][col]
            data[x][y] = m1.data[x][y];
        }
    }
}
bool operator==(const Matrix &m1, const Matrix &m2)
{
    //check if same size
    if(m1.num_rows() == m2.num_rows() && m1.num_cols() == m2.num_cols())
    {
        //loops though each element to check for equavilency
        for(int x = 0; x < m1.num_rows(); x++)
        {
            for(int y = 0; y < m1.num_cols(); y++)
            {
                double value1;
                double value2;
                m1.get(x, y, value1);
                m2.get(x, y, value2);

                //checks if m1 value = m2 value
                if(value1 != value2)
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
bool operator!=(const Matrix &m1, const Matrix &m2)
{
    return !(m1 == m2);
}
std::ostream &operator<<(std::ostream &out_str, const Matrix &m)
{
    //loop through matrix and prints in format
    out_str << "\n" << m.num_rows() << " x " << m.num_cols() <<" matrix:\n" << "[ ";
    for(int x = 0; x < m.num_rows(); x++)
    {
        if(x != 0) out_str << "  ";
        for(int y = 0; y < m.num_cols(); y++)
        {
            double num = 0;
            m.get(x, y, num);
            out_str << num << " ";
        }
        if(x != m.num_rows() - 1) out_str << "\n";
    }
    out_str << "]" << std::endl;
    return out_str;
}