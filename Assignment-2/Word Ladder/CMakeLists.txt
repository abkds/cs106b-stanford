cmake_minimum_required(VERSION 3.5)
project(Word_Ladder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    StanfordCPPLib/private/main.h
    StanfordCPPLib/private/randompatch.h
    StanfordCPPLib/private/tokenpatch.h
    StanfordCPPLib/private/tplatform.h
    StanfordCPPLib/console.h
    StanfordCPPLib/direction.h
    StanfordCPPLib/error.h
    StanfordCPPLib/filelib.h
    StanfordCPPLib/foreach.h
    StanfordCPPLib/gevents.h
    StanfordCPPLib/ginteractors.h
    StanfordCPPLib/gmath.h
    StanfordCPPLib/gobjects.h
    StanfordCPPLib/graph.h
    StanfordCPPLib/grid.h
    StanfordCPPLib/gtimer.h
    StanfordCPPLib/gtypes.h
    StanfordCPPLib/gwindow.h
    StanfordCPPLib/hashmap.h
    StanfordCPPLib/hashset.h
    StanfordCPPLib/lexicon.h
    StanfordCPPLib/map.h
    StanfordCPPLib/platform.h
    StanfordCPPLib/point.h
    StanfordCPPLib/pqueue.h
    StanfordCPPLib/queue.h
    StanfordCPPLib/random.h
    StanfordCPPLib/set.h
    StanfordCPPLib/simpio.h
    StanfordCPPLib/sound.h
    StanfordCPPLib/stack.h
    StanfordCPPLib/strlib.h
    StanfordCPPLib/thread.h
    StanfordCPPLib/tokenscanner.h
    StanfordCPPLib/vector.h
    WordLadder.cpp)

add_executable(Word_Ladder ${SOURCE_FILES})