fn wildcard_match(pattern: &str, text: &str) -> bool {
    let (mut p, mut t) = (0, 0);
    let (mut star, mut match_pos) = (None, 0);

    let pat: Vec<char> = pattern.chars().collect();
    let txt: Vec<char> = text.chars().collect();

    while t < txt.len() {
        if p < pat.len() && (pat[p] == '?' || pat[p] == txt[t]) {
            p += 1; t += 1;
        } else if p < pat.len() && pat[p] == '*' {
            star = Some(p);
            p += 1;
            match_pos = t;
        } else if let Some(s) = star {
            p = s + 1;
            match_pos += 1;
            t = match_pos;
        } else {
            return false;
        }
    }

    while p < pat.len() && pat[p] == '*' { p += 1; }

    p == pat.len()
}
