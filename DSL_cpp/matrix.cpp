// input, addition, transpose and display of the matrix

#include <iostream>
using namespace std;
const int capacity = 10;
const int line_width = 75;

void draw_line(int length = line_width)
{
    for (int i = 0; i < length; i++)
    {
        cout << '-';
    }
    cout << endl;
}

class Matrix
{
private:
    int **arr;
    int row;
    int col;

public:
    Matrix(int r, int c) : row(r), col(c)
    {
        arr = new int *[row];
        for (int i = 0; i < row; i++)
        {
            arr[i] = new int[col];
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < row; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }

    // custom copy constructor for Deep copy
    Matrix(const Matrix &other)
    {
        row = other.row;
        col = other.col;

        arr = new int *[row];
        for (int i = 0; i < row; i++)
        {
            arr[i] = new int[col];
            for (int j = 0; j < col; j++)
            {
                arr[i][j] = other.arr[i][j];
            }
        }
    }

    // helper function, swaps values and resources of this with other;
    void swap(Matrix &other) noexcept
    {
        int **temparr = arr;
        arr = other.arr;
        other.arr = temparr;

        int r = row;
        row = other.row;
        other.row = r;

        int c = col;
        col = other.col;
        other.col = c;
    }

    // Performs C = A, where C's previous resources should be destroyed and replaced with a deep copy of A
    Matrix &operator=(const Matrix &other)
    {
        // handling edge case
        if (this == &other)
        {
            return *this;
        }

        // temp is initialized with deep copy of other and holds its own resources
        Matrix temp(other);
        swap(temp);

        return *this;
    }

    Matrix transpose() const
    {
        Matrix temp(col, row);

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                temp.arr[j][i] = arr[i][j];
            }
        }

        return temp;
    }

    Matrix add(const Matrix &other) const
    {
        if (row != other.row || col != other.col)
        {
            throw "Shape of two matrix is different";
        }

        Matrix temp(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                temp.arr[i][j] = arr[i][j] + other.arr[i][j];
            }
        }

        return temp;
    }

    void init()
    {
        cout << "Taking input for " << row << " rows and " << col << " columns: \n";
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cin >> arr[i][j];
            }
        }
        cout << "Input is complete!\n";
    }

    void show() const
    {
        cout << "Displaying matrix of " << row << " rows and " << col << " columns: \n";
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class Program
{
private:
    int total;
    Matrix *matrices[capacity];

public:
    Program() : total(0)
    {
        for (int i = 0; i < capacity; i++)
        {
            matrices[i] = nullptr;
        }
    }

    ~Program()
    {
        for (int i = 0; i < total; i++)
        {
            delete matrices[i];
        }
    }

    void menu()
    {
        cout << "Matrix Calculator: \n";
        cout << "1. Initialize a new matrix\n";
        cout << "2. Display a matrix\n";
        cout << "3. Transpose a matrix\n";
        cout << "4. Add two matrix\n";
        cout << "5. Exit\n";
    }

    void list()
    {
        cout << "Total " << total << " Available matrices: \n";
        for (int i = 0; i < total; i++)
        {
            cout << '\t' << i + 1 << " . Matrix " << char('A' + i) << endl;
        }
    }

    void perform(int ch)
    {
        switch (ch)
        {
            int no, no2;
        case 1:
            if (total == capacity)
            {
                throw "Capacity Reached";
            }
            cout << "\nEnter the dimensions of the matrix: ";
            int r, c;
            while (true)
            {
                cout << "\nEnter number of rows: ";
                cin >> r;
                cout << "\nEnter number of columns: ";
                cin >> c;
                if (r > 0 && c > 0)
                    break;
                cout << "Enter positive numbers\n";
            }
            matrices[total] = new Matrix(r, c);
            matrices[total]->init();
            total++;
            break;

        case 2:
            list();
            if (total <= 0)
                break;
            cout << "Enter the matrix you want to display: ";
            while (true)
            {
                cin >> no;
                if (no > 0 && no <= total)
                    break;
                cout << "Enter a valid number between 1 and " << total << endl;
            }
            matrices[no - 1]->show();
            break;

        case 3:
            if (total == capacity)
            {
                throw "Capacity Reached";
            }
            list();
            if (total <= 0)
                break;
            cout << "Enter the matrix you want to transpose: ";
            while (true)
            {
                cin >> no;
                if (no > 0 && no <= total)
                    break;
                cout << "Enter a valid number between 1 and " << total << endl;
            }
            matrices[total] = new Matrix(matrices[no - 1]->transpose());
            cout << "Transposed matrix saved at " << total + 1 << " position: \n";
            matrices[total]->show();
            total++;
            break;

        case 4:
            if (total == capacity)
            {
                throw "Capacity Reached";
            }
            list();
            if (total <= 0)
                break;
            cout << "Enter the matrix you want to add: ";
            while (true)
            {
                cin >> no;
                if (no > 0 && no <= total)
                    break;
                cout << "Enter a valid number between 1 and " << total << endl;
            }
            cout << "Enter the second matrix you want to add: ";
            while (true)
            {
                cin >> no2;
                if (no2 > 0 && no2 <= total)
                    break;
                cout << "Enter a valid number between 1 and " << total << endl;
            }
            matrices[total] = new Matrix(matrices[no - 1]->add(*matrices[no2 - 1]));
            cout << "Resultant matrix saved at " << total + 1 << " position: \n";
            matrices[total]->show();
            total++;
            break;

        case 5:
            cout << "Exiting the program. Thank you!\n";
            break;

        default:
            cout << "Enter a valid choice between 1 to 5\n";
        }
    }

    void run()
    {
        int choice = 0;
        do
        {
            draw_line();
            menu();
            try
            {
                cout << "Choice: ";
                cin >> choice;
                perform(choice);
            }
            catch (const char *error)
            {
                cerr << "Error: " << error << endl;
            }
        } while (choice != 5);
    }
};

int main()
{
    Program mock;
    mock.run();
    // test cases
    // try
    // {
    //     Matrix A(2, 3);
    //     A.init();

    //     Matrix B = A.transpose();

    //     A.show();
    //     B.show();
    //     Matrix C(A);
    //     Matrix D = A.add(C);

    //     C.show();
    //     D.show();

    //     D = A;
    //     D.show();
    //     A = A;
    //     A.show();

    //     C = A.add(B);
    // }
    // catch (const char *c)
    // {
    //     cerr << "Error: " << c << endl;
    // }

    return 0;
}
