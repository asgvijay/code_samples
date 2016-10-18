//
//  Door1.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Door1_hpp
#define Door1_hpp

#include <stdio.h>
#include "Space.hpp"
#include <vector>
#include <string>


class Door1 : public Space
{
    
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Door1();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    void killFloor();
    virtual Space* useAFriend(std:: vector<std:: string> a);
     ~Door1();
};

#endif /* Door1_hpp */
