void main(void) { 
    int x; 
    int resp;

    /* calcula 5^4 = 625 */

    x = 0;
    resp = 1;

    while (x < 4){
        resp = resp * 5;
        x = x + 1;
        output(resp);
    }
    output(resp);
}