#include "main.hpp"

#define input_args 
#define input_vars 
#define output int

#ifdef LOCAL
// #define TEST
void _test();
#endif

bl _fastio, _multitest;
char *_input, *_output;

void _settings() {
    _fastio = 1;
    _multitest = 0;
    #ifdef TEST
    _test();
    #endif
    #ifdef LOCAL
    static char input_[] = "input.txt";
    static char output_[] = "";
    #else
    static char input_[] = "";
    static char output_[] = "";
    #endif
    _input = input_;
    _output = output_;
}

void _solve();

int main() {
    #ifdef LOCAL
    auto start = now();
    #endif
    _settings();
    if (_fastio) {
        ios::sync_with_stdio(0);
        cin.tie(0); cout.tie(0);
    }
    if (_input[0]) freopen(_input, "r", stdin);
    if (_output[0]) freopen(_output, "w", stdout);
    int t = 1;
    if (_multitest) cin >> t;
    while (t--) _solve();
    #ifdef LOCAL
    auto finish = now();
    cout << "\nWorking time: " << (int)round((finish - start) / 1e6) << "ms";
    #endif
    re 0;
}

#ifdef TEST
output slow(input_args); // slow but 100% correct solution
output fast(input_args); // fast but not sure if it's a correct solution
void out(const output&);

void copy(str s) {
    auto glob = GlobalAlloc(GMEM_FIXED, sz(s)+1);
    memcpy(glob, s.c_str(), sz(s)+1);
    OpenClipboard(GetDesktopWindow());
    EmptyClipboard();
    SetClipboardData(CF_TEXT,glob);
    CloseClipboard();
}

bl check(const output& ans1, const output& ans2/*, input_args*/) {
    /* check if ans2 is a correct answer if one of the correct answers is ans1 */
    re ans1 == ans2;
}

void _test() {
    const uint64_t TEST_TIME_SECONDS = 5;
    const uint64_t TIME_LIMIT_MILLISECONDS = 0;
    auto _start = now();
    int _count;
    for (_count = 0; now() - _start < 1000000000 * TEST_TIME_SECONDS; ++_count) {
        /* generate input */
        output ans1 = slow(input_vars);
        output ans2;
        bl _tle = 0;
        if (TIME_LIMIT_MILLISECONDS) {
            promise<output> _p;
            future<output> _f = _p.get_future();
            thread([&]{ _p.set_value(fast(input_vars)); }).detach();
            if (_tle = (_f.wait_for(chrono::milliseconds(TIME_LIMIT_MILLISECONDS)) != future_status::ready))
                cout << "Time limit exceeded on test " << _count+1 << '\n';
            else ans2 = _f.get();
        } else ans2 = fast(input_vars);
        if (!_tle) {
            if (check(ans1, ans2/*, input_vars*/)) continue;
            cout << "Wrong answer on test " << _count+1 << '\n';
        }
        cout << "\n============ INPUT =============\n";
        sstr ss;
        if (_multitest) ss << "1\n";
        /* print input to stringstream */
        str _str = ss.str();
        copy(_str);
        cout << _str;
        cout << "\n======== CORRECT ANSWER ========\n";
        out(ans1);
        if (_tle) exit(1);
        cout << "\n========= WRONG ANSWER =========\n";
        out(ans2);
        exit(1);
    }
    cout << _count << " tests passed\n";
    exit(0);
}
#endif

/// ================ ACTUAL CODE STARTS HERE ================ ///

const str NY[] = {"N", "Y"};
const str NoYes[] = {"No", "Yes"};
const str NOYES[] = {"NO", "YES"};

void out(const output& ans) {
    cout << ans << '\n';
}

output slow(input_args) {
    re {};
}

output fast(input_args) {
    re {};
}

void _solve() {
    /* get input */
    auto ans = fast(input_vars);
    out(ans);
}
