//
//  Airport.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Airport_hpp
#define Airport_hpp

#include <stdio.h>
#include "Space.hpp"
#include <vector>
#include <string>


class Airport : public Space
{
    
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Airport();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    virtual Space* useAFriend(std:: vector<std:: string> a);
     ~Airport();
    
};

#endif /* Airport_hpp */
