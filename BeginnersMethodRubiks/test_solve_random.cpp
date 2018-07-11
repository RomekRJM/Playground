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

BOOST_AUTO_TEST_CASE(test_solve_many_random_in_parallel) {
    const int NUM_TASKS = 3;
    array<promise<CubeSolution>, NUM_TASKS> cubePromises;
    array<future<CubeSolution>, NUM_TASKS> cube_tasks;
    array<thread, NUM_TASKS> threads;
    
    for(int i=0; i<NUM_TASKS; ++i) {
        cube_tasks[i] = cubePromises[i].get_future();
        threads[i] = thread(tryToSolveRandom, move(cubePromises[i]));
        threads[i].detach();
    }
    
    int solved = 0;
    
    for(int i=0; i<NUM_TASKS; ++i) {
        cube_tasks[i].wait();    
        CubeSolution solution = cube_tasks[i].get();
    
        cout << "Scramble: " << solution.initialCubeRepresentation
                << " from scramble: " << solution.initialScramble
                << " was solved: " << solution.wasSolved << endl;
        
        solved += solution.wasSolved;
    }
    
    cout << "Solved: " << solved << " out of " << NUM_TASKS << "." << endl;
    BOOST_CHECK(solved == NUM_TASKS);
}