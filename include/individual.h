#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

#include <family.h>


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
char gender;
std::time_t bday; // bday for birthday date
bool alive;
std::time_t dday; // dday for death date
std::vector<std::string> child_id;
std::vector<std::string> spouse_id;

public:
Individual(std::string id1);
~Individual();

void setName(std::string name);
void setGender(char gender);
void setBday(std::time_t bday);
void setDday(std::time_t dday);
void setAlive();
void getChildId(std::vector<Family> family_list);

};
