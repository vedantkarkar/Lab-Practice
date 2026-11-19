// Author: Vedant Karkar
// Date: 18/11/2026 5:37 PM

// Problem Statement:
// Create a program that searches elements by allowing users to choose between:
// • Linear search/Sentinel search
// • Binary search/Fibonacci search
// Compare time complexities for datasets of varying sizes

#include <iostream>

using namespace std;

const int default_cap = 1000;
const int line_width = 70;

void draw_line(int length = line_width)
{
    for (int i = 0; i < length; i++)
    {
        cout << '-';
    }
    cout << endl;
}

class Array
{
private:
    int *arr;
    int total_size;
    int capacity;

public:
    Array() : total_size(0), capacity(default_cap)
    {
        arr = new int[capacity];
    }

    Array(int n) : total_size(0)
    {
        if (n > 0)
        {
            capacity = n;
        }
        else
        {
            capacity = default_cap;
        }
        arr = new int[capacity];
    }

    ~Array()
    {
        delete[] arr;
    }

    bool empty()
    {
        return total_size == 0;
    }

    bool full()
    {
        return total_size == capacity;
    }

    int size()
    {
        return total_size;
    }

    int cap()
    {
        return capacity;
    }

    bool is_sorted()
    {
        for (int i = 0; i < total_size - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                return false;
            }
        }
        return true;
    }

    int linear_search(int key, int &count)
    {
        count = 0;
        for (int i = 0; i < total_size; i++)
        {
            if (arr[i] == key)
            {
                count = i * 2;
                return i;
            }
        }
        count = total_size * 2;
        return -1;
    }

    int sentinel_search(int key, int &count)
    {
        count = 0;

        // cannot access total_size - 1 indexed element if empty()
        if (empty())
        {
            return -1;
        }

        int last = arr[total_size - 1];
        arr[total_size - 1] = key;

        int i = 0;
        while (arr[i] != key)
        {
            i++;
        }
        count = i;

        // restore the array
        arr[total_size - 1] = last;

        if (i != total_size - 1)
        {
            count++;
            return i;
        }
        else if (last == key)
        {
            count += 2;
            return total_size - 1;
        }
        count += 2;
        return -1;
    }

    int binary_search(int key, int &count)
    {
        count = 0;
        // consider that the array is sorted as checking if it is not is the not the concern of this function
        int low = 0;
        int high = total_size - 1;
        while (high >= low)
        {
            count++; // for while loop check
            int mid = low + (high - low) / 2;

            if (arr[mid] == key)
            {
                count++;
                return mid;
            }
            else if (arr[mid] < key)
            {
                count += 2; // if and else check
                low = mid + 1;
            }
            else
            {
                count += 2;
                high = mid - 1;
            }
        }
        return -1;
    }

    int fibonacci_search(int key, int &count)
    {
        count = 0;
        if (empty())
        {
            return -1;
        }

        int fibm2 = 0;
        int fibm1 = 1;
        int fibm = fibm1 + fibm2;

        while (fibm < total_size)
        {
            count++;
            fibm2 = fibm1;
            fibm1 = fibm;
            fibm = fibm1 + fibm2;
        }

        int offset = -1;

        while (fibm > 1)
        {
            count++;
            int i = (offset + fibm2 < total_size - 1) ? offset + fibm2 : total_size - 1;

            if (arr[i] == key)
            {
                count++;
                return i;
            }
            else if (arr[i] < key)
            {
                count += 2;
                offset = i;
                fibm = fibm1;
                fibm1 = fibm2;
                fibm2 = fibm - fibm1;
            }
            else
            {
                count += 2;
                fibm = fibm2;
                fibm1 = fibm1 - fibm2;
                fibm2 = fibm - fibm1;
            }
        }

        if (fibm1 && offset + 1 < total_size && arr[offset + 1] == key)
        {
            return offset + 1;
        }
        return -1;
    }

    void input(int n)
    {
        if (n <= 0 || n > capacity)
        {
            cerr << "Error: Input size is not valid!\n";
            return;
        }
        total_size = n;
        cout << "Taking input for " << n << " integers: \n";
        for (int i = 0; i < total_size; i++)
        {
            cout << "Index " << i << " : ";
            cin >> arr[i];
        }
        cout << "Input of " << n << " integers stored in array.\n";
    }

    void display()
    {
        cout << "Displaying array of size " << total_size << " integers: \n";
        for (int i = 0; i < total_size; i++)
        {
            cout << "Index " << i << ": " << arr[i] << endl;
        }
    }

    void def_init(int size)
    {
        total_size = size;
        for (int i = 0; i < total_size; i++)
        {
            arr[i] = rand();
        }
        cout << "Total " << total_size << " random elements filled in array\n";
    }

    void init(int size)
    {
        total_size = size;
        for (int i = 0; i < total_size; i++)
        {
            arr[i] = i + 1;
        }
        cout << "Total " << total_size << " sequential elements filled in array\n";
    }
};

