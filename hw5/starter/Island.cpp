/*
 * Island.cpp
 * CPSC 223 Pset 5
 *
 * Implementation of the Island class
 * TO STUDENT: Don't forget to remove // TODO before you submit!
 *
 * Author: Braeden Cullen
 */

#include "Island.h"

// Default Constructor (Implemented for you)
Island::Island()
{
    this->name = "NoName";
    this->access = false;
}

Island::Island(string name, bool access)
{
    this->name = name;
    this->access = access;
}

bool Island::isEqual(Island other)
{
    if (this->name == other.name && this->access == other.access)
    {
        return true;
    }
    return false;
}

void Island::print(ostream &outfile)
{
    outfile << this->name << " ";
    if (this->access)
    {
        outfile << "A" << endl;
    }
    else
    {
        outfile << "U" << endl;
    }
}
