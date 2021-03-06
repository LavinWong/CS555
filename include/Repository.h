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
    void setHusWifeName();

    void print_table();
    std::vector<std::string> us01();
    std::vector<std::string> us02();
    std::vector<std::string> us03();
    std::vector<std::string> us04();
    std::vector<std::string> us05();
    std::vector<std::string> us06();
    

};


#endif //NEW2_REPOSITORY_H
