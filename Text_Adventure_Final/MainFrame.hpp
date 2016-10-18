//
//  MainFrame.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef MainFrame_hpp
#define MainFrame_hpp

#include <stdio.h>
#include "Space.hpp"
#include <vector>
#include <string>


class MainFrame : public Space
{
    
private:
    bool madeFriend;
    
public:
    std:: string virtual beFriend();
    int virtual badDecision();
    std:: string virtual getKey();
    virtual Space* moveOn(int a);
    MainFrame();
    void virtual roomOptions();
    void virtual printOptions();
    void virtual removeOptions(int a);
    int virtual getVectorOption(int c);
    virtual Space* useAFriend(std:: vector<std:: string> a);
     ~MainFrame();
    
};

#endif /* MainFrame_hpp */
