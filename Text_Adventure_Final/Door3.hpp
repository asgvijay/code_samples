//
//  Door3.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Door3_hpp
#define Door3_hpp

#include <stdio.h>
#include "Space.hpp"
#include <vector>
#include <string>

class Door3 : public Space
{
    
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Door3();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    void killFloor();
    virtual Space* useAFriend(std:: vector<std:: string> a);
    ~Door3();
};


#endif /* Door3_hpp */
