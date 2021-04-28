//
// Created by Qi Zhao on 3/5/21.
//

#ifndef NEW2_REPOSITORY_H
#define NEW2_REPOSITORY_H

#include "VariadicTable.h"
#include "Family2.h"
#include "Individual2.h"
#include <string>
#include <ctime>
#include <vector>


std::vector<std::string> getOutPutString(std::string line_2);
std::string getValided(char level, std::string tag);
class Repository {
private:
    std::vector<Family2> famList;
    std::vector<Individual2> indiList;
public:
    Repository();
    ~Repository();
    std::string getIndividualName(std::string indi_id);
    std::string getIndividualSex(std::string indi_id);
    void setHusWifeName();
    std::string getBirthByID(std::string ID);
    bool compareAge(std::string b1, std::string b2, std::string sex);
    //bool checkFutureBirthOfLive(std::string currentTime, std::string indiBirth);

    void print_table();
    std::vector<std::string> us01();
    std::vector<std::string> us02();
    std::vector<std::string> us03();
    std::vector<std::string> us04();
    std::vector<std::string> us05();
    std::vector<std::string> us06();
    
    //sprint2
    std::vector<std::string> us07();
    std::vector<std::string> us09();
    std::vector<std::string> us10();
    std::vector<std::string> us12();
    std::vector<std::string> us14();
    std::vector<std::string> us21();

    //sprint3
    std::vector<std::string> us22();
    std::vector<std::string> us23();
    std::vector<std::string> us27();
    std::vector<std::string> us29();
    std::vector<std::string> us30();
    std::vector<std::string> us33();
    
    //sprint4
    std::vector<std::string> us35();
    std::vector<std::string> us36();
    std::vector<std::string> us38();
    std::vector<std::string> us39();
    std::vector<std::string> us40();
    std::vector<std::string> us42();
    

};


#endif //NEW2_REPOSITORY_H
