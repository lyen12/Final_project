#ifndef __WIN_MESSAGE_AGENT__H
#define __WIN_MESSAGE_AGENT__H 

#include "enviro.h"

using namespace enviro;

class win_messageController : public Process, public AgentInterface {

    public:
    win_messageController();
    void init();
    void start();
    void update();
    void stop();

    private:
    //! existing_agents will hold the ids of every block added.
    vector<int> existing_agents;
    int controlling_id;
    bool win = false;
    //! Styling for the added block.
    const json BLOCK_STYLE = { 
                   {"fill", "gray"}, 
                   {"stroke", "black"}, 
    }; 
};

class win_message : public Agent {
    public:
    win_message(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    win_messageController c;
};

DECLARE_INTERFACE(win_message)

#endif