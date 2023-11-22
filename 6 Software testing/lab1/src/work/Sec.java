package work;

public class Sec {
    public static double sec(double x){
        boolean isMinus = false;
        double result = 1, rad;

        x = x % 360;
        if (x < 0) x = -x;
        if (x == 90)
            return Double.POSITIVE_INFINITY;
        else if (x > 90 && x <= 180) {
           isMinus = true;
           x = 90 - (x - 90);
        } else if (x > 180 && x < 270) {
            isMinus = true;
            x = x - 180;
        } else if (x == 270)
            return Double.NEGATIVE_INFINITY;
        else if (x > 270)
            x = 90 - (x - 270);

        rad = deg2rad(x);
        for (int i = 1; i <= 14; i++)
            result = result + ((Math.pow(-1, i)) * (Math.pow(rad, 2 * i)) / getFactorial(2 * i));
        result = 1 / result;
        return isMinus ? (-1 * result) : result;
    }

    public static int getFactorial(int f) {
        if (f <= 1)
            return 1;
        else
            return f * getFactorial(f - 1);
    }

    public static double deg2rad(double value) {
        return (value * Math.PI) / 180;
    }
}
