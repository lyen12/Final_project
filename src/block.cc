#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "block.h"
#define MOVE_OVER 21
#define BLOCK_WIDTH 20
#define SPACE_BETWEEN_BLOCK 1

using namespace enviro;
using namespace std;

// Put your implementations here
//! Controlling_id is a global variable to isolate key event controls to a specific agent
int controlling_id;

blockController::blockController() : Process(), AgentInterface(), on_bottom_piece(false), new_agent(false) {}

void blockController::init() {

    //! Watch for specific keyboard operations
	watch("keydown", [&](Event &e) {
        cout << "blockController.id() = " << id() << endl;
        cout << "controlling_id = " << controlling_id << endl;
        
        if (controlling_id == id()) {
            cout << id() << " == " << controlling_id << endl; 

            auto k = e.value()["key"].get<std::string>();
            //! Sends a Move left signal to the block when 'a' is pressed
            if ( k == "a" && !on_bottom_piece) {
                cout << "id " << id() << " Before move Left Sensor_value(2) is " << sensor_value(2) << "\n";

                if ( sensor_value(2) >= (MOVE_OVER + SPACE_BETWEEN_BLOCK) ) {
                    emit(Event("move_left", {{ "id", id() }}));    
                }         
            //! Sends a Move right signal to the block when 'd' is pressed
            } else if ( k == "d" && !on_bottom_piece) {
                cout << "id " << id() << " Before move Right Sensor_value(0) is " << sensor_value(0) << "\n";

                if ( sensor_value(0) >= (MOVE_OVER + SPACE_BETWEEN_BLOCK) ) {
                    emit(Event("move_right", {{ "id", id() }})); 
                }
            } 
        } else { 
            // cout << id() << " doing nothing because I am not in control." << endl;
        }
    });        
    //! On move_left signal, block will move left 
    watch("move_left", [this](Event e) {
        if ( id() == e.value()["id"] ) {
            goal_x = position().x - MOVE_OVER;
        } 
        //cout << "goal_x is " << goal_x <<"\n";
    });

    watch("move_right", [this](Event e) {
        if ( id() == e.value()["id"] ) {
            goal_x = position().x + MOVE_OVER;
        }
        //cout << "goal_x is " << goal_x <<"\n";
    }); 

    watch("move_down", [this](Event e) {
        if ( id() == e.value()["id"] ) {
            goal_y = position().y + MOVE_OVER; 
        }
        cout << "id " << id() << " Sensor_value(1) is " << sensor_value(1) << "\n";

    }); 

}

void blockController::start() {
    controlling_id = id();
    // cout << "set controlling id to " << controlling_id << "\n";

}
void blockController::update() {
    if ( sensor_value(1) >= (MOVE_OVER + SPACE_BETWEEN_BLOCK) && !on_bottom_piece ){
        emit(Event("move_down", {{ "id", id() }}));
    } else {
        on_bottom_piece = true;
    }
    cout << "id " << id() << " Before teleport ( " << position().x << " , " << position().y << " )" << "\n";

	teleport(goal_x, goal_y, 0);
    cout << "id " << id() << " After teleport ( " << position().x << " , " << position().y << " )" << "\n";

    if (on_bottom_piece == true && new_agent == false) {
        add_agent("block", 0, 0, 0, BLOCK_STYLE);
        new_agent = true;
    }
}
void blockController::stop() {}