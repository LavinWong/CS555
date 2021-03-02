#include <iostream>
#include <fstream>
#include <array>
#include <string>

#include "bprinter/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>

#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif
// qis parser

using namespace std;
void getOutPutString(string line);
string getValided(char level, string tag);
void test_bprinter();

int main(){
    ifstream gedFile;
    string line;
    int counter = 0;
    gedFile.open("src/GEDCOM.ged");
    if (gedFile.is_open())
    {
        while(getline(gedFile, line)){
            cout<<"-->"<<line<<endl;
            string nxtLine;
            getOutPutString(line);
            
        }
        gedFile.close();
    }
    else cout << "Unable to open file"<<endl; 

    test_bprinter();
    // gedFile.close();
    return 0;
}

void getOutPutString(string line_2){
    string line(line_2.begin(), line_2.end()-1);
    string outPut;
    char level;
    level = line[0];
    // get the string at the start of the tag
    if (level == '1' || level == '2'){
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == string::npos || secBlank == string::npos){
            string first_tag (line.begin()+firstBlank+1, line.end());
            if (first_tag == "BIRT"|| first_tag =="DEAT"||first_tag =="MARR"||first_tag =="DIV"){
                outPut.append(1,level);
                outPut += "|"+first_tag+"|Y|"; 
            }else{
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
    cout<<"<--"<<outPut<<endl;
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
  bprinter::TablePrinter tp(&std::cout);
  tp.AddColumn("Name", 10);
  tp.AddColumn("Age", 5);
  tp.AddColumn("Position", 30);
  tp.AddColumn("Allowance", 9);

  tp.PrintHeader();
  tp << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
  tp << "John Doe" << 26 << "Too much float" << 125456789.123456789;
  tp << "John Doe" << 26 << "Typical Int" << 1254;
  tp << "John Doe" << 26 << "Typical float" << 1254.36;
  tp << "John Doe" << 26 << "Too much negative" << -125456789.123456789;
  tp << "John Doe" << 26 << "Exact size int" << 125456789;
  tp << "John Doe" << 26 << "Exact size int" << -12545678;
  tp << "John Doe" << 26 << "Exact size float" << -1254567.8;
  tp << "John Doe" << 26 << "Negative Int" << -1254;
  tp << "Jane Doe" << bprinter::endl();
  tp << "Tom Doe" << 7 << "Student" << -M_PI;
  tp.PrintFooter();

}