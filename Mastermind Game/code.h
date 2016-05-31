//
//  code.h
//  Project1
//
//  Created by Gurtaj Khatra on 9/19/15.
//  Header file for a code object
//

#ifndef CODE_H
#define CODE_H

#include <vector>


class Code {
    private:
        //A vector containing integers that make up the code
        std::vector<int> codeVector;
    public:
        Code();
        Code(std::vector<int>vect);
        Code(int code);
        void initializeRandomCode();
        void printCode();
        int checkCorrect(Code guess);
        int checkIncorrect(Code guess);

};

#endif // CODE_H
