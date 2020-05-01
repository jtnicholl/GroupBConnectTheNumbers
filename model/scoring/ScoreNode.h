#ifndef MODEL_SCORING_SCORENODE_H
#define MODEL_SCORING_SCORENODE_H

#include "ScoreEntry.h"

namespace model {
namespace scoring {

class ScoreNode {
public:
    ScoreNode(ScoreEntry* entry);
    virtual ~ScoreNode();

    const ScoreEntry* getEntry() const;
    int compare(const ScoreNode* other, ScoreEntry::SortType sortType) const;
    ScoreNode* getNext(ScoreEntry::SortType sortType) const;
    void insertNext(ScoreNode* node, ScoreEntry::SortType sortType);

private:
    ScoreEntry* entry;
    ScoreNode* nextTime;
    ScoreNode* nextPuzzle;
};

} // namespace scoring
} // namespace model

#endif // MODEL_SCORING_SCORENODE_H
