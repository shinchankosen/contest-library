struct Fraction {
    long long x, y;
    void reduc() {
        if(y < 0) y = -y, x = -x;
        long long g = abs(__gcd(x, y));
        x /= g; y /= g;
    }
    Fraction(long long x=0, long long y=1): x(x), y(y) {reduc();}
    bool operator<( const Fraction& right ) const { return x*right.y < y*right.x; }
    bool operator>( const Fraction& right ) const { return x*right.y > y*right.x; }
    bool operator==( const Fraction& right ) const { return x == right.x && y == right.y; }
    Fraction operator-() const {return Fraction(-x, y);}
    Fraction& operator+=(const Fraction& v) { 
        x = x*v.y + y*v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator+(const Fraction& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const Fraction& v) { 
        x = x*v.y - y*v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator-(const Fraction& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const Fraction& v) { 
        x *= v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator*(const Fraction& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const Fraction& v) { 
        x *= v.y;
        y *= v.x;
        reduc();
        return *this;
    }
    Fraction operator/(const Fraction& v) const { return Fraction(*this) /= v;}

    bool operator<( const int& right ) const { return x < y*right; }
    bool operator>( const int& right ) const { return x > y*right; }
    bool operator==( const int& right ) const { return x == right && y == 1; }
    Fraction& operator+=(const int& v) { 
        x += y*v;
        return *this;
    }
    Fraction operator+(const int& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const int& v) { 
        x -= y*v;
        return *this;
    }
    Fraction operator-(const int& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const int& v) { 
        x *= v;
        reduc();
        return *this;
    }
    Fraction operator*(const int& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const int& v) {
        y *= v;
        reduc();
        return *this;
    }
    Fraction operator/(const int& v) const { return Fraction(*this) /= v;}

    bool operator<( const long long& right ) const { return x < y*right; }
    bool operator>( const long long& right ) const { return x > y*right; }
    bool operator==( const long long& right ) const { return x == right && y == 1; }
    Fraction& operator+=(const long long& v) { 
        x += y*v;
        return *this;
    }
    Fraction operator+(const long long& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const long long& v) { 
        x -= y*v;
        return *this;
    }
    Fraction operator-(const long long& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const long long& v) { 
        x *= v;
        reduc();
        return *this;
    }
    Fraction operator*(const long long& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const long long& v) {
        y *= v;
        reduc();
        return *this;
    }
    Fraction operator/(const long long& v) const { return Fraction(*this) /= v;}

    Fraction inv() const { return Fraction(y, x); }
    Fraction pow(int t) const {
        if(t < 0) return inv().pow(-t);
        Fraction a(1, 1), d = *this;
        while(t) {
            d *= d;
            if(t & 1) a *= d;
            t >>= 1;
        }
        return a;
    }
    friend ostream& operator << (ostream& os, const Fraction& v) { return os << v.x << "/" << v.y; }  
};