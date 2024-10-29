int
satsum(int v1, int v2)
{
    int sgn_v1;
    int sgn_v2;
    enum 
    {
        MY_INT_MAX = (~0u)>>(!0),
        MY_INT_MIN = ~MY_INT_MAX
    };
    if (v1 > 0) {
        sgn_v1 = 1;
    } else {
        sgn_v1 = -1;
    }
    if (v2 > 0) {
        sgn_v2 = 1;
    } else {
        sgn_v2 = -1;
    }
    if ((sgn_v1 * sgn_v2) < 0){
        return v1 + v2;
    } else {
        if (sgn_v1 > 0) {
            if (MY_INT_MAX - v2 < v1) {
                return MY_INT_MAX;
            }
            return v1 + v2;
        } else {
            if (MY_INT_MIN - v2 < v1) {
                return MY_INT_MIN;
            }
            return v1 + v2;
        }
    }
}
