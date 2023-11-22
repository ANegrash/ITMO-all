public class Cot {
    private final Sin sin;
    private final Cos cos;

    public Cot(Sin sin, Cos cos) {
        this.sin = sin;
        this.cos = cos;
    }

    public Cot() {
        this.sin = new Sin();
        this.cos = new Cos();
    }

    public double cot(double x, double eps) {
        double cosVal = cos.cos(x, eps);
        double sinVal = sin.sin(x, eps);
        if (Double.isNaN(cosVal) || Double.isNaN(sinVal) || sinVal == 0) return Double.NaN;
        return cosVal / sinVal;
    }
}