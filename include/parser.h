//
// Created by Qi Zhao on 3/7/21.
//

#ifndef NEW2_PARSER_H
#define NEW2_PARSER_H

#include <fstream>
#include <array>
#include <vector>

void parser(std::string filepath, std::vector<Family2>* famListPointer, std::vector<Individual2>* indiListPointer) {
    std::ifstream gedFile;
    int currentLine = 0;
    int myLine = 0;
    gedFile.open(filepath);
    if (gedFile.is_open())
    {
        std::vector<std::string> lineResult;
        std::string line;
        bool famFlag = false;
        bool indiFlag = false;
        int dateFlag = 0;
        Family2 famBuff("NA");
        Individual2 indiBuff("NA");

        while(getline(gedFile, line)){
            currentLine ++;
            lineResult = getOutPutString(line); // assign the return value to lineReuslt, contains each line's validTag, level, tag, and args
            if (lineResult[0] == "|Y|"){
                if (lineResult[1] == "0"){
                    // create a new instance of individual or family class, and flush the exsisting instance to indiList or famList based on the type of the instance
                    if (lineResult[2] == "INDI" || lineResult[2] == "FAM"){
                        // flush buffer indi or fam
                        // clear all flag to its default value
                        if (famFlag){
                            famBuff.line = currentLine;
                            (*famListPointer).push_back(famBuff);
                            famBuff = Family2("NA");
                            famFlag = false;
                        }
                        if (indiFlag){
                            indiBuff.line = currentLine;
                            indiBuff.setAge();
                            indiBuff.setAlive();
                            (*indiListPointer).push_back(indiBuff);
                            indiBuff = Individual2("NA");
                            indiFlag = false;
                        }
                        indiFlag = false;
                        famFlag = false;
                        dateFlag = 0;

                        if (lineResult[2] == "INDI"){
                            // create new indi
                            // edit indiFlag
                            indiBuff.setID(lineResult[3]);
                            indiFlag = true;
                        }else{
                            // create new fam
                            // edit famflag
                            famBuff.setID(lineResult[3]);
                            famFlag = true;
                        }
                    }else{
                        // ignore other tag like NOTE, HEAD at level 0
                        continue;
                    }
                }else{
                    // handle level 1 and level 2 tag
                    // handle
                    if (lineResult[2] == "BIRT" || lineResult[2] == "DEAT"
                        || lineResult[2] == "MARR"|| lineResult[2] == "DIV"){
                        // set dateFlag
                        if (lineResult[2] == "BIRT"){
                            dateFlag = 1;
                            continue;
                        }else if(lineResult[2] == "DEAT"){
                            dateFlag = 2;
                            continue;
                        }else if (lineResult[2] == "MARR"){
                            dateFlag = 3;
                            continue;
                        }else if (lineResult[2] == "DIV"){
                            dateFlag = 4;
                            continue;
                        }
                    }

                    // hadle date args according to the dateflag
                    if (lineResult[2] == "DATE"){
                        switch (dateFlag)
                        {
                            case 1:
                                indiBuff.setBday(lineResult[3]);
                                break;
                            case 2:
                                indiBuff.setDday(lineResult[3]);
                                break;
                            case 3:
                                famBuff.setMarr(lineResult[3]);
                                break;
                            case 4:
                                famBuff.setDiv(lineResult[3]);
                                break;
                            default:
                                break;
                        }
                        dateFlag = 0;
                    }

                    // full fill the tag (p.s. except for 4 date fore tag)
                    std::string tag = lineResult[2];
                    std::string arg = lineResult[3];
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
//                        famBuff.setHusName(arg);
                    }else if (tag == "WIFE"){
                        famBuff.setWifeID(arg);
//                        famBuff.setWifeName(arg);
                    }else if (tag == "CHIL"){
                        famBuff.setChildrenList(arg);
                    }
                }
            }else{
                continue;
            }
        }

        if (indiFlag){
            (*indiListPointer).push_back(indiBuff);
        }else if(famFlag){
            (*famListPointer).push_back(famBuff);
        }
        gedFile.close();
    }else std::cout << "unable to open file!" << std::endl;
}

