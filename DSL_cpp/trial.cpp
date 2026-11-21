#include<iostream>
using namespace std;

class HashTable
{
    public:

    string website[10], password[10];
    int n, collision;

    HashTable()
    {
        n=0;
        collision=0;

        for(int i=0;i<10;i++)
        {
            website[i]="";
            password[i]="";
        }
    }

    // Hash Function
    int Hash_Function(string key,int type)
    {
        int sum=0;

        for(int i=0;i<key.length();i++)
        {
            if(type==1)
                sum=sum+key[i];
            else
                sum=sum+(i+1)*key[i];
        }

        return sum%10;
    }

    // Get Website and Password
    void getData()
    {
        cout<<"Enter no. of Websites (maximum 10):";
        cin>>n;

        if(n<1 || n>10)
        {
            cout<<"Invalid number of Websites"<<endl;
            n=0;
            return;
        }

        for(int i=0;i<n;i++)
        {
            cout<<"Enter Website and Password:";
            cin>>website[i]>>password[i];
        }
    }

    // Clear Hash Table
    void Clear()
    {
        for(int i=0;i<10;i++)
        {
            website[i]="";
            password[i]="";
        }

        collision=0;
    }

    // Without Replacement
    void Insert_Without_Replacement(int type)
    {
        string w[10],p[10];

        for(int i=0;i<n;i++)
        {
            w[i]=website[i];
            p[i]=password[i];
        }

        Clear();

        for(int i=0;i<n;i++)
        {
            int index=Hash_Function(w[i],type);

            while(website[index]!="")
            {
                collision++;
                index=(index+1)%10;
            }

            website[index]=w[i];
            password[index]=p[i];
        }

        cout<<"Insertion Without Replacement Completed"<<endl;
    }

    // With Replacement
    void Insert_With_Replacement(int type)
    {
        string w[10],p[10];

        for(int i=0;i<n;i++)
        {
            w[i]=website[i];
            p[i]=password[i];
        }

        Clear();

        for(int i=0;i<n;i++)
        {
            int index=Hash_Function(w[i],type);

            if(website[index]=="")
            {
                website[index]=w[i];
                password[index]=p[i];
            }
            else
            {
                collision++;

                int oldIndex=Hash_Function(website[index],type);

                if(oldIndex!=index)
                {
                    string tempW=website[index];
                    string tempP=password[index];

                    website[index]=w[i];
                    password[index]=p[i];

                    int j=(index+1)%10;

                    while(website[j]!="")
                    {
                        collision++;
                        j=(j+1)%10;
                    }

                    website[j]=tempW;
                    password[j]=tempP;
                }
                else
                {
                    int j=(index+1)%10;

                    while(website[j]!="")
                    {
                        collision++;
                        j=(j+1)%10;
                    }

                    website[j]=w[i];
                    password[j]=p[i];
                }
            }
        }

        cout<<"Insertion With Replacement Completed"<<endl;
    }

    // Display Hash Table
    void Display()
    {
        cout<<"Index"<<'\t'<<"Website"<<'\t'<<"Password"<<endl;

        for(int i=0;i<10;i++)
        {
            cout<<i<<'\t'<<website[i]<<'\t'<<password[i]<<endl;
        }

        cout<<"Total Collisions:"<<collision<<endl;
    }
};

int main()
{
    HashTable h;
    int choice;

    h.getData();

    if(h.n==0)
        return 0;

    do
    {
        cout<<endl<<"1. Without Replacement Hash 1"<<endl;
        cout<<"2. With Replacement Hash 1"<<endl;
        cout<<"3. Without Replacement Hash 2"<<endl;
        cout<<"4. With Replacement Hash 2"<<endl;
        cout<<"5. Display Hash Table"<<endl;
        cout<<"6. Exit"<<endl;

        cout<<"Enter Choice:";
        cin>>choice;

        switch(choice)
        {
            case 1:
                h.Insert_Without_Replacement(1);
                break;

            case 2:
                h.Insert_With_Replacement(1);
                break;

            case 3:
                h.Insert_Without_Replacement(2);
                break;

            case 4:
                h.Insert_With_Replacement(2);
                break;

            case 5:
                h.Display();
                break;

            case 6:
                cout<<"Exit"<<endl;
                break;

            default:
                cout<<"Invalid Choice"<<endl;
        }

    }while(choice!=6);

    return 0;
}
