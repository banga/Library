#include <time.h>
#include <stdio.h>

#define MAXLEN 100000

/* Big Number */
typedef struct{
	char d[MAXLEN];
	int len;
} bignum;

void make_bignum(int n, bignum* bn) {
	for(bn->len = 0; n && bn->len < MAXLEN; bn->len++, n /= 10)
		bn->d[bn->len] = n % 10;
	for(int i = 0, j = bn->len-1; i < j; i++, j--) {
		char c = bn->d[i]; bn->d[i] = bn->d[j]; bn->d[j] = c;
	}
}

void make_bignum(const char* str, bignum* bn) {
	for(bn->len = 0; str[bn->len] && bn->len < MAXLEN; bn->len++)
		bn->d[bn->len] = str[bn->len] - '0';
}

void copy(const bignum& src, bignum* dest) {
	dest->len = src.len;
	for(int i = 0; i < src.len; i++) dest->d[i] = src.d[i];
}

void print(const bignum& n) {
	for(int i = 0; i < n.len; i++) printf("%c", '0'+n.d[i]);
}

void add(const bignum& a, const bignum& b, bignum* s) {
	char sum, cy = 0, d[MAXLEN];
	int i = a.len-1, j = b.len-1, last = MAXLEN-1;
	while(i >= 0 && j >= 0) {
		sum = a.d[i--] + b.d[j--] + cy;
		cy = sum / 10;
		d[last--] = sum % 10;
	}
	while(i >= 0) {
		sum = a.d[i--] + cy;
		cy = sum / 10;
		d[last--] = sum % 10;
	}
	while(j >= 0) {
		sum = b.d[j--] + cy;
		cy = sum / 10;
		d[last--] = sum % 10;
	}
	while(cy) {
		d[last--] = cy % 10;
		cy /= 10;
	}

	s->len = MAXLEN-1-last;
	for(int i = 0; i < s->len; i++) s->d[i] = d[last+i+1];
}

bool greater(const bignum& a, const bignum& b) {
	if(a.len != b.len) return (a.len > b.len);

	for(int i = 0; i < a.len; i++)
		if(a.d[i] != b.d[i])
			return a.d[i] > b.d[i];

	return false;
}

bool subtract(bignum a, bignum b, bignum* s) {
	bool neg = greater(b,a);
	if(neg) {
		subtract(b,a,s);
		return true;
	}

	char dif, bw = 0, d[MAXLEN], da, db;
	int i = a.len-1, j = b.len-1, last = MAXLEN-1;
	while(j >= 0) {
		dif = a.d[i--] - b.d[j--] + bw;
		bw = 0;
		while(dif < 0) {
			bw--;
			dif += 10;
		}
		d[last--] = dif;
	}

	while(i >= 0) {
		dif = a.d[i--] + bw;
		bw = 0;
		while(dif < 0) {
			bw--;
			dif += 10;
		}
		d[last--] = dif;
	}

	while(bw) {
		d[last--] = (10 + bw % 10) % 10;
		bw /= 10;
	}

	while(last < MAXLEN-1 && d[last+1] == 0) last++;

	s->len = MAXLEN-1-last;
	for(int i = 0; i < s->len; i++) s->d[i] = d[last+i+1];

	return false;
}

void halve(const bignum& n, bignum* h) {
	h->len = 0;
	char cy = 0, sum;
	bool begin = true;
	for(int i = 0; i < n.len; i++) {
		sum = n.d[i] + cy*10;
		cy = sum & 1;
		if(begin && sum < 2) continue;
		h->d[h->len++] = sum >> 1;
		begin = false;
	}
}

void multiply(const bignum& a, const bignum& b, bignum* m) {
	m->len = a.len + b.len;

	if(m->len > MAXLEN) {
		printf("\nOVERFLOW in mutliply");
		return;
	}

	int prod, sum, cy = 0;
	for(int k = 0; k < m->len; k++) {
		sum = cy;
		for(int i = k, j = 0; i >= 0 && j < b.len; i--, j++) {
			if(i >= a.len) continue;
			prod = a.d[a.len-1-i] * b.d[b.len-1-j];
			sum += prod;
		}
		cy = sum / 10;
		m->d[m->len-1-k] = sum % 10;
	}

	if(m->d[0] == 0) {
		m->len--;
		for(int i = 0; i < m->len; i++) m->d[i] = m->d[i+1];
	}
}

/* Fractional Number */
typedef struct{
	bignum N, D;
} fracnum;

void make_fracnum(int N, int D, fracnum* f) {
	make_bignum(N, &(f->N)); make_bignum(D, &(f->D));
}

void copy(const fracnum& src, fracnum* dest) {
	copy(src.N, &(dest->N));
	copy(src.D, &(dest->D));
}

void add(const fracnum& a, const fracnum& b, fracnum* c) {
	multiply(a.D, b.D, &c->D);
	bignum t1, t2;
	multiply(a.N, b.D, &t1);
	multiply(a.D, b.N, &t2);
	add(t1, t2, &c->N);
}

void print(const fracnum& f) {
	print(f.N); printf(" / "); print(f.D);
}

clock_t end_t1 = clock() + 21 * CLOCKS_PER_SEC, end_t2 = end_t1 + 3 * CLOCKS_PER_SEC;

void print(fracnum* f) {
	int ints = 0, d;
	while(greater(f->N, f->D)) f->D.len++, ints++;
	bignum t;

	char buf[MAXLEN];
	int i = 0;

	while(clock() < end_t2 && f->N.len < MAXLEN) {
		for(d = 0; d <= 9 && greater(f->N, f->D); d++) {
			subtract(f->N, f->D, &t);
			f->N = t;
		}
		buf[i++] = d+'0';
		f->N.d[f->N.len++] = 0;
		if(ints == 0) buf[i++] = '.';
		ints--;
	}
	buf[i] = 0;

	for(i = 0; buf[i] == '0'; i++);
	printf("%s", buf+i);
}

void eval_e() {
	fracnum sum, term, tf;
	make_fracnum(1, 1, &term);
	make_fracnum(1, 1, &sum);
	bignum t, n;

	int i = 1;
	while(clock() < end_t1) {
		make_bignum(i++, &n);
		multiply(n, term.D, &t);
		copy(t, &term.D);
		add(sum, term, &tf);
		copy(tf, &sum);

		while(sum.N.len > 0 && sum.D.len > 0 && sum.N.d[sum.N.len-1] == 0 
				&& sum.D.d[sum.D.len-1] == 0)
		       sum.N.len--, sum.D.len--;
	}

	print(&sum);
}

int main() {
	//fracnum f;
	//make_fracnum(22, 7, &f);
	//print(&f, 100); printf("\n");
	
	adeval_e();
}
