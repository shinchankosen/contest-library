#include <bits/stdc++.h>
#define be(v) (v).begin(),(v).end()
#define pb(q) push_back(q)
#define rep(i, n) for(int i=0;i<n;i++)
#define all(i, v) for(auto& i : v)
typedef long long ll;
using namespace std;
const ll mod=1000000007, INF=(1LL<<60);
#define doublecout(a) cout<<fixed<<setprecision(10)<<a<<endl;

struct matrix {
    int nrow, ncol;
    double a[nrow][ncol];
};
typedef struct matrix MATRIX;

double access(matrix mat, int i, int j) { // a[i][j] 
    return mat.a[i][j];
}

MATRIX* allocM(int nrow, int ncol) {
    double a[nrow][ncol] = {0.0};
    MATRIX mat = {nrow, ncol, a};
    return &mat;
}

void freeM(MATRIX* m) {
    free();
}

void printM(MATRIX* m) {
    for(int i = 0; i < m->nrow; i ++) {
        for(int j = 0; j < m->ncol; j ++) {
            // printf("%lf ", (*m).a[i][j]);
            printf("%lf ", m->a[i][j]);
        }
        printf("\n");
    }
}

MATRIX* addM(MATRIX* m1, MATRIX* m2) {
    if(m1->nrow != m2->nrow || m1->ncol != m2->ncol) {
        return NULL;
    }
    MATRIX* ret = allocM(m1->nrow, m1->ncol);
    for(int i = 0; i < m1->nrow; i ++) {
        for(int j = 0; j < m1->ncol; j ++) {
            ret->a[i][j] = m1->a[i][j] + m2->a[i][j];
        }
    }
    return ret;
}

MATRIX* subM(MATRIX* m1, MATRIX* m2) {
    if(m1->nrow != m2->nrow || m1->ncol != m2->ncol) {
        return NULL;
    }
    MATRIX* ret = allocM(m1->nrow, m1->ncol);
    for(int i = 0; i < m1->nrow; i ++) {
        for(int j = 0; j < m1->ncol; j ++) {
            ret->a[i][j] = m1->a[i][j] - m2->a[i][j];
        }
    }
    return ret;
}

MATRIX* mulM(MATRIX* m1, MATRIX* m2) {
    if(m1->ncol != m2->nrow) {
        return NULL;
    }
    for(int i = 0; i < m1->nrow; i ++) {
        for(int j = 0; j < m2->ncol; j ++) {
            double num = 0.0;
            for(int k = 0; k < m1->ncol; k ++) {
                num += m1->a[i][k] * m2->a[k][j];
            }
            ret->a[i][j] = num;
        }
    }
    return ret;
}


int main(int argc, char **argv) {
    return 0;
}
