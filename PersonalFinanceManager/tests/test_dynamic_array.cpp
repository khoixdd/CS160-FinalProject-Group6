#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include "../include/DynamicArray.h"

void fillArray (int n, DynamicArray<int> &arr) {
    for (int i = 1; i <= n; ++i) {
        if (arr.size() >= i)
            arr.at(i - 1) = i;
        else
            arr.pushBack(i);
    }
}

void testEmpty() {
    DynamicArray<int> arr;

    assert(arr.size() == 0);
    assert(arr.capacity() >= 0);
}

void testCopyInitialization () {
    DynamicArray<int> arr;
    fillArray(5, arr);

    DynamicArray<int> copy(arr);
 
    assert(copy.size() == arr.size());
    for (int i = 0; i < arr.size(); ++i) {
        assert(copy.at(i) == arr.at(i));
    }

    copy.at(0) = -1;
    copy.pushBack(6);
    assert(arr.at(0) == 1);
    assert(arr.size() == 5);
 
    // int expected[] = {10, 20, 30, 40, 50};
    // assert();
}

void testCopyEmptyArray () {
    DynamicArray<int> emp;
    DynamicArray<int> arr(emp);

    assert(arr.size() == 0);
    assert(arr.capacity() >= arr.size());

    assert(arr.pushBack(1));
    assert(arr.size() == 1);
    assert(emp.size() == 0);
}

void testAssignInitialization () {
    DynamicArray<int> arr;
    DynamicArray<int> tmp;

    fillArray(10, arr);

    tmp = arr;

    assert(tmp.size() == arr.size());
    assert(tmp.capacity() >= tmp.size());

    for (int i = 0; i < tmp.size(); ++i)
        assert(tmp.at(i) == arr.at(i));
}

void testSelfAssignment () {
    DynamicArray<int> arr;
    fillArray(4, arr);
 
    DynamicArray<int>& tmp = arr;  
    arr = tmp;                       
 
    for (int i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == (i + 1));
}

void testPushBack () {
    DynamicArray<int> arr;

    assert(arr.pushBack(3) == true);
    assert(arr.pushBack(8) == true);
    assert(arr.pushBack(11) == true);

    int beforePushBackSize = arr.size();
    int numOfPushBackEle = 5;

    for (int i = 0; i < numOfPushBackEle; ++i)
        arr.pushBack(2 * i + 5);

    assert(beforePushBackSize + numOfPushBackEle == arr.size());

    for (int i = beforePushBackSize; i < arr.size(); ++i) {
        int val = (2 * (i - beforePushBackSize) + 5);
        assert (arr.at(i) == val);
    }
}

void testGrow () {
    // To always have room for new elements
    DynamicArray<int> arr;
    int n = 1025; 
 
    for (int i = 0; i < n; ++i) {
        assert(arr.pushBack(3 * i + 1) == true);
        assert(arr.capacity() >= arr.size());  
    }
 
    assert(arr.size() == n);
    for (int i = 0; i < n; ++i) {
        assert(arr.at(i) == 3 * i + 1);
    }
}

void testPreserveElements () {
    DynamicArray<int> arr;

    int test = 20;

    for (int i = 1; i <= test; ++i) {
        arr.pushBack(i * 8 + 3);
        for (int j = 0; j < i; ++j)
            assert(arr.at(j) == (j + 1) * 8 + 3);
    }
}

void testEraseAtTwoEnds () {
    DynamicArray<int> arr;

    fillArray(5, arr);

    // Erase the first element
    assert(arr.eraseAt(0));

    assert(arr.size() == 4);
    assert(arr.at(0) == 2);
    assert(arr.at(1) == 3);
    assert(arr.at(2) == 4);
    assert(arr.at(3) == 5);

    // Erase the last element
    assert(arr.eraseAt(arr.size() - 1));

    assert(arr.size() == 3);
    assert(arr.at(0) == 2);
    assert(arr.at(1) == 3);
    assert(arr.at(2) == 4);

    assert(arr.capacity() >= arr.size());
}

