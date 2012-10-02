#ifndef BINOMIAL_HEAPS_BINOMIAL_HEAP_H_
#define BINOMIAL_HEAPS_BINOMIAL_HEAP_H_

namespace lib {

template <typename K>
class BinomialHeap {
  public:
    BinomialHeap()
      : head_(0) { }

    explicit BinomialHeap(const K& key)
      : head_(new Node(key)) { }

    ~BinomialHeap() {
      DeleteTree(head_);
    }

    void Insert(const K& key) {
      BinomialHeap<K> heap(key);
      Union(&heap);
    }

    bool ExtractMinimum(K *key) {
      if (!head_) {
        return false;
      }

      Node *min = head_, *pmin = 0;
      Node *prev = head_, *n = head_->sibling_;
      while (n) {
        if (n->key_ < min->key_) {
          min = n;
          pmin = prev;
        }
        prev = n;
        n = n->sibling_;
      }

      if (pmin) {
        pmin->sibling_ = min->sibling_;
      } else {
        head_ = head_->sibling_;
      }

      if (min->child_) {
        BinomialHeap heap;
        MakeHeapFromChildren(min, &heap);
        Union(&heap);
      }

      *key = min->key_;
      delete min;
      return true;
    }

    K *Minimum() {
      if (!head_) {
        return 0;
      }

      Node *min = head_;
      for (Node *n = head_->sibling_; n; n = n->sibling_) {
        if (n->key_ < min->key_)
          min = n;
      }

      return &min->key_;
    }

    void Union(BinomialHeap *heap) {
      Merge(heap);

      if (!head_ || !head_->sibling_)
        return;

      Node *prev = 0, *n = head_, *next = head_->sibling_;
      while (next) {
        if ((n->degree_ != next->degree_)
            /* 3 nodes of equal degree */
            || (next->sibling_ && n->degree_ == next->sibling_->degree_)) {
          prev = n;
          n = next;
        } else {
          if (n->key_ <= next->key_) {
            n->sibling_ = next->sibling_;
            Node::Link(next, n);
          } else {
            if (!prev) {
              head_ = next;
            } else {
              prev->sibling_ = next;
            }
            Node::Link(n, next);
            n = next;
          }
        }
        next = n->sibling_;
      }
    }

    void Print() {
      if (head_)
        head_->Print();
    }

  private:
    void Merge(BinomialHeap *heap) {
      if (!heap || !heap->head_) return;

      if (!head_) {
        head_ = heap->head_;
        heap->head_ = 0;
        return;
      }

      Node *n = 0;
      Node *p = head_, *q = heap->head_;

      if (p->degree_ <= q->degree_) {
        n = p;
        p = p->sibling_;
      } else {
        n = q;
        q = q->sibling_;
      }
      head_ = n;

      while (p && q) {
        if (p->degree_ <= q->degree_) {
          n->sibling_ = p;
          p = p->sibling_;
        } else {
          n->sibling_ = q;
          q = q->sibling_;
        }
        n = n->sibling_;
      }

      while (p) {
        n->sibling_ = p;
        n = n->sibling_;
        p = p->sibling_;
      }

      while (q) {
        n->sibling_ = q;
        n = n->sibling_;
        q = q->sibling_;
      }

      heap->head_ = 0;
    }

    class Node {
      public:
        K key_;
        int degree_;
        Node *parent_;
        Node *sibling_;
        Node *child_;

        explicit Node(const K& key)
          : key_(key), degree_(0), parent_(0), sibling_(0), child_(0) { }

        void Print();

        static void Link(Node *node, Node *root) {
          node->parent_ = root;
          node->sibling_ = root->child_;
          root->child_ = node;
          ++root->degree_;
        }
    };

    Node *head_;

    static void MakeHeapFromChildren(Node *node, BinomialHeap *heap) {
      heap->head_ = 0;
      Node *n = node->child_;
      while (n != 0) {
        Node *next = n->sibling_;
        n->sibling_ = heap->head_;
        n->parent_ = 0;
        heap->head_ = n;
        n = next;
      }
    }

    void DeleteTree(Node *n) {
      if (n) {
        DeleteTree(n->child_);
        DeleteTree(n->sibling_);
        delete n;
      }
    }
};

}  // namespace lib

#endif  // BINOMIAL_HEAPS_BINOMIAL_HEAP_H_
