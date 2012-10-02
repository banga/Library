CC=g++
CFLAGS=-Wall -g
SRCS=binomial_heap.h binomial_heap.cc binomial_heap_test.cc
OBJS=binomial_heap.o binomial_heap_test.o
TARGETS=binomial_heap_test

# Main library
binomial_heap.o: binomial_heap.cc binomial_heap.h
	$(CC) $(CFLAGS) -c binomial_heap.cc -o binomial_heap.o

# Use Google's testing framework
GTEST_DIR=../googletest
TEST_FLAGS=$(CFLAGS) -I$(GTEST_DIR)/include

libgtest.a: $(GTEST_DIR)/make/gtest-all.o
	ar -rv libgtest.a $(GTEST_DIR)/make/gtest-all.o

$(GTEST_DIR)/make/gtest-all.o:
	cd $(GTEST_DIR)/make; make;

# Test file
binomial_heap_test.o: binomial_heap_test.cc binomial_heap.h
	$(CC) $(TEST_FLAGS) -c binomial_heap_test.cc -o binomial_heap_test.o

binomial_heap_test: $(OBJS) libgtest.a
	$(CC) $(TEST_FLAGS) libgtest.a -o binomial_heap_test $(OBJS)

test: binomial_heap_test
	./binomial_heap_test

lint: $(SRCS)
	cpplint.py --filter=-legal $(SRCS)

clean:
	rm $(OBJS) $(TARGETS) 
