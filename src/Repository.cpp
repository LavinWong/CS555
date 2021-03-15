//
// Created by Qi Zhao on 3/5/21.
//

#include "Repository.h"
#include "parser.h"
#include <algorithm>


Repository::Repository() {
    std::string filepath = "src/GEDCOM.ged";
    parser(filepath,&famList,&indiList);
    setHusWifeName();
}

Repository::~Repository() {

}

void Repository::print_table() {
    std::cout<<"Individuals"<<std::endl;
    VariadicTable<std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string> vt({"ID", "Name", "Gender", "Birthday", "Age", "Alive", "Death", "Child", "Spouse"});  // todo edit the table head

    for (auto indi: indiList){
        vt.addRow(indi.getID(), indi.getName(), indi.getGender(), indi.getBday(), indi.getAge(), indi.getAlive(), indi.getDday(), indi.getFamcList(), indi.getFamsList());
    }
    vt.print(std::cout);

    std::cout<<"Families"<<std::endl;
    VariadicTable<std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string> vt2({"ID", "Married", "Divorced", "Husband ID", "Husband Name", "Wife ID", "Wife Name", "Children"});  // todo edit the table head

    for (auto fam: famList){
        vt2.addRow(fam.getID(), fam.getMarr(), fam.getDiv(), fam.getHusID(), fam.getHusName(), fam.getWifeID(), fam.getWifeName(), fam.getChildrenList());
    }
    vt2.print(std::cout);
}

std::string Repository::getIndividualName(std::string indi_id) {
    for (auto indi: indiList){
        if (indi.getID() == indi_id){
            return indi.getName();
        }
    }
    return "NA";
}

void Repository::setHusWifeName() {
    int size = famList.size();
    for (int index = 0; index<size; index++){
        std::string hus_id = famList[index].getHusID();
        std::string wife_id = famList[index].getWifeID();
        if (hus_id != "NA"){
            famList[index].setHusName(getIndividualName(hus_id));
        }else{
            famList[index].setHusName("NA");
        }
        if (wife_id != "NA"){
            famList[index].setWifeName(getIndividualName(wife_id));
        }else{
            famList[index].setWifeName("NA");
        }
    }
}

// add us01 to us06 here 

std::vector<std::string> Repository::us01() {
    // todo
    std::time_t now;
    time(&now);
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    strftime(output,20,"%F",timeinfo);
    std::string out2 = output;
    std::vector<std::string> result = {};

    for (auto indi: indiList){
        if (indi.getBday() != "NA"){
            if (out2 < indi.getBday()){
                if(std::find(result.begin(), result.end(), indi.getID())==result.end()){
                    result.push_back(indi.getID());
                    // print error message 
                }else {
                    // do nothing
                }
                std::cout<< "ERROR: INDIVIDUAL: US01: "+indi.getID()+": Birthday "+indi.getBday()+" occurs in the future."<<std::endl;
            }
        }

        if (indi.getDday() != "NA"){
            if (out2 < indi.getDday()){
                // todo
                if (std::find(result.begin(), result.end(), indi.getID())==result.end()){
                    result.push_back(indi.getID());
                }else{
                    // do nothing
                }
                std::cout<< "ERROR: INDIVIDUAL: US01: "+indi.getID()+": Death "+indi.getDday()+" occurs in the future."<<std::endl;
            }
        }
    }

    for(auto fam: famList){
        if (fam.getMarr() != "NA"){
            if (out2 < fam.getMarr()){
                if(std::find(result.begin(), result.end(), fam.getID())==result.end()){
                    result.push_back(fam.getID());
                }else {
                    // do nothing
                }
                std::cout<< "ERROR: FAMILY: US01: "+fam.getID()+": Marriage "+fam.getMarr()+" occurs in the future."<<std::endl;
            }
        }

        if (fam.getDiv() != "NA"){
            if (out2 < fam.getDiv()){
                if(std::find(result.begin(), result.end(), fam.getID())==result.end()){
                    result.push_back(fam.getID());
                }else {
                    // do nothing
                }
                std::cout<< "ERROR: FAMILY: US01: "+fam.getID()+": Divorce "+fam.getDiv()+" occurs in the future."<<std::endl;
            }
        }
    }
    return result;
}

std::vector<std::string> Repository::us02() {
    // todo
    std::vector<std::string> result = {};
    for (auto indi: indiList)
    {
        if (indi.getBday()!="NA")
        {
            std::string personID;
            personID = indi.getID();
            for (auto fam: famList)
            {
                std::string husBday;
                std::string wifeBday;
                if (fam.getMarr()!="NA")
                {
                    if (personID == fam.getHusID())
                    {
                        husBday = indi.getBday();
                    }
                    else if (personID == fam.getWifeID())
                    {
                        wifeBday = indi.getBday();
                    }
                }
            
                if (husBday < fam.getMarr() || wifeBday < fam.getMarr())
                {
                    if(std::find(result.begin(), result.end(), indi.getID())==result.end())
                    {
                        result.push_back(indi.getID());
                    }
                    else
                    {
                     // do nothing
                    }
                }
            }
        }
    }
    return result;
}

std::vector<std::string> Repository::us03() {
    // todo
    std::vector<std::string> result = {};
    for (auto indi: indiList)
    {
        std::string personID;
        if (indi.getBday()!="NA")
        {
            if (indi.getDday()!="NA")
            {
                if(indi.getBday()<indi.getDday())
                {
                    if (std::find(result.begin(), result.end(), indi.getID())==result.end())
                    {
                        result.push_back(indi.getID());
                    }
                    else
                    {
                        // do nothing
                    }
                }
            }
        }
    }
    return result;
    
}

void Repository::us04() {
    // todo
}

void Repository::us05() {
    // todo
}

std::vector<std::string> Repository::us06() {
    // todo
    std::vector<std::string> result = {};
    for (auto fam: famList){
        if (fam.getDiv()!="NA"){
            std::string husDday;
            std::string wifeDday;
            for (auto indi: indiList){
                if (indi.getID() == fam.getHusID()){
                    husDday = indi.getDday();
                }else if (indi.getID() == fam.getWifeID()){
                    wifeDday = indi.getDday();
                }
            }
            if (husDday < fam.getDiv() || wifeDday < fam.getDiv()) {
                if(std::find(result.begin(), result.end(), fam.getID())==result.end()){
                    result.push_back(fam.getID());
                }else {
                    // do nothing
                }
            }

        }
    }
    return result;
}