/*int fatorial ( int n){
    if(n == 1)
        return 1;
    else
    {
        return n* fatorial (n -1) ;
    }
}

int main ( void ){
    int n;
    int fat ;
    n = input () ;
    fat = fatorial (n);
    output ( fat );
}*/




/*void main(void) { 
    int x; 
    x = 1;
    while (x <= 4){
        x = x + 1;
    }
    output(x);
    return 0;
}*/

/*void main(void) { 
    int x[5]; 
    x[1] = 22;
    while (x[1] <= 5){
        x[2] = x[1] + 1;
    }
    output(x);
    return 0;
}*/

/*int gcd ( int u , int v){
    if (v ==0) return u;
    else return gcd (v , u -u /v*v) ;
}
void main ( void ){
    int x; int y;
    x = input () ;
    y = input () ;
    output ( gcd (x ,y));
}*/

/*int vet [ 10 ];
int minloc ( int a [] , int low , int high ){
    int i; int x; int k;
    k = low ;
    x = a [ low ];
    i = low + 1;
    while (i < high ){
    if (a [i] < x ){
        x = a [i ];
        k = i ;
    }
    i = i + 1;
    }
    return k;
}
void sort ( int a [] , int low , int high ){
    int i; int k;
    i = low ;
    while (i < high -1) {
        int t;
        k = minloc (a ,i , high );
        t = a [k ];
        a[k ] = a[ i ];
        a[i ] = t;
        i = i + 1;
    }
}

void main ( void ){
    int i;
    i = 0;
    while (i < 10) {
        vet [i] = input () ;
        i = i + 1;
    }
    sort ( vet ,0 ,10) ;
    i = 0;
    while (i < 10) {
        output ( vet [i ]) ;
        i = i + 1;
    }
}*/