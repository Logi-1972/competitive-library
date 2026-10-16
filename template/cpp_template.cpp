// テンプレート・ライブラリ(公開): https://github.com/Logi-1972/competitive-library
// 自分用テンプレート。正本は ~/atcoder/my-library/template/cpp_template.cpp で、
// mkprob / mkcontest / mkfile(~/atcoder/sh/)はここからコピーする。
//
// 個人の基礎マクロ集として my-library/maspypy/my_template.hpp を土台にする方針(2026-09-16〜)。
// my-library は atcoder リポジトリ管理下の自分用ライブラリ(kyo-library/maspypy-libraryから
// 実際に使う関数を移植したもの)。外部の ~/kyo-library・~/maspypy-library は push権限が無い/
// 自分の管理下に無いため、以後はこちら(my-library)を編集・参照する。詳細: my-library/README.md
//
// ll/u32/u64/i128/u128、vc<T>等のエイリアス、FOR/all/eb等のマクロ、chmin/chmax、MIN/MAXマクロ、
// argsort/concat等はすべてmy_template.hppで提供される。重複・衝突するこのファイル独自定義
// (旧ll/i128/u32/u64/u128、all、MIN/MAX、chmin/chmax)は撤去済み。
// 詳細: atcoder/docs/CPP_TEMPLATE.md（本ファイルの詳しい仕様）/ atcoder/docs/maspypy-library.md
//
// #include <bits/stdc++.h> と using namespace std; は my_template.hpp が内部で
// 行っているため本来不要だが、明示しておきたいのでここにも書いておく
// (include guard / 再宣言なので二重に書いても問題ない)。
#include <bits/stdc++.h>
using namespace std;
#include "my-library/maspypy/my_template.hpp"
// #include <atcoder/all>
// using namespace atcoder;

// my-library/kyo(ACLとは独立の自作系ライブラリ、kyo-library由来): 使うヘッダのコメントアウトを外す(-I不要)
// #include "my-library/kyo/Data_structure/UnionFind.hpp"

// my-library/maspypyの数論(nt/)・mod計算(mod/)・データ構造(ds/)・グラフ(graph/)などの
// 個別ヘッダを使う場合はここに追加する(my_template.hppは上で読み込み済み)
// #include "my-library/maspypy/nt/factor.hpp"

using ld = long double;

// 注意: my-library/kyo と my-library/maspypy の両方に UnionFind 等、名前が重複するものが
// 存在する。同時にincludeすると再定義エラーになるので、どちらか一方を選んで使うこと。
//
// 方針: ライブラリ(my_template.hpp等)で完結する機能はこのファイルには書かない。
// 大きい安全な定数が欲しい場合は INF/INFLL の代わりに my_template.hpp の infty<T>
// (infty<int>, infty<ll> 等)を使う(Graph/WeightedGraphも同様にmy-library/maspypy/
// graph/base.hppのGraph<T,directed>で完結するため撤去した)。
// 下記の argsort(カスタム比較関数を渡せる版)・concat/operator+/operator+=
// (新しいvectorを返す非破壊版)は、my_template.hpp側には無い機能を持つため維持している。

// for文の短縮マクロ
#define rep0(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define rrep(i, a, b) for (int i = (int)(a); i > (int)(b); --i)
#define srep(i, a, b, step) \
    for (long long i = (a); (step) > 0 ? i < (b) : i > (b); i += (step))

// よく使う定数
constexpr ll MOD = 998244353;
constexpr ll MOD2 = 1000000007;

// x以上の最小要素を指すiterator(lower_bound)。無ければc.end()
template <class C, class T>
auto ge_it(const C &c, const T &x)
{
    return c.lower_bound(x);
}

// x以下の最大要素を指すiterator。無ければc.end()
template <class C, class T>
auto le_it(const C &c, const T &x)
{
    auto it = c.upper_bound(x);
    if (it == c.begin())
        return c.end();
    --it;
    return it;
}

// x以上の最小要素の値。無ければout_of_rangeを送出
template <class C, class T>
typename C::value_type ge_val(const C &c, const T &x)
{
    auto it = ge_it(c, x);
    if (it == c.end())
        throw out_of_range("ge_val: no element >= x");
    return *it;
}

