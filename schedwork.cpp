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
bool recursive_helper(AvailabilityMatrix& avail,
                      const size_t dailyNeed,
                      const size_t maxShifts,
                      DailySchedule& sched,
                      int row,
                      int col,
                      int* daysWorked);
void fillDaysWorked(int* daysWorked, int index, int maxSize);
bool isValidStateR(const size_t maxShifts,
                   int* daysWorked,
                   int maxSize,
                   int index);

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
    int daysWorked[avail[0].size()];
    AvailabilityMatrix availcopy = avail;
    int maxSize = avail[0].size();
    fillDaysWorked(daysWorked, 0, maxSize);

    for (int i = 0; i < avail.size(); i++){
        vector<Worker_T> v;
        for (int j = 0; j < dailyNeed; j++){
            v.push_back(INVALID_ID);
        }
        sched.push_back(v);
    }
    bool b =  recursive_helper(availcopy, dailyNeed, maxShifts, sched, 0, 0, daysWorked);
    return b;
}

void fillDaysWorked(int* daysWorked, int index, int maxSize){
    if (index > maxSize - 1){
        return;
    }

    daysWorked[index] = 0;
    fillDaysWorked(daysWorked, index + 1, maxSize);
}
//for each column in availability matrix, 0 to k
//if worker is available, add worker to sched
//if isValidState
//case 1: if d workers in day n
//recurse next day
//case 2: if <d workers in day n
//recurse same day
//remove choice
bool recursive_helper(AvailabilityMatrix& avail,
                      const size_t dailyNeed,
                      const size_t maxShifts,
                      DailySchedule& sched,
                      int rowAvail,
                      int day,
                      int* daysWorked){
    if (isValidStateR(maxShifts, daysWorked, avail[0].size(), 0) && rowAvail == sched.size()){
        return true;
    }
    for (Worker_T col = 0; col < avail[0].size(); col++){
        if (avail[rowAvail][col] == 1){
            sched[rowAvail][day] = col;
            avail[rowAvail][col] = false;
            daysWorked[col]++;
            if (isValidStateR(maxShifts, daysWorked, avail[0].size(), 0)){
                if (day == dailyNeed-1){
                    if (recursive_helper(avail, dailyNeed, maxShifts, sched, rowAvail+1, 0, daysWorked)){
                        return true;
                    }
                }
                else{
                    if (recursive_helper(avail, dailyNeed, maxShifts, sched, rowAvail, day +1, daysWorked)) {
                        return true;
                    }
                }
            }
            daysWorked[col]--;
            avail[rowAvail][col] = true;
            sched[rowAvail][day] = INVALID_ID;
        }
    }
    return false;
}


bool isValidStateR(const size_t maxShifts,
                  int* daysWorked,
                  int maxSize,
                  int index){
    if (index > maxSize - 1){
        return true;
    }

    if (daysWorked[index] > maxShifts){
        return false;
    }

    return isValidStateR(maxShifts, daysWorked, maxSize, index + 1);
}
