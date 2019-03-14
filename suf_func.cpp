vector < int > z_func (string s) {
    int n = sz(s);
    vector < int > z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (z[i] + i < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1, l = i;
        }
    }
    return z;
}

vector < int > suf_func (string s) {
    int n = sz(s);
    reverse(s.begin(), s.end());
    vector < int > suf(n), z = z_func(s);
    for (int i = n - 1; i >= 0; i--) {
        if (z[i]) suf[n - 1 - (i + z[i] -1)] = z[i];
    }
    for (int i = 0; i < n; i++) {
        if (i) suf[i] = max(suf[i - 1] - 1, suf[i]);
    }
    return suf;
}
