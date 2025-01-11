def calc_strong_suf(pat):
    strong_suf = [None for _ in range(len(pat))]
    pat = ''.join(reversed(pat))
    z = [0 for _ in range(len(pat))]
    l, r = 0, 1
    for i in range(1, len(pat)):
        if i < r:
            z[i] = min(z[i - l], r - i)
        while i + z[i] < len(pat) and pat[i + z[i]] == pat[z[i]]:
            z[i] += 1
        if i + z[i] > r:
            l, r = i, i + z[i]
        if strong_suf[z[i]] is None: strong_suf[z[i]] = i
    return strong_suf

""" def ag_match(text, pat):
    pos = len(pat) - 1
    while pos < len(text):
        dist = 0
        while dist <= len(pat):
            cur_jump = suf_text_i[pos_text]
            if cur_jump is not None and cur_jump > 0:
                if suf_pat[len(pat) - 1 - dist] < cur_jump:
                    suf_text_i[pos] = dist
                    break
                dist += cur_jump
            else:
                if text[pos - dist] != pat[len(pat) - 1 - dist]:
                    break
                dist += 1
        if suf_text_i[pos] is None:
            suf_text_i[pos] = dist
        if dist == len(pat):
            report_occurence(pos - len(pat) + 1)
        pos += max(1, shift) """

if __name__ == '__main__':
    print(calc_strong_suf([11, 45, 11, 45, 90]))