// x以下の最大要素の値。無ければout_of_rangeを送出
template <class C, class T>
typename C::value_type le_val(const C &c, const T &x)
{
    auto it = le_it(c, x);
    if (it == c.end())
        throw out_of_range("le_val: no element <= x");
    return *it;
}

// set/multisetからxを削除。setは0/1個、multisetは1個だけ。削除成功したかを返す
template <class T, class Compare, class Alloc>
bool discard_one(set<T, Compare, Alloc> &s, const T &x)
{
    return s.erase(x) > 0;
}

template <class T, class Compare, class Alloc>
bool discard_one(multiset<T, Compare, Alloc> &s, const T &x)
{
    auto it = s.find(x);
    if (it == s.end())
        return false;
    s.erase(it); // erase only one
    return true;
}

// set/multisetからxを削除。multisetは全部削除。削除した個数を返す
template <class T, class Compare, class Alloc>
int discard_all(set<T, Compare, Alloc> &s, const T &x)
{
    return (int)s.erase(x); // 0 or 1
}

template <class T, class Compare, class Alloc>
int discard_all(multiset<T, Compare, Alloc> &s, const T &x)
{
    return (int)s.erase(x); // remove all x
}

// ソート済みvectorでx以上/xより大きい最初の位置を返す(lower_bound/upper_bound相当)
template <class T, class U>
int bisect_left(const vector<T> &v, const U &x)
{
    return int(lower_bound(v.begin(), v.end(), x) - v.begin());
}

template <class T, class U>
int bisect_right(const vector<T> &v, const U &x)
{
    return int(upper_bound(v.begin(), v.end(), x) - v.begin());
}

// floor(a/b)。負数でも数学的に正しい(C++の/はゼロ方向切り捨てなので単純な a/b とは異なる)
template <class T, class U>
auto floor_div(T a, U b)
{
    auto q = a / b, r = a % b;
    return q - ((r != 0) && ((r < 0) != (b < 0)));
}

// ceil(a/b)。負数でも数学的に正しい
template <class T, class U>
auto ceil_div(T a, U b)
{
    auto q = a / b, r = a % b;
    return q + ((r != 0) && ((r < 0) == (b < 0)));
}

// floor(sqrt(n))をnと同じ型で返す(ll/i128どちらでも可、0<=n)
template <class T>
T isqrt(T n)
{
    T r = (T)sqrtl((long double)n);
    while (i128(r + 1) * (r + 1) <= (i128)n)
        r++;
    while (i128(r) * r > (i128)n)
        r--;
    return r;
}

// nが平方数ならtrue
template <class T>
bool is_square(T n)
{
    T r = isqrt(n);
    return i128(r) * r == (i128)n;
}

