// Build a Password Manager with Collision Handling: Create a hash table
// storing (website, password) pairs using Linear Probing with replacement and
// without replacement. Compare collision rates for different hash functions.

// 1. insert
// 2. Search
// 3. display
// 4. compare

#include <iostream>

using namespace std;

const int line_width = 75;

void draw_line(int length = line_width)
{
    for (int i = 0; i < length; i++)
    {
        cout << '-';
    }
    cout << endl;
}

struct Entry
{
    string key;
    string value;
    bool occupied;

    Entry() : key("NA"), value("NA"), occupied(false) {}
};

enum HashMethod
{
    ASCII,
    WeightedASCII
};

class HashTable
{
private:
    // data members for determining capacity and size of both tables
    int capacity;
    int size_woR;
    int size_wR;

    // Table represented as array of entries (key, value) pairs
    Entry *tableWR;
    Entry *tableWOR;

    // Defines the hash function from the available choices by enum HashMethod
    HashMethod method;

    int collisions1;
    int collisions2;

public:
    HashTable(int cap, HashMethod hash_function) : capacity(cap), method(hash_function),
                                                   size_woR(0), size_wR(0), collisions1(0), collisions2(0)
    {
        tableWOR = new Entry[capacity];
        tableWR = new Entry[capacity];
    }

    ~HashTable()
    {
        delete[] tableWOR;
        delete[] tableWR;
    }

    // keeping a same full function as i will be allowing insertion in both table simultaneously
    bool fullWOR() const
    {
        return size_woR == capacity;
    }

    bool fullWR() const
    {
        return size_wR == capacity;
    }

    int hash(string key)
    {
        int h = 0;
        if (method == ASCII)
        {
            for (int i = 0; i < key.length(); i++)
            {
                h += key[i];
            }
            h = h % capacity;
        }
        else if (method == WeightedASCII)
        {
            for (int i = 0; i < key.length(); i++)
            {
                h += (i + 1) * key[i];
            }
            h = h % capacity;
        }
        return h;
    }

    // return -1 if not found and index if found for a table
    int search(const Entry *table, string key, int &cost)
    {
        int index = hash(key);
        cost = 1;
        if (table[index].occupied && table[index].key == key)
        {
            return index;
        }

        for (int probe = 1; probe < capacity; probe++)
        {
            index = (index + 1) % capacity;
            cost++;
            if (!table[index].occupied)
            {
                return -1;
            }
            if (table[index].key == key)
            {
                return index;
            }
        }
        return -1;
    }

    int searchWOR(string key, int &cost)
    {
        return search(tableWOR, key, cost);
    }

    int searchWR(string key, int &cost)
    {
        return search(tableWR, key, cost);
    }

    // simpler helper for contains that returns true or false
    bool contains(const Entry *table, string key)
    {
        int cost;
        return search(table, key, cost) != -1;
    }

    bool insertWOR(string key, string value, int &collision)
    {
        collision = 0;
        if (fullWOR())
        {
            cout << "Table is full, insert is not possible!\n";
            return false;
        }
        if (contains(tableWOR, key))
        {
            cout << "Key already present in the (without replacement) table!\n";
            return false;
        }

        int index = hash(key);
        if (tableWOR[index].occupied)
        {
            collision = 1;
            for (int probe = 1; probe < capacity; probe++)
            {
                index = (index + 1) % capacity;
                if (!tableWOR[index].occupied)
                {
                    tableWOR[index].key = key;
                    tableWOR[index].value = value;
                    tableWOR[index].occupied = true;
                    size_woR++;
                    return true;
                }
            }
        }
        else
        {
            tableWOR[index].key = key;
            tableWOR[index].value = value;
            tableWOR[index].occupied = true;
            size_woR++;
            return true;
        }
        return false;
    }

