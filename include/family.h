#ifndef FAMILY_H
#define FAMILY_H

#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

class Family{
/** Family
 *  
 *  1. Any family has one default value set for each attributes if the parser does not give the parameter
 *      e.g. No divorce date is given from the parser
 *           then the default divorce date is "NA"
 * 
 *  2. Any date format is "YYYY-MM-DD"
 * 
 * 
 * 
    \todo finish the following functions: setMarrDate(), setDivDate(), setHusId(), setHusName(), setWifeId(),setWifeName(),setChildrenId()

*/
private:
std::string id;
std::time_t marr_d; // marr_d for married date, default value is NA
std::time_t div_d; // div_d for divorced date, default value is NA

std::string hus_id;
std::string hus_name;
std::string wife_id;
std::string wife_name;

std::vector<std::string> children_id;
std::time_t transfer_sting_to_time(std::string str);

public:
Family(std::string id1);
~Family();

void setID(std::string id);
void setMarrDate(std::string marr_d);
void setDivDate(std::string div_d);
void setHusID(std::string hus_id);
void setWifeID(std::string wife_id);
void setHusName(std::string hus_id);
void setWifeName(std::string wife_id);
void setChildID(std::string child_id);

std::string getID();
std::string getMarrDate();
std::string getDivDate();
std::string getHusID();
std::string getHusName();
std::string getWifeID();
std::string getWifeName();
std::string getChildrenList();

};

#endif