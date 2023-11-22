public class Cos {

    private final Sin sin;

    public Cos(Sin sin) {
        this.sin = sin;
    }

    public Cos() {
        this.sin = new Sin();
    }

    public double cos(double x, double eps) {
        double x_init = x;
        x %= Math.PI * 2;
        if (Double.POSITIVE_INFINITY == x || Double.NEGATIVE_INFINITY == x)
            return Double.NaN;

        if (x < -Math.PI)
            while (x < -Math.PI) x += 2 * Math.PI;

        if (x > Math.PI)
            while (x > Math.PI) x -= 2 * Math.PI;

        double result;
        if (x > Math.PI / 2 || x < -Math.PI / 2)
            result = -1 * Math.sqrt(1 - sin.sin(x_init, eps) * sin.sin(x_init, eps));
        else
            result = Math.sqrt(1 - sin.sin(x_init, eps) * sin.sin(x_init, eps));

        if (Math.abs(result) > 1) return Double.NaN;
        if (Math.abs(result) <= eps) return 0;
        return result;
    }
}
