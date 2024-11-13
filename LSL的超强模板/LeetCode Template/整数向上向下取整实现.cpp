int floor_div(int a, int b) {
    int q = a / b;
    int r = a % b;
    if (r != 0 && ((a ^ b) < 0)) {
        q -= 1;
    }
    return q;
}

int ceil_div(int a, int b) {
    int q = a / b;
    int r = a % b;
    if (r != 0 && ((a ^ b) > 0)) {
        q += 1;
    }
    return q;
}