// https://www.hackerrank.com/challenges/morgan-and-a-string/problem

string morganAndString(string a, string b) {
    int m = a.length(), n = b.length();
    string s = "";
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (a[i] <= b[j]) {
            s.push_back(a[i]); i++;
        }
        else if (a[i] > b[j]) {
            s.push_back(b[j]); j++;
        }
    }
    while (i < m) {
        s.push_back(a[i]); i++;
    }
    while (j < n) {
        s.push_back(b[j]); j++;
    }
    return s;
}