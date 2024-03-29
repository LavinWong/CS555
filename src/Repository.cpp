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

std::string Repository::getIndividualSex(std::string indi_id) {
    for (auto indi: indiList){
        if (indi.getID() == indi_id){
            return indi.getGender();
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
		std::string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}
 
	return res;
}

std::string Repository::getBirthByID(std::string ID) {
    for (auto indi: indiList) {
        if (indi.getID() == ID) {
            std::string birth = indi.getBday();
            return birth;
        }
    }
}

bool Repository::compareAge(std::string b1, std::string b2, std::string sex) {
    if (stoi(b2.substr(0, 4)) > stoi(b1.substr(0, 4))) {
        return false;
    }
    if (sex == "F") {
        if (((stoi(b1.substr(0, 4)) - stoi(b2.substr(0, 4))) >= 60) &&
            (stoi(b2.substr(5, 2)) < stoi(b1.substr(5, 2))))
            return false;
        else if (((stoi(b1.substr(0, 4)) - stoi(b2.substr(0, 4))) == 60) &&
            (stoi(b2.substr(5, 2)) > stoi(b1.substr(5, 2))))
            return false;
        else
            return true;
    }
    else {
        if (((stoi(b1.substr(0, 4)) - stoi(b2.substr(0, 4))) >= 80) &&
            (stoi(b2.substr(5, 2)) < stoi(b1.substr(5, 2))))
            return false;
        else if (((stoi(b1.substr(0, 4)) - stoi(b2.substr(0, 4))) == 80) &&
            (stoi(b2.substr(5, 2)) > stoi(b1.substr(5, 2))))
            return false;
        else   
            return true;
    }
}

bool Repository::checkFutureBirthOfLive(std::string currentTime, std::string indiBirth) {
    int currentDate = stoi(currentTime.substr(8, 2));
    int currentMonth = stoi(currentTime.substr(5, 2));
    int currentYear = stoi(currentTime.substr(0, 4));
    int indiDate = stoi(indiBirth.substr(8, 2));
    int indiMonth = stoi(indiBirth.substr(5, 2));
    if (currentMonth == 1) {
        if ((indiMonth == currentMonth) && (indiDate > currentDate))
            return true;
        else if ((indiMonth == (currentMonth+1)) && (indiDate <= (currentDate-1)))
            return true;
        else if (indiMonth == (currentMonth+2)) {
            if (((currentYear % 4) == 0) && (((currentYear % 100) != 0) || ((currentYear % 400) == 0))) {
                if ((indiDate <= ((31 - currentDate + 30) - 29)) && ((31 - currentDate + 30) > 29))
                    return true; 
            }
            else {
                if ((indiDate <= ((31 - currentDate + 30) - 28)) && ((31 - currentDate + 30) > 28))
                    return true; 
            }
        } 
    }
    else if (currentMonth == 2) {
        if (((currentYear % 4) == 0) && (((currentYear % 100) != 0) || ((currentYear % 400) == 0))) {
            if ((indiMonth == currentMonth) && (indiDate > currentDate))
                return true;
            else if ((indiMonth == (currentMonth+1)) && (indiDate <= (currentDate+1)))
                return true;
        }
        else {
            if ((indiMonth == currentMonth) && (indiDate > currentDate))
                return true;
            else if ((indiMonth == (currentMonth+1)) && (indiDate <= (currentDate+2)))
                return true;
        }
    }
    else if ((currentMonth % 2) != 0) {
        if ((indiMonth == currentMonth) && (indiDate > currentDate))
            return true;
        else if ((indiMonth == (currentMonth+1)) && (indiDate <= currentDate))
            return true;
    }
    else if ((currentMonth % 2) == 0) {
        if ((indiMonth == currentMonth) && (indiDate > currentDate))
            return true;
        else if ((indiMonth == (currentMonth+1)) && (indiDate <= (currentDate-1)))
            return true;
    }
    return false;
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
    std::vector<std::string> result = {};
    for (auto indi: indiList){
        if (indi.getAge()!="NA"){
            if (indi.getAgeInt()>150){
                if (std::find(result.begin(), result.end(), indi.getID())==result.end()){
                    result.push_back(indi.getID());
                }else{
                    // do nothing
                }
                std::cout<< "ERROR: INDIVIDUAL: US07: "+indi.getID()+"'s Age "+indi.getAge()+" is too old, over 150 yrs old! "<<std::endl;
            }
        }
    }
    return result;
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
        if (fam.getMarr() == "NA")
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
	    if(husBday!="NA" && wifeBday!="NA")
	    {
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
            	else if(((year3-year1)==14 && month3>month1) || ((year3-year1)==14 && month3==month1 && day3>=day1))
		{
                	if(std::find(result.begin(), result.end(), fam.getHusID())==result.end())
                	{
                    		result.push_back(fam.getHusID());
                	}
                }
            	if((year3-year2)>14)
            	{
                	if(std::find(result.begin(), result.end(), fam.getWifeID())==result.end())
                	{
                    		result.push_back(fam.getWifeID());
                	}
            	}
            	else if(((year3-year2)==14 && month3>month2) || ((year3-year2)==14 && month3==month2 && day3>=day2))
            	{
                	if(std::find(result.begin(), result.end(), fam.getWifeID())==result.end())
                	{
                    		result.push_back(fam.getWifeID());
                	}
            	}
	    }
        }
        
    }
    
    return result;
    
}

