# This is your coding interview problem for today.
#
# This problem was asked by Google.
#
# Given a string, split it into as few strings as possible such that each string is a palindrome.
#
# For example, given the input string racecarannakayak, return ["racecar", "anna", "kayak"].
#
# Given the input string abc, return ["a", "b", "c"].

# brute-force:
# 1. fn to check palindrom
# 2. iterate from each pos to end and check if pali
# 2a. if successful: add to result and continue with rest
# 2b. else add current position to result and continue from next position


def is_pali(str):
    return str == str[::-1]

for w in ["racecar", "anna", "kayak"]:
    print(w, 'is pali:', is_pali(w))

def find_pali(str):
    a, b = 0, len(str)-1
    res = []
    while a<len(str):
        while b>=a:
            if is_pali(str[a:b+1]):
                res.append(str[a:b+1])
                a = b+1
                b = len(str) -1
                break
            else:
                b -= 1
    return res

print(find_pali("racecarannakayak"))
print("--------------")
print(find_pali("abbaracecarannakayak"))
print(find_pali("abbaraceannaraccarannakayak"))