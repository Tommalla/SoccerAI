#ifndef GRAPH_MCTSAI_HPP
#define GRAPH_MCTSAI_HPP
#include "MCTSAI.hpp"

/**
 * @brief Abstract base class for Graph implementations of MCTS.
 *
 */
class GraphMCTSAI: public MCTSAI {
public:
	GraphMCTSAI(const engine::Coord width, const engine::Coord height, const double& c,
		       const size_t& expandBorder, const size_t& memorySize);

protected:
	virtual void expand(Board& s, MCTSStatus* node);
	virtual std::tuple<MCTSStatus*, MCTSStatus*, DirId> pickSon(Board& s, MCTSStatus* node) const;
	virtual DirId generateMove();
	virtual void resetMemory() = 0;
	virtual bool isLeaf(Board& s, MCTSStatus* node);
	/**
	 * @brief Returns a pair: pointer to the MCTSStatus object representing the node with hash `hash` in MCTS tree
	 * and the boolean value: true if the object was present in the underlying storage, false if it had to be created.
	 * Requires getNode and assertNodeCreated to be implemented.
	 */
	std::pair<MCTSStatus*, bool> getOrCreateNode(const engine::Hash& hash);
	/**
	 * @brief Returns a pair: pointer to the MCTSStatus object representing the edge with hash `hash` in MCTS tree
	 * and the boolean value: true if the object was present in the underlying storage, false if it had to be created.
	 * Requires getNode and assertNodeCreated to be implemented.
	 */
	std::pair<MCTSStatus*, bool> getOrCreateEdge(const engine::Hash& hash);
	/**
	 * @brief Returns a pointer to the MCTSStatus object representing the node with hash `hash` in MCTS tree.
	 * Assumes that assertNodeCreated was run sometime prior to its' invocation. A logical assumption is that
	 * you can require the node to have been created in the underlying storage prior to the invocation of this
	 * method.
	 */
	virtual MCTSStatus* getNode(const engine::Hash& hash) const = 0;
	/**
	 * @brief Returns a pointer to the MCTSStatus object representing the edge with hash `hash` in MCTS tree.
	 * Assumes that assertEdgeCreated was run sometime prior to its' invocation. A logical assumption is that
	 * you can require the edge to have been created in the underlying storage prior to the invocation of this
	 * method.
	 */
	virtual MCTSStatus* getEdge(const engine::Hash& hash) const = 0;
	/**
	 * @brief Creates the node in the underlying storage if it's not present there.
	 *
	 * @return true if the edge was already present, false otherwise.
	 */
	virtual bool assertNodeCreated(const engine::Hash& hash) = 0;
	/**
	 * @brief Creates the edge in the underlying storage if it's not present there.
	 *
	 * @return true if the edge was already present, false otherwise.
	 */
	virtual bool assertEdgeCreated(const engine::Hash& hash) = 0;
	virtual bool isNodeCreated(const engine::Hash& hash) const = 0;
	virtual bool isEdgeCreated(const engine::Hash& hash) const = 0;
};

#endif // GRAPH_MCTSAI_HPP