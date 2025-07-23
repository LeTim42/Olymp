#include "main.hpp"

#define input_args 
#define input_vars 
#define output int

#ifdef LOCAL
// #define TEST
void _test();
#endif

const bl _fastio = 1;
const bl _multitest = 0;
#ifdef LOCAL
const char* _input = "input.txt";
const char* _output = "";
#else
const char* _input = "";
const char* _output = "";
#endif

void _solve();

int main() {
    #ifdef TEST
    _test();
    #endif
    #ifdef LOCAL
    auto start = now();
    #endif
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
#include <thread>
#include <future>
#include "rnd.hpp"

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

// #define INPUT_ARGS_IN_CHECK

bl check(const output& ans_slow, const output& ans_fast
    #ifdef INPUT_ARGS_IN_CHECK
    , input_args
    #endif
) {
    /* check if ans_fast is a correct answer if one of the correct answers is ans_slow */
    re ans_slow == ans_fast;
}

void _test() {
    const uint64_t TEST_TIME_SECONDS = 5;
    const uint64_t TIME_LIMIT_MILLISECONDS = 0;
    auto _start = now();
    int _count;
    for (_count = 0; now() - _start < 1000000000 * TEST_TIME_SECONDS; ++_count) {
        /* generate input */
        output ans_slow = slow(input_vars);
        output ans_fast;
        bl _tle = 0;
        if (TIME_LIMIT_MILLISECONDS) {
            promise<output> _p;
            future<output> _f = _p.get_future();
            thread([&]{ _p.set_value(fast(input_vars)); }).detach();
            if (_tle = (_f.wait_for(chrono::milliseconds(TIME_LIMIT_MILLISECONDS)) != future_status::ready))
                cout << "Time limit exceeded on test " << _count+1 << '\n';
            else ans_fast = _f.get();
        } else ans_fast = fast(input_vars);
        if (!_tle) {
            if (check(ans_slow, ans_fast
                #ifdef INPUT_ARGS_IN_CHECK
                , input_vars
                #endif
            )) continue;
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
        out(ans_slow);
        if (_tle) exit(1);
        cout << "\n========= WRONG ANSWER =========\n";
        out(ans_fast);
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
