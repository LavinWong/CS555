#include "individual.h"

Individual::Individual(std::string id1){
    id = id1;
    // todo initializer
    // name = "NA";
    // gender = 'M';
    // bday = time(NULL);
}

Individual::~Individual(){

}

void Individual::setID(std::string id2){
    id = id2;
}

void Individual::setName(std::string name2){
    name = name2;
}

void Individual::setGender(std::string gender2){
    gender = gender2;
}

void Individual::setBday(std::string bday){
    // to do

}

void Individual::setDday(std::string dday){
    // to do

}

void Individual::setAlive(){
    alive = true;
}

void Individual::setFamcList(std::string famc_id){
    famcList.push_back(famc_id);
}

void Individual::setFamsList(std::string fams_id){
    famsList.push_back(fams_id);
}

std::string Individual::getID(){
    return id;
}
std::string Individual::getName(){
    return name;
}
std::string Individual::getGender(){
    return gender;
}
std::string Individual::getBday(){
    //todo
    // mock
    return "1900-01-01";
}
std::string Individual::getAlive(){
    if (alive){
        return "Y";
    }else{
        return "N";
    }
}
std::string Individual::getDday(){
    //todo
    // mock
    return "1900-01-02";
}

std::string Individual::getFamcList(){
    std::string str(famcList.begin(), famcList.end());
    return str;
}

std::string Individual::getFamsList(){
    std::string str(famsList.begin(), famsList.end());
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