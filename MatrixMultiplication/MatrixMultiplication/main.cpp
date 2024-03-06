#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#define ROWS 500
#define COLS 500

class Matrix
{
public:
    std::vector<std::vector<int>> matrix;
    int rows;
    int cols;
	Matrix(std::string filename)
	{
        this->matrix = std::vector<std::vector<int>>(ROWS, std::vector<int>(COLS));
        std::ifstream f;
        f.open(filename);

        for (unsigned i = 0; i < ROWS; ++i) {
            for (unsigned j = 0; j < COLS; ++j) {
                f >> this->matrix[i][j];
            }
        }

        f.close();
        this->cols = COLS;
        this->rows = ROWS;
	}
    Matrix(int rows, int cols)
    {
        this->matrix = std::vector<std::vector<int>>(rows, std::vector<int>(cols));
        this->rows = rows;
        this->cols = cols;
    }
    void print()
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                std::cout << this->matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

void multiplication(Matrix a, Matrix b, Matrix r, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            for (int k = 0; k < a.rows; k++)
            {
                r.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }
}

int main()
{
    Matrix a = Matrix("matrix.txt");
    Matrix b = Matrix("matrix.txt");
    Matrix c = Matrix(ROWS, COLS);
    

    std::chrono::duration<double> duration;

    auto start = std::chrono::high_resolution_clock::now();
    multiplication(a, b, c, 0, ROWS);
    auto end = std::chrono::high_resolution_clock::now();

    duration = end - start;
    std::cout << duration.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    std::thread first(multiplication, std::ref(a), std::ref(b), std::ref(c), 0, ROWS/2);
    std::thread second(multiplication, std::ref(a), std::ref(b), std::ref(c), ROWS/2, ROWS);

    first.join();
    second.join();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << duration.count() << " seconds\n";
	return 0;
}