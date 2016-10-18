//
//  Winner.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Winner_hpp
#define Winner_hpp

#include <stdio.h>

#include <stdio.h>
#include "Space.hpp"
#include <vector>
#include <string>


class Winner : public Space
{
    
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Winner();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    virtual Space* useAFriend(std:: vector<std:: string> a);
    virtual ~Winner();
    
};

#endif /* Winner_hpp */
