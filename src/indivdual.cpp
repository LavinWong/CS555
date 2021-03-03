#include "individual.h"
#include <iostream>  
#include <time.h>  
#include <stdlib.h>  
#include <string.h>


Individual::Individual(std::string id1){
    id = id1;
    name = "NA";
    gender = 'M';
    bday = time(NULL);
}

Individual::~Individual(){

}

void Individual::setName(std::string name){
    // to do

}

void Individual::setGender(char gender){
    // todo

}

void Individual::setBday(std::time_t bday){
    // to do

}

void Individual::setDday(std::time_t dday){
    // to do

}

void Individual::setAlive(){
    // to do

}

void Individual::getChildId(std::vector<Family> family_list){
    // to do

}

time_t transfer_sting_to_time(std::string str)
{
    if(str == "NA")
    {
        tm tm1;
        tm1.tm_year = 0;                
        tm1.tm_mon = 0;                    
        tm1.tm_mday = 0;
        tm1.tm_hour = 0;                        
        tm1.tm_min = 0;                       
        tm1.tm_sec = 0;                       
        tm1.tm_isdst = 0;                          
        time_t ans = mktime(&tm1); 
        return ans;
    }    
    char *date = (char*)str.data();
    tm tm1;                                    
    int year, month, day, hour=0, minute=0, second=0;
    sscanf(date, "%d-%d-%d", &year, &month, &day);
    tm1.tm_year = year - 1900;                
    tm1.tm_mon = month - 1;                    
    tm1.tm_mday = day;
    tm1.tm_hour = hour;                        
    tm1.tm_min = minute;                       
    tm1.tm_sec = second;                       
    tm1.tm_isdst = 0;                          
    time_t ans = mktime(&tm1); 
    return ans;
}
