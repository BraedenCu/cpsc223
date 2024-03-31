/**
 * Name: Braeden Cullen
 * Assignment: Treasure Hunter
 * Class: CPSC223 Spring 2024
 * Date: March 30th
 * Implementation of the Island class 
 * 
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
        outfile << "A" << " ";
    }
    else
    {
        outfile << "U" <<  " ";
    }
}
