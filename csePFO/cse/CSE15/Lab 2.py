
def cartesian_product(X,Y):  
    cp = [] 
    count = 0
    
    for i in range(len(X)):
        for j in range(len(Y)):
            cp.append([])
            cp[count].append(X[i])
            cp[count].append(Y[j])
    count = count+1
    return cp
   

def power_set(X):    
    result = [[]] 
    for item in X:
        result.extend([ss + [item] for ss in result])
    return result
