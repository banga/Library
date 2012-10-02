#include "binomial_heap.h"
#include <iostream>

namespace lib {

  template <class T>
  void BinomialHeap<T>::Node::Print() {
    std::cout << key_ << "(" << degree_ << "): ";
    if (child_)
      std::cout << "Child = " << child_->key_ << " ";
    if (sibling_)
      std::cout << "Sibling = " << sibling_->key_;
    std::cout << std::endl;

    if (sibling_)
      sibling_->Print();
    if (child_)
      child_->Print();
  }

}  // namespace lib
