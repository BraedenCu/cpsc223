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
    Island newIsland; 
    newIsland.name = name;
    newIsland.access = access;
}

bool Island::isEqual(Island other)
{
    // name and accessiblity levels must both be equal
    if (this->name == other.name && this->access == other.access)
    {
        return true;
    }
    return false;
}

void Island::print(ostream &outfile)
{
    // print the name and accessiblity level of the island
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
