#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <future>
#include <chrono>
#include "beginners_method.hpp"
#include "cube.hpp"
#include "cube_generator.hpp"

struct CubeSolution {
    CubeSolution(string i, bool s, string is) : 
        initialCubeRepresentation(i), wasSolved(s), initialScramble(is) {};
    string initialCubeRepresentation;
    string initialScramble;
    bool wasSolved;
};

void tryToSolveRandom(promise<CubeSolution> cubePromise) {
    string initialScramble;
    Cube cube = CubeGenerator::fromRandomScramble(initialScramble);
    string cubeString = cube.asShortString();
    CubeSolution cubeSolution = CubeSolution(cubeString, false, initialScramble);
    
    try {
        BeginnersMethod().solve(cubeString);
        cubeSolution.wasSolved = true;
    } catch (StalemateException se) {
        cubeSolution.wasSolved = false;
    }
    
    cubePromise.set_value_at_thread_exit(cubeSolution);

}

BOOST_AUTO_TEST_CASE(test_random_1) {
    promise<CubeSolution> cubePromise;
    future<CubeSolution> cube_task = cubePromise.get_future();
    thread th = thread(tryToSolveRandom, move(cubePromise));
    th.detach();
    cube_task.wait();
    
    CubeSolution solution = cube_task.get();
    
    cout << "Scramble: " << solution.initialCubeRepresentation
            << " from scramble: " << solution.initialScramble
            << " was solved: " << solution.wasSolved << endl;
    BOOST_CHECK(solution.wasSolved);
}