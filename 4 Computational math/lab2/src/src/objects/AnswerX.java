package src.objects;

import src.services.FormatterToDouble;

public class AnswerX {
    public double x;
    public int iterations;

    public AnswerX (double x, int iterations) {
        this.x = x;
        this.iterations = iterations;
    }

    @Override
    public String toString() {
        return "x = " + FormatterToDouble.format(x) + " за " + iterations + " итераций";
    }
}
