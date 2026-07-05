# 累積和

任意次元の累積和ライブラリです。

## 特徴

- 任意次元に対応
- 0-indexed なインターフェース
- `query()` は半開区間 `[l, r)` で取得
- `at(i, j, ...)` と `at({i, j, ...})` の両方に対応

内部では 1-indexed の累積和を保持しますが、利用者は意識する必要はありません。

---

## コンストラクタ

```cpp
Rui<T> sum(n1, n2, ..., nk);
```

各次元のサイズを指定します。

### 例

```cpp
Rui<ll> sum(n, m);
Rui<int> sum(x, y, z);
Rui<double> sum(a, b, c, d);
```

---

## at()

要素へアクセスします。

### 可変長引数版

```cpp
sum.at(i, j, ...);
```

### vector版

```cpp
sum.at({i, j, ...});
```

どちらも

```
0 <= index < size
```

でアクセスします。

### 例

```cpp
sum.at(i, j) += x;

vector<int> p = {i, j};
sum.at(p) += x;

sum.at({i, j}) = 5;
```

---

## build()

累積和を構築します。

```cpp
sum.build();
```

各要素の追加が終わったあとに **一度だけ** 呼んでください。

### 例

```cpp
Rui<ll> sum(n, m);

rep(i, n) rep(j, m) {
    sum.at(i, j) += a[i][j];
}

sum.build();
```

---

## query()

半開区間 `[l, r)` の総和を取得します。

### 可変長引数版

```cpp
sum.query(l1, r1, l2, r2, ...);
```

### vector版

```cpp
sum.query({l1, r1, l2, r2, ...});
```

返す範囲は

```
[l1, r1) × [l2, r2) × ...
```

です。

空区間 (`l >= r`) が含まれる場合は `T()` を返します。

---

## 使用例

### 2次元

```cpp
Rui<ll> sum(n, m);

rep(i, n)
rep(j, m)
    sum.at(i, j) += a[i][j];

sum.build();

ll ans = sum.query(lx, rx, ly, ry);
```

これは

```
lx <= i < rx
ly <= j < ry
```

を満たすすべての要素の総和を返します。

---

### 3次元

```cpp
Rui<ll> sum(x, y, z);

sum.at(i, j, k) += v;

sum.build();

ll ans = sum.query(
    lx, rx,
    ly, ry,
    lz, rz
);
```

---

## 計算量

`K` 次元、各次元のサイズを

```
N1, N2, ..., NK
```

とすると、

```
M = N1 × N2 × ... × NK
```

として

| 操作 | 計算量 |
|------|---------|
| `at()` | O(K) |
| `build()` | O(KM) |
| `query()` | O(K2^K) |

---

## 実装例

ABC465 F で使用しました。

提出:
https://atcoder.jp/contests/abc465/submissions/77222686