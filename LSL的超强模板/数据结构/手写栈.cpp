struct Stack {
  int st[10000];
  int p;

  Stack() : p(0) {}

  void push(int x) { st[p++] = x; }
  void pop() { --p; }
  int top() { return st[p - 1]; }
  int size() { return p; }
};