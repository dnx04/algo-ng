typedef uint64_t ull;
struct H {
  ull x;
  H(ull x = 0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) {
    auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64);
  }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;  // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(sz(str) + 1), pw(ha) {
    pw[0] = 1;
    rep(i, 0, sz(str)) ha[i + 1] = ha[i] * C + str[i], pw[i + 1] = pw[i] * C;
  }
  H hashInterval(int a, int b) {  // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

vector<H> getHashes(string& str, int length) {
  if (sz(str) < length) return {};
  H h = 0, pw = 1;
  rep(i, 0, length) h = h * C + str[i], pw = pw * C;
  vector<H> ret = {h};
  rep(i, length, sz(str)) {
    ret.push_back(h = h * C + str[i] - pw * str[i - length]);
  }
  return ret;
}

H hashString(string& s) {
  H h{};
  for (char c : s) h = h * C + c;
  return h;
}