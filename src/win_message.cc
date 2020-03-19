#include <iostream>
#include <vector>
#include "win_message.h"

using namespace enviro;
using namespace std;

// Put your implementations here
win_messageController::win_messageController() : Process(), AgentInterface() {}

//! Display Win Message.
void win_messageController::init() {
    watch("win", [&](Event& e) {
		label("YOU WIN! Rerun Enviro", -70, 5);
	});
}
void win_messageController::start() {}

//! If the block reaches the finish line, a lable "You Win!" will display. 
void win_messageController::update() {}
void win_messageController::stop() {}