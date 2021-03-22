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

        // adding another unit test case
        another_unit_test();
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
    }
    
    void us09_test(){
        Repository repo;
        std::vector<std::string> result = {"@I1@", "@I2@","@I5@"};
        std::vector<std::string> result2 = repo.us09();
        std::vector<std::string> result3 = result;
        std::cout<<"-----US09_test------"<<std::endl;
        for (auto str: result2){
            std::cout<<str<<std::endl;
         }
         std::cout<<"-----US09_test_END------"<<std::endl;
         std::cout<<"-----US09_result------"<<std::endl;
         for (auto str: result3){
             std::cout<<str<<std::endl;
         }
         std::cout<<"-----US09_result_END------"<<std::endl;
        CHECKT(repo.us09() != result);
    }
    
    void us10_test(){
    }
    
     void us12_test(){
    }
    
     void us14_test(){
    }
    
     void us21_test(){
    }

    void another_unit_test() {
        // example unit test case :D (showcase needed)
        CHECK(2,2);
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