std::vector<std::string> Repository::us12() {
    std::vector<std::string> result = {};
    for (auto fam: famList) {
        if ((fam.getWifeID() == "NA") || (fam.getHusID() == "NA")) {
            if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                result.push_back("NA");
            } else {
                // do nothing
            }
            std::cout << "ERROR: FAMILY: US12: " + fam.getID() + ": The mother's or father's ID is not provided." << std::endl;
            continue;
        }
        std::string momBirth = getBirthByID(fam.getWifeID());
        if (momBirth == "NA") {
            if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                result.push_back("NA");
            } else {
                // do nothing
            }
            std::cout << "ERROR: FAMILY: US12: " + fam.getID() + ": The mother's birth is not provided." << std::endl;
            continue;
        }
        std::string faBirth = getBirthByID(fam.getHusID());
        if (faBirth == "NA") {
            if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                result.push_back("NA");
            } else {
                // do nothing
            }
            std::cout << "ERROR: FAMILY: US12: " + fam.getID() + ": The father's birth is not provided." << std::endl;
            continue;
        }
        std::vector<std::string> childList = fam.getChildrenVector();
        for (auto child: childList) {
            std::string childBirth = getBirthByID(child);
            if (childBirth == "NA") {
                if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                    result.push_back("NA");
                } else {
                    // do nothing
                }
                std::cout << "ERROR: FAMILY: US12: " + fam.getID() + ": The child's birth is not provided." << std::endl;
                continue;
            }
            if (compareAge(childBirth, momBirth, "F") == false) {
                if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                    result.push_back(fam.getID());
                } else {
                    // do nothing
                }
                std::cout << "ERROR: FAMILY: US12: " + fam.getID() + ": The mother is more than 60 years older than this children: " + child << std::endl;
            }
            if (compareAge(childBirth, faBirth, "M") == false) {
                if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                    result.push_back(fam.getID());
                } else {
                    // do nothing
                }
                std::cout << "ERROR: FAMILY: US12: " + fam.getID() + ": The father is more than 80 years older than this children: " + child << std::endl;
            }
        }
    }
    return result;
}

std::vector<std::string> Repository::us14() {
    std::vector<std::string> result = {};
    std::vector<std::string> childs = {};
    std::string childBirth;
    int c = 0;
    int max = 0;
    for (auto fam: famList) {
        std::vector<std::string> childList = fam.getChildrenVector();
        if (childList.size() == 0) {
            if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                result.push_back("NA");
            } else {
                // do nothing
            }
            std::cout << "ERROR: FAMILY: US14: " + fam.getID() + ": The child's information is not provided." << std::endl;
            continue;
        }
        for (auto child: childList) {
            childBirth = getBirthByID(child);
            childs.push_back(childBirth);
            c++;
        }
        int tempArray[c];
        c = 0;
        for (auto child1: childList) {
            for (auto count: childs) {
                if (count == child1) {
                    tempArray[c]++;
                    if (tempArray[c] > max)
                        max = tempArray[c];
                }
                if (max > 6) {
                    if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                        result.push_back(fam.getID());
                    } else {
                        // do nothing
                    }
                    std::cout << "ERROR: FAMILY: US14: " + fam.getID() + ": There are more than five siblings born at the same time." << std::endl;
                    return result;
                }
                c++;
            }
        }
        c = 0;
        max = 0;
    }
    return result;
}

