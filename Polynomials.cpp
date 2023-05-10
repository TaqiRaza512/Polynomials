#include <iostream>
#include <fstream>
using namespace std;

#define MaxCapacity 100
void CreateFile(void);

struct Polynomial
{
    int Cs[MaxCapacity];
    int d;
};

void Init(Polynomial& poly1, Polynomial& poly2)
{
    ifstream Rdr("Polynomials.txt");
    Rdr >> poly1.d;
    for (int i = 0; i < poly1.d + 1; i++)
    {
        Rdr >> poly1.Cs[i];
    }
    Rdr >> poly2.d;
    for (int i = 0; i < poly2.d + 1; i++)
    {
        Rdr >> poly2.Cs[i];
    }
}

void PrintPoly(Polynomial& poly)
{
    for (int i = 0; i <= poly.d; i++)
    {

        if (i != 0)
            cout << ((poly.Cs[i] >= 0) ? "+" : "");

        cout << poly.Cs[i];

        if (i != poly.d)
        {
            if (i != poly.d - 1)
                cout << "x^" << poly.d - i;
            else
                cout << "x";
        }
    }

}

int evaluate(Polynomial& P, int x)
{
    int result = 0;
    for (int i = 0; i < P.d + 1; i++)
    {
        result += P.Cs[i] * pow(x, (P.d - i));
    }
    return result;
}

void AddPoly(Polynomial& poly1, Polynomial& poly2)
{
    Polynomial poly3;

    for (int i = 0; i <= poly1.d; i++)
    {

        if (poly2.d - i >= 0)
        {
            poly3.Cs[poly1.d - i] = poly1.Cs[poly1.d - i] + poly2.Cs[poly2.d - i];
        }
        else
            poly3.Cs[poly1.d - i] = poly1.Cs[poly1.d - i];

    }
    poly3.d = poly1.d;

    cout << endl;
    PrintPoly(poly3);
    cout << endl;
}

void SubPoly(Polynomial& poly1, Polynomial& poly2)
{
    Polynomial poly3;

    for (int i = 0; i <= poly1.d; i++)
    {

        if (poly2.d - i >= 0)
        {
            poly3.Cs[poly1.d - i] = poly1.Cs[poly1.d - i] - poly2.Cs[poly2.d - i];
        }
        else
            poly3.Cs[poly1.d - i] = poly1.Cs[poly1.d - i];

    }
    poly3.d = poly1.d;

    cout << endl;
    PrintPoly(poly3);
    cout << endl;
}

void MultiPoly(const Polynomial& poly1, const Polynomial& poly2)
{
    Polynomial poly3, poly4;

    int arr[MaxCapacity], r = 0;

    for (int i = 0; i <= poly1.d; i++)
    {
        for (int j = 0; j <= poly2.d; j++)
        {
            poly3.Cs[r] = poly1.Cs[i] * poly2.Cs[j];
            arr[r] = (poly1.d - i) + (poly2.d - j);
            r++;
        }
    }
    poly3.d = (poly1.d + 1) * (poly2.d + 1) - 1;


    cout << endl << " poly 3 : ";
    PrintPoly(poly3);
    cout << endl;
    cout << endl << " arr: ";
    for (int i = 0; i < poly3.d + 1; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    int sum = 0; r = 0;
    for (int i = 0; i <= poly3.d; i++)
    {
        if (poly3.Cs[i] != 0)
        {
            for (int j = 0; j <= poly3.d; j++)
            {
                if (arr[j] == arr[i])
                {
                    sum += poly3.Cs[j];
                }
            }
            poly4.Cs[r] = sum;
            r++;
            sum = 0;
        }
    }
    poly4.d = r;
    cout << endl << " poly 4 : ";
    PrintPoly(poly4);
    cout << endl;
}

void Menu()
{
    cout << endl;
    cout << "\n\t1 : Evaluate Polynomial for value of x";
    cout << "\n\t2 : Add Polynomials";
    cout << "\n\t3 : Sub Polynomials";
    cout << endl;
}

int main()
{
    Polynomial poly1, poly2;
    Init(poly1, poly2);
    char Tocontinue;
    int choice;
    int x, pol = 1;

    do
    {
        cout << "\n\tPolynomials: ";
        cout << "\n\tPoly 1: ";
        PrintPoly(poly1);
        cout << "\n\tPoly 2: ";
        PrintPoly(poly2);
        Menu();
        cout << "\n----------------------------------------------------------\n\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter value of x : ";
            cin >> x;
            cout << "\nSelect polynomial: ";
            cin >> pol;
            if (pol == 1)
            {
                cout << endl << "Result: " << evaluate(poly1, x) << endl;
            }
            else
                cout << endl << "Result: " << evaluate(poly2, x) << endl;
            break;
        case 2:
            cout << endl << "Adding Polynomials: ";
            AddPoly(poly1, poly2);
            break;
        case 3:
            cout << endl << "Subtracting Polynomials: ";
            SubPoly(poly1, poly2);
            break;
        default:
            break;
        }
        cout << "\n DO YOU WANT TO CONTINUE: (Y/N)? ";
        cin >> Tocontinue;

        cout << endl;
        system("pause");
        system("cls");

    } while (Tocontinue == 'y' || Tocontinue == 'Y');

    //MultiPoly(poly1, poly2);
    //AddPoly(poly1, poly2);
    //SubPoly(poly1, poly2);


}

void CreateFile()
{
    int arr[] = { 5,0,12,2,0,3,2 };
    int arr2[] = { 5,0,12,0,0,3 };

    ofstream Rtr("Polynomials.txt");
    Rtr << 6 << endl;
    for (int i = 0; i < 7; i++)
    {
        Rtr << arr[i] << " ";
    }
    Rtr << endl << 5 << endl;
    for (int i = 0; i < 6; i++)
    {
        Rtr << arr2[i] << " ";
    }
    cout << "\nFile Created\n\n";
}