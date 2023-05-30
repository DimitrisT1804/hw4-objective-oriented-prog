#include <iostream>
using namespace std;
int main() {
  int intArray[5];
  int *ptr = intArray+10000;
  *ptr = 10;
}