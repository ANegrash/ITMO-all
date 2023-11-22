public class Function {
    Sec sec;
    Log log;
    Ln ln;
    Tan tan;
    Cos cos;
    Cot cot;
    Sin sin;
    Csc csc;

    public Function() {
        this.sec = new Sec();
        this.ln = new Ln();
        this.log = new Log(ln);
        this.tan = new Tan();
        this.cos = new Cos();
        this.cot = new Cot();
        this.sin = new Sin();
        this.csc = new Csc();
    }

    public Function(Sec sec, Ln ln, Log log, Tan tan, Cos cos, Cot cot, Sin sin, Csc csc) {
        this.sec = sec;
        this.log = log;
        this.ln = ln;
        this.tan = tan;
        this.cos = cos;
        this.cot = cot;
        this.sin = sin;
        this.csc = csc;
    }

    public double SystemSolve(double x, double eps) {
        if (x <= 0)
            return ((((((sec.sec(x, eps) / tan.tan(x, eps)) - (cos.cos(x, eps) + cos.cos(x, eps))) + cot.cot(x, eps)) * (((sec.sec(x, eps) / tan.tan(x, eps)) - (cos.cos(x, eps) + cos.cos(x, eps))) + cot.cot(x, eps))) - (sin.sin(x, eps) + csc.csc(x, eps))) * cot.cot(x, eps));
        else
            return (((((log.log(5, x, eps) * log.log(3, x, eps)) * log.log(3, x, eps)) - log.log(5, x, eps)) / ((log.log(2, x, eps) * (ln.ln(x, eps) + log.log(10, x, eps))) + log.log(2, x, eps))) * ln.ln(x, eps));
    }
}
