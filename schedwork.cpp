#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool recursive_helper(const AvailabilityMatrix& avail,
                      const size_t dailyNeed,
                      const size_t maxShifts,
                      DailySchedule& sched,
                      int row,
                      int col,
                      int*& daysWorked);
bool isValidState(const AvailabilityMatrix& avail,
                  const size_t dailyNeed,
                  const size_t maxShifts,
                  DailySchedule& sched,
                  int*& daysWorked);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int* daysWorked = new int[avail[0].size()];
    bool b =  recursive_helper(avail, dailyNeed, maxShifts, sched, 0, 0, daysWorked);
    delete[] daysWorked;
    return b;
}

bool recursive_helper(const AvailabilityMatrix& avail,
                      const size_t dailyNeed,
                      const size_t maxShifts,
                      DailySchedule& sched,
                      int rowAvail,
                      int day,
                      int*& daysWorked){
    if (isValidState(avail, dailyNeed, maxShifts, sched, daysWorked) && rowAvail == sched.size() && day == dailyNeed){
        return true;
    }
    //for each column in availability matrix, 0 to k
    //if worker is available, add worker to sched
        //if isValidState
            //case 1: if d workers in day n
                //recurse next day
            //case 2: if <d workers in day n
                //recurse same day
    //remove choice
    for (Worker_T col = 0; col < avail.size(); col++){
        if (avail[rowAvail][col] == 1){
            sched[rowAvail].push_back(col);
            daysWorked[col]++;
            if (isValidState(avail, dailyNeed, maxShifts, sched, daysWorked)){
                if (day == dailyNeed-1){
                    recursive_helper(avail, dailyNeed, maxShifts, sched, rowAvail+1, 0, daysWorked);
                }
                else{
                    recursive_helper(avail, dailyNeed, maxShifts, sched, rowAvail, day +1, daysWorked);
                }
            }
            daysWorked[col]--;
            sched[rowAvail].pop_back();
        }
    }
    return false;
}

bool isValidState(const AvailabilityMatrix& avail,
                  const size_t dailyNeed,
                  const size_t maxShifts,
                  DailySchedule& sched,
                  int*& daysWorked){
    //if workers above max
    //for all rows n
        //for all columns d
            //if count..
    //maybe we should make arr of size k that holds the amount of days each nurse is working
    for (int i = 0; i < avail[0].size(); i++){
        if (daysWorked[i] > maxShifts){
            return false;
        }
    }
    //return false

    //i think availability will always match with this implementation
    //if availability does not match
    //return false
    return true;
}
