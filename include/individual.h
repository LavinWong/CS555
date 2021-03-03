#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

#include "family.h"


class Individual{
/** Individual
 *  
 *  1. Any individual has one default value set for each attributes if the parser does not give the parameter
 *      e.g. No death date is given from the parser
 *           then the default death date is "NA"
 * 
 *  2. Any date format is "YYYY-MM-DD"
 * 
 * 
 * 
    \todo finish the following functions: setName(), setGender(), setBday, setAlive(), setDday(), getChildId(), getSpouseId()
*/
private:

std::string id;
std::string name;
std::string gender;
std::time_t bday; // bday for birthday date
bool alive;
std::time_t dday; // dday for death date
std::vector<std::string> famcList;
std::vector<std::string> famsList;

std::time_t transfer_sting_to_time(std::string str);

public:
Individual(std::string id1);
~Individual();

void setID(std::string id);
void setName(std::string name);
void setGender(std::string gender);
void setBday(std::string bday);
void setDday(std::string dday);
void setAlive();
void setFamcList(std::string famc_id);
void setFamsList(std::string fams_id);


std::string getID();
std::string getName();
std::string getGender();
std::string getBday();
std::string getAlive();
std::string getDday();
std::string getFamcList();
std::string getFamsList();

};

#endif