#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "beginners_method.hpp"

BOOST_AUTO_TEST_CASE(test_full_run) {
    // On solved ( GRW on FRU ): R, U, L, D', R, U
    string actual = BeginnersMethod().
            solve("WRWWGYRRG,OBBGWWRYR,OOGWBYWOY,BBOYYWRGO,GOYBRBYRB,WRBOOGGGY");
    
    BOOST_CHECK(actual == "R,U,R',U'");
}