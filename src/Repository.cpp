//
// Created by Qi Zhao on 3/5/21.
//

#include "Repository.h"
#include "parser.h"

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

void Repository::us01() {
    // todo
}

void Repository::us02() {
    // todo
}

void Repository::us03() {
    // todo
}

void Repository::us04() {
    // todo
}

void Repository::us05() {
    // todo
}

void Repository::us06() {
    // todo
}