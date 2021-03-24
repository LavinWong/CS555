//
// Created by Qi Zhao on 3/5/21.
//

#include "Repository.h"
#include "parser.h"
#include <algorithm>
#include <string.h>

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

std::vector<std::string> split(const std::string& str, const std::string& delim) 
{
	std::vector<std::string> res;
	if("" == str) return res;
	char * strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) 
       {
		string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}
 
	return res;
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

std::vector<std::string> Repository::us02()
{
    // todo
    std::vector<std::string> result = {};
    for (auto indi: indiList)
    {
        if (indi.getBday() != "NA")
        {
            std::string husBday;
            std::string wifeBday;
            std::string Marrday;
            for(auto fam: famList)
            {
                if (fam.getMarr()!="NA")
                {
                   
                    if (indi.getID() == fam.getHusID())
                    {
                        husBday = indi.getBday();
                        Marrday = fam.getMarr();
                    }
                    else if (indi.getID() == fam.getWifeID())
                    {
                        wifeBday = indi.getBday();
                        Marrday = fam.getMarr();
                    }
                }
            
                
            }
            if(husBday < Marrday || wifeBday < Marrday)
            {
                if(std::find(result.begin(), result.end(), indi.getID())==result.end())
                {
                    result.push_back(indi.getID());
                    // print error message 
                }
                else
                {
                    // do nothing
                }
            }
            else if(Marrday=="")
            {
                std::cout<< "ERROR: INDIVIDUAL: US02: "+indi.getID()+": There is no currrect marryage date."<<std::endl;
            }
            else
            {
                 std::cout<< "ERROR: INDIVIDUAL: US02: "+indi.getID()+": Birthday "+indi.getBday()+" is later than marrage."<<std::endl;
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
        if (indi.getBday()!="NA")
        {
            std::string bday=indi.getBday();
            if (indi.getDday()!="NA")
            {
                std::string dday=indi.getDday();
                if(bday<dday)
                {
                    if (std::find(result.begin(), result.end(), indi.getID())==result.end())
                    {
                        result.push_back(indi.getID());
                    }
                    else
                    {
                        // do nothing
                    }
                    std::cout<< "ERROR: INDIVIDUAL: US03: "+indi.getID()+": Birthday "+indi.getBday()+" is later than death."<<std::endl;
                }
                else
                {
                    //std::cout<< "ERROR: INDIVIDUAL: US03: "+indi.getID()+": Birthday "+indi.getBday()+" is later than death."<<std::endl;
                }
            }
        }
    }
    return result;    
}

std::vector<std::string> Repository::us04() {
    std::vector<std::string> result = {};
    for (auto fam: famList) {
        //std::cout << fam.getDiv() << std::endl;
        if ((fam.getMarr() != "NA") && (fam.getDiv() != "NA")) {
            std::string marrTime;
            marrTime = fam.getMarr();
            std::string divTime;
            divTime = fam.getDiv();
            if (marrTime > divTime) {
                if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                    result.push_back(fam.getID());
                } else {
                    // do nothing
                }
                std::cout << "ERROR: FAMILY: US04: " + fam.getID() + ": Marriage " + fam.getMarr() + " occurs after divorce." << std::endl;
            }
        }
        else if ((fam.getMarr() == "NA") && (fam.getDiv() != "NA")) {
            std::cout << "ERROR: FAMILY: US04: " + fam.getID() + ": There is no married date provided." << std::endl;
        }
        else if ((fam.getMarr() != "NA") && (fam.getDiv() == "NA")) {
            std::cout << "ERROR: FAMILY: US04: " + fam.getID() + ": There is no divorced date provided." << std::endl;
        }
        else if ((fam.getMarr() == "NA") && (fam.getDiv() == "NA")) {
            std::cout << "ERROR: FAMILY: US04: " + fam.getID() + ": There is no married and divorced date provided." << std::endl;
        }
    }
    return result;
}

std::vector<std::string> Repository::us05() {
    std::vector<std::string> result = {};
    std::string husId = "";
    std::string wifeId = "";
    std::string husDday = "";
    std::string wifeDday = "";
    for (auto fam: famList) {
        if (fam.getMarr() != "NA") {
            std::string marriedTime = fam.getMarr();
            if (fam.getHusID() != "NA") {
                husId = fam.getHusID();
            }
            if (fam.getWifeID() != "NA") {
                wifeId = fam.getWifeID();
            }
            for (auto indi: indiList) {
                if (indi.getID() == husId) {
                    husDday = indi.getDday();
                }
                else if (indi.getID() == wifeId) {
                    wifeDday = indi.getDday();
                }
            }
            if ((husDday < marriedTime) || (wifeDday < marriedTime)) {
                if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                    result.push_back(fam.getID());
                } else {
                    // do nothing
                }
                std::cout << "ERROR: FAMILY: US05: " + fam.getID() + ": Death of either spouse in fam " + fam.getMarr() + " occurs before married." << std::endl;
            }
            else {
                if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                    result.push_back("NA");
                } else {
                    // do nothing
                }
            }
        }
        else {
            std::cout << "ERROR: FAMILY: US05: " + fam.getID() + ": There is no married date provided." << std::endl;
        }
    }
    return result;
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
                if (husDday < fam.getDiv())
                    std::cout<< "ERROR: FAMILY: US06: "+fam.getID()+": Divorce "+fam.getDiv()+" before the Husband death "+husDday<<std::endl;
                if (wifeDday < fam.getDiv())
                    std::cout<< "ERROR: FAMILY: US06: "+fam.getID()+": Divorce "+fam.getDiv()+" before the Wife death "+wifeDday<<std::endl;
            }

        }
    }
    return result;
}
std::vector<std::string> Repository::us07() {
    // todo
}
std::vector<std::string> Repository::us09() {
    // todo
    std::vector<std::string> result = {};
    for (auto fam: famList)
    {
        std::string husBday;
        std::string wifeBday;
        std::vector<std::string> childlist;
          
        for (auto indi: indiList)
        {
             if (indi.getID() == fam.getHusID())
             {
                husBday = indi.getBday();
             }
             else if (indi.getID() == fam.getWifeID())
             {
                wifeBday = indi.getBday();
             }      
        }

        if(fam.getChildrenVector().size()!=0)
        {   
            for (auto id:fam.getChildrenVector())
            {   
                //std::cout<<id<<std::endl;
                std::string childBday;
                for (auto indi: indiList)
                {
                    if (indi.getID() == id)
                    {
                        childBday = indi.getBday(); 
                    }
            
                    if(husBday < childBday && wifeBday < childBday) 
                    {
                        if(std::find(result.begin(), result.end(), id)==result.end())
                        {
                            result.push_back(id);
                        }
                        else 
                        {
                             // do nothing
                        }
                    }
                }
            }
        }
        
    }
    return result;  
}
std::vector<std::string> Repository::us10() {
    // todo
    std::vector<std::string> result = {};
    for (auto fam: famList)
    {
        std::string husBday;
        std::string wifeBday;
        std::string Marrday;
        if (fam.getMarr() != "NA")
        {
            std::cout << "ERROR: FAMILY: US10: " + fam.getID() + ": There is no married date provided." << std::endl;
        }
        else
        {
            for (auto indi: indiList)
            {
                if (indi.getID() == fam.getHusID())
                {
                    husBday = indi.getBday();
                }
                else if (indi.getID() == fam.getWifeID())
                {
                    wifeBday = indi.getBday();
                }      
            }
            Marrday = fam.getMarr();
            std::vector<std::string> date1 = split(husBday, "-");
            std::vector<std::string> date2 = split(wifeBday, "-");
            std::vector<std::string> date3 = split(Marrday, "-");
            int year1 = std::stoi(date1[0]);
            int year2 = std::stoi(date2[0]);
            int year3 = std::stoi(date3[0]);
            int month1 = std::stoi(date1[1]);
            int month2 = std::stoi(date2[1]);
            int month3 = std::stoi(date3[1]);
            int day1 = std::stoi(date1[2]);
            int day2 = std::stoi(date2[2]);
            int day3 = std::stoi(date3[2]);
            if((year3-year1)>14)
            {
                if(std::find(result.begin(), result.end(), fam.getHusID())==result.end())
                {
                    result.push_back(fam.getHusID());
                }
            }
            else if(((year3-year1)==14 && month3>month1) || ((year3-year1)==14 && month3=month1 && day3>=day1))
            {
                if(std::find(result.begin(), result.end(), fam.getHusID())==result.end())
                {
                    result.push_back(fam.getHusID());
                }
            }
            if((year2-year1)>14)
            {
                if(std::find(result.begin(), result.end(), fam.getWifeID())==result.end())
                {
                    result.push_back(fam.getWifeID());
                }
            }
            else if(((year2-year1)==14 && month2>month1) || ((year2-year1)==14 && month2=month1 && day2>=day1))
            {
                if(std::find(result.begin(), result.end(), fam.getWifeID())==result.end())
                {
                    result.push_back(fam.getWifeID());
                }
            }
        }
        
    }
    
    return result;
    
}
std::vector<std::string> Repository::us12() {
    // todo
}
std::vector<std::string> Repository::us14() {
    // todo
}
std::vector<std::string> Repository::us21() {
    // todo
}

