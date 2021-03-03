#include "family.h"

Family::Family(std::string id1){
    id = id1;
}

Family::~Family(){

}

void Family::setMarrDate(std::time_t marr_d){
    // todo

}
void Family::setDivDate(std::time_t div_d){
    // todo

}
void Family::setHusId(std::string hus_id){
    // todo

}
void Family::setWifeId(std::string wife_id){
    // todo

}
void Family::setHusName(std::string hus_id){
    // todo

}
void Family::setWifeName(std::string wife_id){
    // todo

}
void Family::getChildrenId(std::vector<std::string> children_id){
    // todo
    
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