    bool insertWR(string key, string value, int &collision)
    {
        collision = 0;
        if (fullWR())
        {
            cout << "Table is full, insert is not possible!\n";
            return false;
        }
        if (contains(tableWR, key))
        {
            cout << "Key already present in the (with replacement) table!\n";
            return false;
        }

        int index = hash(key);
        if (tableWR[index].occupied)
        {
            collision = 1;
            int existing_h = hash(tableWR[index].key);
            if (existing_h == index)
            {
                for (int probe = 1; probe < capacity; probe++)
                {
                    index = (index + 1) % capacity;
                    if (!tableWR[index].occupied)
                    {
                        tableWR[index].key = key;
                        tableWR[index].value = value;
                        tableWR[index].occupied = true;
                        size_wR++;
                        return true;
                    }
                }
            }
            else
            {
                string existing_key = tableWR[index].key;
                string existing_value = tableWR[index].value;

                tableWR[index].key = key;
                tableWR[index].value = value;
                tableWR[index].occupied = true;

                for (int probe = 1; probe < capacity; probe++)
                {
                    index = (index + 1) % capacity;
                    if (!tableWR[index].occupied)
                    {
                        tableWR[index].key = existing_key;
                        tableWR[index].value = existing_value;
                        tableWR[index].occupied = true;
                        size_wR++;
                        return true;
                    }
                }
            }
        }
        else
        {
            tableWR[index].key = key;
            tableWR[index].value = value;
            tableWR[index].occupied = true;
            size_wR++;
            return true;
        }
        return false;
    }

    // the public function to insert in both the tables simultaneously
    void insert(string key, string value)
    {
        int collision1, collision2;
        bool success = insertWOR(key, value, collision1);
        if (success)
        {
            collisions1 += collision1;
            cout << "(" << key << " -> " << value << ") inserted successfully in table (without replacement)\n";
            cout << "Collisions = " << collision1 << endl;
        }
        else
        {
            cout << "Insertion failed in table (without replacement)\n";
        }
        success = insertWR(key, value, collision2);
        if (success)
        {
            collisions2 += collision2;
            cout << "(" << key << " -> " << value << ") inserted successfully in table (with replacement)\n";
            cout << "Collisions = " << collision2 << endl;
        }
        else
        {
            cout << "Insertion failed in table (with replacement)\n";
        }
    }

    Entry getWOR(int index)
    {
        if (index < 0 || index >= capacity)
        {
            cerr << "index not valid!\n";
            return Entry();
        }
        return tableWOR[index];
    }

    void display()
    {
        cout << "Table maintaining linear probing without replacement: ";
        cout << "Size of HashTable = " << size_woR << endl;
        cout << "Total capacity of HashTable = " << capacity << endl;
        cout << "Load factor = " << (float)size_woR / capacity << endl;
        draw_line();
        cout << "INDEX\t|\tKEY\t|\tVALUE\t|\tHOME ADDRESS |\n";
        for (int i = 0; i < capacity; i++)
        {
            if (tableWOR[i].occupied)
            {
                cout << i << ". " << tableWOR[i].key << " -> " << tableWOR[i].value << " : hash = " << hash(tableWOR[i].key) << endl;
            }
            else
            {
                cout << i << ". \033[31mEMPTY\033[0m\n";
            }
        }
        draw_line();
        cout << "Table maintaining linear probing with replacement: ";
        cout << "Size of HashTable = " << size_wR << endl;
        cout << "Total capacity of HashTable = " << capacity << endl;
        cout << "Load factor = " << (float)size_wR / capacity << endl;
        draw_line();
        cout << "INDEX\t|\tKEY\t|\tVALUE\t|\tHOME ADDRESS |\n";
        for (int i = 0; i < capacity; i++)
        {
            if (tableWR[i].occupied)
            {
                cout << i << ". " << tableWR[i].key << " -> " << tableWR[i].value << " : hash = " << hash(tableWR[i].key) << endl;
            }
            else
            {
                cout << i << ". \033[31mEMPTY\033[0m\n";
            }
        }
        draw_line();
    }

