#include "individual.h"

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