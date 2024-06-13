/*

Palindromic Index

Remove this index and the string becomes palindrome.
*/

bool isPalindrome (string s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j])
            return false;
        else {
            i++; j--;
        }
    }
    return true;
}

int palindromeIndex(string s) {
    int i = 0, j = s.length() - 1;
    int remove = -1;
    while (i < j) {
        if (s[i] == s[j]) {
            i++; j--;
        }
        else if (isPalindrome(s, i + 1, j))
            return i;
        else if (isPalindrome(s, i, j - 1))
            return j;
    }
    return -1;
}