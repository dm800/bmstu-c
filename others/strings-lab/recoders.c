char caesar(char a) { 
    int num = (int)a;
    if ((num > 64) && (num < 91)) {
        num = (num + 3) - 26 * ((num + 3) / 91);
    }
    else {
        num = (num + 3) - 26 * ((num + 3) / 123);
    }
    return (char)num;
}