std::vector<std::string> Repository::us21() {
    // todo
    std::vector<std::string> result = {};
    for (auto fam: famList){
        if (fam.getHusID()!="NA" && fam.getWifeID()!="NA"){
            if (getIndividualSex(fam.getHusID())!="M"){
                if(std::find(result.begin(), result.end(), fam.getID())==result.end()){
                    result.push_back(fam.getID());
                }else {
                    // do nothing
                }
                std::cout<< "ERROR: FAMILY: US21: "+fam.getID()+": Husband "+fam.getHusID()+" is not Male! "<<std::endl;
            }
            if (getIndividualSex(fam.getWifeID())!="F"){
                if(std::find(result.begin(), result.end(), fam.getID())==result.end()){
                    result.push_back(fam.getID());
                }else {
                    // do nothing
                }
                std::cout<< "ERROR: FAMILY: US21: "+fam.getID()+": Wife "+fam.getWifeID()+" is not Female! "<<std::endl;
            }
        }
    }
    return result;
}

std::vector<std::string> Repository::us22(){
    // todo
    std::vector<std::string> result = {};
    for (auto fam: famList)
    {
    	std::string famid;
	famid = fam.getID();
	int i = 0;
	for (auto fam: famList)
	{
	    if(famid == fam.getID())
	    {
	        i++;
	    }
	}
	if(i==1)
	{
	    if(std::find(result.begin(), result.end(), fam.getID())==result.end())
	    {
                result.push_back(fam.getID());
	    }
	}
	else
	{
	    std::cout<< "ERROR: FAMILY: US22: "+fam.getID()+" is not unique! "<<std::endl;
	}
    }
    for (auto indi: indiList)
    {
    	std::string indiId;
	indiId = indi.getID();
	int i = 0;
	for (auto indi: indiList)
	{
	    if(indiId == indi.getID())
	    {
	        i++;
	    }
	}
	if(i==1)
	{
	    if(std::find(result.begin(), result.end(), indi.getID())==result.end())
	    {
                result.push_back(indi.getID());
	    }
	}
	else
	{
	    std::cout<< "ERROR: FAMILY: US22: "+indi.getID()+" is not unique! "<<std::endl;
	}
    }
    return result;
}

std::vector<std::string> Repository::us23(){
    // todo
    std::vector<std::string> result = {};
    for (auto indi: indiList)
    {
	std::string p_name;
	std::string p_birth;
	p_name = indi.getName();
	p_birth = indi.getBday();
	int i = 0;
	for (auto indi: indiList)
    	{
	    if(indi.getName() != "NA" &&  indi.getBday() != "NA")
	    {
		if(p_name == indi.getName() && p_birth == indi.getBday())
		{
		    i++;
		}
	    }
	} 
	if(i==1)
	{
	    if(std::find(result.begin(), result.end(), indi.getID())==result.end())
	    {
                result.push_back(indi.getID());
	    }
	}
	else if(p_name == "NA" ||  p_birth == "NA")
	{
	     std::cout<< "ERROR: FAMILY: US23: "+indi.getID()+" is not have name or birthday! "<<std::endl;
	}
	else
	{
	    std::cout<< "ERROR: FAMILY: US23: "+indi.getID()+" is not have unique name and birthday! "<<std::endl;
	}
    }
    return result;
}

std::vector<std::string> Repository::us27(){
    // todo
    std::vector<std::string> result = {};
    for (auto indi: indiList){
        if(std::find(result.begin(), result.end(), indi.getID())==result.end()){
            result.push_back(indi.getID());
            result.push_back(indi.getAge());
            std::cout<< "LIST: INDIVIDUAL: US27: "+indi.getID()+": Age: "+indi.getAge()+". "<<std::endl;
        }else {
            // do nothing
        }
    }
    return result;
}

