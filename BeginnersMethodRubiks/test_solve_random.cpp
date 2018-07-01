#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <future>
#include <chrono>
#include "beginners_method.hpp"
#include "cube.hpp"
#include "cube_generator.hpp"

struct CubeSolution {
    CubeSolution(string i, bool s) : initialCubeRepresentation(i), wasSolved(s) {};
    string initialCubeRepresentation;
    bool wasSolved;
};

void tryToSolveRandom(promise<CubeSolution> cubePromise) {
    Cube cube = CubeGenerator::fromRandomScramble();
    string cubeString = cube.asShortString();
    CubeSolution cubeSolution = CubeSolution(cubeString, false);
    
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
    
    BOOST_CHECK(cube_task.get().wasSolved);
}