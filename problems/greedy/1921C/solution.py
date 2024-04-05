def solve():
    string = input()
    n, f, a, b = string.split(" ")
    n = int(n)
    f = int(f)
    a = int(a)
    b = int(b)
    
    
    arr = input();
    arr = arr.split(" ")
    prev = 0
    for i in range(0,n):
        arr[i] = int(arr[i])
        var1 = (arr[i]-prev)*a
        var2 = b;
        f-= min(var1, var2)
        #print(i , arr[i], var1, var2, f)
        prev = arr[i]
        if(f<=0):
            print("NO")
            return 0
    print("yes");
    return 0
                
    
    
    
 
t = int(input())
 
while t:
    solve()
    t-=1
