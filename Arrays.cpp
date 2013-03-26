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
  while (left != right) {
    mid = left + (right - left)/2;
    if (terms[mid] < item) left = mid + 1;
    else right = mid;
  }
  return (left == count ? false : terms[left] == item);
}

// last find position in sorted order
// returns false with left = count for item > last
// Check Boundaries before use
bool lastsortloc (element terms[], counter count, element item, counter & left)
{
  counter right = count - 1, mid;
  if (!firstsortloc(terms, count, item, left)) return false;
  while (left != right) {
    mid = left + (right + 1 - left)/2;
    if (terms[mid] > item) right = mid - 1;
    else left = mid;
    if (term[right] != item) --right;
    else left = right;
  }
  return (terms[left] == item);
}

// returns cieling postion.second = count for item > last
// Check Boundaries before use
cpair floorNcieling (element terms[], counter count, element item)
{
  cpair position;
  firstsortloc(terms, count, item, position.first);
  if (lastsortloc(terms + position.first, count - position.first, 
    item, position.second)) ++position.second;
  if (position.first) --position.first;
  return position;
}