    void compare()
    {
        cout << "Analysing table maintaining linear probing without replacement: \n";
        if (method == ASCII)
        {
            cout << "Hash function used : Sum of ASCII Value, hash += (ASCII(i))\n";
        }
        else if (method == WeightedASCII)
        {
            cout << "Hash function used : Weighted Sum of ASCII Value, hash += (i+1)*(ASCII(i))\n";
        }
        int total_cost = 0;
        cout << "Total elements present in HashTable: " << size_woR << endl;
        cout << "Load factor = " << (float)size_woR / capacity << endl;
        if (size_woR != 0)
        {
            for (int i = 0; i < capacity; i++)
            {
                if (tableWOR[i].occupied)
                {
                    int cost;
                    search(tableWOR, tableWOR[i].key, cost);
                    total_cost += cost;
                }
            }
            cout << "Total search cost for all the elements = " << total_cost << endl;
            cout << "Average search cost per element = " << (float)total_cost / size_woR << endl;
            cout << "Total Collisions while insertion of all keys = " << collisions1 << endl;
        }
        draw_line();
        cout << "Analysing table maintaining linear probing with replacement: \n";
        if (method == ASCII)
        {
            cout << "Hash function used : Sum of ASCII Value, hash += (ASCII(i))\n";
        }
        else if (method == WeightedASCII)
        {
            cout << "Hash function used : Weighted Sum of ASCII Value, hash += (i+1)*(ASCII(i))\n";
        }
        cout << "Total elements present in HashTable: " << size_wR << endl;
        cout << "Load factor = " << (float)size_wR / capacity << endl;
        if (size_wR != 0)
        {
            total_cost = 0;
            for (int i = 0; i < capacity; i++)
            {
                if (tableWR[i].occupied)
                {
                    int cost;
                    search(tableWR, tableWR[i].key, cost);
                    total_cost += cost;
                }
            }
            cout << "Total search cost for all the elements = " << total_cost << endl;
            cout << "Average search cost per element = " << (float)total_cost / size_wR << endl;
            cout << "Total Collisions while insertion of all keys = " << collisions2 << endl;
        }
    }
};

// just for seperating the output of different sections of the program
string bold(string str)
{
    return "\033[1m" + str + "\033[0m";
}

class Program
{
private:
    HashTable table1;
    HashTable table2;

public:
    Program(int capacity) : table1(capacity, ASCII), table2(capacity, WeightedASCII) {}

    void menu()
    {
        cout << "\033[33mProgram Menu: \033[0m\n";
        cout << "1. Insert a website, password pair\n";
        cout << "2. Search a website for password\n";
        cout << "3. Display table\n";
        cout << "4. Compare between tables\n";
        cout << "5. Exit program\n";
    }

    void perform(int choice)
    {
        switch (choice)
        {
        case 1:
        {
            string key, value;
            cout << "Enter the website: \n";
            getline(cin, key);
            cout << "Enter the password: \n";
            getline(cin, value);
            table1.insert(key, value);
            table2.insert(key, value);
            break;
        }

        case 2:
        {
            string key;
            int cost;
            cout << "Enter a key to search: \n";
            getline(cin, key);
            int i = table1.searchWOR(key, cost);
            if (i == -1)
            {
                cout << "Website not present in the hash table\n";
            }
            else
            {
                cout << "Website: " << table1.getWOR(i).key << endl;
                cout << "Password: " << table1.getWOR(i).value << endl;
            }
            break;
        }

        case 3:
        {
            cout << bold("Display for ASCII addition hash: ") << endl;
            table1.display();
            cout << "\n"
                 << bold("Display for Weighted ASCII addition hash: ") << endl;
            table2.display();
            break;
        }

        case 4:
        {
            draw_line();
            cout << bold("Comparison for ASCII addition hash: ") << endl;
            table1.compare();
            draw_line();
            cout << "\n"
                 << bold("Comparison for Weighted ASCII addition hash: ") << endl;
            table2.compare();
            break;
        }

        case 5:
        {
            cout << "Exiting the program!\n";
            break;
        }

        default:
        {
            cout << "Enter a valid choice!\n";
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
            cin.ignore();
            perform(choice);
        } while (choice != 5);
    }
};

int main()
{
    Program PasswordHandler(5);
    PasswordHandler.run();

    return 0;
}
