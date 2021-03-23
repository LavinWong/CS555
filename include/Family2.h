//
// Created by Qi Zhao on 3/5/21.
//

#ifndef NEW2_FAMILY2_H
#define NEW2_FAMILY2_H

#include <string>
#include <ctime>
#include <vector>

std::time_t str_to_t_time(std::string str);

class Family2 {
private:
    std::string id;
    std::time_t marr_d; // marr_d for married date, default value is NA
    std::time_t div_d; // div_d for divorced date, default value is NA

    std::string hus_id;
    std::string hus_name;
    std::string wife_id;
    std::string wife_name;

    std::vector<std::string> children_id;
public:
    Family2(std::string id1);
    ~Family2();

    std::string getID();
    void setID(std::string id2);
    std::string getMarr();
    void setMarr(std::string marr_d2);
    std::string getDiv();
    void setDiv(std::string div_d2);

    std::string getHusName();
    void setHusName(std::string hus_name2);
    std::string getHusID();
    void setHusID(std::string hus_id2);
    std::string getWifeName();
    void setWifeName(std::string wife_name2);
    std::string getWifeID();
    void setWifeID(std::string wife_id2);

    std::string getChildrenList();
    void setChildrenList(std::string child_id);

    std::vector<std::string> getChildrenVector();

};


#endif //NEW2_FAMILY2_H