class Program
{
private:
    Array a;

public:
    // can add a random init and benchmark all searches
    void menu()
    {
        cout << "Array Search Menu: \n";
        cout << "1. Initialize a new array\n";
        cout << "2. Initialize a sequentially sorted array\n";
        cout << "3. Display Array\n";
        cout << "4. Perform linear search\n";
        cout << "5. Perform Sentinel Search\n";
        cout << "6. Perform Fibonnaci Search\n";
        cout << "7. Perform Binary Search\n";
        cout << "8. Perform Benchmarking\n";
        cout << "9. Exit\n";
    }

    void perform(int ch)
    {
        switch (ch)
        {
        case 1:
        {
            int size;
            while (true)
            {
                cout << "Enter the size of the array between 0 and " << a.cap() << ": \n";
                cin >> size;
                if (size >= 0 && size <= a.cap())
                {
                    break;
                }
                cout << "Enter a valid number\n";
            }
            a.input(size);
            break;
        }

        case 2:
        {
            int size;
            while (true)
            {
                cout << "Enter the size of the array between 0 and " << a.cap() << ": \n";
                cin >> size;
                if (size >= 0 && size <= a.cap())
                {
                    break;
                }
                cout << "Enter a valid number\n";
            }
            a.init(size);
            break;
        }

        case 3:
        {
            a.display();
            break;
        }

        case 4:
        {
            int key, count;
            cout << "Enter the key to find: ";
            cin >> key;
            int found = a.linear_search(key, count);
            cout << "Linear Search Results: \n";
            if (found == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << found << "\n";
                cout << count << " comparisons checked\n";
            }
            break;
        }

        case 5:
        {
            int key, count;
            cout << "Enter the key to find: ";
            cin >> key;
            int found = a.sentinel_search(key, count);
            cout << "Sentinel Search Results: \n";
            if (found == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << found << "\n";
                cout << count << " comparisons checked\n";
            }
            break;
        }

        case 6:
        {
            if (!a.is_sorted())
            {
                cout << "Sorted array is required by fibonacci search.\n";
                break;
            }
            int key, count;
            cout << "Enter the key to find: ";
            cin >> key;
            int found = a.fibonacci_search(key, count);
            cout << "Fibonnaci Search Results: \n";
            if (found == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << found << "\n";
                cout << count << " comparisons checked\n";
            }
            break;
        }

        case 7:
        {
            if (!a.is_sorted())
            {
                cout << "Sorted array is required by Binary search.\n";
                break;
            }
            int key, count;
            cout << "Enter the key to find: ";
            cin >> key;
            int found = a.binary_search(key, count);
            cout << "Binary Search Results: \n";
            if (found == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << found << "\n";
                cout << count << " comparisons checked\n";
            }
            break;
        }

        case 8:
        {
            int key, count;
            cout << "Enter the key to find: ";
            cin >> key;
            int foundl = a.linear_search(key, count);
            cout << "Linear Search Results: \n";
            if (foundl == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << foundl << "\n";
                cout << count << " comparisons checked\n";
            }
            int founds = a.sentinel_search(key, count);
            cout << "Sentinel Search Results: \n";
            if (founds == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << founds << "\n";
                cout << count << " comparisons checked\n";
            }
            if (!a.is_sorted())
            {
                cout << "Sorted array is required by Binary search and fibonacci search.\n";
                break;
            }
            int foundb = a.binary_search(key, count);
            cout << "Binary Search Results: \n";
            if (foundb == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << foundb << "\n";
                cout << count << " comparisons checked\n";
            }
            int foundf = a.fibonacci_search(key, count);
            cout << "Fibonacci Search Results: \n";
            if (foundf == -1)
            {
                cout << "Element not found in the array\n";
                cout << count << " comparisons checked\n";
            }
            else
            {
                cout << "Element found at index " << foundf << "\n";
                cout << count << " comparisons checked\n";
            }
            break;
        }

        case 9:
        {
            cout << "Exiting Program\n";
            break;
        }

        default:
        {
            cout << "Enter a valid input\n";
        }
        }
    }

    void run()
    {
        int choice;
        do
        {
            draw_line();
            menu();
            cout << "Choice: ";
            cin >> choice;
            perform(choice);
        } while (choice != 9);
    }
};

int main()
{
    Program mock;
    mock.run();
    return 0;
}
