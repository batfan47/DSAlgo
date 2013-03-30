#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#define MAXCOUNT 99999
#define lower(a, b) (a < b ? a : b)
#define higher(a, b) (a > b ? a : b)
using namespace::std;
typedef unsigned counter;
typedef long long element;
typedef pair<element, element> epair;
typedef pair<counter, counter> cpair;

counter gcd (const counter a, const counter b) { return (b ? gcd (b, a%b) : a); }

inline void swap (element & a, element & b) { 
  if ( a == b ) return;
  element temp = b;
  b = a;
  a = temp;
}

inline void reverse (element terms[], const counter n) {
  for (counter start = 0, end = n - 1; start < end; 
       ++start, --end) swap (terms[start], terms[end]);
}

// Rotate array forward(right) by jump
inline void rotate (element terms[], const counter n, const counter jump) {
  if (!n) return; // DBZ if not checked
  element temp;
  counter gcd = n, k = jump, i, position;
  for (; k != 0; i = k, k = gcd % k, gcd = i);
  for (i = 0; i != gcd; ++i) {
    temp = terms [i];
    position = k = i;
    do {
      terms[position] = terms[k];
      position = k;
      if (k >= jump) k -= jump;
      else k += (n - jump);
    } while (k != i);
    terms[position] = temp;
  }
}

// Kadanes Algorithm to compute maximum contigous sum
// startloc, endloc indicate sum binding indices
element kadane (const element terms[], const counter n, 
  	counter &startloc, counter &endloc) {
  if (!n) return 0;
  element max = terms[0], cmax = terms[0];
  counter cstart = 0, cend = 0;
  for (counter i = 1; i < n; ++i) {
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

// Min & Max of an array. Returns 0s for 0 count
epair minmax (const element terms[], const counter n) {
  epair minmax;
  if (!n || (n % 2)) {
    minmax.first = n ? terms[0]:0;
    minmax.second = n ? terms[0]:0;
    if (!n) return minmax;
  }
  else {
    if (terms[0] < terms[1]) {
      minmax.first = terms[0];
      minmax.second = terms[1];
    }
    else {
      minmax.first = terms[1];
      minmax.second = terms[0];
    }
  }
  for (counter i = n % 2 ? 1 : 2; i != n; i += 2) {
    if (terms[i] < terms[i + 1]) {
      minmax.first = lower (minmax.first, terms[i]);
      minmax.second = higher (minmax.second, terms[i + 1]);
    }
    else {
      minmax.first = lower (minmax.first, terms[i + 1]);
      minmax.second = higher (minmax.second, terms[i]);
    }
  }
  return minmax;
}

void mergesort (element terms[], const counter n) {
  if (n < 2) return;
  counter mid = n/2;
  mergesort (terms, mid);
  mergesort (terms + mid, n - mid);
  counter left = 0, right = mid, position = 0;
  element * ptr = new (element[n]);
  while (left < mid && right < n)
    ptr[position++] = terms[left] <= terms[right] ? 
		    terms[left++] : terms[right++];
  while (left < mid) ptr[position++] = terms[left++];
  for (counter i = 0; i < position; ++i) terms[i] = ptr[i];
  delete[] ptr;
}

// Random Pivot 3 way Quick Sort
void quicksort (element terms[], const counter n) {
  if (n < 2) return;
  srand (time(NULL));
  counter left = 0, position = 0, right = n - 1;
  element pivot = terms [rand() % n];
  while (position <= right)
    if (terms[position] == pivot) ++position;
    else if (terms[position] < pivot)
      swap(terms[left++], terms[position++]);
    else swap(terms[position], terms[right--]);
  quicksort (terms, left);
  quicksort (terms + position, n - position);
}

// first item insert position in sorted array
// returns false with left = count for item > last
bool firstsortloc (const element terms[], const counter n, const element item, 
		   counter & left) {
  counter right = n, mid;
  left = 0;
  while (terms[left] != item && left != right) {
    mid = left + (right - left)/2;
    if (terms[mid] < item)
      left = mid + 1;
    else right = mid;
  }
  return (left == n ? false : terms[left] == item);
}

// item occurence count in sorted array
// startindex = count for item > last
counter sortcount (const element terms[], const counter n, const element item, 
		  counter & startindex) {
  if (!firstsortloc(terms, n, item, startindex)) return 0;
  counter left = startindex, right = n - 1, mid;
  while (terms[right] != item && left != right) {
    --right; // We know it's not item
    mid = left + (right - left)/2;
    if (terms[mid] > item)
      right = mid - 1;
    else left = mid;
  }
  return (right + 1 - startindex);
}
