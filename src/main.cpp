#include <iostream>
#include <fstream>
#include <array>
#include <string>

#include "bprinter/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "family.h"
#include "individual.h"

#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif
// qis parser

using namespace std;
string* getOutPutString(string line);
string getValided(char level, string tag);
void test_bprinter(vector<Family> famList, vector<Individual> indiList);

int main(){
    ifstream gedFile;
    string line;
    int counter = 0;

    string* lineResult;

    bool indiFlag = false;
    bool famFlag = false;
    Family famBuff("Default");
    Individual indiBuff("Default");

    int dateFlag = 0; // 0 for No date, 1 for birt, 2 for deat, 3 for marr, 4 for div 

    vector<Individual> indiList;
    vector<Family> famList;

    gedFile.open("src/GEDCOM.ged"); // open ged file

    if (gedFile.is_open())
    {
        while(getline(gedFile, line)){
            lineResult = getOutPutString(line); // assign the return value to lineReuslt, contains each line's validTag, level, tag, and args
            if (*(lineResult+1) == "|Y|"){
                // check the line is valid or not, if valid continue
                if (*(lineResult+2) == "0"){
                    // create a new instance of individual or family class, and flush the exsisting instance to indiList or famList based on the type of the instance
                    if (*(lineResult+3) == "INDI" || *(lineResult+3) == "FAM"){
                        // flush buffer indi or fam
                        // clear all flag to its default value
                        if (famFlag){
                            famList.push_back(famBuff);
                            famFlag = false;
                        }
                        if (indiFlag){
                            indiList.push_back(indiBuff);
                            indiFlag = false;
                        }
                        indiFlag = false;
                        famFlag = false;
                        dateFlag = 0;

                        if (*(lineResult+3) == "INDI"){
                            // create new indi
                            // edit indiFlag
                            indiBuff.setID(*(lineResult+4));
                            indiFlag = true;
                        }else{
                            // create new fam
                            // edit famflag
                            famBuff.setID(*(lineResult+4));
                            famFlag = true;
                        }
                    }else{
                        // ignore other tag like NOTE, HEAD at level 0
                        continue;
                    }
                }else{
                    // handle level 1 and level 2 tag
                    // handle 
                    if (*(lineResult+3) == "BIRT" || *(lineResult+3) == "DEAT"
                        || *(lineResult+3) == "MARR"|| *(lineResult+3) == "DIV"){
                        // set dateFlag 
                        if (*(lineResult+3) == "BIRT"){
                            dateFlag = 1;
                        }else if(*(lineResult+3) == "DEAT"){
                            dateFlag = 2;
                        }else if (*(lineResult+3) == "MARR"){
                            dateFlag = 3;
                        }else if (*(lineResult+3) == "DIV"){
                            dateFlag = 4;
                        }
                    }
                    
                    // hadle date args according to the dateflag
                    if (*(lineResult+3) == "DATE"){
                        switch (dateFlag)
                        {
                        case 1:
                            indiBuff.setBday(*(lineResult+4));
                            break;
                        case 2:
                            indiBuff.setDday(*(lineResult+4));
                            break;
                        case 3:
                            famBuff.setMarrDate(*(lineResult+4));
                            break;
                        case 4:
                            famBuff.setMarrDate(*(lineResult+4));
                            break;
                        default:
                            break;
                        }
                        dateFlag = 0;
                    }

                    // full fill the tag (p.s. sexcept for 4 date fore tag)
                    string tag = *(lineResult+3);
                    string arg = *(lineResult+4);
                    if (tag == "NAME"){
                        indiBuff.setName(arg);
                    }else if (tag == "SEX"){
                        indiBuff.setGender(arg);
                    }else if (tag == "FAMC"){
                        indiBuff.setFamcList(arg);
                    }else if (tag == "FAMS"){
                        indiBuff.setFamsList(arg);
                    }else if (tag == "HUSB"){
                        famBuff.setHusID(arg);
                        famBuff.setHusName(arg);
                    }else if (tag == "WIFE"){
                        famBuff.setWifeID(arg);
                        famBuff.setWifeName(arg);
                    }else if (tag == "CHIL"){
                        famBuff.setChildID(arg);
                    }
                }
            }else{
                // if not valid, ignore line
                continue;
            }
        }
        gedFile.close();
    }
    else cout << "Unable to open file"<<endl; 

    test_bprinter(famList, indiList);
    // gedFile.close();
    return 0;
}


