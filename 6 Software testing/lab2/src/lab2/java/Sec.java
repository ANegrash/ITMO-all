public class Sec {
    private final Cos cos;

    public Sec(Cos cos) {
        this.cos = cos;
    }

    public Sec() {
        this.cos = new Cos();
    }

    public double sec(double x, double eps) {
        double cosVal = cos.cos(x, eps);
        if (Double.isNaN(cosVal) || cosVal == 0) return Double.NaN;
        return 1 / cosVal;
    }
}
