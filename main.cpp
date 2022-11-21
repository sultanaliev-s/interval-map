#include <iostream>
#include "interval_map.hpp"

using namespace std;

class Key {
    public:
    
    int k;

    Key(int i) : k(i) {
    }

    Key(const Key& other)
    {
        k = other.k;
    }

    Key& operator=(const Key& other)
    {
        k = other.k;
        return *this;
    }

    bool operator<(const Key& other) const {
        return k < other.k;
    }
};

class Val {
    public:

    int v;

    Val(int i) : v(i) {
    }

    Val(const Val& other)
    {
        v = other.v;
    }

    Val& operator=(const Val& other)
    {
        v = other.v;
        return *this;
    }

    bool operator==(const Val& other) const {
        return v == other.v;
    }
};

bool assertSz(int actual, int expected) {
    return actual == expected;
}

bool assert(int actual, int expected) {
    return actual == expected;
}

bool assert(Val actual, Val expected) {
    return actual == expected;
}

bool assert(Val actual, int expected) {
    return actual == Val(expected);
}

void testEmpty() {
    interval_map<Key, Val> m(0);
    m.insert(Key(1), Key(3), Val(1));
    bool res = assertSz(m.size(), 1);

    if (!res) {
        cout << "testEmpty failed" << endl;
    }
}

void testBeginButNotEnd() {
    interval_map<Key, Val> m(0);
    m.set(Key(2), Val(2));
    m.insert(Key(1), Key(3), Val(1));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(1)), Val(1));

    if (!res) {
        cout << "testBeginButNotEnd failed" << endl;
    }
}

void testBeginAndEnd() {
    interval_map<Key, Val> m(0);
    m.set(Key(3), Val(2));
    m.insert(Key(1), Key(3), Val(1));
    bool res = assertSz(m.size(), 2);
    res &= assert(m.get(Key(1)), 1);
    res &= assert(m.get(Key(3)), 2);

    if (!res) {
        cout << "testBeginAndEnd failed" << endl;
    }
}

void testHasElementsEqualTo() {
    interval_map<Key, Val> m(0);
    m.set(Key(1), Val(1));
    m.set(Key(2), Val(2));
    m.insert(Key(2), Key(5), Val(10));
    bool res = assertSz(m.size(), 2);
    res &= assert(m.get(Key(1)), 1);
    res &= assert(m.get(Key(2)), 10);

    if (!res) {
        cout << "testHasElementsEqualTo failed" << endl;
    }
}

void testHasElementsEqualToAndIsNotLast() {
    interval_map<Key, Val> m(0);
    m.set(Key(1), Val(1));
    m.set(Key(2), Val(2));
    m.set(Key(5), Val(30));
    m.insert(Key(2), Key(5), Val(10));
    bool res = assertSz(m.size(), 3);
    res &= assert(m.get(Key(1)), 1);
    res &= assert(m.get(Key(2)), 10);
    res &= assert(m.get(Key(5)), 30);

    if (!res) {
        cout << "testHasElementsEqualToAndIsNotLast failed" << endl;
    }
}

void testHasElementsInsideNewInterval() {
    interval_map<Key, Val> m(0);
    m.set(Key(2), Val(2));
    m.set(Key(3), Val(3));
    m.set(Key(5), Val(30));
    m.insert(Key(1), Key(6), Val(10));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(1)), 10);

    if (!res) {
        cout << "testHasElementsInsideNewInterval failed" << endl;
    }
}

void testHasElementsInsideNewIntervalDefaultVal() {
    interval_map<Key, Val> m(0);
    m.set(Key(2), Val(2));
    m.set(Key(3), Val(3));
    m.set(Key(5), Val(30));
    m.insert(Key(1), Key(6), Val(0));
    bool res = assertSz(m.size(), 0);

    if (!res) {
        cout << "testHasElementsInsideNewIntervalDefaultVal failed" << endl;
    }
}

void testIntervalThatIsAlreadyIncluded() {
    interval_map<Key, Val> m(0);
    m.set(Key(1), Val(1));
    m.set(Key(5), Val(30));
    m.insert(Key(2), Key(4), Val(1));
    bool res = assertSz(m.size(), 2);
    res &= assert(m.get(Key(1)), 1);
    res &= assert(m.get(Key(5)), 30);
    res &= assert(m.get(Key(2)), 0);

    if (!res) {
        cout << "testIntervalThatIsAlreadyIncluded failed" << endl;
    }
}

void testIntervalThatIsNeighbouringSameValues() {
    interval_map<Key, Val> m(0);
    m.set(Key(1), Val(1));
    m.set(Key(4), Val(4));
    m.set(Key(6), Val(1));
    m.insert(Key(4), Key(6), Val(1));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(1)), 1);


    if (!res) {
        cout << "testIntervalThatIsNeighbouringSameValues failed" << endl;
    }
}

