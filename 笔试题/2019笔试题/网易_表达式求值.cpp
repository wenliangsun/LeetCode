#include <bits/stdc++.h>

using namespace std;

/**
 * 今天上课，老师教了小易怎么计算加法和乘法，乘法的优先级大于加法，但是如果一个运算加了括号，那么它的优先级是最高的。
 * 现在小易希望你帮他计算给定3个数a，b，c，在它们中间添加"+","*","("，")"符号，能够获得的最大值。
 */

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    int res = max((a + b) * c, max((a + c) * b, max((b + c) * a, a * b * c)));
    cout << res << endl;
    return 0;
}