// CPlusPlusUnit - C++ Unit testing TDD framework (github.com/cppunit/cppunit)
#include "cppunit.h"

#include <iostream>
#include "Family2.h"
#include "Individual2.h"
#include "Repository.h"


class Cppunit_tests: public Cppunit {
    void test_list() {
        // test suites for the all user story

        print_table_test();

        // add your unit test case function here

        // for example: adding unit test for us01()
        us01_test();
        us02_test();
        us03_test();
        us04_test();
        us05_test();
        us06_test();
        
        //sprint2
        us07_test();
        us09_test();
        us10_test();
        us12_test();
        us14_test();
        us21_test();

        //sprint3
        us22_test();
        us23_test();
        us27_test();
        us29_test();
        us30_test();
        us33_test();

        //sprint4
        us35_test();
        us36_test();
        us38_test();
        us39_test();
        us40_test();
        us42_test();

    }

    void us01_test(){
        // declare us01 unit test function.
        Repository repo;
        std::vector<std::string> result = {"@I7@", "@I14@", "@F1@", "@F2@"};
        std::vector<std::string> result2 = repo.us01();
        // std::cout<<"-----US01_test------"<<std::endl;
        // for (auto str: result2){
        //     std::cout<<str<<std::endl;
        // }
        // std::cout<<"-----US01_test_END------"<<std::endl;
        CHECKT(repo.us01() == result);

    }

    void us02_test(){
        // declare us01 unit test function.
        Repository repo;
        std::vector<std::string> result = {"@I1@", "@I2@","@I5@"};
        //std::vector<std::string> result2 = repo.us02();
        //std::vector<std::string> result3 = result;
        //std::cout<<"-----US02_test------"<<std::endl;
        //for (auto str: result2){
            //std::cout<<str<<std::endl;
         //}
         //std::cout<<"-----US02_test_END------"<<std::endl;
         //std::cout<<"-----US02_result------"<<std::endl;
         //for (auto str: result3){
             //std::cout<<str<<std::endl;
         //}
         //std::cout<<"-----US02_result_END------"<<std::endl;
        CHECKT(repo.us02() == result);

    }

    void us03_test(){
        // declare us01 unit test function.
        Repository repo;
        std::vector<std::string> result = {"@I7@","@I15@","@I16@","@I18@"};
       // std::vector<std::string> result2 = repo.us03();
        //std::vector<std::string> result3 = result;
        //std::cout<<"-----US03_test------"<<std::endl;
        // for (auto str: result2){
            // std::cout<<str<<std::endl;
         //}
         //std::cout<<"-----US03_test_END------"<<std::endl;
        //std::cout<<"-----US03_result------"<<std::endl;
         //for (auto str: result3){
            // std::cout<<str<<std::endl;
         //}
        // std::cout<<"-----US03_result_END------"<<std::endl;
        CHECKT(repo.us03() == result);

    }

    void us04_test() {
        Repository repo;
        std::vector<std::string> result = {"@F2@"};
        std::vector<std::string> result1 = repo.us04();
        CHECKT(result1 == result);
    }

    void us05_test() {
        Repository repo;
        std::vector<std::string> result = {"NA"};
        std::vector<std::string> result1 = repo.us05();
        CHECKT(result1 == result);
    }

    void us06_test(){
        // add test case for us06
        Repository repo;
        std::vector<std::string> result = {"@F5@"};
        CHECKT(repo.us06() == result);

    }
    
    void us07_test(){
        // add test case for us07
        Repository repo;
        std::vector<std::string> result = {"@I15@"};
        std::vector<std::string> result2 = repo.us07();
        // std::cout<<"-----US07_test------"<<std::endl;
        // for (auto str: result2){
        //     std::cout<<str<<std::endl;
        // }
        // std::cout<<"-----US07_test_END------"<<std::endl;
        CHECKT(repo.us07() == result);
    }
    
    void us09_test(){
        Repository repo;
        std::vector<std::string> result = {"@I3@", "@I2@","@I4@","@I17@","@I11@","@I14@","@I23@"};
        std::vector<std::string> result2 = repo.us09();
        std::vector<std::string> result3 = result;
        // std::cout<<"-----US09_test------"<<std::endl;
        // for (auto str: result2){
        //     std::cout<<str<<std::endl;
        //  }
        //  std::cout<<"-----US09_test_END------"<<std::endl;
        //  std::cout<<"-----US09_result------"<<std::endl;
        //  for (auto str: result3){
        //      std::cout<<str<<std::endl;
        //  }
        //  std::cout<<"-----US09_result_END------"<<std::endl;
        CHECKT(repo.us09() == result);
    }
    
    void us10_test(){
        Repository repo;
        std::vector<std::string> result = {"@I1@", "@I2@"};
        std::vector<std::string> result2 = repo.us10();
        std::vector<std::string> result3 = result;
        // std::cout<<"-----US10_test------"<<std::endl;
        // for (auto str: result2){
        //     std::cout<<str<<std::endl;
        //  }
        //  std::cout<<"-----US10_test_END------"<<std::endl;
        //  std::cout<<"-----US10_result------"<<std::endl;
        //  for (auto str: result3){
        //      std::cout<<str<<std::endl;
        //  }
        //  std::cout<<"-----US10_result_END------"<<std::endl;
        CHECKT(repo.us10() == result);
    }
    
     void us12_test(){
        Repository repo;
        std::vector<std::string> result = {"NA","@F5@"};
        std::vector<std::string> result1 = repo.us12();
        CHECKT(result1 == result);
    }
    
