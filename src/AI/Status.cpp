#include "Status.hpp"

GraphStatus::GraphStatus()
: hash{0} {}

void GraphStatus::reset() {
	hash = 0;
}

MCTSStatus::MCTSStatus()
: wins{0}
, plays{0}
, lastMoveId{-1} {}

void MCTSStatus::reset() {
	wins = plays = 0;
	lastMoveId = -1;
}

bool MCTSStatus::isLeaf() const {
	return false;
}

TreeMCTSStatus::TreeMCTSStatus()
: MCTSStatus{}
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

void TreeMCTSStatus::reset() {
	MCTSStatus::reset();
	firstChild = nullptr;
	numChildren = 0;
}

bool TreeMCTSStatus::isLeaf() const {
	return firstChild == nullptr;
}

AlphaBetaStatus::AlphaBetaStatus()
: GraphStatus{}
, alpha{0}
, beta{0} {}

void AlphaBetaStatus::reset() {
	hash = 0;
	alpha = beta = 0;
}