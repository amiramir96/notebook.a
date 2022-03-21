#include "Direction.hpp"
#include "Notebook.hpp"
#include "doctest.h"
#include <array>
#include <string>

TEST_CASE("Bad input"){
    ariel::Notebook nb; 

    /* out of col */
    CHECK_THROWS(nb.write(1, 1, 100, ariel::Direction::Horizontal, "check"));
    CHECK_THROWS(nb.write(1, 1, 10111276, ariel::Direction::Horizontal, "check"));
    CHECK_THROWS(nb.write(1, 1, 100, ariel::Direction::Vertical, "check"));
    CHECK_THROWS(nb.write(1, 1, 10112321, ariel::Direction::Vertical, "check"));
    
    CHECK_THROWS(nb.read(1,0,100, ariel::Direction::Horizontal, 5));
    CHECK_THROWS(nb.read(1,0,10111276, ariel::Direction::Horizontal, 5));
    CHECK_THROWS(nb.read(1,0,100, ariel::Direction::Vertical, 5));
    CHECK_THROWS(nb.read(1,0,10111276, ariel::Direction::Horizontal, 5));
    
    // len 0 shall be empty string BUT with col invalid - shall throw !
    CHECK_THROWS(nb.read(0,0,100, ariel::Direction::Horizontal, 0));
    CHECK_THROWS(nb.read(0,0,100, ariel::Direction::Vertical, 0));
    // len 0 shall be write nothin BUT with col invalid - shall throw !
    CHECK_THROWS(nb.write(0,0,100, ariel::Direction::Horizontal, 0));
    CHECK_THROWS(nb.write(0,0,100, ariel::Direction::Vertical, 0));
   
    // downline shall pass
    CHECK_NOTHROW(nb.write(1,0,99, ariel::Direction::Horizontal, "something_else_that_shall_go_downline"));

    // check write->erase->write scheme    
    nb.write(0,0,0, ariel::Direction::Horizontal, "c-h-e-c-k");
    nb.erase(0,0,0, ariel::Direction::Horizontal, 8); // erase the 'k' from the string we writed
    for (unsigned int i=0; i < 100; i++){
        if (i < 8){
            // throw only at horiz writing not vertical
            CHECK_THROWS(nb.write(0,0,i, ariel::Direction::Horizontal, "check_throws"));
            CHECK_NOTHROW(nb.write(0,0,i, ariel::Direction::Vertical, "check_throws"));
        }
        else if (i == 8){
            // excat place - shall throw both dirs of writing
            CHECK_THROWS(nb.write(0,0,i, ariel::Direction::Horizontal, "check_throws"));
            CHECK_THROWS(nb.write(0,0,i, ariel::Direction::Vertical, "check_throws"));
        }
        else {
            // sholdnt throw anyway
            CHECK_NOTHROW(nb.write(0,0,i, ariel::Direction::Horizontal, "check_throws"));
            CHECK_NOTHROW(nb.write(0,0,i, ariel::Direction::Vertical, "check_throws"));
        }
    }

    // erase when nothing is writend, shall wont mark "erase"! so shouldnt throw!
    nb.write(1,0,0, ariel::Direction::Horizontal, "______________________");
    nb.erase(1,0,0, ariel::Direction::Horizontal, 5);
    CHECK_NOTHROW(nb.write(1,0,0, ariel::Direction::Horizontal, "check_throws"));
    CHECK_NOTHROW(nb.write(1,0,3, ariel::Direction::Vertical, "check_throws"));
}

TEST_CASE("Good input"){
    ariel::Notebook nbg;

    // len 0 shall be empty string
    CHECK_EQ(nbg.read(0,0,0, ariel::Direction::Horizontal, 0), "");
    CHECK_EQ(nbg.read(0,0,0, ariel::Direction::Vertical, 0), "");

    // basic reading
    CHECK_EQ(nbg.read(0,0,0, ariel::Direction::Horizontal, 3), "___");
    CHECK_EQ(nbg.read(0,0,0, ariel::Direction::Vertical, 3), "_\n_\n_\n");

    // check downline while reading
    CHECK_EQ(nbg.read(0,0,98, ariel::Direction::Horizontal, 3), "__\n_"); // downline once
    // downline twice for a text
    CHECK_EQ(nbg.read(1,0,98, ariel::Direction::Horizontal, 103), "__\n______________________________________________________________________________________________________________\n_");
}