void testEraseMiddle () {
    DynamicArray<int> arr;
    fillArray(5, arr);
    
    int beforeEraseSize = arr.size();

    assert(arr.eraseAt(1) == true);
 
    int expected[] = {1, 3, 4, 5};
    
    assert(arr.size() == beforeEraseSize - 1);

    for (int i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == expected[i]);
}

void testEraseInvalidIndexes () {
    DynamicArray<int> arr;
    fillArray(3, arr);
 
    assert(arr.eraseAt(-1) == false);
    assert(arr.eraseAt(3) == false);
 
    for (int i = 0; i < arr.size(); ++i)
        assert(arr.at(i) == (i + 1));
}

void testAtChangeValue () {
    DynamicArray<int> arr;

    int n = 5;

    fillArray(n, arr);

    int p = 2, val = -34;
    if (p >= n) {
        std::cout << "Choose another position to change value throught .at()\n";
    }
    arr.at(p) = val;

    for (int i = 0; i < n; ++i) {
        if (i == p)
            assert(arr.at(i) == val);
        else
            assert(arr.at(i) == i + 1);
    }
}

void testAtInvalidIndexes () {
    DynamicArray<int> arr;

    bool ok = arr.eraseAt(-1);
    assert(ok == false);
    ok = arr.eraseAt(0);
    assert(ok == false);

    bool thrown = false;
    try {
        arr.at(0);
    } catch (const std::out_of_range&) { 
        thrown = true; 
    }
    assert(thrown);

    fillArray(3, arr);
    thrown = false;
    try {
        arr.at(-1);
    } catch (const std::out_of_range&) { 
        thrown = true; 
    }
    assert(thrown);

    thrown = false;
    try {
        arr.at(3); 
    } catch (const std::out_of_range&) { 
        thrown = true;
    }
    assert(thrown);
}

void testStringElements () {
    DynamicArray<std::string> arr;

    assert(arr.pushBack("wallet"));
    assert(arr.pushBack("category"));

    assert(arr.size() == 2);
    assert(arr.at(0) == "wallet");
    assert(arr.at(1) == "category");

    assert(arr.eraseAt(0));
    assert(arr.size() == 1);
    assert(arr.at(0) == "category");
}

void testCopyCtorIsDeepCopy () {
    DynamicArray<int> a;
    fillArray(5, a);
    DynamicArray<int> b(a);

    assert(&a.at(0) != &b.at(0));

    b.at(2) = 999;
    assert(a.at(2) == 3);
    a.at(4) = -5;
    assert(b.at(4) == 5);

    for (int i = 0; i < 100; ++i) b.pushBack(i);
    assert(a.size() == 5);
    assert(b.size() == 105);
}

void testAssignIsDeepCopy () {
    DynamicArray<int> a;
    fillArray(6, a);

    DynamicArray<int> b;
    fillArray(20, b);  
    b = a;

    assert(b.size() == 6);
    assert(&a.at(0) != &b.at(0));
    b.at(0) = 100;
    assert(a.at(0) == 1);

    DynamicArray<int> empty;
    b = empty;
    assert(b.size() == 0);
    assert(b.pushBack(7));
    assert(b.at(0) == 7);

    DynamicArray<int> c, d;
    d = c = a;
    assert(c.size() == 6 && d.size() == 6);
    assert(&c.at(0) != &d.at(0));
}

void testConstAt () {
    DynamicArray<int> arr;
    fillArray(3, arr);
    const DynamicArray<int>& c = arr;

    assert(c.at(1) == 2);
    bool thrown = false;
    try {
        c.at(3);
    } catch (const std::out_of_range&) {
        thrown = true; 
    }
    assert(thrown);
}

void testPushBackSelf () {
    DynamicArray<int> arr;
    fillArray(4, arr);
    assert(arr.pushBack(arr.at(0)));
    assert(arr.size() == 5 && arr.at(4) == 1);
}

