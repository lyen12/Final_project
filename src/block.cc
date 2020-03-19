#include <iostream>
#include <stdlib.h>
#include <vector>
#include "block.h"
#define LEVEL_DIFFICULTY 500
#define WIN_LINE 65

using namespace enviro;
using namespace std;

// Put your implementations here
//! Controlling_id is a global variable to isolate key event controls to a specific agent
int controlling_id;

blockController::blockController() : Process(), AgentInterface() {}

void blockController::init() {

    watch("keydown", [&](Event &e) {
        //! This checks to make sure the Player only controls the most recently added block.
        if (controlling_id == id()) {
            //! Set k to the specific key being pressed.
            auto k = e.value()["key"].get<std::string>();
            //! If spacebar is pressed, drop the block straight to the bottom.
            if ( k == " " && !drop && !win) {
                //! send drop signal in addition to the block id and it's 
                //! position the moment the spacebar is pressed.
                emit(Event("drop", {
                    { "id", id() },
                    { "x", position().x }, 
                    { "y", position().y } 
                }));
                drop = true; 
            } 
        } 
    });        
    //! move block right
    watch("move_right", [this](Event e) {
        if ( id() == e.value()["id"] ) {
            //! Change direction
            v = -v;
        }
    }); 
    //! move block left
    watch("move_left", [this](Event e) {
        if ( id() == e.value()["id"] ) {
            //! Change direction
            v = -v; 
        }
    }); 
    //! set drop state to true and capture position 
    watch("drop", [this](Event e) {
        if ( id() == e.value()["id"] ) {
            drop = true;
            goal_x = e.value()["x"];
            goal_y = e.value()["y"]; 
        }
    }); 
    //! if block collides with left bumper, move right
    notice_collisions_with("bumper", [&](Event &e) {
        if ( !drop  ) {
          emit(Event("move_right", {{ "id", id() }}));
        }
    }); 
    //!  if block colllides with right bumper, move left   
    notice_collisions_with("bumper2", [&](Event &e) {
        if ( !drop ) {
          emit(Event("move_left", {{ "id", id() }}));
        }
    }); 
}

void blockController::start() {
    //! capture most recently added block id
    controlling_id = id();

    //! speed will make the level more difficult
    v = LEVEL_DIFFICULTY;

    //! Initialize conditions
    stop_block = false;
    drop = false;
    win = false;
    count = 0;

    //! send block id over to win_message to be stored.
    emit(Event("adding_agent", {{ "id", id() }}));
}

void blockController::update() {
    //! Allow the block to bounce left and right 
    if (!drop && !win) {
        prevent_rotation();
        apply_force(v,0);
        // goal_x = position().x;
        // goal_y = position().y;
    } 
    //! Block will drop to the bottom when spacebar is pressed (sets drop to true)
    else if (drop && !win) {
        //! Prevents the block from spinning
        prevent_rotation();
        //! Stops the block where the spacebar was pressed.
        if (!stop_block) {
            teleport(goal_x, goal_y, 0);
            stop_block = true;
        }
        //! Count is for giving time for the block to drop to the bottom.
        count++;
        //! Apply a downward force on the block.
        omni_apply_force(0,1500);
        
        if (count == 15) {
            //! Once block hits the ground, add a new block.
            add_agent("block", 0, 0, 0, BLOCK_STYLE);
            //cout << "id " << id() << " y position  after dropping is " << position().y << "\n";
            
            //! If the block's position reaches the Win line, a win event will be emitted to win_message.cc.
            if (position().y < WIN_LINE ) {
                emit(Event("win"));
                win = true;
                omni_apply_force(0,1500);
                cout << "win state is " << win << "\n";
            }
        }
    }
    
    
}
void blockController::stop() {}