std::vector<std::string> getOutPutString(std::string line_2){
    std::string line(line_2.begin(), line_2.end()-1);
    char level;
    level = line[0];
    std::vector<std::string> outputVec;

    if (level == '1' || level == '2'){
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == std::string::npos || secBlank == std::string::npos){
            // only has one tag, no args
            // for example, 1 BIRT

            std::string first_tag (line.begin()+firstBlank+1, line.end());
            if (first_tag == "BIRT"|| first_tag =="DEAT"||first_tag =="MARR"||first_tag =="DIV"){
                outputVec.emplace_back("|Y|");
                outputVec.emplace_back("1");
                outputVec.push_back(first_tag);
                return outputVec;
            }else{
                outputVec.emplace_back("|N|");
                return outputVec;
            }

        }else{
            // for any other level 1 tag
            // for example, 1 NAME Jenny
            std::string level_str(1,level);
            std::string tag (line.begin()+firstBlank+1, line.begin()+secBlank);
            std::string argLine (line.begin()+secBlank+1, line.end());
            std::string validTag = getValided(level, tag);
            if (validTag == "|Y|"){
                // valid tag case, which has one tag, one arg
                outputVec.push_back(validTag);
                outputVec.push_back(level_str);
                outputVec.push_back(tag);
                outputVec.push_back(argLine);
                return outputVec;
            }else{
                // invalid tag case
                outputVec.emplace_back("|N|");
//                outputString[0] = "|N|";
                return outputVec;
            }
            // outPut += "|"+tag+"|"+validTag+"|"+argLine;
        }
    }else if (level == '0')
    {
        std::string validTag;
        size_t firstBlank = line.find_first_of(" ");
        size_t secBlank = line.find_first_of(" ", firstBlank+1);
        if (firstBlank == std::string::npos || secBlank == std::string::npos){
            outputVec.emplace_back("|N|");
            return outputVec;
        }else{
            std::string first_arg (line.begin()+firstBlank+1, line.begin()+secBlank);
            std::string sec_arg (line.begin()+secBlank+1, line.end());
            outputVec.emplace_back("0");
            if (sec_arg == "INDI" || sec_arg == "FAM"){
                validTag = "|Y|";
                outputVec.emplace(outputVec.begin(),validTag);
                outputVec.push_back(sec_arg);
                outputVec.push_back(first_arg);
                return outputVec;
            }else{
                validTag = getValided(level, first_arg);
                outputVec.emplace(outputVec.begin(),validTag);
                outputVec.push_back(first_arg);
                outputVec.push_back(sec_arg);
                return outputVec;
            }
        }
    }else{
        outputVec.emplace_back("|N|");
        return outputVec;
    }
}

std::string getValided(char level, std::string tag){
    // validate the level tag combination
    std::string answer;
    answer = "|N|";

    char level0 = '0';
    std::array<std::string, 3> level0_tag = {"NOTE","HEAD","TRLR"};
    if (level == level0){
        for(auto x: level0_tag){
            if (x == tag){
                answer = "|Y|";
                break;
            }
        }
    }

    char level1;
    level1 = '1';
    std::array<std::string, 11> level1_tag = {"NAME","SEX","BIRT","DEAT","FAMC","FAMS","MARR","HUSB","WIFE","CHIL","DIV"};
    if (level == level1){
        for(auto x: level1_tag){
            if (x == tag){
                answer = "|Y|";
                break;
            }
        }
    }

    char level2;
    level2 = '2';
    std::array<std::string, 1> level2_tag = {"DATE"};
    if (level == level2){
        for(auto x: level2_tag){
            if (x == tag){
                answer = "|Y|";
                break;
            }
        }
    }

    // this part need to verify the key is validated.

    return answer;
}

#endif //NEW2_PARSER_H
