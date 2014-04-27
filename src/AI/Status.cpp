#include "Status.hpp"

MCTSStatus::MCTSStatus()
: wins{0}
, plays{0} {}

void MCTSStatus::reset() {
	StatusTemplate<MCTSStatus>::reset();
	lastMoveId = -1;
	wins = plays = 0;
}