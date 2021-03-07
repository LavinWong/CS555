//
// Created by Qi Zhao on 3/5/21.
//

#include "Family2.h"

Family2::Family2(std::string id1) {
    id = id1;
    marr_d = str_to_t_time("NA");
    div_d = str_to_t_time("NA");
    hus_id = "NA";
    wife_id = "NA";
}

Family2::~Family2() {

}

void Family2::setID(std::string id2){
    id = id2;
}

std::string Family2::getID() {
    return id;
}

void Family2::setMarr(std::string marr_d2) {
    marr_d = str_to_t_time(marr_d2);
}

std::string Family2::getMarr() {
    if (marr_d == -1){
        return "NA";
    }
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&marr_d);
    strftime(output,20,"%F",timeinfo);
    std::string out2 = output;
    return out2;
}

void Family2::setDiv(std::string div_d2){
    div_d = str_to_t_time(div_d2);
}

void Family2::setHusName(std::string hus_name2){
    // todo
    hus_name = hus_name2;
}

void Family2::setWifeName(std::string wife_name2){
    // todo
    wife_name = wife_name2;
}

void Family2::setHusID(std::string hus_id2){
    hus_id = hus_id2;
}

void Family2::setWifeID(std::string wife_id2){
    wife_id = wife_id2;
}

void Family2::setChildrenList(std::string child_id) {
    children_id.push_back(child_id);
}

std::string Family2::getChildrenList() {
    std::string output = "{ ";
    for (auto child_id: children_id){
        output += child_id + ", ";
    }
    output += "}";
    return output;
}

std::string Family2::getDiv(){
    if (div_d == -1){
        return "NA";
    }
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&div_d);
    strftime(output,20,"%F",timeinfo);
    std::string out2 = output;
    return out2;
}
std::string Family2::getHusName(){
    return hus_name;
}
std::string Family2::getHusID(){
    return hus_id;
}
std::string Family2::getWifeName(){
    return wife_name;
}
std::string Family2::getWifeID(){
    return wife_id;
}


std::time_t str_to_t_time(std::string str)
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
    char month_str2[3];
    std::string month_str;
    int year, month, day, hour=0, minute=0, second=0;
    sscanf(date, "%d %s %d", &day,&month_str2, &year);
    month_str = std::string(month_str2);
    if (month_str == "JAN"){
        month = 1;
    }else if (month_str == "FEB"){
        month = 2;
    }else if (month_str == "MAR"){
        month = 3;
    }else if (month_str == "APR"){
        month = 4;
    }else if (month_str == "MAY"){
        month = 5;
    }else if (month_str == "JUN"){
        month = 6;
    }else if (month_str == "JUL"){
        month = 7;
    }else if (month_str == "AUG"){
        month = 8;
    }else if (month_str == "SEP"){
        month = 9;
    }else if (month_str == "OCT"){
        month = 10;
    }else if (month_str == "NOV"){
        month = 11;
    }else if (month_str == "DEC"){
        month = 12;
    }
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