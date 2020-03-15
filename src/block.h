#ifndef BLOCK_AGENT__H
#define BLOCK_AGENT__H 

#include "enviro.h"

using namespace enviro;

class blockController : public Process, public AgentInterface {

    public:
    blockController();
    void init();
    void start();
    void update();
    void stop();

    private:
    double goal_x, goal_y;
    double rotate;
    bool on_bottom_piece; 
    bool new_agent;
    const json BLOCK_STYLE = { 
                   {"fill", "gray"}, 
                   {"stroke", "black"}, 
               }; 
};


class block : public Agent {
    public:
    block(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    blockController c;
};

DECLARE_INTERFACE(block)

#endif