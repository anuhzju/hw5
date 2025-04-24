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

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCounts,
    size_t day
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    size_t numDays = avail.size();
    if(numDays == 0 || avail[0].empty()){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t numWorkers = avail[0].size();
    sched.resize(numDays, vector<Worker_T>());

    vector<size_t> shiftCounts(numWorkers, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCounts,
    size_t day
) {
    if (day == avail.size()){
        return true;
    }
    size_t numWorkers = avail[0].size();
    vector<Worker_T>& todaySchedule = sched[day];

    for (Worker_T worker = 0; worker < numWorkers; ++worker){
        if (!avail[day][worker]){
            continue;
        }
        if (shiftCounts[worker] >= maxShifts){
            continue;
        }
        if (find(todaySchedule.begin(), todaySchedule.end(), worker) != todaySchedule.end()){
            continue;
        }

        todaySchedule.push_back(worker);
        ++shiftCounts[worker];
        if (todaySchedule.size() == dailyNeed){
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, day + 1)){
                return true;
            }
        }
        else {
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, day)){
                return true;
            }
        }

        todaySchedule.pop_back();
        --shiftCounts[worker];
    }
    return false;
}

