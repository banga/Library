namespace lib {

double Random();

template <typename K, typename V=K>
class SkipList {
  public:
    SkipList(int max_level=16, double p=0.5)
        : max_level_(max_level), p_(p) {
      header_ = new Node(K(), V(), max_level_);
      for (int i = 0; i <= max_level_; ++i)
        header_->next_[i] = 0;
    }

    ~SkipList() {
      Node *n = header_;
      while (n) {
        Node *next = n->next_[0];
        delete n;
        n = next;
      }
    }

    void Insert(const K& key) {
      Insert(key, key);
    }

    void Insert(const K& key, const V& value) {
      Node *new_node = MakeNode(key, value);
      Node *update[new_node->level_+1];
      Node *n = header_;

      for (int i = max_level_; i >= 0; --i) {
        while (n->next_[i] && n->next_[i]->key_ < key) {
          n = n->next_[i];
        }
        if (i <= new_node->level_) {
          update[i] = n;
        }
      }

      for (int i = new_node->level_; i >= 0; --i) {
        new_node->next_[i] = update[i]->next_[i];
        update[i]->next_[i] = new_node;
      }
    }

    V* Find(const K& key) {
      Node *n = header_;

      for (int i = max_level_; i >= 0; --i) {
        while (n->next_[i] && n->next_[i]->key_ < key) {
          n = n->next_[i];
        }
        if (n->next_[i] && n->next_[i]->key_ == key) {
          return &n->next_[i]->value_;
        }
      }

      return 0;
    }

    void Delete(const K& key) {
      Node *update[max_level_+1];
      Node *n = header_;
      for (int i = max_level_; i >= 0; --i) {
        while (n->next_[i] && n->next_[i]->key_ < key) {
          n = n->next_[i];
        }
        update[i] = n;
      }

      n = n->next_[0];

      if (n) {
        for (int i = 0; i <= n->level_; ++i) {
          update[i]->next_[i] = n->next_[i];
        }
      }

      delete n;
    }

    int Size() {
      Node *n = header_->next_[0];
      int size = 0;

      while (n) {
        n = n->next_[0];
        ++size;
      }
      
      return size;
    }

  private:
    class Node {
      public:
        K key_;
        V value_;
        int level_;
        Node** next_;

        Node(const K& key, const V& value, int level)
            : key_(key), value_(value), level_(level), next_(0) {
          next_ = new Node*[level_+1];
        }

        ~Node() {
          delete[] next_;
        }
    };

    int max_level_;
    double p_;
    Node* header_;

    Node* MakeNode(const K& key, const V& value) {
      int level = 0;
      while (level < max_level_ && Random() > p_) {
        ++level;
      }
      return new Node(key, value, level);
    }
};

}  // namespace lib
