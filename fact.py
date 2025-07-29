def fact(n):
    if n==1:
        return 1
    else:
        exp = n*fact(n-1)
    return exp
    
print(str(fact(5)))