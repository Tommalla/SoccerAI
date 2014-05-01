#include "Status.hpp"

MCTSStatus::MCTSStatus()
: StatusTemplate<MCTSStatus>{}
, wins{0}
, plays{0} {}

void MCTSStatus::reset() {
	StatusTemplate<MCTSStatus>::reset();
	lastMoveId = -1;
	wins = plays = 0;
}

AlphaBetaStatus::AlphaBetaStatus()
: StatusTemplate<AlphaBetaStatus>{}
, hash{0} {}

void AlphaBetaStatus::reset() {
	StatusTemplate<AlphaBetaStatus>::reset();
	hash = 0;
}
