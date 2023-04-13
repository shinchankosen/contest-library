vector<int> z_algorithm(string S){
    int n = S.size();
    vector<int> Z(n);
    Z[0] = n;
    int i = 1, j = 0;
    while(i < n){
        while(i + j < n && S[j] == S[i + j]) j++;
        Z[i] = j;
        if(j == 0) { i++; continue; }
        int k = 1;
        while(i + k < n && k + Z[k] < j){
            Z[i + k] = Z[k];
            k++;
        }
        i += k; j -= k;
    }
    return Z;
}