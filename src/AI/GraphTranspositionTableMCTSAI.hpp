#ifndef GRAPH_TRANSPOSITION_TABLE_MCTS_AI_HPP
#define GRAPH_TRANSPOSITION_TABLE_MCTS_AI_HPP
#include "GraphMCTSAI.hpp"
#include "TranspositionTable.hpp"

class GraphTranspositionTableMCTSAI: public GraphMCTSAI {
	typedef TranspositionTable<GraphMCTSStatus> TTType;
public:
	GraphTranspositionTableMCTSAI(const engine::Coord width, const engine::Coord height, const double& c, const size_t& expandBorder, const size_t& memorySize);

protected:
	virtual void resetMemory();
	virtual DirId generateMove();
	virtual std::pair< MCTSStatus*, bool > getOrCreateNode(const engine::Hash& hash);
	virtual std::pair< MCTSStatus*, bool > getOrCreateEdge(const engine::Hash& hash);
	virtual bool assertNodeCreated(const engine::Hash& hash);
	virtual bool assertEdgeCreated(const engine::Hash& hash);
	virtual MCTSStatus* getNode(const engine::Hash& hash) const;
	virtual MCTSStatus* getEdge(const engine::Hash& hash) const;
	virtual bool isNodeCreated(const engine::Hash& hash) const;
	virtual bool isEdgeCreated(const engine::Hash& hash) const;

private:
	std::pair<MCTSStatus*, bool> getOrCreate(TTType& tt, const engine::Hash& hash);
	template<bool Node>
	void reuseDFS(Board& s);

	TTType nodesTT;
	TTType edgesTT;
};

template<bool Node>
void GraphTranspositionTableMCTSAI::reuseDFS(Board& s) {
	auto moves = s.getMoves();
	int currentValue = getFieldsUsed();
	bool change;
	engine::Hash hash;
	GraphMCTSStatus* iter;

	for (const auto& m: moves) {
		hash = Node ? s.getHashAfter(m) : s.getMoveHash(m);

		if ((Node ? isNodeCreated(hash) : isEdgeCreated(hash)) && (iter = (Node ? nodesTT.get(hash) : edgesTT.get(hash)))->value < currentValue) {
			change = s.play(m);

			iter->value = currentValue;
			reuseDFS<Node>(s);

			s.undo(m, change);
		}
	}
}


#endif // GRAPH_TRANSPOSITION_TABLE_MCTS_AI_HPP