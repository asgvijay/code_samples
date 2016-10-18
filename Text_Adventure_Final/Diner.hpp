//
//  Diner.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Diner_hpp
#define Diner_hpp

#include "Space.hpp"
#include <stdio.h>

class Diner : public Space
{

private:
    bool madeFriend;
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Diner();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    virtual Space* useAFriend(std:: vector<std:: string> a);
    ~Diner();
};



#endif /* Diner_hpp */
