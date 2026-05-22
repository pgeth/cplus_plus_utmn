#include <iostream>
#include <vector>
#include <limits>

struct Node
{
  long long value;
  int left;
  int right;
};

bool isBST(const std::vector<Node>& tree, int idx, long long lo, long long hi)
{
  if (idx == -1)
    return true;
  const Node& n = tree[idx];
  if (n.value <= lo || n.value >= hi)
    return false;
  return isBST(tree, n.left, lo, n.value) && isBST(tree, n.right, n.value, hi);
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<Node> tree(n);
  for (int i = 0; i < n; ++i)
    std::cin >> tree[i].value >> tree[i].left >> tree[i].right;

  const long long NEG_INF = std::numeric_limits<long long>::min();
  const long long POS_INF = std::numeric_limits<long long>::max();
  std::cout << (isBST(tree, 0, NEG_INF, POS_INF) ? "TRUE" : "FALSE");
}
