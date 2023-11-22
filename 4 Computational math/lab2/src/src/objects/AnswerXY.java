package src.objects;

import src.services.FormatterToDouble;

public class AnswerXY {
    public double x;
    public double y;
    public int iterations;

    public AnswerXY (double x, double y, int iterations) {
        this.x = x;
        this.y = y;
        this.iterations = iterations;
    }

    @Override
    public String toString() {
        return "x = " + FormatterToDouble.format(x) + "; y = " + FormatterToDouble.format(y) + " за " + iterations + " итераций";
    }
}
