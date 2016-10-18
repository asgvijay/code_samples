//
//  Library.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Library_hpp
#define Library_hpp

#include <stdio.h>
#include "Space.hpp"
#include <vector>
#include <string>

class Library : public Space
{
    
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    Library();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    virtual Space* useAFriend(std:: vector<std:: string> a);
    ~Library();
    
};


#endif /* Library_hpp */
