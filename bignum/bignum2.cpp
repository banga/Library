#include <vector>
#include <cstdio>

using std::vector;

class bignum {
	static const int BITS = 32;
	static const unsigned long long MASK = 0xFFFFFFFF;
	public:
	vector<unsigned int> a;

	bignum(unsigned int x = 0) {
		a.push_back(x);
	}

	bignum& operator = (bignum b) {
		a.clear();
		for(int i = 0; i < b.a.size(); i++)
			a.push_back(b.a[i]);
		return *this;
	}

	bignum operator * (unsigned int x) {
		unsigned long long cy = 0, sum = 0;
		bignum bn;
		bn.a.clear();
		for(int i = 0; i < a.size(); i++) {
			sum = ((unsigned long long)a[i]*x+cy);
			bn.a.push_back(sum & MASK);
			cy = sum >> BITS;
			printf("sum = %llu a[%d] = %u cy = %llu\n", sum, i, (unsigned int)(sum & MASK), cy);
		}
		while(cy) {
			bn.a.push_back(cy & MASK);
			cy >>= BITS;
		}
		return bn;
	}

	void fdiv(unsigned int x, bignum* q, unsigned int* r) {
		unsigned long long cy = 0;
		vector<unsigned int> qa;
		for(int i = a.size()-1; i >= 0; i--) {
			cy = (cy << 32) + a[i];
			qa.push_back(cy / x);
			cy = cy % x;
		}
		*r = cy;
		q->a.clear();

		while(qa.size() && qa[qa.size()-1] == 0) qa.pop_back();
		for(int i = qa.size()-1; i >= 0; i--)
			q->a.push_back(qa[i]);
	}

	bignum pow(unsigned int n) {
		if(n == 1) return *this;
		bignum bn = this->pow(n >> 1);
		bn = bn * bn;
		if(n & 1)
			bn = bn * (*this);
		return bn;
	}

	bool isZero() {
		for(int i = 0; i < a.size(); i++)
			if(a[i]) return false;
		return true;
	}


	void print() {
		printf("[");
		printf("%d: ", a.size());
		for(int i = a.size()-1; i >= 0; i--) {
			printf("%u", a[i]);
			if(i) printf(", ");
		}
		printf("]");
	}

	void printDecimal() {
		static const unsigned int BASE = 1000000;
		bignum x = *this;
		unsigned int d;
		vector<unsigned int> digits;
		while(!x.isZero()) {
			x.fdiv(BASE, &x, &d);
			digits.push_back(d);
		}
		printf("%u", digits[digits.size()-1]);
		for(int i = digits.size()-2; i >= 0; i--)
			printf("%06u", digits[i]);
		printf(" ");
	}
};

int main() {
	bignum b(99712);
	bignum q;
	int r;

	b.print(); printf("\n");
	b.printDecimal(); printf("\n");
	b = b * 234512;
	b.print(); printf("\n");
	b.printDecimal(); printf("\n");
	b = b * 99668;
	b.print(); printf("\n");
	b.printDecimal(); printf("\n");
//	b.fdiv(99712, &q, &r);
//	q.print();
//	printf("%d\n", r);

	return 0;
}
