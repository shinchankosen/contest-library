struct node {
    int x, y;
    bool operator<( const node& right ) const {
        return x == right.x ? y < right.y : x < right.x;
    }
    node& operator+=(const node& v) { x += v.x; return *this;}
    node operator+(const node& v) const { return node(*this) += v;}
    int inner(const node& right) const { return x*right.x + y*right.y;}
};