#include <string>
#include "Direction.hpp"
#include <iostream>
namespace ariel{
    
    class Notebook{
        /* clean class just to compile all via instructions of Ex2 part a */
        public:
            Notebook(){}
            ~Notebook(){}
        void write(unsigned int page, unsigned int row, unsigned int col, Direction dir, std::string content){}
        std::string read(unsigned int page, unsigned int row, unsigned int col, Direction dir, unsigned int len)
        {
            std::string output;
            return output; 
        }
        void erase(unsigned int page, unsigned int row, unsigned int col, Direction dir, unsigned int len){}
        void show(unsigned int page){}
    };
};