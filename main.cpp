/*
    Name: Ramon Perez, CS 302-1004
    Description: This program will simulate a match of Mercenaries from Resident Evil 3. It will read
    in a file to get the names of the mercenaries players that will compete, then it will read another
    where each line is an event in the game (mercenary defeated enemy or saved civilian). The program
    uses an priority queue in maxheap order to maintain the list of mercenaries and their current point
    rankings. Every time a mercenary earns points, the heapArray that holds all of the point values will
    be updated, and the priority queue will use bubbleUp to switch the places of mercenaries in case one
    gains more points than another. Finally, the program will output the priority queue and rank the mercenaries.
    Point Values:
    - Zombies × 1.0
    - Spiders × 1.1
    - Drain Deimos × 1.2
    - Zombie Dogs × 1.3
    - Hunters × 1.4
    - Nemesis × 1.5
    - Civilians Rescued × 2.0
    Output: Instances where there is a new leader in the rankings, then the overall rankings once the simulation file
    is read.
*/
#include "priorityQ.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <iomanip>

using namespace std;

struct mercType
{
    // tracks how many of each monsters is
    // defeated and civilian saved for a
    // mercenary
    int zombies;
    int spiders;
    int drainDeimos;
    int zombieDogs;
    int hunters;
    int nemesis;
    int civilians;
    // default constructor , optional but can
    // be helpful
    mercType()
    {
        // 8:23
        zombies = spiders = drainDeimos = zombieDogs
        = hunters = nemesis = civilians = 0;
    }
    // do not actual try to overload the
    // question mark operator , you can overload
    // any comparison operator you like and it will
    // be used in your bubbleUp and bubbleDown

    bool operator>(const mercType &rhs) const
    {
        // Compute the values of this-> and rhs mercTypes
        // and return true if this-> is bigger
        // 9:28
        // 9:43 purpose of the overloads

        double thisScore, rhsScore = 0;

        // Compute score for *this
        thisScore += this->zombies;
        thisScore += this->spiders * 1.1;
        thisScore += this->drainDeimos * 1.2;
        thisScore += this->zombieDogs * 1.3;
        thisScore += this->hunters * 1.4;
        thisScore += this->nemesis * 1.5;
        thisScore += this->civilians * 2;

        // Compute score for rhs
        rhsScore += rhs.zombies;
        rhsScore += rhs.spiders * 1.1;
        rhsScore += rhs.drainDeimos * 1.2;
        rhsScore += rhs.zombieDogs * 1.3;
        rhsScore += rhs.hunters * 1.4;
        rhsScore += rhs.nemesis * 1.5;
        rhsScore += rhs.civilians * 2;

        //cout << "thisScore: " << thisScore << "\nrhsScore: " << rhsScore << endl; // Debug

        return (thisScore > rhsScore) ? true : false;
    }
    
    // You might need to overload + or +=
    // operators , would be needed in the
    // increaseKey function
    void operator+=(const mercType &rhs) 
    {
        // 25:18
        mercType sumMercType;
        sumMercType = rhs;

        this->zombies +=rhs.zombies;
        this->spiders +=rhs.spiders;
        this->drainDeimos +=rhs.drainDeimos;
        this->zombieDogs +=rhs.zombieDogs;
        this->hunters +=rhs.hunters;
        this->nemesis +=rhs.nemesis;
        this->civilians +=rhs.civilians;
    }
};

double getMercScore(priorityQ<std::string, mercType> mercenaries)
{
    /*
    FUNCTION_IDENTIFIER: This was not a provided function. This function will
    take the mercType parameter passed in and calculate its point totals.
    Return Value: double value holding mercenaries's score
    */
    double mercScore = 0;
    mercScore += mercenaries.get_front_priority().zombies;
    mercScore += mercenaries.get_front_priority().spiders * 1.1;
    mercScore += mercenaries.get_front_priority().drainDeimos * 1.2;
    mercScore += mercenaries.get_front_priority().zombieDogs * 1.3;
    mercScore += mercenaries.get_front_priority().hunters * 1.4;
    mercScore += mercenaries.get_front_priority().nemesis * 1.5;
    mercScore += mercenaries.get_front_priority().civilians * 2;

    return mercScore;
}

int main()
{
    /*
    FUNCTION_IDENTIFIER: This operator overload function will help with finding
    and inserting entries to the hashmap. It will also resize the tables if the
    load factor is above 20%.
    Return Value: table value at index
    */
    priorityQ<std::string, mercType> mercenaries;

    string mercFileName, simFileName = "";
    cout << "\nEnter mercenaries file: ";
    cin >> mercFileName;
    cout << "\n\nEnter simulation file: ";
    cin >> simFileName;

    fstream mercFile;
    mercFile.open(mercFileName); // mercFile.open(mercFileName);
    string mercName = "";
    string prevMerc = "";
    while (mercFile)
    {
        // 27:57
        mercFile >> mercName;
        
        // Prevent Duplicates
        if (mercName != prevMerc)
        {
            mercenaries.push_back(mercName, mercType());
        }
        prevMerc = mercName;
    }
    mercFile.close();



    fstream simFile;
    simFile.open(simFileName);

    string creature = "";
    int creatNum = 0;
    string leader = "";
    while(simFile >> mercName >> creature >> creatNum)
    {
        mercType entry;
        // cout << "\nEntry: " << mercName << " killed " << creatNum << " " << creature << endl; // Debug
        if (creature == "zombies")
        {
            entry.zombies = creatNum;
        }
        else if (creature == "spiders")
        {
            entry.spiders = creatNum;
        }
        else if (creature == "drainDeimos")
        {
            entry.drainDeimos = creatNum;
        }
        else if (creature == "zombieDogs")
        {
            entry.zombieDogs = creatNum;
        }
        else if (creature == "hunters")
        {
            entry.hunters = creatNum;
        }
        else if (creature == "nemesis")
        {
            entry.nemesis = creatNum;
        }
        else // civilians
        {
            entry.civilians = creatNum;
        }

        mercenaries.increaseKey(mercName, entry);

        // Leader Check
        if (leader != mercenaries.get_front_key())
        {
            double mercScore = getMercScore(mercenaries);

            cout << "\nWe have a new leader: " << mercName
            << " Score: " << fixed << setprecision(1) << mercScore << endl;

            leader = mercName;
        }
    }


    // Display Rankings
    int myRank = 1;
    while (!mercenaries.isEmpty())
    {
        cout << "Rank " << myRank
        << "\nName: " << mercenaries.get_front_key()
        << " Score: " << fixed << setprecision(1) << getMercScore(mercenaries) << endl << endl;

        ++myRank;
        mercenaries.pop_front();
    }

    simFile.close();

    return 0;
}