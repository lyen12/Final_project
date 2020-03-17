#ifndef __BUMPER2_AGENT__H
#define __BUMPER2_AGENT__H 

#include "enviro.h"

using namespace enviro;

class bumper2Controller : public Process, public AgentInterface {

    public:
    bumper2Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class bumper2 : public Agent {
    public:
    bumper2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    bumper2Controller c;
};

DECLARE_INTERFACE(bumper2)

#endif