void testMemberSwap() {
    DynamicArray<int> a, b;

    // a = {10, 20, 30}
    assert(a.pushBack(10));
    assert(a.pushBack(20));
    assert(a.pushBack(30));

    // b = {7, 8}
    assert(b.pushBack(7));
    assert(b.pushBack(8));

    // Save the original information.
    int aSize = a.size();
    int bSize = b.size();

    int aCapacity = a.capacity();
    int bCapacity = b.capacity();

    const int* aFirst = &a.at(0);
    const int* bFirst = &b.at(0);

    // Member function swap.
    a.swap(b);

    // Check sizes and capacities.
    assert(a.size() == bSize);
    assert(b.size() == aSize);

    assert(a.capacity() == bCapacity);
    assert(b.capacity() == aCapacity);

    // Check elements.
    assert(a.at(0) == 7);
    assert(a.at(1) == 8);

    assert(b.at(0) == 10);
    assert(b.at(1) == 20);
    assert(b.at(2) == 30);

    // Check that memory ownership was swapped, not copied.
    assert(&a.at(0) == bFirst);
    assert(&b.at(0) == aFirst);

    // Test self-swap.
    const int* oldFirst = &a.at(0);
    int oldSize = a.size();
    int oldCapacity = a.capacity();

    a.swap(a);

    assert(a.size() == oldSize);
    assert(a.capacity() == oldCapacity);
    assert(&a.at(0) == oldFirst);
    assert(a.at(0) == 7);
    assert(a.at(1) == 8);
}

void testSwapUsingADL() { // Test dynamic array swapping via Argument-Dependent Lookup
    DynamicArray<std::string> a, b;

    assert(a.pushBack("wallet"));
    assert(a.pushBack("expense"));

    assert(b.pushBack("income"));

    const std::string* aFirst = &a.at(0);
    const std::string* bFirst = &b.at(0);

    int aSize = a.size();
    int bSize = b.size();

    int aCapacity = a.capacity();
    int bCapacity = b.capacity();

    // Use ADL to find the custom swap function.
    using std::swap;
    swap(a, b);

    // Check sizes and capacities.
    assert(a.size() == bSize);
    assert(b.size() == aSize);

    assert(a.capacity() == bCapacity);
    assert(b.capacity() == aCapacity);

    // Check elements.
    assert(a.size() == 1);
    assert(a.at(0) == "income");

    assert(b.size() == 2);
    assert(b.at(0) == "wallet");
    assert(b.at(1) == "expense");

    // Check that memory ownership was swapped, not copied.
    assert(&a.at(0) == bFirst);
    assert(&b.at(0) == aFirst);
}

int main() {
    std::cout << "Starting test dynamic array\n\n";

    testEmpty();
    std::cout << "Empty Test PASSED\n";
    
    testCopyInitialization();
    std::cout << "Copy array Test PASSED\n";

    testCopyEmptyArray();
    std::cout << "Copy empty array Test PASSED\n";

    testPushBack();
    std::cout << "PushBack Test PASSED\n";

    testGrow();
    std::cout << "Grow Test PASSED\n";

    testPreserveElements();
    std::cout << "Element preservation Test PASSED\n";

    testEraseAtTwoEnds();
    std::cout << "Erase first and last Test PASSED\n";

    testEraseInvalidIndexes();
    std::cout << "Erase invalid indexes PASSED\n";

    testAtInvalidIndexes();
    std::cout << "At invalid indexes Test PASSED\n";

    testSelfAssignment();
    std::cout << "Self assignment Test PASSED\n";

    testStringElements();
    std::cout << "Element string type PASSED\n";

    testAssignInitialization();
    std::cout << "Assignment Test PASSED\n";

    testEraseMiddle();
    std::cout << "Erase middle Test PASSED\n";

    testAtChangeValue();
    std::cout << "At change value Test PASSED\n";

    testConstAt();
    std::cout << "Const at Test PASSED\n";

    testPushBackSelf();
    std::cout << "PushBack an element in itself Test PASSED\n";

    testCopyCtorIsDeepCopy();
    std::cout << "Copy ctor deep copy Test PASSED\n";

    testAssignIsDeepCopy();
    std::cout << "Assign deep copy Test PASSED\n";

    testMemberSwap();
    std::cout << "Member swap Test PASSED\n";

    testSwapUsingADL();
    std::cout << "ADL swap Test PASSED\n";

    std::cout << "\n\n";
    std::cout << "All tests passed\n";
    // std::cerr << "NOT IMPLEMENTED: test_dynamic_array.cpp - replace this stub with real assertions.\n";
    return 0;
}