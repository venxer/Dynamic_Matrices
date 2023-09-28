#include "Matrix.h"
#include <iostream>

Matrix::Matrix(const Matrix &m)
{
    //copy row and col
    row = m.num_rows();
    col = m.num_cols();
    
    data = new double*[row];
    for(unsigned x = 0; x < row; x++)
    {
        //create row
        data[x] = new double[col];
        for(unsigned y = 0; y < col; y++)
        {
            //allocate data[row][col]
            double num;
            m.get(x, y, num);
            data[x][y] = num;
        }
    }
}
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
Matrix::~Matrix()
{
    clear();
}
int Matrix::num_rows() const
{
    return row;
}
int Matrix::num_cols() const
{
    return col;
}
void Matrix::clear()
{
    if(data == NULL)
    {
        return;
    }
    for(unsigned int x = 0; x < row; x++)
    {
        //delete col
        delete[] data[x];
    }
    //delete row
    delete[] data;
    row = 0;
    col = 0;
}
bool Matrix::get(int aRow, int aCol, double &num) const
{
    if(data == NULL)
    {
        return false;
    }
    //checks neg and not in bound
    if(!(aRow >= 0 && aCol >= 0) || 
       !((int)row > aRow && (int)col > aCol))
       return false;

    num = data[aRow][aCol];
    return true;
}
bool Matrix::set(int aRow, int aCol, double num)
{
    if(data == NULL)
    {
        return false;
    }
    //checks neg and not in bound
    if(!(aRow >= 0 && aCol >= 0) ||
       !((int)row > aRow && (int)col > aCol))
       return false;
    
    data[aRow][aCol] = num; 
    return true;
}

void Matrix::multiply_by_coefficent(double coefficent)
{
    for(unsigned int x = 0; x < row; x++)
    {
        for(unsigned int y = 0; y < col; y++)
        {
            data[x][y] *= coefficent;
        }
    }
}
bool Matrix::swap_row(unsigned int sourceRow, unsigned int targetRow)
{
    //checks neg and not in bound
    if(!(row <= sourceRow && row <= targetRow))
       return false;
    
    //swap rows
    double *temp = data[sourceRow];
    data[sourceRow] = data[targetRow];
    data[targetRow] = temp;
    return true;
}
bool Matrix::add(Matrix &m2)
{
    if(m2.num_rows() == (int)row && m2.num_cols() == (int)col)
    {
        for(unsigned int x = 0; x < row; x++)
        {
            for(unsigned int y = 0; y < col; y++)
            {
                double num;
                m2.get(x, y, num);
                data[x][y] += num;
            }
        }
        return true;
    }
    return false;
}
bool Matrix::subtract(Matrix &m2)
{
    if(m2.num_rows() == (int)row && m2.num_cols() == (int)col)
    {
        for(unsigned int x = 0; x < row; x++)
        {
            for(unsigned int y = 0; y < col; y++)
            {
                double num;
                m2.get(x, y, num);
                data[x][y] = data[x][y] - num;
            }
        }
        return true;
    }
    return false;
}
void Matrix::operator=(const Matrix &m1)
{
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
            double num;
            m1.get(x, y, num);
            data[x][y] = num;
        }
    }
}
bool operator==(const Matrix &m1, const Matrix &m2)
{
    //check if same size
    if(m1.num_rows() == m2.num_rows() && m1.num_cols() == m2.num_cols())
    {
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
double* Matrix::get_row(unsigned int numRow) const
{
    if(row > numRow)
    {
        double* output = new double[col];
        for(unsigned int x = 0; x < col; x++)
        {
            output[x] = data[numRow][x];
        }
        return output;
    }
    return NULL;

}
double* Matrix::get_col(unsigned int numCol) const
{
    if(col > numCol)
    {
        double *output = new double(row);
        for(unsigned int x = 0; x < row; x++)
        {
            output[x] = data[x][col];
        }
        return output;
    }
    return NULL;
}
Matrix* Matrix::quarter()
{
    int qRow = (int)(0.5 + row/2.0);
    int qCol = (int)(0.5 + col/2.0);
    Matrix* output = new Matrix[4];
    for(int x = 0; x < 4; x++)
    {
        //set size for each quarter
        output[x] = Matrix(qRow, qCol, 0.0);
        int rStart = 0;
        int cStart = 0;
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

        for(int r = 0; r < qRow; r++)
        {
            for(int c = 0; c < qCol; c++)
            {
                double value;
                get(r + rStart, c + cStart, value);

                output[x].set(r, c, value);
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