//
// Created by Ivan Babayev on 25.07.20.
//

#ifndef PATTERN_ROBOT_H
#define PATTERN_ROBOT_H
#include <string>
using namespace std;

class Speed{
 enum speed {high, avarage, low};
};
class Range{
    enum range{far,middle,low};
};
class Prio{
    enum prio{human,cars,obstacle};
};


class robot {
    string name;
    virtual bool setSpeed(Speed speedConfig) = 0;
    virtual bool setSensors(Range range, Prio Priority) = 0;
    virtual void drive() = 0;
    virtual void Scan() = 0;

};




#endif //PATTERN_ROBOT_H
