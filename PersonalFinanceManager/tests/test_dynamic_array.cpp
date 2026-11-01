#include <iostream>
#include <cassert>
#include <string>
#include "..\include\DynamicArray.h"

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
    assert(tmp.capacity() == tmp.capacity());

    for (int i = 1; i < tmp.size(); ++i)
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
 
    int expected[] = {1, 3, 4};
    
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
    assert (ok == false);
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

    std::cout << "\n\n";
    std::cout << "All tests passed\n";
    // std::cerr << "NOT IMPLEMENTED: test_dynamic_array.cpp - replace this stub with real assertions.\n";
    return 0;
}