std::vector<std::string> Repository::us29(){
    // todo
    std::vector<std::string> result = {};
    for (auto indi: indiList){
        if (indi.getDday()!="NA"){
            if(std::find(result.begin(), result.end(), indi.getID())==result.end()){
                result.push_back(indi.getID());
                std::cout<< "LIST: INDIVIDUAL: US29: "+indi.getID()+": Age: "+indi.getAge()+" is Dead. The Death day is: "+indi.getDday()<<std::endl;
            }else {
                // do nothing
            }
        }
    }
    return result;
}

std::vector<std::string> Repository::us30() {
    std::vector<std::string> result = {};
    std::vector<std::string> peopleList = {};
    for (auto fam: famList) {
        std::string husb = fam.getHusName();
        std::string wife = fam.getWifeName();
        if ((husb != "NA") && (wife != "NA")) {
            if (fam.getDiv() == "NA") {
                peopleList.push_back(fam.getHusID());
                peopleList.push_back(fam.getWifeID());
            }
            else {
                if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                    result.push_back(fam.getID());
                } 
                else {
                    // do nothing
                }
                std::cout << "ERROR: FAMILY: US30: " + fam.getID() + ": The family has divorced people." << std::endl;
            }
        }
        else {
            if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                    result.push_back(fam.getID());
            } 
            else {
                // do nothing
            }
            std::cout << "ERROR: FAMILY: US30: " + fam.getID() + ": The family has no husband or wife." << std::endl;
        }
    }

    std::cout << "Married People:" << std::endl;
    int c = 0;
    for (auto people: peopleList) {
        if (c != 0)
            std::cout << ", ";
        std::cout << people;
        c = 1;
    }
    std::cout << std::endl;

    return result;
}

