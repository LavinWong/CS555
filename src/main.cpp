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
        us06_test();

        // adding another unit test case
        another_unit_test();
    }

    void us01_test(){
        // declare us01 unit test function.
        Repository repo;
        std::vector<std::string> result = {"@I7@", "@I14@", "@F1@", "@F2@"};
        std::vector<std::string> result2 = repo.us01();
        std::cout<<"-----US01_test------"<<std::endl;
        for (auto str: result2){
            std::cout<<str<<std::endl;
        }
        std::cout<<"-----US01_test_END------"<<std::endl;
        CHECKT(repo.us01() == result);

    }

    void us02_test(){
        // declare us01 unit test function.
        Repository repo;
        std::vector<std::string> result = {"@I1@"};
        CHECKT(repo.us02() != result);

    }

    void us03_test(){
        // declare us01 unit test function.
        Repository repo;
        std::vector<std::string> result = {"@I1@"};
        CHECKT(repo.us03() != result);

    }

    void us06_test(){
        // add test case for us06
        Repository repo;
        std::vector<std::string> result = {"@F5@"};
        CHECKT(repo.us06() == result);

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
