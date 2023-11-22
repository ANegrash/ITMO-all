public class Tan {
    private final Sin sin;
    private final Cos cos;

    public Tan(Sin sin, Cos cos) {
        this.sin = sin;
        this.cos = cos;
    }

    public Tan() {
        this.sin = new Sin();
        this.cos = new Cos();
    }

    public double tan(double x, double eps) {
        double cosVal = cos.cos(x, eps);
        double sinVal = sin.sin(x, eps);
        if (Double.isNaN(sinVal) || Double.isNaN(cosVal) || cosVal == 0) return Double.NaN;
        return sinVal / cosVal;
    }
}