std::vector<std::string> Repository::us33() {
    std::vector<std::string> result = {};
    std::vector<std::string> peopleList = {};
    std::string husbAlive;
    std::string wifeAlive;
    std::time_t now;
    time(&now);
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    strftime(output,20,"%F",timeinfo);
    std::string out2 = output;

    for (auto fam: famList) {
        if (fam.getChildrenList() != "{ }") {
            std::vector<std::string> childList = fam.getChildrenVector();
            std::string husb = fam.getHusName();
            std::string wife = fam.getWifeName();
            if ((husb != "NA") && (wife != "NA")) {
                std::string husbID = fam.getHusID();
                std::string wifeID = fam.getWifeID();
                for (auto indi: indiList) {
                    if (indi.getID() == husbID)
                        husbAlive = indi.getAlive();
                }
                for (auto indi: indiList) {
                    if (indi.getID() == wifeID)
                        wifeAlive = indi.getAlive();
                }
                if ((husbAlive == "False") && (wifeAlive == "False")) {
                    for (auto childs: childList) {
                        for (auto indi: indiList) {
                            if (indi.getID() == childs) {
                                std::string birth = indi.getBday();
                                if (birth == "NA") {
                                    std::cout << "ERROR: FAMILY: US33: " + indi.getID() + ": The birth information is not provided." << std::endl;
                                    continue;
                                }
                                int ages = stoi(out2.substr(0, 4)) - stoi(birth.substr(0, 4));
                                if (stoi(out2.substr(5, 2)) < stoi(birth.substr(5, 2)))
                                    ages = ages - 1;
                                if (ages < 18) {
                                    peopleList.push_back(childs);
                                }
                                else {
                                    if (std::find(result.begin(), result.end(), "NA") == result.end()) {
                                        result.push_back("NA");
                                    } 
                                    else {
                                        // do nothing
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    std::cout << "ERROR: FAMILY: US33: " + fam.getID() + ": The family has no children who is orphane." << std::endl;
                }
            }
            else {
                std::cout << "ERROR: FAMILY: US33: " + fam.getID() + ": The family has no husband or wife." << std::endl;
            }
        }
        else {
            std::cout << "ERROR: FAMILY: US33: " + fam.getID() + ": The family has no children." << std::endl;
        }
    }

    std::cout << "Orphaned Children:" << std::endl;
    if (peopleList.empty())
        std::cout << "NA" << std::endl;
    else {
        int c = 0;
        for (auto people: peopleList) {
            if (c != 0)
                std::cout << ", ";
            std::cout << people;
            c = 1;
        }
        std::cout << std::endl;
    }

    return result;
}

std::vector<std::string> Repository::us35(){
    // todo
    std::time_t now;
    time(&now);
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    strftime(output,20,"%F",timeinfo);
    std::string out2 = output;
    std::vector<std::string> result = {};
    for (auto indi: indiList)
    {
        if (indi.getBday() != "NA")
	{
	    std::string bday;
	    bday = indi.getBday();
	    std::vector<std::string> date1 = split(bday, "-");
            std::vector<std::string> date2 = split(out2, "-");

            int year1 = std::stoi(date1[0]);
            int year2 = std::stoi(date2[0]);
            int month1 = std::stoi(date1[1]);
            int month2 = std::stoi(date2[1]);	
            int day1 = std::stoi(date1[2]);
            int day2 = std::stoi(date2[2]);
            
	    if (year1==year2 && month2==month1 && (day2-day1) <= 30)
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
	    if (year1==year2 && (month2-month1) == 1)
	    {
		if((month2 % 2) == 0 && month2 < 7 && month2 != 2)
		{
		    if((day2+30-day1)>=0)
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
		}
		if((month2 % 2) == 1 && month2 <= 7)
		{
		    if((day2+31-day1)>=0)
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
		}
		if((month2 % 2) == 0 && month2 > 7)
		{
		    if((day2+31-day1)>=0)
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
		}
		if((month2 % 2) == 1 && month2 > 7)
		{
		    if((day2+30-day1)>=0)
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
		}
		if(month2 ==2)
		{
		    if((day2+28-day1)>=0)
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
		}
			
                
            }
        }
	else	
	{
            std::cout<< "ERROR: INDIVIDUAL: US01: "+indi.getID()+": Birthday is not exist."<<std::endl;
	}
    }
    return result;
}

std::vector<std::string> Repository::us36(){
    // todo
    std::time_t now;
    time(&now);
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    strftime(output,20,"%F",timeinfo);
    std::string out2 = output;
    std::vector<std::string> result = {};
    for (auto indi: indiList)
    {
        if (indi.getDday() != "NA")
	{
	    std::string dday;
	    dday = indi.getDday();
	    std::vector<std::string> date1 = split(dday, "-");
            std::vector<std::string> date2 = split(out2, "-");

            int year1 = std::stoi(date1[0]);
            int year2 = std::stoi(date2[0]);
            int month1 = std::stoi(date1[1]);
            int month2 = std::stoi(date2[1]);	
            int day1 = std::stoi(date1[2]);
            int day2 = std::stoi(date2[2]);
            
	    if (year1==year2 && month2==month1 && (day2-day1) <= 30)
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
	    if (year1==year2 && (month2-month1) == 1)
	    {
		if((month2 % 2) == 0 && month2 < 7 && month2 != 2)
		{
		    if((day2+30-day1)>=0)
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
		}
		if((month2 % 2) == 1 && month2 <= 7)
		{
		    if((day2+31-day1)>=0)
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
		}
		if((month2 % 2) == 0 && month2 > 7)
		{
		    if((day2+31-day1)>=0)
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
		}
		if((month2 % 2) == 1 && month2 > 7)
		{
		    if((day2+30-day1)>=0)
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
		}
		if(month2 ==2)
		{
		    if((day2+28-day1)>=0)
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
		}
			
                
            }
        }
	else	
	{
            std::cout<< "ERROR: INDIVIDUAL: US01: "+indi.getID()+": Death date is not exist."<<std::endl;
	}
    }
    return result;
}

std::vector<std::string> Repository::us38() {
    std::vector<std::string> result = {};
    std::vector<std::string> peopleList = {};
    std::time_t now;
    time(&now);
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    strftime(output,20,"%F",timeinfo);
    std::string currentTime = output;
    for (auto indi: indiList) {
        if (indi.getAlive() == "True") {
            if (indi.getBday() == "NA") {
                std::cout << "ERROR: INDIVIDUAL: US38: "+indi.getID()+": Birth date is not exist."<<std::endl;
                continue;
            }
            std::string indiBirth = indi.getBday();
            bool temp = checkFutureBirthOfLive(currentTime, indiBirth);
            if (temp == true) {
                peopleList.push_back(indi.getID());
                if (std::find(result.begin(), result.end(), indi.getID()) == result.end()) {
                    result.push_back(indi.getID());
                } 
                else {
                    // do nothing
                }
            }
        }
        else {
            std::cout << "ERROR: INDIVIDUAL: US38: "+indi.getID()+": The individual is not alive."<<std::endl;
        }
    }
    std::cout << "Living people whose birthdays occur in the next 30 days:" << std::endl;
    if (peopleList.empty())
        std::cout << "NA" << std::endl;
    else {
        int c = 0;
        for (auto people: peopleList) {
            if (c != 0)
                std::cout << ", ";
            std::cout << people;
            c = 1;
        }
        std::cout << std::endl;
    }
    return result; 
}

std::vector<std::string> Repository::us39() {
    std::vector<std::string> result = {};
    std::vector<std::string> peopleList = {};
    std::time_t now;
    time(&now);
    char output[20];
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    strftime(output,20,"%F",timeinfo);
    std::string currentTime = output;
    for (auto fam: famList) {
        std::string husbID = fam.getHusID();
        std::string wifeID = fam.getWifeID();
        std::string husbAlive;
        std::string wifeAlive;
        if ((husbID != "NA") && (wifeID != "NA")) {
            if (fam.getDiv() == "NA") {
                for (auto indi: indiList) {
                    if (indi.getID() == husbID) {
                        husbAlive = indi.getAlive();
                    }
                    else if (indi.getID() == wifeID) {
                        wifeAlive = indi.getAlive();
                    }
                }
                if ((husbAlive == "True") && (wifeAlive == "True")) {
                    std::string marrBirth = fam.getMarr();
                    if (marrBirth == "NA") {
                        std::cout << "ERROR: FAMILY: US39: " + fam.getID() + ": The married date is not provided." << std::endl;
                        continue;
                    }
                    bool temp = checkFutureBirthOfLive(currentTime, marrBirth);
                    if (temp == true) {
                        peopleList.push_back(husbID);
                        peopleList.push_back(wifeID);
                        if (std::find(result.begin(), result.end(), fam.getID()) == result.end()) {
                            result.push_back(fam.getID());
                        } 
                        else {
                            // do nothing
                        }
                    }
                }
                else {
                    std::cout << "ERROR: FAMILY: US39: " + fam.getID() + ": One of the couple is not alive." << std::endl;
                }
            }
            else {
                std::cout << "ERROR: FAMILY: US39: " + fam.getID() + ": The family has divorced people." << std::endl;
            }
        }
        else {
            std::cout << "ERROR: FAMILY: US39: " + fam.getID() + ": The family has no husband or wife." << std::endl;
        }
    }

    std::cout << "Living couples whose marriage anniversaries occur in the next 30 days:" << std::endl;
    int c = 0;
    for (auto people: peopleList) {
        if (c != 0)
            std::cout << ", ";
        std::cout << people;
        c = 1;
    }
    std::cout << std::endl;

    return result;
}

std::vector<std::string> Repository::us40(){
    // todo
    std::vector<std::string> result = {"NA"};
    for(auto indi: indiList){
        std::cout<< "US40: Individual: "+indi.getID()+" at line "+std::to_string(indi.line)<<std::endl;
    }
    for(auto fam: famList){
        std::cout<< "US40: Family: "+fam.getID()+" at line "+std::to_string(fam.line)<<std::endl;
    }
    return result;
}

std::vector<std::string> Repository::us42(){
    // todo
    std::vector<std::string> result = {};
    for(auto indi: indiList){
        if ((indi.hasBDate && indi.getBday() == "NA") || (indi.hasDDate && indi.getDday()=="NA")){
            if(std::find(result.begin(), result.end(), indi.getID())==result.end()){
                result.push_back(indi.getID());
                std::cout<< "ERROR: INDIVIDUAL: US42: "+indi.getID()+": has invalid date data "<<std::endl;
            }else {
                // do nothing
            }
        }
    }
    for(auto fam: famList){
        if ((fam.hasMDate && fam.getMarr() == "NA") || (fam.hasDDate && fam.getDiv()=="NA")){
            if(std::find(result.begin(), result.end(), fam.getID())==result.end()){
                result.push_back(fam.getID());
                std::cout<< "ERROR: FAMILY: US42: "+fam.getID()+": has invalid date data "<<std::endl;
            }else {
                // do nothing
            }
        }
    }
    return result;
}

