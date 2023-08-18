double sqrt2(double num) {
    double err = 0.0001,
        res = num;

    while (res - num/res > err)
        res = (res + num/res) / 2;

    return res;
}