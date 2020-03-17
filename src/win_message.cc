#include <iostream>
#include <vector>
#include "win_message.h"

using namespace enviro;
using namespace std;

// Put your implementations here
win_messageController::win_messageController() : Process(), AgentInterface() {}

void win_messageController::init() {

	watch("adding_agent", [&](Event& e) {
		controlling_id = e.value()["id"];
		existing_agents.push_back(controlling_id);
		cout << "id being added to vector is " << controlling_id << "\n";
	});

	watch("button_click", [&](Event& e) {
        if ( e.value()["value"] == "Reset" ) {
            while ( !existing_agents.empty()) {
                    remove_agent(existing_agents.back());
                    existing_agents.pop_back();
                }
              
                add_agent("block", 0, 0, 0, BLOCK_STYLE);   
            }
    
    });
    watch("win", [&](Event& e) {
		win = true;
	});
}
void win_messageController::start() {
	win = false;
}
void win_messageController::update() {
	if ( win ) {
		label("YOU WIN!", 0, 0); 
	} else {
		clear_label();
	}
}
void win_messageController::stop() {}