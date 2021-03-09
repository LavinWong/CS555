//
// Created by Qi Zhao on 3/5/21.
//

#include "Individual2.h"

Individual2::Individual2(std::string id2) {
    id = id2;
    gender = "NA";
    dday = str_to_t_time("NA");
    famc = "NA";
    fams = "NA";
}

Individual2::~Individual2() {

}

std::string Individual2::getID() {
    return id;
}
void Individual2::setID(std::string id2){
    id = id2;
}
void Individual2::setName(std::string name2){
    name = name2;
}

void Individual2::setAge() {
    if (bday == -1){
        age = -1;

    }else{
        if (dday == -1){
            time_t now;
            time(&now);
            double seconds;
            seconds = difftime(now, bday);
            age = (int) (seconds/(60*60*24*365));
        }else{
            double seconds;
            seconds = difftime(dday, bday);
            age = (int) (seconds/(60*60*24*365));
        }
    }
}

std::string Individual2::getAge(){
    if (age == -1){
        return "NA";
    }else{
        std::string age_str = std::to_string(age);
        return age_str;
    }
}

void Individual2::setGender(std::string gender2){
    gender = gender2;
}
void Individual2::setBday(std::string bday2){
    bday = str_to_t_time(bday2);
}
void Individual2::setDday(std::string dday2){
    dday = str_to_t_time(dday2);
}
void Individual2::setAlive(){
    if (dday == -1){
        if (bday == -1){
            alive = false;
        }else{
            alive = true;
        }
    }else{
        alive = false;
    }
}
void Individual2::setFamcList(std::string famc_id2) {
    famc = famc_id2;
}
void Individual2::setFamsList(std::string fams_id2){
    fams = fams_id2;
}

std::string Individual2::getName(){
    return name;
}
std::string Individual2::getGender(){
    return gender;
}
std::string Individual2::getBday(){
    if (bday == -1){
        return "NA";
    }else{
        char output[20];
        struct tm* timeinfo;
        timeinfo = localtime(&bday);
        strftime(output,20,"%F",timeinfo);
        std::string out2 = output;
        if (out2 == "1899-12-31"){
            return "NA";
        }
        return out2;
    }
}
std::string Individual2::getAlive(){
    if (alive) {
        return "True";
    }else{
        return "False";
    }
}
std::string Individual2::getDday(){
    if (dday == -1){
        return "NA";
    }else{
        char output[20];
        struct tm* timeinfo;
        timeinfo = localtime(&dday);
        strftime(output,20,"%F",timeinfo);
        std::string out2 = output;
        if (out2 == "1899-12-31"){
            return "NA";
        }
        return out2;
    }
}
std::string Individual2::getFamcList(){
    return famc;
}
std::string Individual2::getFamsList(){
    return fams;
}