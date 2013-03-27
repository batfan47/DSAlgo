#include <iostream>
#define higher(a, b) (a > b ? a : b)
using namespace::std;
typedef long long element;
typedef unsigned long counter;
typedef pair<counter, counter> cpair;

element kadane (element terms[], counter count, counter &startloc, counter & endloc)
{
  if (!count) return 0;
  element max = terms[0], currMax = terms[0];
  counter cstart = 0, cend = 0;
  for (counter i = 1; i < count; ++i) {
    if (currMax + terms[i] > terms[i]) currMax += terms[i];
    else {
      currMax = terms[i];
      cstart = i;
    }
    cend = i;
    cout << currMax << " " << max << endl;
    if (currMax > max) {
      max = currMax += terms[i];
      startloc = cstart;
      endloc = cend;
    }
  }
  return max;
}

void mergesort (element terms[], counter count)
{
  if (count < 2) return;
  counter mid = count/2;
  mergesort (terms, mid);
  mergesort (terms + mid, count - mid);
  counter left = 0, right = mid, position = 0;
  element * ptr = new (element[count]);
  while (left < mid && right < count)
    ptr[position++] = terms[left] <= terms[right] ? terms[left++] : terms[right++];
  while (left < mid) ptr[position++] = terms[left++];
  for (counter i = 0; i < position; ++i) terms[i] = ptr[i];
  delete[] ptr;
}

// first insert position in sorted order
// returns false with left = count for item > last
// Check boundaries before use
bool firstsortloc (element terms[], counter count, element item, counter & left)
{
  counter right = count, mid;
  left = 0;
  while (left != right && terms[left] != item) {
    mid = left + (right - left)/2;
    if (terms[mid] < item)
      left = mid + 1;
    else right = mid;
  }
  return (left == count ? false : terms[left] == item);
}

// Count occurence of item in sorted terms
counter sortcount(element terms[], counter count, element item)
{
  counter position, left, right = count - 1, mid;
  if (!firstsortloc(terms, count, item, position)) return 0;
  left = position;
  while (left != right) {
    mid = left + (right + 1 - left)/2;
    if (terms[mid] > item)
      right = mid - 1;
    else left = mid;
    if (terms[right] == item)
      left = right;
    else --right;
  }
  left = position;
  return (right + 1 - left);
}
