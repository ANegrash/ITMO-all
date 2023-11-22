package src.methods;

import src.objects.AnswerX;
import src.objects.Func;

//метод касательных
public class Tangent {
    public AnswerX calculate (Func function, double precision, double approx, int iterationCount) {

        double newApprox = approx - (function.calcFunc(approx) / function.calcDer(approx));
        double diff = Math.abs(function.calcFunc(newApprox));

        if ( diff < precision || iterationCount > 50 )
            return new AnswerX(newApprox, iterationCount);
        return calculate(function, precision, newApprox, iterationCount + 1);
    }
}
