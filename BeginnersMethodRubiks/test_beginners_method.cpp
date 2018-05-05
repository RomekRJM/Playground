#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "beginners_method.hpp"

BOOST_AUTO_TEST_CASE(test_full_run) {
    string actual = BeginnersMethod().
            solve("YRWYRGORG,BOORYGOGO,GYWOOWBBG,WBRYWBYWY,BOYWGWWOR,RYBRBGRBG");
    
    BOOST_CHECK(actual == "R,U,R',U'");
}