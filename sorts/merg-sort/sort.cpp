#include <iostream>
#include "../genarr.h"
#include "../timer.h"
#include <vector>

using namespace std;
void MergeSortImpl(vector<int>& values, vector<int>& buffer, int l, int r) {
  if (l < r) {
    int m = (l + r) / 2;
    MergeSortImpl(values, buffer, l, m);
    MergeSortImpl(values, buffer, m + 1, r);

    int k = l;
    for (int i = l, j = m + 1; i <= m || j <= r; ) {
      if (j > r || (i <= m && values[i] < values[j])) {
        buffer[k] = values[i];
        ++i;
      } else {
        buffer[k] = values[j];
        ++j;
      }
      ++k;
    }
    for (int i = l; i <= r; ++i) {
      values[i] = buffer[i];
    }
  }
}

int main() {
    Timer t;
    int size = 1000;
    int * myVec= init_arr(size, 0,100);
    vector<int> values(myVec, myVec + size);
  if (!values.empty()) {
    vector<int> buffer(values.size());
    MergeSortImpl(values, buffer, 0, values.size() - 1);
  }

  return 0;
}
