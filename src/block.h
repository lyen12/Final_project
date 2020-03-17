#ifndef BLOCK_AGENT__H
#define BLOCK_AGENT__H 
#include <vector>


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
    
    //! goal_x and goal_y are the block's desired position 
    double goal_x, goal_y; 

    //! new_agent is a boolean variable to determine if a new agent has been
    //! just created.
    bool new_agent;

    //! drop is a boolean variable to determine if the block is called to
    //! drop by the Player.
    int count;
    bool drop;
    bool win;
    bool moving_left;
    bool moving_right;
    bool stop_block;
    double v = 0;

    //! Styling for the added block.
    const json BLOCK_STYLE = { 
                   {"fill", "gray"}, 
                   {"stroke", "black"}, 
    }; 

    //! Level starts at 1. This will determine the difficulty.
    int level = 1;
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