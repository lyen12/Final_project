#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "block.h"
#define block_width 28

using namespace enviro;
using namespace std;

// Put your implementations here

blockController::blockController() : Process(), AgentInterface(), on_bottom_piece(false), rotate(0), new_agent(false) {}

void blockController::init() {
    //! Watch for specific a,s,d,w key operations

	watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            //! Sends a Move left signal to the block when 'a' is pressed
            if ( k == "a" && !on_bottom_piece) {
                emit(Event("move_left", { 
    			}));             
            //! Sends a Move right signal to the block when 'd' is pressed
            } else if ( k == "d" && !on_bottom_piece) {
                emit(Event("move_right", {
    			})); 
            } else if ( k == "w" && !on_bottom_piece) {
                emit(Event("rotate", {
                }));       
            //! Sends a move down faster signal to the block when 's' is pressed
            } else if ( k == "s" && !on_bottom_piece) {
                emit(Event("move_down_faster", {
                })); 
            } 
        
    });        
    //! On move_left signal, block will move left 
    watch("move_left", [this](Event e) {
        if ( sensor_value(2) > 2 ) {
            goal_x = position().x - block_width;
        } 
        cout << "goal_x is " << goal_x <<"\n";
        cout << "Sensor_value(2) is " << sensor_value(2) << "\n";
    });

    watch("move_right", [this](Event e) {
        if ( sensor_value(0) > 2 ) {
            goal_x = position().x + block_width;
        }
        cout << "goal_x is " << goal_x <<"\n";
        cout << "Sensor_value(0) is " << sensor_value(0) << "\n";

    }); 

    // watch("move_down_faster", [this](Event e) {
    //     if ( grid_bottom_edge - ( position().y + block_width/2 ) >= block_width ){
    //         goal_y = position().y + block_width;
    //     } 
    //     cout << "goal_y is " << goal_y << "\n";
    // }); 
    
    watch("move_down", [this](Event e) {
        if ( sensor_value(1) > 2 ){
            goal_y = position().y + 10;
        } 
        // cout << "Sensor_value(1) is " << sensor_value(1) << "\n";
    }); 

    watch("rotate", [this](Event e) {
        rotate = rotate + M_PI/2;
    }); 
}

void blockController::start() {}
void blockController::update() {
    if ( sensor_value(1) > 2 ){
        emit(Event("move_down", {}));
    } else {
        on_bottom_piece = true;
    }
	teleport(goal_x, goal_y, rotate);
    // if (on_bottom_piece == true && new_agent == false) {
    //     Agent& block = add_agent("block", 0, -245, 0, BLOCK_STYLE);
    //     new_agent = true;
    // }
}
void blockController::stop() {}