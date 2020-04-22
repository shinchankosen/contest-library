////lambda
auto f = [&](auto&& f,int x) -> int{return x;};



struct node{
    int x,y;
    // 最後のconstを忘れると"instantiated from here"というエラーが出てコンパイルできないので注意
    bool operator<( const node& right ) const {
        return x == right.x ? y < right.y : x < right.x;
    }
    node& operator+=(const node& v) { x += v.x; return *this;}
    node operator+(const node& v) const { return node(*this) += v;}
    int inner(const node& right) const { return x*right.x + y*right.y;}
};


istream& operator>>(istream& is, node& v) {
  is >> v.x >> v.y; return is;
}

/////3変数構造体
struct node{
    int x,y,z;
    bool operator<( const node& right ) const {
        if(x == right.x){
            if(y == right.y) return z < right.z;
            else return y < right.y;
        }else return x < right.x;
    }
};


////第3引数sort
bool judge( const node& left, const node& right ) {
    return left.x == right.x ? left.y < right.y : left.x < right.x;
}
