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
void test_bprinter();

int main(){
    ifstream gedFile;
    string line;
    int counter = 0;
    string* lineResult;
    vector<Individual> indiList;
    vector<Family> famList;

    gedFile.open("src/GEDCOM.ged"); // open ged file

    if (gedFile.is_open())
    {
        while(getline(gedFile, line)){
            lineResult = getOutPutString(line); // assign the return value to lineReuslt, contains each line's validTag, level, tag, and args
            if (*(lineResult+1) == "|Y|"){
                if (*(lineResult+2) == "0"){
                    if (*(lineResult+3) == "INDI" || *(lineResult+3) == "FAM"){
                        // create new indi or new fam
                        // edit 

                    }else{
                        // ignore other tag like NOTE, HEAD at level 0

                    }
                }else{
                    if (*(lineResult+3) == "BIRT" || *(lineResult+3) == "DEAT"
                        || *(lineResult+3) == "MARR"|| *(lineResult+3) == "DIV"){
                        // create new indi or new fam

                    }else{
                        // ignore other tag like NOTE, HEAD at level 0

                    }
                    // full fill the tag (p.s. sexcept for 4 date fore tag

                }
            }else{
                // ignore invalid line

            }
        }
        gedFile.close();
    }
    else cout << "Unable to open file"<<endl; 

    test_bprinter();
    // gedFile.close();
    return 0;
}


string* getOutPutString(string line_2){
    string line(line_2.begin(), line_2.end()-1);
    string outPut;
    char level;
    level = line[0];
    string outputString[4];
    string outputStringD[3];    // output array for 4 date Tag, BIRT, DEAT, DIV, MARR

    // get the string at the start of the tag
    if (level == '1' || level == '2'){
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == string::npos || secBlank == string::npos){
            string first_tag (line.begin()+firstBlank+1, line.end());
            
            if (first_tag == "BIRT"|| first_tag =="DEAT"||first_tag =="MARR"||first_tag =="DIV"){
                outPut.append(1,level);
                outPut += "|"+first_tag+"|Y|"; 
                return outputStringD;
            }else{
                outputString[0] = "|N|";
                outPut = "|N|"+line;
            }

        }else{
            string tag (line.begin()+firstBlank+1, line.begin()+secBlank);
            string argLine (line.begin()+secBlank+1, line.end());
            outPut.append(1,level);
            string validTag = getValided(level, tag);
            outPut += "|"+tag+"|"+validTag+"|"+argLine;
        }
    }else if (level == '0')
    {   
        string validTag;
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == string::npos || secBlank == string::npos){
            outPut = "|N|"+line;
        }else{
            string first_arg (line.begin()+firstBlank+1, line.begin()+secBlank);
            string sec_arg (line.begin()+secBlank+1, line.end());
            outPut.append(1,level);
            if (sec_arg == "INDI" || sec_arg == "FAM"){
                validTag = "Y";
                outPut += "|"+sec_arg+"|"+validTag+"|"+first_arg;
            }else{
                validTag = getValided(level, first_arg);
                outPut += "|"+first_arg+"|"+validTag+"|"+sec_arg;
            }
        }
    }else{
        outPut = "|N|"+line;
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

void test_bprinter(){
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
  indiTable << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
  tp.PrintFooter();

}