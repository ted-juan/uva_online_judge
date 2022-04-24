#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <boost/format.hpp>

//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using namespace std;

class Time
{
public:    
    Time(int _hours, int _minutes) : hours(_hours), minutes(_minutes) {}

    bool operator>(const Time &t) const
    {
        return ((hours - t.hours) * 60 + minutes - t.minutes > 0) ?
                true : false;
    }
    Time operator-(const Time &t) const
    {
        int64_t diff = (hours - t.hours) * 60 + minutes - t.minutes;
        return Time(diff/60, diff%60);
    }
    string show_time()
    {
        string text = str(boost::format("%02d:%02d") % hours % minutes);
        return text;
    }
    string show_text_time()
    {
        const string hours_text = (hours > 0) ? to_string(hours) + " hours and " : "";
        return  hours_text + to_string(minutes) + " minutes.";
    }
private:
    int hours;
    int minutes;
};

class time_set
{
public:    
    time_set(Time _start_time, Time _end_time) 
        : start_time(_start_time), end_time(_end_time)
        , interval(_end_time - _start_time) {}

    bool greater_start_time(const time_set &t1)
    {
        return (start_time > t1.start_time);
    }
    bool is_get_off_early()
    {
        return (end_time > start_time);
    }
    static bool compare_interval(const time_set &n1, const time_set &n2)
    {
        return (n2.interval > n1.interval); 
    }
    static bool compare_start_time(const time_set &n1, const time_set &n2)
    {
        return (n2.start_time > n1.start_time); 
    }
    const Time get_start_time() const
    {
        return start_time;
    }
    const Time get_end_time() const
    {
        return end_time;
    }
    void set_start_time(const Time &t)
    {
        start_time = t;
    }
    const string show_start_time() 
    {
        return start_time.show_time();
    }
    const string show_interval()
    {
        return interval.show_text_time(); 
    }
private:
    Time start_time;
    Time end_time;
    Time interval;
};

time_set find_the_longest_nap_time(vector <time_set> &nap_time_list)
{
    auto max = *std::max_element(nap_time_list.begin(),
                            nap_time_list.end(),
                            time_set::compare_interval);
    return max;                             
}

void compute_nap_time(vector <time_set> &work_time_list, vector <time_set> &nap_time_list)
{
    time_set tmp ({10, 0}, {18, 0});
    nap_time_list.clear();

    sort(work_time_list.begin(), work_time_list.end(),time_set::compare_start_time);

    for ( auto &it : work_time_list)
    {
        if (it.greater_start_time(tmp))
            nap_time_list.push_back({tmp.get_start_time(), it.get_start_time()});

        tmp.set_start_time(it.get_end_time());
    }    
    if (tmp.is_get_off_early())
        nap_time_list.push_back({tmp.get_start_time(), tmp.get_end_time()});
}

bool read_daily_to_work_list(std::istream & is, vector <time_set> &work_time_list)
{
    int num; 
    string line;
    int start_hours, start_minutes, end_hours, end_minutes;

    if (!getline(is, line))
        return false;

    work_time_list.clear();
    num = stoi(line);

    for (auto i=0; i<num; i++)
    {
        getline(is, line);
        sscanf(line.c_str(), "%d:%d %d:%d", 
            &start_hours,
            &start_minutes,
            &end_hours,
            &end_minutes);
        work_time_list.push_back(
                time_set({start_hours, start_minutes}, {end_hours, end_minutes}));
    }        
    return true;
}

void print_the_longest_nap_time(std::ostream & os, int day, time_set &nap)
{
        os << "Day #" << day << ": the longest nap starts at " << 
            nap.show_start_time() << " and will last for " << 
            nap.show_interval() << endl;
}

void resolve_uva(std::istream & is, std::ostream & os)
{
    vector <time_set> work_time_list;
    vector <time_set> nap_time_list;
    int day = 1;
    
    while(1)
    {
        if (read_daily_to_work_list(is, work_time_list) == false)
            break;

        compute_nap_time(work_time_list, nap_time_list);
        time_set nap = find_the_longest_nap_time(nap_time_list);
        print_the_longest_nap_time(os, day, nap);
        day++;            
    }
}

int main(int argc, char** argv)    
{
#ifdef ONLINE_JUDGE
    resolve_uva(cin, cout);
    return 0;
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}