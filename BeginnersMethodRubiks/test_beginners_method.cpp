#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "beginners_method.hpp"

BOOST_AUTO_TEST_CASE(test_full_run) {
    map<string, string> cubeSolution = {
        // On solved ( GRW on FRU ): R, U, L, D', R, U
        {
            "WRWWGYRRG,OBBGWWRYR,OOGWBYWOY,BBOYYWRGO,GOYBRBYRB,WRBOOGGGY",
            "R,U,L,U,U,L,U,L,L,U,F,F,R,R,U,B,B,R,U,R',U',y,R,U,R',U',U,U,U,"
            "R,U,R',U',R,U,R',U',R,U,R',U',y,y,R,U,R',U',U,R,U,R',U',U,U,U,"
            "R,U,R',U',y,U,R,U,R',U',y,y,U,U',L',U',L,U,y',R,U,R',U',z,B,"
            "R,U,R',U',B',z',U,U,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,"
            "L',U',L,U,L',U',L,U,z2,R,U,R',U',R,U,R',U',D',R,U,R',U',R,U,R',U',"
            "D',D',R,U,R',U',R,U,R',U'z2,D',D',D',D',D',R,U,R',U',L',U',L,U,"
            "R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',L',U',L,U,"
            "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,y,R,U,R',U',L',U',L,U,"
            "R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',L',U',L,U,"
            "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U"
        },
        // On solved ( GRW on FRU ): D'2 F'2 U' L'2 D'2 U R'2 D' F' L'2 D' U R' U'2 L' U L'2 B' L'2 F'2
//        {
//            "WGOYGORBW,WBRYWWBWG,YOGRBGRYY,BROBYROOW,YBGWRGGWB,RGOOORBYY",
//            "will fail..."
//        }
    };
    
    int solved = 0;
    for_each(cubeSolution.begin(), cubeSolution.end(), [&](pair<string, string> p) {
        solved += BeginnersMethod().solve(p.first) == p.second ? 1 : 0;
    });
    
    BOOST_CHECK(solved == cubeSolution.size());
}