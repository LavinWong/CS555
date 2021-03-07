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
        us01();

        // adding another unit test case
        another_unit_test();
    }

    void us01(){
        // declare us01 unit test function.

        // Integral type match check.
        CHECK(2 + 2, 4);

        // Boolean type value check.
        CHECKT(2 + 2 == 4);

        // String match check.
        CHECKS("a" "b", "ab");

    }

    void another_unit_test() {
        // failed unit test case :D (showcase needed)
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