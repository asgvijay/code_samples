//
//  Space.hpp
//  Project: Final
//
//  Author: Vijay Kumar
//  Date: 3/14/16


#ifndef Space_hpp
#define Space_hpp

#include <stdio.h>
#include <vector>
#include <string>

class Space
{
  
protected:
    Space* spaceName1;
    Space* spaceName2;
    Space* spaceName3;
    Space* spaceName4;
    Space* lockSpace;
    std:: string people;
    std:: string keys;
    std:: vector<std::pair<std::string, int>> options;
    std:: string spaceName;
    Space* self;
    bool first;
    
public:
    Space();
    virtual ~Space();
    std:: string virtual beFriend() = 0;
    int virtual badDecision() = 0;
    std:: string virtual getKey() = 0;
    virtual Space* moveOn(int a);
    void setSpace(Space* a, Space* b, Space *c, Space* d, Space* e);
    void virtual roomOptions() =0;
    void virtual printOptions()=0;
    void virtual removeOptions(int a) = 0;
    int virtual getVectorOption(int c) = 0;
    std:: string getSpaceName();
    virtual Space* useAFriend(std:: vector<std:: string> a);
 
};

#endif /* Space_hpp */
