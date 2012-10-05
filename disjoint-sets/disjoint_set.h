#ifndef DISJOINT_SETS_DISJOINT_SET_H_
#define DISJOINT_SETS_DISJOINT_SET_H_

/*
 * An implementation of the disjoin-set forests data structure with path 
 * compression and union by rank
 */

namespace lib {

template <typename Key>
class DisjointSet {
  public:
    const Key& key() {
      return key_;
    }

    DisjointSet(const Key& key)
      : key_(key), rank_(1), parent_(this) { }

    DisjointSet* FindSet() {
      if (parent_ != this)
        parent_ = parent_->FindSet();
      return parent_;
    }

    void Union(DisjointSet &other) {
      DisjointSet *root = FindSet(), *other_root = other.FindSet();

      if (root == other_root)
        return;

      if (root->rank_ > other_root->rank_) {
        other_root->parent_ = root;
      } else if (root->rank_ < other_root->rank_) {
        root->parent_ = other_root->parent_;
      } else {
        other_root->parent_ = root;
        ++root->rank_;
      }
    }

  private:
    Key key_;
    DisjointSet *parent_;
    int rank_;
};

}  // namespace lib

#endif  // DISJOINT_SETS_DISJOINT_SET_H_
