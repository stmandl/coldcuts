# This problem was asked by Dropbox.
#
# Spreadsheets often use this alphabetical encoding for its columns: "A", "B", "C", ..., "AA", "AB", ..., "ZZ", "AAA", "AAB", ....
#
# Given a column number, return its alphabetical column id.
# For example, given 1, return "A". Given 27, return "AA".

# def mod26(n):
#     n_orig = n
#     if n == 0: 
#         divs = [0]
#     else:
#         divs = []
#         while n > 0:
#             divs.append(n % 26)
#             n //= 26
#             #print("a", n, divs)
#     return "".join([chr(ord('A')+n) for n in reversed(divs)]), divs, n_orig

def base10ToBase26Letter(num):
    ''' Converts any positive integer to Base26(letters only) with no 0th 
    case. Useful for applications such as spreadsheet columns to determine which 
    Letterset goes with a positive integer.
    '''
    if num <= 0:
        return ""
    elif num <= 26:
        return chr(96+num)
    else:
        return base10ToBase26Letter(int((num-1)/26))+chr(97+(num-1)%26)

for i in range(100):
    print(i, base10ToBase26Letter(i))