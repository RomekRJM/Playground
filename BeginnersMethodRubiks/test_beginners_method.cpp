#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "beginners_method.hpp"

BOOST_AUTO_TEST_CASE(test_full_run) {
    // On solved ( GRW on FRU ): R, U, L, D', R, U
    string actual = BeginnersMethod().
            solve("WRWWGYRRG,OBBGWWRYR,OOGWBYWOY,BBOYYWRGO,GOYBRBYRB,WRBOOGGGY");
    
    BOOST_CHECK(actual == "R,U,L,U,U,L,U,L,L,U,F,F,R,R,U,B,B,"
            "R,U,R',U',y,R,U,R',U',U,U,U,R,U,R',U',R,U,R',U',R,U,R',U',y,y,"
            "R,U,R',U',R,U,R',U',y,U,U,U,R,U,R',U',U,U,U,y,y,y,y,"
            "U',L',U',L,U,y',R,U,R',U',F,R,U,R',U',F',z,B,R,U,R',U',B',"
            "z',U,y,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,"
            "L',U',L,U,L',U',L,U,z2,R,U,R',U',R,U,R',U',D',D',R,U,R',U',"
            "R,U,R',U',D',R,U,R',U',R,U,R',U'z2,D',D',D',D',D',R,U,R',U',"
            "L',U',L,U,R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',"
            "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,y,y,y,R,U,R',U',"
            "L',U',L,U,R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',"
            "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U");
}