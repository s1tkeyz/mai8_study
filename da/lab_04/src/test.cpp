#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using position_t = std::pair<size_t, size_t>;
using string_t = std::vector<uint32_t>;
using text_t = std::vector<std::pair<uint32_t, position_t>>;
using pattern_t = string_t;

std::map<uint32_t, std::vector<size_t>> calcRPos(const pattern_t& p) {
    size_t n = p.size();
    std::map<uint32_t, std::vector<size_t>> rpos;
    for (size_t i = 0; i < n; ++i) {
        rpos[p[i]].push_back(i);
    }
    return rpos;
}

size_t getBCShift(size_t notmatchpospat, uint32_t notmatchword, std::map<uint32_t, std::vector<size_t>> rpos){
    if(!rpos.contains(notmatchword))
        return 1;

    int64_t posBadinPat = -1;
    for (size_t i = rpos[notmatchword].size(); i > 0; --i) {
        if(rpos[notmatchword][i - 1] < notmatchpospat){
            posBadinPat = rpos[notmatchword][i - 1];
            break;
        }
    }
    if(posBadinPat ==-1)
        return 1;
    size_t shift = notmatchpospat - posBadinPat;
    return shift;
}

std::vector<size_t> calcZFunction(const pattern_t& p) {
    size_t n = p.size();

    size_t l = 0;
    size_t r = 0;

    std::vector<size_t> zf(n, 0);
    for (size_t i = 1; i < n; ++i) {
        if (i <= r)
            zf[i] = std::min(r - i + 1, zf[i - l]);

        while (i + zf[i] < n && (p[n - 1 - zf[i]] == p[n - 1 - (i + zf[i])]))
            zf[i]++;

        if (i + zf[i] - 1 > r) {
            l = i;
            r = i + zf[i] - 1;
        }
    }
    return zf;
}


std::vector<size_t> calcGoodSuffix(const pattern_t& p){
    std::vector<size_t> zFunction = calcZFunction(p);

    size_t n = p.size();
    std::vector<size_t> N(zFunction.rbegin(), zFunction.rend());
    std::vector<size_t> L(n + 1, n);

    size_t j;
    for(size_t i = 0; i < n - 1; ++i) {
        j = n - N[i];
        L[j] = i;
    }

    std::vector<size_t> l(n + 1, n);
    for(size_t i = n; i > 0; --i) {
        j = n - i + 1;
        if (N[j - 1] == j) {
            l[i - 1] = (j - 1);
        }
        else {
            l[i - 1] = l[i];
        }
    }

    for(size_t i = 0; i < n + 1; ++i)
        if (L[i] == n) {
            L[i] = l[i];
        }

    for (auto &x : L) {
        if (x != n) {
            x = n - 1 - x;
        }
    }
    return L;
}

std::vector<size_t> calcPS(const pattern_t& p, const std::vector<size_t>& nf) {
    size_t n = p.size();

    std::vector<size_t> ps(n, 0);

    for (size_t i = n; i > 0; i--) {
        size_t j = n - i;
        if (nf[j] == j + 1) {
            ps[i - 1] = j + 1;
        } 
        else {
            if (i - 1 == n - 1) {
                ps[i - 1] = 0;
            } 
            else {
                ps[i - 1] = ps[i];
            }
        }
    }
    return ps;
}

int main(void) {
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);

    pattern_t pattern;
    text_t text;

    std::string s;

    getline(std::cin, s, '\n');
    std::istringstream ipatternstr(s);

    uint32_t x;
    while(ipatternstr >> x) { pattern.push_back(x); }

    position_t cur_pos = {0, 0};
    while(getline(std::cin, s, '\n')) {
        std::istringstream ipatternstr(s);
        uint32_t x;
        while(ipatternstr >> x) {
            text.push_back({x, cur_pos});
            cur_pos.second++;
        }
        cur_pos.first++;
    }

    std::map<uint32_t, std::vector<size_t>> rpos = calcRPos(pattern);
    std::vector<size_t> zf = calcZFunction(pattern);
    std::vector<size_t> nf(zf.rbegin(), zf.rend());
    std::vector<size_t> gs = calcGoodSuffix(pattern);
    std::vector<size_t> ps = calcPS(pattern, nf);

    std::vector<position_t> occurances;
    std::vector<size_t> M(text.size());

    size_t n = pattern.size();
    size_t i = 0;
    size_t h = 0;
    size_t k = n;

    while (k <= text.size()) {
        i = n - 1;
        h = k - 1;
        while (true) {
            if (M[h] == 0) {
                if (pattern[i] == text[h].first) {
                    if (i == 0) {
                        occurances.push_back(text[k - n].second);
                        M[k - 1] = n;
                        if (n > 2) {
                            k += n - ps[1];
                        } 
                        else {
                            k++;
                        }
                        break;
                    } else {
                        i--;
                        h--;
                    }
                } 
                else {
                    M[k - 1] = k - h -1;
                    k += std::max({gs[i + 1], getBCShift(i, text[h].first, rpos)});
                    break;
                }
            } 
            else if (M[h] < nf[i]) {
                i -= M[h];
                h -= M[h];
            } 
            else if (M[h] >= nf[i] && nf[i] >= i) {
                occurances.push_back(text[k - n].second);
                M[k - 1] = k - 1 - h;
                if (n > 2) {
                    k += n - ps[1];
                } else {
                    k++;
                }
                break;
            } 
            else if (M[h] > nf[i] && nf[i] < i) {
                M[k - 1] = k - h - 1;
                h -= nf[i];
                i -= nf[i];
                k += std::max({gs[i + 1], getBCShift(i, text[h].first, rpos)});
                break;
            } 
            else if (M[h] == nf[i] && nf[i] < i) {
                i -= M[h];
                h -= M[h];
            }
        }
    }

    for (const auto &o : occurances) {
        std::cout << o.first + 1 << ", " << o.second + 1 << '\n';
    }

    return EXIT_SUCCESS;
}