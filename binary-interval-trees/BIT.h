/**
 * Binary Indexed Tree
 * As described in http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
 * Author: Shrey Banga
 */
typedef struct BIT {
  BIT(const BIT& b)
  : size(b.size), elems(0) {
    elems = new int[size];
    for(unsigned int i = 0; i < size; i++)
      elems[i] = b.elems[i];
  }

  BIT& operator = (const BIT& b) {
    delete[] elems;

    size = b.size;
    elems = new int[size];

    for(unsigned int i = 0; i < size; i++)
      elems[i] = b.elems[i];
    
    return *this;
  }

  BIT(unsigned int maxIdx) 
  : size(maxIdx + 1), elems(0) {
    elems = new int[size]();
  }

  ~BIT() {
    delete[] elems;
  }

  void add(unsigned int idx, int value) {
    idx++; // internally stored from index 1

    while(idx < size) {
      elems[idx] += value;
      idx += (idx & -idx);
    }
  }

  int readCumulative(unsigned int idx) {
    idx++; // internally stored from index 1

    int sum = 0;
    while(idx) {
      sum += elems[idx];
      idx = idx & (idx - 1);
    }

    return sum;
  }

  int readSingle(unsigned int idx) {
    idx++; // internally stored from index 1

    int sum = 0;
    if(idx) {
      sum = elems[idx];
      unsigned int common = idx - (idx & -idx);
      idx--;
      while(idx != common) {
        sum -= elems[idx];
        idx = idx & (idx - 1);
      }
    }
    return sum;
  }

  unsigned int size;
  int *elems;
} BIT;
