//
//  Bar.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Bar_hpp
#define Bar_hpp

#include <stdio.h>

#include <stdio.h>
#include "Space.hpp"


class Bar : public Space
{
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Bar();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    virtual Space* useAFriend(std:: vector<std:: string> a);
    ~Bar();
};


#endif /* Bar_hpp */
