CC=g++
CFLAGS=-Wall -g
SRCS=disjoint_set.h disjoint_set.cc disjoint_set_test.cc
OBJS=disjoint_set.o disjoint_set_test.o
TARGETS=disjoint_set_test

# Main library
disjoint_set.o: disjoint_set.cc disjoint_set.h
	$(CC) $(CFLAGS) -c disjoint_set.cc -o disjoint_set.o

# Use Google's testing framework
GTEST_DIR=../googletest
TEST_FLAGS=$(CFLAGS) -I$(GTEST_DIR)/include

libgtest.a: $(GTEST_DIR)/make/gtest-all.o
	ar -rv libgtest.a $(GTEST_DIR)/make/gtest-all.o

$(GTEST_DIR)/make/gtest-all.o:
	cd $(GTEST_DIR)/make; make;

# Test file
disjoint_set_test.o: disjoint_set_test.cc disjoint_set.h
	$(CC) $(TEST_FLAGS) -c disjoint_set_test.cc -o disjoint_set_test.o

disjoint_set_test: $(OBJS) libgtest.a
	$(CC) $(TEST_FLAGS) libgtest.a -o disjoint_set_test $(OBJS)

test: disjoint_set_test
	./disjoint_set_test

lint: $(SRCS)
	cpplint.py --filter=-legal $(SRCS)

clean:
	rm $(OBJS) $(TARGETS) libgtest.a
