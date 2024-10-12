#include <iostream>
#include <math.h>
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::vector; 
using std::setprecision;
using std::fixed;
using std::showpoint; 

//----- conversions -------------------------------------------

int toIndex(float x) {
    int hour = floor(x);
    if(x == hour)
        return hour * 4; 
    else 
        return (hour * 4) + round((x - hour)/0.15); 
}

float toTime(int i) {
    int hour = i / 4;
    int minutes = i % 4; 
    return hour + (minutes * 0.15);
    }
//---------------------------------------------------------------

const int TIME_INTERVALS = 97;
const bool BUSY = true;
const bool FREE = false; 

class Schedule{
public:

//------ constructors ---------------------------------------

    Schedule() {
        this->name = "no name";
        for(int i = 0; i < TIME_INTERVALS; i++) {
            this->schedule[i] = FREE; 
        }
    }

    Schedule(string name) {
        this->name = name;
        for(int i = 0; i < TIME_INTERVALS; i++) {
            this->schedule[i] = FREE;
        }
    }
//------------------------------------------------------------

//----- getters/setters --------------------------------------

    void setTimeInterval(float start, float end) {
        this->start = start;
        this->end = end;
    }

    float getStartTime() {
        return this->start;
    }

    float getEndTime() {
        return this->end;
    }

    void setSchedule(int i, bool c) {
        this->schedule[i] = c;
    }

    bool getSchedule(int i) {
        return schedule[i];
    }
//-------------------------------------------------------------

//----- insert busy time interval -------------------------------

    void addBusyTime(float start, float end) {
        for(int i = toIndex(start); i < toIndex(end); i++) {
            schedule[i] = BUSY;
        }
    }
//----------------------------------------------------------------

//----- print the user's schedule --------------------------------

    void showUserSchedule() {
        bool prev = false; 
        cout << "----- " << name << "'s schedule ----- " << endl;
        for(int i = 0; i < TIME_INTERVALS; i++) {
            if(schedule[i] != prev) {
                prev = !prev; 
                cout << fixed << showpoint; 
                cout << setprecision(2) << toTime(i);
                if(schedule[i]) cout << " - ";
                else cout << endl;
            }
        }
        if(schedule[TIME_INTERVALS - 1] == BUSY)
            cout << toTime(TIME_INTERVALS - 1) << endl;
        cout << "---------------------------" << endl;   
    }
//-----------------------------------------------------------------

private:
    string name;
    bool schedule[TIME_INTERVALS];
    float start;
    float end;
};

class Group {
public:

//----- constructor -----------------------------------------------

    Group(string n) {
        group_name = n;
        g_schedule = Schedule();
        group_start = -1.00;
        group_end = 25.00;
    }
//-----------------------------------------------------------------

//----- apply the free time period defined by user ---------------

   void applyInterval() {
        for(int i = 0; i < toIndex(group_start); i++) 
            g_schedule.setSchedule(i, BUSY);
        for(int i = toIndex(group_end); i < TIME_INTERVALS; i++) 
            g_schedule.setSchedule(i, BUSY);
    }

//----------------------------------------------------------------

//----- add group members' schedule -------------------------------

    void addSchedule(Schedule s) {
        if(group_start < s.getStartTime())
            group_start = s.getStartTime();
        if(group_end > s.getEndTime())
            group_end = s.getEndTime();
        
        for(int i = 0; i <= TIME_INTERVALS; i++) {
            if(s.getSchedule(i) == BUSY) 
                g_schedule.setSchedule(i, BUSY);
        }
    }

//------------------------------------------------------------------

//----- * algorithm 3: finding the overlapping free intervals ------

    void findMeetingTimes(float meeting_length) {
        applyInterval();
        
        int counter = 0;
        int required = toIndex(meeting_length);

        for(int i = 0; i < TIME_INTERVALS; i++) {

            if(g_schedule.getSchedule(i) == FREE) counter++;
            if(g_schedule.getSchedule(i) == BUSY) counter = 0;

            if(counter == required) {
                meeting_times.push_back(toTime(i - required + 1));
                meeting_times.push_back(toTime(i + 1));
            }

            if(counter > required) {
                meeting_times.pop_back();
                meeting_times.push_back(toTime(i + 1));
            }
        }
        printGroupSchedule();
    }

    void printGroupSchedule() {
        cout << "----- available times -----" << endl;
        for(int i = 0; i < meeting_times.size(); i++) {
            cout << fixed << showpoint; 
            cout << setprecision(2) << meeting_times[i]; 
            if(i % 2 == 0) cout << "-";
            else cout << endl;
        }
    }

//------------------------------------------------------------------

private:
    string group_name; 
    Schedule g_schedule; 
    vector <float> meeting_times; 
    float group_start;
    float group_end;
};

int main() {

    Schedule sample_one("one");
    sample_one.addBusyTime(7.00, 8.30);
    sample_one.addBusyTime(12.00, 13.00);
    sample_one.addBusyTime(16.00, 18.00);
    sample_one.setTimeInterval(9.00, 19.00);
    sample_one.showUserSchedule();

    Schedule sample_two("two");
    sample_two.addBusyTime(9.00, 10.30);
    sample_two.addBusyTime(12.20, 13.30);
    sample_two.addBusyTime(14.00, 15.00);
    sample_two.addBusyTime(16.00, 17.00);
    sample_two.setTimeInterval(9.00, 18.30);
    sample_two.showUserSchedule();

    Group sample_group("sample");
    sample_group.addSchedule(sample_one);
    sample_group.addSchedule(sample_two);
    sample_group.findMeetingTimes(0.30);

    return 0;
}