    void us14_test(){
        Repository repo;
        std::vector<std::string> result = {"NA"};
        std::vector<std::string> result1 = repo.us14();
        CHECKT(result1 == result);
    }
    
     void us21_test(){
        Repository repo;
        std::vector<std::string> result = {"@F7@", "@F13@"};
        std::vector<std::string> result2 = repo.us21();
        // std::cout<<"-----US21_test------"<<std::endl;
        // for (auto str: result2){
        //     std::cout<<str<<std::endl;
        // }
        // std::cout<<"-----US21_test_END------"<<std::endl;
        CHECKT(repo.us21() == result);
    }

    void us22_test(){
        Repository repo;
        std::vector<std::string> result = {"@F1@", "@F2@", "@F4@", "@F3@", "@F5@", "@F6@", "@F7@", "@F8@", "@F9@", "@F10@", "@F11@", "@F12@", "@F13@" ,"@I1@", "@I2@","@I3@", "@I4@","@I5@", "@I6@","@I7@", "@I8@","@I9@", "@I10@","@I11@", "@I12@","@I13@", "@I14@","@I15@", "@I16@","@I17@", "@I18@","@I19@", "@I20@","@I21@", "@I22@","@I23@", "@I24@","@I25@"};
        //std::vector<std::string> result2 = repo.us22();
        //std::vector<std::string> result3 = result;
         //std::cout<<"-----US22_test------"<<std::endl;
         //for (auto str: result2){
         //    std::cout<<str<<std::endl;
         // }
         // std::cout<<"-----US22_test_END------"<<std::endl;
          //std::cout<<"-----US22_result------"<<std::endl;
         // for (auto str: result3){
          //    std::cout<<str<<std::endl;
         // }
         // std::cout<<"-----US22_result_END------"<<std::endl;
        CHECKT(repo.us22() == result);
    }

    void us23_test(){
        //todo
        Repository repo;
        std::vector<std::string> result = {"@I1@", "@I2@","@I3@", "@I5@", "@I6@","@I7@", "@I8@","@I9@", "@I10@","@I11@", "@I12@","@I13@", "@I14@","@I15@", "@I16@","@I17@", "@I18@","@I19@", "@I20@","@I21@", "@I22@","@I23@", "@I24@","@I25@"};
        //std::vector<std::string> result2 = repo.us23();
       // std::vector<std::string> result3 = result;
         //std::cout<<"-----US23_test------"<<std::endl;
         //for (auto str: result2){
            // std::cout<<str<<std::endl;
          //}
         // std::cout<<"-----US23_test_END------"<<std::endl;
          //std::cout<<"-----US23_result------"<<std::endl;
         // for (auto str: result3){
              //std::cout<<str<<std::endl;
          //}
          //std::cout<<"-----US23_result_END------"<<std::endl;
        CHECKT(repo.us23() == result);
    }
    
    void us27_test(){
        //todo
        Repository repo;
        std::vector<std::string> result = {"@I1@","52","@I2@","50","@I3@","24","@I4@","NA","@I5@", "75", "@I6@","52","@I7@","51","@I8@","46","@I9@","50","@I10@","53","@I11@","28","@I12@","49","@I13@","24","@I14@","NA","@I15@","178","@I16@","118","@I17@","85","@I18@","75","@I19@","80","@I20@","59","@I21@","59","@I22@","56","@I23@","30","@I24@","30","@I25@","28"};
        std::vector<std::string> result1 = repo.us27();
        CHECKT(result1 == result)
    }
    
    void us29_test(){
        //todo
        Repository repo;
        std::vector<std::string> result = {"@I7@","@I15@","@I16@","@I18@"};
        std::vector<std::string> result1 = repo.us29();
        CHECKT(result1 == result)
    }
    
    void us30_test() {
        Repository repo;
        std::vector<std::string> result = {"@F2@", "@F3@", "@F5@"};
        std::vector<std::string> result1 = repo.us30();
        CHECKT(result1 == result);
    }
    
    void us33_test(){
        Repository repo;
        std::vector<std::string> result = {"NA"};
        std::vector<std::string> result1 = repo.us33();
        CHECKT(result1 == result);
    }
    
    void us35_test(){
        //todo
        Repository repo;
        std::vector<std::string> result = {"@I1@", "@I2@","@I3@", "@I5@", "@I6@","@I7@", "@I8@","@I9@", "@I10@","@I11@", "@I12@","@I13@", "@I14@","@I15@", "@I16@","@I17@", "@I18@","@I19@", "@I20@","@I21@", "@I22@","@I23@", "@I24@","@I25@"};
        std::vector<std::string> result2 = repo.us35();
        std::vector<std::string> result3 = result;
         std::cout<<"-----US35_test------"<<std::endl;
        for (auto str: result2){
             std::cout<<str<<std::endl;
          }
          std::cout<<"-----US35_test_END------"<<std::endl;
          std::cout<<"-----US35_result------"<<std::endl;
          for (auto str: result3){
              std::cout<<str<<std::endl;
          }
          std::cout<<"-----US35_result_END------"<<std::endl;
        CHECKT(repo.us35() != result);
    }
    
    void us36_test(){
        //todo
    }
    
    void us38_test(){
        //todo
    }
    
    void us39_test(){
        //todo
    }
    
    void us40_test(){
        //todo
    }
    
    void us42_test(){
        //todo
    }
    

    void print_table_test() {
        Repository repo;
        repo.print_table();
    }
};

int main(int argc, char *argv[]) {
    // Test invocation example.
    return (new Cppunit_tests)->run();
}
