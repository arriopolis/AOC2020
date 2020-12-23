#include <iostream>
#include <string>
using namespace std;

const int NUM_MOVES = 10000000;
const int NUM_CUPS = 1000000;

int main() {
  // nodes[i] will indicate what number follows i in the cycle.
  // We will use 0-based indexing instead of the 1-based indexing in the
  // problem statement, to avoid having to subtract 1 all the time.
  int * nodes = new int[NUM_CUPS];

  // Read the input.
  string s;
  cin >> s;
  int prev = -1, first;
  for (char c : s) {
    if (prev != -1) {
      nodes[prev] = (int)(c-'0'-1);
    } else {
      first = (int)(c-'0'-1);
    }
    prev = (int)(c-'0'-1);
  }

  // Pad the cycle with sufficiently many cups.
  for (int i = s.size(); i < NUM_CUPS; i++) {
    nodes[prev] = i;
    prev = i;
  }
  nodes[prev] = first;

  int src = first;
  for (int a = 0; a < NUM_MOVES; a++) {

    // We have two pointers, starting at the current location.
    // src will walk through the part that is to be picked up,
    // dest will become where we store the picked up part.
    int dest = src;

    // Store the start of the picked up part for later insertion purposes.
    int pick_up = nodes[dest];

    // We store in a bitmask which values just below our current value
    // are in the picked up part.
    int flags = 0;

    // Walk through the picked up part.
    for (int i = 0; i < 3; i++) {
      src = nodes[src];
      if ((dest - src + NUM_CUPS) % NUM_CUPS <= 3) {
        flags |= (0x1 << (dest - src + NUM_CUPS) % NUM_CUPS - 1);
      }
    }

    // Set our current position in the cycle to point to
    // right after the picked up part.
    nodes[dest] = nodes[src];
    // So now we have removed the picked up part, dest is just before
    // where the picked up part is removed, and src is at the last entry
    // of the picked up part.

    // Move dest to where the picked up part is to be inserted.
    dest--;
    while (flags%2 != 0) {
      dest--;
      flags >>= 1;
    }
    dest = (dest + NUM_CUPS) % NUM_CUPS;

    // Store where we need to have our next iteration.
    int next = nodes[src];

    // Insert the picked up part.
    nodes[src] = nodes[dest];
    nodes[dest] = pick_up;

    // Start the new iteration.
    src = next;
  }

  // Calculate the product (and compensate for the 0-indexing).
  cout << (long long)(nodes[0]+1) * (long long)(nodes[nodes[0]]+1) << endl;

  // Because we are nice coders.
  delete[] nodes;
}
