# This is your coding interview problem for today.
# This problem was asked by IBM.
# Given a string with repeated characters, rearrange the string so that no two adjacent characters are the same. If this is not possible, return None.
# For example, given "aaabbc", you could return "ababac". Given "aaab", return None.


def arrange(s):
    s = list(s)
    for i in range(1, len(s)):
        if s[i] == s[i-1]:
            for j in range(i+1,len(s)):
                if s[j] != s[i]:
                    tmp = s[j]
                    s[j] = s[i]
                    s[i] = tmp
                    break
            if s[i] == s[i-1]:
                return False
    return "".join(s)

print(arrange("aaabbc"))
print(arrange("aaab"))
print(arrange("aacab"))
