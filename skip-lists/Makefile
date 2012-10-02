CC=g++
CFLAGS=-Wall -g
SRCS=skip_list.h skip_list.cc skip_list_test.cc
OBJS=skip_list.o skip_list_test.o
TARGETS=skip_list_test

# Main library
skip_list.o: skip_list.cc skip_list.h
	$(CC) $(CFLAGS) -c skip_list.cc -o skip_list.o

# Use Google's testing framework
GTEST_DIR=../googletest
TEST_FLAGS=$(CFLAGS) -I$(GTEST_DIR)/include

libgtest.a: $(GTEST_DIR)/make/gtest-all.o
	ar -rv libgtest.a $(GTEST_DIR)/make/gtest-all.o

$(GTEST_DIR)/make/gtest-all.o:
	cd $(GTEST_DIR)/make; make;

# Test file
skip_list_test.o: skip_list_test.cc
	$(CC) $(TEST_FLAGS) -c skip_list_test.cc -o skip_list_test.o

skip_list_test: $(OBJS) libgtest.a
	$(CC) $(TEST_FLAGS) libgtest.a -o skip_list_test $(OBJS)

test: skip_list_test
	./skip_list_test

lint:
	cpplint.py --filter=-legal $(SRCS)

clean:
	rm $(OBJS) $(TARGETS) 
