#include "Status.hpp"

GraphStatus::GraphStatus()
: hash{0} {}

MCTSStatus::MCTSStatus()
: wins{0}
, plays{0} {}

TreeMCTSStatus::TreeMCTSStatus()
: MCTSStatus{}
, lastMoveId{-1}
, firstChild{nullptr}
, numChildren{0} {}

TreeMCTSStatus* TreeMCTSStatus::getFirstChild() const {
	return firstChild;
}

size_t TreeMCTSStatus::getNumChildren() const {
	return numChildren;
}

void TreeMCTSStatus::setChildren(TreeMCTSStatus* firstChild, const size_t& numChildren) {
	this->firstChild = firstChild;
	this->numChildren = numChildren;
}

AlphaBetaStatus::AlphaBetaStatus()
: GraphStatus{}
, result{0} {}