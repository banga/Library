#include <iostream>
#include <exception>
#include <stdexcept>
#include <time.h>

using namespace std;

template <class T>
class vector {
	T* elems;
	size_t capacity, count;
public:
	typedef T* iterator;

	vector() 
	: capacity(0), count(0), elems(0) {
		reserve(8);
	}

	vector(size_t n, const T& value = T()) 
	: capacity(0), count(0), elems(0) {
		reserve(n);
		for(count = 0; count < n; count++)
			elems[count] = value;
	}

	void reserve(size_t size) {
		if(capacity < size) {
			T* new_elems = new T[size];
			if(!new_elems)
				throw runtime_error("Cannot allocate memory");
			if(elems) {
				for(size_t i = 0; i < count; i++)
					new_elems[i] = elems[i];
				delete[] elems;
			}

			cout << "Increased capacity from " << capacity << " to " << size << endl;
			capacity = size;
			elems = new_elems;
		}
	}

	T& operator[] (size_t i) {
		if(i >= count)
			throw range_error("Index out of bounds");
		return elems[i];
	}

	void push_back (const T& x) {
		if(count == capacity)
			reserve(capacity * 2);
		elems[count++] = x;
	}

	void pop_back () {
		if(count == 0)
			throw underflow_error("pop_back() called on empty vector");
		elems[--count] = T();
	}

	T& back() {
		if(count == 0)
			throw range_error("back() called on empty vector");
		return elems[count-1];
	}

	size_t size() {
		return count;
	}

	iterator begin() {
		return iterator(elems);
	}

	iterator end() {
		return iterator(elems + count);
	}
};

template <class iterator, class function>
void for_each (iterator begin, iterator end, function f) {
	for(; begin != end; begin++)
		f(*begin);
}

template <class iterator, class function>
void transform (iterator begin, iterator end, function f) {
	for(; begin != end; begin++)
		*begin = f(*begin);
}

template <class iterator, class value_type>
iterator binary_search(iterator begin, iterator end, value_type value) {
	iterator mid, last = end;
	while(begin < end) {
		mid = begin + (end - begin) / 2;
		if(*mid == value)
			return mid;
		if(*mid > value)
			end = mid;
		else
			begin = mid + 1;
	}
	return last;
}

void print(int x) {
	cout << x << " ";
}

int square(int x) {
	return x + 1;
}

int main() {
	vector<int> a, b(8), c(8,5);
	int x[] = {2, 4, 6, 8, 10};

	a.reserve(100000000);

	try {
		for(int i = 0; i < 100000000; i++)
			a.push_back(i+1);

		//for(vector<int>::iterator it = a.begin(); it != a.end(); it++)
		//	cout << *it << " ";
		//cout << endl;

		//transform(a.begin(), a.end(), square);
		//for_each(a.begin(), a.end(), print);
		//cout << endl;

		//transform(x, x + 5, square);
		//for_each(x, x + 5, print);
		//cout << endl;

		clock_t t = clock();
		cout << *binary_search(a.begin(), a.end(), 5) << endl;
		t = clock() - t;
		cout << t << " " << t / (float) CLOCKS_PER_SEC << endl;
		//cout << endl;
/*
		for(int i = 0; i < b.size(); i++)
			cout << b[i] << " ";
		cout << endl;

		for(int i = 0; i < c.size(); i++)
			cout << c[i] << " ";
		cout << endl;
*/	} catch(exception& e) {
		cout << "Exception caught: " << e.what() << endl;
	}
}