// a^eを繰り返し二乗法で計算(オーバーフローはTの範囲内で発生しうる)
template <class T>
T ipow(T a, long long e)
{
    T r = 1;
    while (e > 0)
    {
        if (e & 1)
            r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

// vをcomp順(省略時は昇順)に見たときのindex列を返す(stable)
// my_template.hppにも同名の1引数版argsortがあるが、比較関数の指定はできないため、
// こちらはカスタム比較(降順等)に対応した上位互換として維持している
// (comp省略時の1引数呼び出しはmy_template.hpp側が実際には選ばれる。動作確認済みで
// 結果は同じなので実害は無い)
template <class T, class Alloc, class Compare = less<T>>
vector<int> argsort(const vector<T, Alloc> &v, Compare comp = Compare())
{
    int n = (int)v.size();
    vector<int> order(n);
    iota(all(order), 0);
    stable_sort(all(order), [&](int i, int j)
                { return comp(v[i], v[j]); });
    return order;
}

template <class T, class Alloc>
void apply_order_one(const vector<int> &order, vector<T, Alloc> &v)
{
    assert(order.size() == v.size());
    vector<T, Alloc> res(v.get_allocator());
    res.reserve(v.size());
    for (int i : order)
    {
        assert(0 <= i && i < (int)v.size());
        res.push_back(v[i]);
    }
    v.swap(res);
}

// order[i]番目の要素を新しいi番目にする(複数vecsをまとめて並べ替え可)
template <class... Vecs>
void apply_order(const vector<int> &order, Vecs &...vs)
{
    (apply_order_one(order, vs), ...);
}

// keyを基準にargsort+apply_orderし、対応する複数vectorをまとめて並べ替える
template <class Key, class Alloc, class... Vecs>
void sort_by_key(vector<Key, Alloc> &key, Vecs &...vs)
{
    vector<int> order = argsort(key);
    apply_order(order, key, vs...);
}

// コピーを反転して返す(元データは変更しない)
template <class C>
C reversed(C c)
{
    reverse(c.begin(), c.end());
    return c;
}

// vの要素と同じ型Tで総和を返す
template <class T>
T sum(const vector<T> &v)
{
    return accumulate(v.begin(), v.end(), T(0));
}

// vの要素の総和をlong doubleで返す
template <class T>
ld sum_ld(const vector<T> &v)
{
    return accumulate(v.begin(), v.end(), 0.0L);
}

// a,bを連結した新しいvectorを返す(A+Bと同じ、a,bは変更しない)
// my_template.hppのconcatは第1引数を破壊的に(mutateして)結合するvoid関数のため、
// 非破壊で新しいvectorが欲しい場合はこちらを使う(operator+/+=もこれに依存)
template <class T, class AllocA, class AllocB>
vector<T, AllocA> concat(const vector<T, AllocA> &a, const vector<T, AllocB> &b)
{
    vector<T, AllocA> res;
    res.reserve(a.size() + b.size());
    res.insert(res.end(), a.begin(), a.end());
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

// vector同士をA+Bで連結
template <class T, class AllocA, class AllocB>
vector<T, AllocA> operator+(const vector<T, AllocA> &a, const vector<T, AllocB> &b)
{
    return concat(a, b);
}

// vectorの末尾にbを追記(A+=B)
template <class T, class AllocA, class AllocB>
vector<T, AllocA> &operator+=(vector<T, AllocA> &a, const vector<T, AllocB> &b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

// サイズ固定のarray同士を連結した新しいarray<T,N+M>を返す
template <class T, size_t N, size_t M>
array<T, N + M> concat(const array<T, N> &a, const array<T, M> &b)
{
    array<T, N + M> res{};
    copy(a.begin(), a.end(), res.begin());
    copy(b.begin(), b.end(), res.begin() + N);
    return res;
}

// 区切り文字付きjoinヘルパー
template <class It>
string join(It first, It last, const string &sep)
{
    ostringstream oss;
    bool first_elem = true;
    for (auto it = first; it != last; ++it)
    {
        if (!first_elem)
            oss << sep;
        first_elem = false;
        oss << *it;
    }
    return oss.str();
}

// vの各要素をsep区切りで連結した文字列を返す
inline string join(const vector<string> &v, const string &sep)
{
    size_t total = 0;
    if (!v.empty())
        total = (v.size() - 1) * sep.size();
    for (const auto &s : v)
        total += s.size();
    string res;
    res.reserve(total);
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            res += sep;
        res += v[i];
    }
    return res;
}

// sの各文字の間にsepを挟んだ文字列を返す
inline string join(const string &s, const string &sep)
{
    if (s.empty())
        return "";
    string res;
    if (!sep.empty())
        res.reserve(s.size() + (s.size() - 1) * sep.size());
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (i)
            res += sep;
        res += s[i];
    }
    return res;
}

// 任意のコンテナをsep区切りの文字列にまとめる
template <class C>
string join(const C &c, const string &sep)
{
    return join(c.begin(), c.end(), sep);
}

// 文字cの出現回数
inline int count(const string &s, char c)
{
    return int(std::count(s.begin(), s.end(), c));
}

// 部分文字列tの出現回数(重なりは数えない。tが空文字ならs.size()+1)
inline int count(const string &s, const string &t)
{
    if (t.empty())
        return int(s.size() + 1);
    int cnt = 0;
    size_t pos = 0;
    while (true)
    {
        pos = s.find(t, pos);
        if (pos == string::npos)
            break;
        ++cnt;
        pos += t.size(); // Python str.count と同じく重なりは数えない
    }
    return cnt;
}

// s内のfromをすべてtoに置換した新しい文字列を返す(sは変更しない)
inline string replace(string s, const string &from, const string &to)
{
    if (from.empty())
        return s;
    size_t pos = 0;
    while (true)
    {
        pos = s.find(from, pos);
        if (pos == string::npos)
            break;
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
    return s;
}

// 文字fromをすべてtoに置換した新しい文字列を返す
inline string replace(string s, char from, char to)
{
    std::replace(s.begin(), s.end(), from, to);
    return s;
}

// 連続する同じ値をまとめてvector<pair<値,連続回数>>で返す(ランレングス圧縮)
template <class C>
auto rle(const C &s)
{
    vector<pair<typename C::value_type, int>> res;
    for (const auto &x : s)
    {
        if (!res.empty() && res.back().first == x)
            res.back().second++;
        else
            res.push_back({x, 1});
    }
    return res;
}

// 上下左右4方向/斜め含む8近傍の差分配列(dxが行方向i, dyが列方向j)
constexpr int DX4[] = {1, 0, -1, 0};
constexpr int DY4[] = {0, 1, 0, -1};
constexpr int DX8[] = {1, 1, 0, -1, -1, -1, 0, 1};
constexpr int DY8[] = {0, 1, 1, 1, 0, -1, -1, -1};

// 0<=i<h && 0<=j<w の短縮形
inline bool in_grid(ll i, ll j, ll h, ll w)
{
    return 0 <= i && i < h && 0 <= j && j < w;
}

// rotate90等の内部ヘルパー。h行w列の空グリッドを作る(vector<string>にも対応)
template <class G>
G make_grid(int h, int w)
{
    using Row = typename G::value_type;
    if constexpr (is_same_v<Row, string>)
        return G(h, string(w, ' '));
    else
        return G(h, Row(w));
}

// 反時計回りに90度回転したw行h列のグリッドを返す(4回で元に戻る)
template <class G>
G rotate90(const G &g)
{
    int h = (int)g.size();
    int w = (int)g[0].size();
    G res = make_grid<G>(w, h);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            res[w - 1 - j][i] = g[i][j];
    return res;
}

// 時計回りに90度回転したw行h列のグリッドを返す(rotate90の逆変換)
template <class G>
G rotate90_cw(const G &g)
{
    int h = (int)g.size();
    int w = (int)g[0].size();
    G res = make_grid<G>(w, h);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            res[j][h - 1 - i] = g[i][j];
    return res;
}

// 180度回転したh行w列のグリッドを返す(rotate90を2回適用と同じ)
template <class G>
G rotate180(const G &g)
{
    G res(g);
    reverse(res.begin(), res.end());
    for (auto &row : res)
        reverse(row.begin(), row.end());
    return res;
}

// 転置したw行h列のグリッドを返す
template <class G>
G transpose(const G &g)
{
    int h = (int)g.size();
    int w = (int)g[0].size();
    G res = make_grid<G>(w, h);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            res[j][i] = g[i][j];
    return res;
}

// 左右反転(サイズは変わらない)
template <class G>
G flip_h(const G &g)
{
    G res(g);
    for (auto &row : res)
        reverse(row.begin(), row.end());
    return res;
}

// 上下反転(サイズは変わらない)
template <class G>
G flip_v(const G &g)
{
    G res(g);
    reverse(res.begin(), res.end());
    return res;
}

// background以外のセルを含む最小矩形(バウンディングボックス)に切り詰める。無ければ空グリッド
template <class G, class B>
G trim_grid(const G &g, const B &background)
{
    int h = (int)g.size();
    int w = (int)g[0].size();
    int min_i = h, max_i = -1, min_j = w, max_j = -1;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (g[i][j] != background)
            {
                min_i = min(min_i, i);
                max_i = max(max_i, i);
                min_j = min(min_j, j);
                max_j = max(max_j, j);
            }
        }
    }
    if (max_i < min_i)
        return {};

    G res = make_grid<G>(max_i - min_i + 1, max_j - min_j + 1);
    for (int i = min_i; i <= max_i; i++)
        for (int j = min_j; j <= max_j; j++)
            res[i - min_i][j - min_j] = g[i][j];
    return res;
}

// グラフが必要な場合は my-library/maspypy/graph/base.hpp の Graph<T, directed> を使う
// (#include "my-library/maspypy/graph/base.hpp")。無向/有向・重みあり/なしを1つで
// カバーする上位互換で、graph/以下の他のアルゴリズム(dijkstra等)もこれを前提にしている。

int main()
{
    // ここにコードを書く
}
