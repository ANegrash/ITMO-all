package src.methods;

import src.objects.AnswerX;
import src.objects.Func;

//метод хорд
public class Chord {
    public AnswerX calculate (Func function, double precision, double begin, double end, int iterationCount) {

        double newBegin = begin - (function.calcFunc(begin) / (function.calcFunc(end) - function.calcFunc(begin)) * (end - begin));
        double diff = Math.abs(function.calcFunc(newBegin));

        if (diff < precision || iterationCount > 50)
            return new AnswerX(newBegin, iterationCount);
        return calculate(function, precision, newBegin, end, iterationCount + 1);
    }
}

