#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;


struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x),y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
}px[maxn], p[maxn];

bool cmp_x(const Point &A, const Point &B) {
    return A.x < B.x;
}

bool cmp_y(const Point &A, const Point &B) {
    return A.y < B.y;
}

double dis(Point &A, Point &B) {
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

double solve(int l, int r) {
    if (l >= r) return 1e18;
    int mid = (l + r) / 2;
    double ans = min(solve(l, mid), solve(mid+1, r));

    // merge
    int cnt = 0, pl = l, pr = mid+1;
    while (pl <= mid && pr <= r) {
        if(cmp_y(px[pl], px[pr])) p[cnt++] = px[pl++];
        else p[cnt++] = px[pr++];
    }
    while (pl <= mid) p[cnt++] = px[pl++];
    while (pr <= r) p[cnt++] = px[pr++];
    for (int i = 0; i < cnt; i++) px[l+i] = p[i];

    // find points in [x-\delta, x+\delta]
    cnt = 0;
    for (int i = l; i <= r; i++) if (fabs(px[mid].x-px[i].x) <= ans)
        p[cnt++] = px[i];
    for (int i = 0; i < cnt; i++)
        for (int j = i+1; j < cnt && p[j].y - p[i].y <= ans; j++)
            ans = min(ans, dis(p[i], p[j]));
    return ans;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {

        for (int i = 0; i < n; i++) {
            px[i].read();
        }
        sort(px, px+n, cmp_x);
        printf("%.2f\n", solve(0, n-1) / 2);

    }
    return 0;
}