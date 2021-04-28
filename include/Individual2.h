//
// Created by Qi Zhao on 3/5/21.
//

#ifndef NEW2_INDIVIDUAL2_H
#define NEW2_INDIVIDUAL2_H

#include <string>
#include <ctime>
#include <vector>
#include "Family2.h"


class Individual2 {
private:
    std::string id;
    std::string name;
    std::string gender;
    std::time_t bday; // bday for birthday date
    int age;
    bool alive;
    
    std::time_t dday; // dday for death date
    std::string famc;
    std::string fams;
    
public:
    Individual2(std::string id2);
    ~Individual2();

    bool hasBDate;
    bool hasDDate;
    int line;
    void setID(std::string id2);
    void setName(std::string name2);
    void setGender(std::string gender2);
    void setBday(std::string bday2);
    void setDday(std::string dday2);
    void setAge();
    void setAlive();
    void setFamcList(std::string famc_id2);
    void setFamsList(std::string fams_id2);


    std::string getID();
    std::string getName();
    std::string getGender();
    std::string getBday();
    std::string getAlive();
    std::string getDday();
    std::string getFamcList();
    std::string getFamsList();

    std::string getAge();
    int getAgeInt();
};


#endif //NEW2_INDIVIDUAL2_H
