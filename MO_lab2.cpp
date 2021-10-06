﻿#include <iomanip>
#include <iostream>
#include <fstream>

void simplex(double s_matrix[4][4], int key, char variable)
{
    const unsigned int basis_size = 3;
    const unsigned int matrix_length = 4;
    const unsigned int matrix_width = 4;

    double ad_matrix[matrix_length][matrix_width];

    int basis_variables[basis_size] = { 1 , 2, 3 };
    int free_variables[basis_size] = { 4, 5, 6 };
    double min = -1;
    std::cout << std::fixed;
    std::cout << "        s0         ";
    for (int i = 0; i < basis_size; i++)
    {
        std::cout << variable << basis_variables[i] << "          ";
    }
    std::cout << std::endl;
    for (int i = 0; i < matrix_length; ++i)
    {
        if (i <= 2) std::cout << variable << free_variables[i] << "  ";
        else std::cout << "F   ";
        for (int j = 0; j < matrix_width; ++j)
        {
            std::cout << std::setw(8) << std::setprecision(3) << s_matrix[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    bool f = true;
    int perm_col, perm_str;
    bool exist = true;
    while (f && exist)
    {
        perm_str = -1;
        perm_col = -1;

        for (int i = 0; i < matrix_length - 1; ++i)
        {
            if (s_matrix[i][0] < 0)
            {
                perm_str = i;
                break;
            }
        }
        if (perm_str >= 0)
        {
            exist = false;
            for (int i = 1; i < matrix_width; ++i)
            {
                if (s_matrix[perm_str][i] < 0)
                {
                    perm_col = i;
                    exist = true;
                    break;
                }
            }
            if (exist)
            {
                for (int i = 0; i < matrix_length - 1; ++i)
                {
                    if (
                        ((s_matrix[i][0] / s_matrix[i][perm_col]) >= 0) 
                        &&
                        ((min < 0) || (s_matrix[i][0] / s_matrix[i][perm_col] < min))
                       )
                    {
                        min = s_matrix[i][0] / s_matrix[i][perm_col];
                        perm_str = i;
                    }
                }
                for (int i = 0; i < matrix_length; i++)
                {
                    for (int j = 0; j < matrix_width; j++)
                    {
                        if (i != perm_str && j != perm_col)
                        {
                            ad_matrix[i][j] = s_matrix[i][j] - s_matrix[i][perm_col] * s_matrix[perm_str][j] / s_matrix[perm_str][perm_col];
                        }
                        else if (i != perm_str)
                        {
                            ad_matrix[i][j] = -1 * s_matrix[i][j] / s_matrix[perm_str][perm_col];
                        }
                        else if (j != perm_col)
                        {
                            ad_matrix[i][j] = s_matrix[i][j] / s_matrix[perm_str][perm_col];
                        }
                        else
                        {
                            ad_matrix[i][j] = 1 / s_matrix[i][j];
                        }
                        if (abs(ad_matrix[i][j]) <= pow(10, -12)) ad_matrix[i][j] = abs(ad_matrix[i][j]);
                    }
                }
                for (int i = 0; i < matrix_length; ++i)
                    for (int j = 0; j < matrix_width; ++j)
                        s_matrix[i][j] = ad_matrix[i][j];
                std::swap(basis_variables[perm_col - 1], free_variables[perm_str]);
                std::cout << "         s0         ";
                for (int i = 0; i < basis_size; i++)
                {
                    std::cout << variable << basis_variables[i] << "         ";
                }
                std::cout << std::endl;
                for (int i = 0; i < matrix_length; ++i)
                {
                    if (i <= 2) std::cout << variable << free_variables[i] << "  ";
                    else std::cout << "F   ";
                    for (int j = 0; j < matrix_width; ++j)
                    {
                        std::cout << std::setw(8) << std::setprecision(3) << s_matrix[i][j] << "   ";
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
        }
        else f = false;
    }
    if (exist) f = true;
    bool unlim = false;
    while (f && !unlim)
    {
        perm_col = -1;
        min = -1;
        for (int i = 1; i < matrix_width; ++i)
        {
            if (s_matrix[matrix_length - 1][i] > 0)
            {
                perm_col = i;
                break;
            }
        }
        if (perm_col > 0)
        {
            unlim = true;
            for (int i = 0; i < matrix_length - 1; ++i)
                if (s_matrix[i][perm_col] > 0)
                {
                    unlim = false;
                    break;
                }
            if (!unlim)
            {
                for (int i = 0; i < matrix_length - 1; ++i)
                {
                    if (
                        ((s_matrix[i][0] / s_matrix[i][perm_col]) >= 0) 
                        &&
                        ((min < 0) || (s_matrix[i][0] / s_matrix[i][perm_col] < min))
                       )
                    {
                        min = s_matrix[i][0] / s_matrix[i][perm_col];
                        perm_str = i;
                    }
                }
                for (int i = 0; i < matrix_length; i++)
                {
                    for (int j = 0; j < matrix_width; j++)
                    {
                        if (i != perm_str && j != perm_col)
                        {
                            ad_matrix[i][j] = s_matrix[i][j] - s_matrix[i][perm_col] * s_matrix[perm_str][j] / s_matrix[perm_str][perm_col];
                        }
                        else if (i != perm_str)
                        {
                            ad_matrix[i][j] = -1 * s_matrix[i][j] / s_matrix[perm_str][perm_col];
                        }
                        else if (j != perm_col)
                        {
                            ad_matrix[i][j] = s_matrix[i][j] / s_matrix[perm_str][perm_col];
                        }
                        else
                        {
                            ad_matrix[i][j] = 1 / s_matrix[i][j];
                        }
                        if (abs(ad_matrix[i][j]) <= pow(10, -12)) ad_matrix[i][j] = abs(ad_matrix[i][j]);
                    }
                }
                for (int i = 0; i < matrix_length; ++i)
                    for (int j = 0; j < matrix_width; ++j)
                        s_matrix[i][j] = ad_matrix[i][j];
                std::swap(basis_variables[perm_col - 1], free_variables[perm_str]);
                std::cout << "         s0         ";
                for (int i = 0; i < basis_size; i++)
                {
                    std::cout << variable << basis_variables[i] << "         ";
                }
                std::cout << std::endl;
                for (int i = 0; i < matrix_length; ++i)
                {
                    if (i <= 2) std::cout << variable << free_variables[i] << "  ";
                    else std::cout << "F   ";
                    for (int j = 0; j < matrix_width; ++j)
                    {
                        std::cout << std::setw(8) << std::setprecision(3) << s_matrix[i][j] << "   ";
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
        }
        else f = false;
    }
    std::cout << std::endl << "end" << std::endl;
    for (int i = 0; i < basis_size; ++i)
    {
        if (basis_variables[i] <= basis_size)
            std::cout << variable << basis_variables[i] << " = 0" << std::endl;
    }
    for (int i = 0; i < basis_size; ++i)
    {
        if (free_variables[i] <= basis_size)
            std::cout << variable << free_variables[i] << " = " << s_matrix[i][0] << std::endl;
    }
    std::cout << "F  = " << s_matrix[matrix_length - 1][0] * key << std::endl;
}

void dual_method()
{
    const unsigned int basis_size = 3;
    const unsigned int matrix_length = 4;
    const unsigned int matrix_width = 4;
    double s_matrix[matrix_length][matrix_width];
    double d_matrix[matrix_length][matrix_width];
    std::ifstream in("data.txt");
    for (int i = 0; i < matrix_width - 1; ++i)
        in >> s_matrix[matrix_length - 1][i + 1];

    for (int i = 0; i < matrix_length - 1; ++i)
        for (int j = 0; j < matrix_width - 1; ++j)
        {
            in >> s_matrix[i][j + 1];
        }
    for (int i = 0; i < matrix_length - 1; ++i)
        in >> s_matrix[i][0];
    s_matrix[matrix_length - 1][0] = 0;
    in.close();
    for (int i = 0; i < matrix_length; i++)
        for (int j = 1; j < matrix_width; j++)
        {
            d_matrix[j - 1][i + 1] = -1 * s_matrix[i][j];
            if (d_matrix[j - 1][i + 1] == 0) d_matrix[j - 1][i + 1] = abs(d_matrix[j - 1][i + 1]);
        }
    for (int i = 0; i < matrix_length - 1; i++)
    {
        d_matrix[i][0] = -1 * s_matrix[matrix_length - 1][i + 1];
        if (d_matrix[i][0] == 0) d_matrix[i][0] = abs(d_matrix[i][0]);
    }
    for (int i = 0; i < matrix_width - 1; i++)
    {
        d_matrix[matrix_length - 1][i + 1] = -1 * s_matrix[i][0];
        if (d_matrix[matrix_length - 1][i + 1] == 0) d_matrix[matrix_length - 1][i + 1] = abs(d_matrix[matrix_length - 1][i + 1]);
    }
    d_matrix[matrix_length - 1][0] = 0;

    std::cout << "\t\tDirect task" << std::endl << std::endl;
    simplex(s_matrix, -1, 'x');
    std::cout << std::endl << "\t\tDual task" << std::endl << std::endl;
    simplex(d_matrix, 1, 'y');
}

int main()
{
    dual_method();
    return 0;
}
