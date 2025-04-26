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
// checks for valid state

bool isValid(
    int day,
    Worker_T worker,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    const std::vector<int>& count_

);

// does the recursive backtracking
bool scheduleHelper(
    int day,
    int slot,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<int>& count_
);

// Add your implementation of schedule() and other helper functions here



// returns true if solution is found
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

    // sets up sched to be nxk matrix of values -1
    sched.assign(avail.size(), std::vector<Worker_T>(dailyNeed, INVALID_ID));

    // create vector of ints to keep track of how many
    // shifts each worker has been assigned
    std::vector<int> count(avail[0].size());
    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, sched, count);
}
bool isValid(
    int day,
    Worker_T worker,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    const std::vector<int>& count_
)
{
    // checks if worker is available
    if (avail[day][worker] == 0)
    {
        return false;
    }
    // if the worker has worked to much
    else if (count_[worker] >= maxShifts)
    {
        return false;
    }
    // if the worker is already scheudled that day
    else if (std::find(sched[day].begin(), sched[day].end(), worker) != sched[day].end())
    {
        return false;
    }
    else 
    {
        return true;
    }
}
bool scheduleHelper(
    int day,
    int slot,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<int>& count_
)
{
    // # of days and workers
    size_t n = avail.size();    
    size_t k = avail[0].size();   
    // base case
    if (day == n)
    {
        return true;
    }
    // if at the end of the day
    if (slot == dailyNeed)
    {
        return scheduleHelper(day + 1, 0, avail, dailyNeed, maxShifts, sched, count_);
    }
    // loop throughy all workers
    for (Worker_T worker = 0; worker < k; worker++)
    {
        if (!isValid(day, worker, avail, dailyNeed, maxShifts, sched, count_))
        {
            continue;
        }
        // insert the worker into slot
        sched[day][slot] = worker;
        count_[worker]++;
        // recursively go to next slot
        if (scheduleHelper(day, slot + 1, avail, dailyNeed, maxShifts, sched, count_))
        {
            return true;
        }
        // backtrack
        sched[day][slot] = INVALID_ID;
        count_[worker]--;
    }
    return false;

}
