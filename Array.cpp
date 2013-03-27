#include <iostream>
using namespace::std;
typedef long long element;
typedef unsigned long counter;
typedef pair<counter, counter> cpair;

element kadane (element terms[], counter count, counter &startloc, counter &endloc)
{
  if (!count) return 0;
  element max = terms[0], cmax = terms[0];
  counter cstart = 0, cend = 0;
  for (counter i = 1; i < count; ++i) {
    if (terms[i] > cmax + terms[i]) {
      cmax = terms[i];
      cstart = i;
    }
    else cmax += terms[i];
    cend = i;
    if (cmax > max) {
      max = cmax;
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
bool firstsortloc (element terms[], counter n, element item, counter & left)
{
  counter right = n, mid;
  left = 0;
  while (left != right && terms[left] != item) {
    mid = left + (right - left)/2;
    if (terms[mid] < item)
      left = mid + 1;
    else right = mid;
  }
  return (left == n ? false : terms[left] == item);
}

// Count occurrence of item in sorted terms
// startindex = count for item > last
counter sortcount(element terms[], counter n, element item, counter & startindex)
{
  counter left, right = n - 1, mid;
  if (!firstsortloc(terms, n, item, startindex)) return 0;
  left = startindex;
  while (left != right && terms[right] != item) {
    --right; // We know it's not item
    mid = left + (right - left)/2;
    if (terms[mid] > item)
      right = mid - 1;
    else left = mid;
  }
  return (right + 1 - startindex);
}
