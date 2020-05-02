#ifndef MODEL_SCORING_SCORENODE_H
#define MODEL_SCORING_SCORENODE_H

#include "ScoreEntry.h"

namespace model {
namespace scoring {

/**
 * Node used by the ScoreBoard to store ScoreEntry objects.
 */
class ScoreNode {
public:
    /**
     * Construct a new ScoreNode.
     *
     * @pre entry != nullptr
     *
     * @param entry score entry to hold
     */
    ScoreNode(ScoreEntry* entry);
    /**
     * Destructor.
     */
    virtual ~ScoreNode();

    /**
     * Get the stored score entry.
     *
     * @return the score entry
     */
    const ScoreEntry* getEntry() const;
    /**
     * Compare this node to another for sorting.
     *
     * @pre other != nullptr
     *
     * @param other node to compare to
     * @param sortType sorting method to compare by
     *
     * @return comparison result
     */
    int compare(const ScoreNode* other, ScoreEntry::SortType sortType) const;
    /**
     * Get the next node in the list.
     *
     * @param sortType sorting method to get next node by
     *
     * @return the next node in the list
     */
    ScoreNode* getNext(ScoreEntry::SortType sortType) const;
    /**
     * Insert a new node in the list after this one.
     *
     * @pre node != null
     * @post this->getNext(sortType) == node, node->getNext(sortType) == this->getNext(sortType)@prev
     *
     * @param node node to insert
     * @param sortType sorting method to insert on
     */
    void insertNext(ScoreNode* node, ScoreEntry::SortType sortType);
    /**
     * Set the next node in the list.
     *
     * @post this->getNext(sortType) == node
     *
     * @param node node to set
     * @param sortType sorting method to insert on
     */
    void setNext(ScoreNode* node, ScoreEntry::SortType sortType);

private:
    ScoreEntry* entry;
    ScoreNode* nextTime;
    ScoreNode* nextPuzzle;
};

} // namespace scoring
} // namespace model

#endif // MODEL_SCORING_SCORENODE_H
