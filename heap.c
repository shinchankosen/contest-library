//E1740 村上慎治

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int h[11], n = 7;

void upheap(int k) {
    int i = k / 2, v = h[k];
    while (i > 0) {
        if (h[i] >= v) {
            h[k] = v;
            return;
        }
        h[k] = h[i];
        k = i;
        i = k / 2;
    }
    h[k] = v;
}

void downheap(int k) {
    int i = k * 2, v = h[k];
    while (i <= n) {
        if (i < n && h[i] < h[i + 1]) i++;
        if (h[i] <= v) {
            h[k] = v;
            return;
        }
        h[k] = h[i];
        k = i;
        i = k * 2;
    }
    h[k] = v;
}

void insert(int x) {
    if (n == 10) {
        printf("ヒープは満杯です。\n");
        return;
    }
    n++;
    h[n] = x;
    upheap(n);
}

void delete() {
    if (n == 0) {
        printf("ヒープは空です。\n");
        return;
    }
    printf("最大値は%dです。\n", h[1]);
    n--;
    if (n > 1) {
        h[1] = h[n];
        downheap(1);
    }
}

void  write() {
    if (n == 0) printf("ヒープは空です。");
    int i;
    for (i = 1; i <= n; i++) printf("%d ", h[i]);
    printf("\n");
}

void makeheap() {
    int i;
    for (i = n / 2; i >= 1; i--) downheap(i);
}

int main(int argc, char** argv) {
    char c;
    int num, i;
    for (i = 1; i <= n; i++) h[i] = i;
    makeheap();
    while (1) {
        printf("文字を入力してください: ");
        scanf("%s", &c);
        switch (c) {
        case 'i':
            printf("数値を入力してください: ");
            scanf("%d", &num);
            insert(num);
            break;
        case 'd':
            delete();
            break;
        case 'p':
            write();
            break;
        case 'q':
            printf("終了します。\n");
            return 0;
        default:
            printf("使えるのは {i, d, p, q} です。\n");
            break;
        }
    }
    return 0;
}
