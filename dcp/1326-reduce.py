# This is your coding interview problem for today.

# This problem was asked by Stripe.

# reduce (also known as fold) is a function that takes in an array, a combining
# function, and an initial value and builds up a
#  result by calling the combining function on each element of the array, left
#  to right. For example, we can write sum() in terms of reduce:

# def add(a, b):
#     return a + b

# def sum(lst):
#     return reduce(lst, add, 0)
# This should call add on the initial value with the first element of the
# array, and then the result of that with the second element of the array, and
# so on until we reach the end, when we return the sum of the array.

# Implement your own version of reduce.

# We will be sending the solution tomorrow, along with tomorrow's question. As
# always, feel free to shoot us an email if there's anything we can help with.

lst = [1,2,3,4,5,6]

def add(a, b):
    return a + b


def reduce(lst, f, init):
  res = init
  for e in lst:
    res = f(res, e)
  return res

print(reduce(lst, add, 0))