int gcd (int u, int v) {
    
    u = 4;
    v = u + 1;

    if (v == 0) 
        return u ; 
    else 
        return gcd(v,u-u/v*v); 
     
}

void main(void) { 
    int x; 
    int y;
    x = input(); 
    y = input(); 
    output(gcd(x,y));
}