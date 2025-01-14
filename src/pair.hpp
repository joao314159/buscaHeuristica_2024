#pragma once

#include <iostream>

using namespace std;

class Pair
{
public:
    int first_Element;
    int second_Element;
    double distance_Element;

public:
    Pair() {
        first_Element = 0;
        second_Element = 0;
        distance_Element = 0;
    }
    Pair(int first_Element, int second_Element, double distance_Element)
    {
        this->first_Element = first_Element;
        this->second_Element = second_Element;
        this->distance_Element = distance_Element;
    }
    void to_String() {
        cout << "first_Element: " << first_Element << endl;
        cout << "second_Element: " << second_Element << endl;
        cout << "distance_Element: " << distance_Element << endl;
    }

    void set_first_Element(int first_Element) {
        this->first_Element = first_Element;
    }
    void set_second_Element(int second_Element) {
        this->second_Element = second_Element;
    }
    void set_distance_Element(double distance_Element) {
        this->distance_Element = distance_Element;
    }

    int get_first_Element() {
        return first_Element;
    }
    int get_second_Element() {
        return second_Element;
    }
    double get_distance_Element() {
        return distance_Element;
    }
};
