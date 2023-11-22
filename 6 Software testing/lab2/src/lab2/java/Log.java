public class Log {

    private final Ln ln;

    public Log(Ln ln) {
        this.ln = ln;
    }

    public Log() {
        this.ln = new Ln();
    }

    public double log(double base, double digit, double esp) {
        return ln.ln(digit, esp) / ln.ln(base, esp);
    }

}