void testIntervalThatIsNeighbouringSameValues2() {
    interval_map<Key, Val> m(0);
    m.set(Key(1), Val(1));
    m.set(Key(5), Val(4));
    m.set(Key(8), Val(1));
    m.insert(Key(4), Key(8), Val(1));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(1)), 1);


    if (!res) {
        cout << "testIntervalThatIsNeighbouringSameValues2 failed" << endl;
    }
}

void testIntervalThatIsNeighbouringSameValues3() {
    interval_map<Key, Val> m(0);
    m.set(Key(1), Val(1));
    m.set(Key(5), Val(4));
    m.set(Key(8), Val(1));
    m.insert(Key(4), Key(10), Val(1));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(1)), 1);


    if (!res) {
        cout << "testIntervalThatIsNeighbouringSameValues3 failed" << endl;
    }
}

void testInsertDefault() {
    interval_map<Key, Val> m(-1);
    m.insert(Key(4), Key(10), Val(-1));
    bool res = assertSz(m.size(), 0);

    if (!res) {
        cout << "testInsertDefault failed" << endl;
    }
}

void testMakeDefaultFromMultipleIntervals() {
    interval_map<Key, Val> m(-1);
    m.set(Key(1), Val(1));
    m.set(Key(3), Val(-1));
    m.set(Key(5), Val(1));
    m.set(Key(8), Val(-1));
    bool res = assertSz(m.size(), 4);
    m.insert(Key(0), Key(3), Val(-1));
    res &= assertSz(m.size(), 2);
    m.insert(Key(3), Key(6), Val(-1));
    res &= assertSz(m.size(), 0);

    if (!res) {
        cout << "testMakeDefaultFromMultipleIntervals failed" << endl;
    }
}

void testInsertSameIntervals() {
    interval_map<Key, Val> m(-1);

    m.insert(Key(0), Key(5), Val(1));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(0)), 1);
    res &= assert(m[Key(1)], 1);

    m.insert(Key(4), Key(10), Val(1));
    res &= assertSz(m.size(), 1);
    res &= assert(m.get(Key(0)), 1);
    res &= assert(m[Key(1)], 1);

    m.insert(Key(10), Key(10), Val(1));
    res &= assertSz(m.size(), 1);
    res &= assert(m.get(Key(0)), 1);
    res &= assert(m[Key(1)], 1);

    if (!res) {
        cout << "testInsertSameIntervals failed" << endl;
    }
}

void testInsertDifferentIntervals() {
    interval_map<Key, Val> m(-1);

    m.insert(Key(0), Key(5), Val(1));
    bool res = assertSz(m.size(), 1);
    res &= assert(m.get(Key(0)), 1);
    res &= assert(m[Key(1)], 1);

    m.insert(Key(4), Key(10), Val(2));
    res &= assertSz(m.size(), 2);
    res &= assert(m.get(Key(4)), 2);
    res &= assert(m[Key(5)], 2);

    m.insert(Key(10), Key(15), Val(-1));
    res &= assertSz(m.size(), 3);
    res &= assert(m.get(Key(10)), -1);
    res &= assert(m[Key(11)], -1);

    if (!res) {
        cout << "testInsertDifferentIntervals failed" << endl;
    }
}

void testHasElementLessThan() {
    interval_map<Key, Val> m(-1);
    m.set(Key(1), Val(1));
    m.set(Key(5), Val(2));
    m.set(Key(10), Val(3));

    m.insert(Key(11), Key(15), Val(5));
    bool res = assertSz(m.size(), 4);
    res &= assert(m.get(Key(11)), 5);
    res &= assert(m[Key(15)], 5);

    if (!res) {
        cout << "testHasElementLessThan failed" << endl;
    }
}

void testHasElementLessThanAndIsNotLast() {
    interval_map<Key, Val> m(-1);
    m.set(Key(1), Val(1));
    m.set(Key(5), Val(2));
    m.set(Key(10), Val(3));
    m.set(Key(17), Val(20));

    m.insert(Key(11), Key(15), Val(5));
    bool res = assertSz(m.size(), 5);
    res &= assert(m.get(Key(11)), 5);
    res &= assert(m[Key(15)], 5);
    res &= assert(m[Key(18)], 20);

    if (!res) {
        cout << "testHasElementLessThanAndIsNotLast failed" << endl;
    }
}

int main() {
    testEmpty();
    testBeginButNotEnd();
    testBeginAndEnd();
    testHasElementsEqualTo();
    testHasElementsEqualToAndIsNotLast();
    testHasElementsInsideNewInterval();
    testHasElementsInsideNewIntervalDefaultVal();
    testIntervalThatIsAlreadyIncluded();
    testIntervalThatIsNeighbouringSameValues();
    testIntervalThatIsNeighbouringSameValues2();
    testIntervalThatIsNeighbouringSameValues3();
    testInsertDefault();
    testMakeDefaultFromMultipleIntervals();
    testInsertSameIntervals();
    testInsertDifferentIntervals();
    testHasElementLessThan();
    testHasElementLessThanAndIsNotLast();

    return 0;
}