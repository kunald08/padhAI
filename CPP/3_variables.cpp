#include <iostream>
using namespace std;

int main()
{
    int n;  // Declaration of Integer value;
    n = 10; // initialization

    int myNum = 5;               // Integer (whole number without decimals)
    double myFloatNum = 5.99;    // Floating point number (with decimals)
    char myLetter = 'D';         // Character
    string myText = "Hello";     // String (text)
    bool myBoolean = true;       // Boolean (true or false)
    
    cout << n << myNum << myFloatNum << myLetter << myText << myBoolean <<"\n";
    
    // declare multiple variables;
    int x = 4, y = 6, z = 9;
    cout << "\n" << x+y+z;

    // same value;
    x = y = z = 50;
    cout << "\n" << x+y+z;
    
    // A-Z | a-z | 0-9 | _ | cannot start with digit;

    // Constants: unchangeable and read-only
    const int minutesPerHour = 60;

    cout << "##################################\n";
    
    // Calculate the Area of a Rectangle

    int length = 4;
    int width = 6;

    // Calculate the area of a rectangle
    int area = length * width;

    // Print the variables
    cout << "Length is: " << length << "\n";
    cout << "Width is: " << width << "\n";
    cout << "Area of the rectangle is: " << area << "\n";

    return 0;
}