string* getOutPutString(string line_2){
    string line(line_2.begin(), line_2.end()-1);
    string outPut;
    char level;
    level = line[0];
    string outputString[4];     // output array for other tag, including all INVALID tag
    string outputStringD[3];    // output array for 4 VALID date Tag, BIRT, DEAT, DIV, MARR

    if (level == '1' || level == '2'){
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == string::npos || secBlank == string::npos){
            // only has one tag, no args
            // for example, 1 BIRT

            string first_tag (line.begin()+firstBlank+1, line.end());
            if (first_tag == "BIRT"|| first_tag =="DEAT"||first_tag =="MARR"||first_tag =="DIV"){
                outputStringD[0] = "|Y|";
                outputStringD[1] = "1";     // assume the level is '1', bad smell
                outputStringD[2] = first_tag;
                // outPut.append(1,level);
                // outPut += "|"+first_tag+"|Y|"; 
                return outputStringD;
            }else{
                outputString[0] = "|N|";
                return outputString;
                // outPut = "|N|"+line;
            }

        }else{
            // for any other level 1 tag
            // for example, 1 NAME Jenny

            string tag (line.begin()+firstBlank+1, line.begin()+secBlank);
            string argLine (line.begin()+secBlank+1, line.end());
            outPut.append(1,level);
            string validTag = getValided(level, tag);
            if (validTag == "|Y|"){
                // valid tag case, which has one tag, one arg
                outputString[0] = validTag;
                outputString[1] = level;
                outputString[2] = tag;
                outputString[3] = argLine;
                return outputString;
            }else{
                // invalid tag case
                outputString[0] = "|N|";
                return outputString;
            }
            // outPut += "|"+tag+"|"+validTag+"|"+argLine;
        }
    }else if (level == '0')
    {   
        string validTag;
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == string::npos || secBlank == string::npos){
            outputString[0] = "|N|";
            return outputString;
            // outPut = "|N|"+line;
        }else{
            string first_arg (line.begin()+firstBlank+1, line.begin()+secBlank);
            string sec_arg (line.begin()+secBlank+1, line.end());
            outputString[1] = "0";
            // outPut.append(1,level);
            if (sec_arg == "INDI" || sec_arg == "FAM"){
                validTag = "Y";
                outputString[0] = validTag;
                outputString[2] = sec_arg;
                outputString[3] = first_arg;
                return outputString;
                // outPut += "|"+sec_arg+"|"+validTag+"|"+first_arg;
            }else{
                validTag = getValided(level, first_arg);
                outputString[0] = validTag;
                outputString[2] = first_arg;
                outputString[3] = sec_arg;
                return outputString;
                // outPut += "|"+first_arg+"|"+validTag+"|"+sec_arg;
            }
        }
    }else{
        outputString[0] = "|N|";
        return outputString;
        // outPut = "|N|"+line;
    }
}

string getValided(char level, string tag){
    // validate the level tag combination
    string answer;
    answer = 'N';
    
    char level0 = '0';
    array<string, 3> level0_tag = {"NOTE","HEAD","TRLR"};
    if (level == level0){
        for(auto x: level0_tag){
            if (x == tag){
                answer = 'Y';
                break;
            }
        }
    }

    char level1;
    level1 = '1';
    array<string, 11> level1_tag = {"NAME","SEX","BIRT","DEAT","FAMC","FAMS","MARR","HUSB","WIFE","CHIL","DIV"};
    if (level == level1){
        for(auto x: level1_tag){
            if (x == tag){
                answer = 'Y';
                break;
            }
        }
    }

    char level2;
    level2 = '2';
    array<string, 1> level2_tag = {"DATE"};
    if (level == level2){
        for(auto x: level2_tag){
            if (x == tag){
                answer = 'Y';
                break;
            }
        }
    }

    // this part need to verify the key is validated. 
    
    return answer;
}

void test_bprinter(vector<Family> famList, vector<Individual> indiList){
    // print individual and family table

    // print individual table
    bprinter::TablePrinter indiTable(&std::cout);
    indiTable.AddColumn("ID", 5);
    indiTable.AddColumn("Name", 10);
    indiTable.AddColumn("Gender", 3);
    indiTable.AddColumn("Birthday", 12);
    indiTable.AddColumn("Alive", 3);
    indiTable.AddColumn("Death", 12);
    indiTable.AddColumn("Child", 12);
    indiTable.AddColumn("Spouse", 12);

    indiTable.PrintHeader();
    // print each row
    for (auto indi: indiList){
        indiTable << indi.getID() << indi.getName() << indi.getGender() 
            << indi.getBday() << indi.getAlive() << indi.getDday() << indi.getFamcList() << indi.getFamsList();
    }
    // indiTable << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
    indiTable.PrintFooter();

    // print family table
    bprinter::TablePrinter famTable(&std::cout);
    famTable.AddColumn("ID", 5);
    famTable.AddColumn("Married", 12);
    famTable.AddColumn("Divorced", 12);
    famTable.AddColumn("Husband_ID", 5);
    famTable.AddColumn("Husband_Name", 10);
    famTable.AddColumn("Wife_ID", 5);
    famTable.AddColumn("Wife_Name", 10);
    famTable.AddColumn("Children", 12);
    
    famTable.PrintHeader();
    // print each row
    for (auto fam: famList){
        indiTable << fam.getID() << fam.getMarrDate() << fam.getDivDate() 
            << fam.getHusID() << fam.getHusName() << fam.getWifeID() << fam.getWifeName() << fam.getChildrenList();
    }
    famTable.PrintFooter();

}