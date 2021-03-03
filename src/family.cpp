#include "family.h"

Family::Family(std::string id1){
    id = id1;
}

Family::~Family(){

}

void Family::setID(std::string id2){
    id = id2;
}

void Family::setMarrDate(std::string marr_d){
    // todo

}
void Family::setDivDate(std::string div_d){
    // todo

}
void Family::setHusID(std::string hus_id2){
    hus_id = hus_id2;
}
void Family::setWifeID(std::string wife_id2){
    wife_id = wife_id2;
}
void Family::setHusName(std::string hus_id2){
    // todo
    // mock
    hus_name = "Husband /Name/";
}
void Family::setWifeName(std::string wife_id2){
    // todo
    // mock
    wife_name = "Wife /Wife/";
}

void Family::setChildID(std::string child_id2){
    children_id.push_back(child_id2);
}

std::string Family::getID(){
    return id;
}
std::string Family::getMarrDate(){
    // todo
    // mock
    return "1900-01-03";
}
std::string Family::getDivDate(){
    // todo
    // mock
    return "1900-01-04";
}
std::string Family::getHusID(){
    return hus_id;
}
std::string Family::getHusName(){
    return hus_name;
}
std::string Family::getWifeID(){
    return wife_id;
}
std::string Family::getWifeName(){
    return wife_name;
}
std::string Family::getChildrenList(){
    std::string str(children_id.begin(), children_id.end());
    return str;
}

std::time_t transfer_sting_to_time(std::string str)
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