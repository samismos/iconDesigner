// IconBuilder.cpp : This file contains the 'main' function. Program execution begins and ends there. 

#include <iostream> 
#include "Functions.h"

using namespace std;

int main()
{
    print_string_with_background_color("R", "Welcome ");
    print_string_with_background_color("O", "User,");
    cout << endl;
    print_string_with_background_color("Y", "to");
    print_string_with_background_color("G", "the ");
    print_string_with_background_color("B", "Icon ");
    print_string_with_background_color("V", "Builder ");
    print_string_with_background_color("P", "Pro");
    cout << endl;
    initializeMenu();
}



