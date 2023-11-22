package src.methods;

import src.objects.AnswerXY;
import src.objects.EqSystem;

//метод простой итерации
public class Iteration {
    public AnswerXY calculate (EqSystem system, double precision, double x, double y, int iterationCount) {

        double newX = system.x1(y);
        double newY = system.y2(x);

        double diffX = Math.abs(newX - x);
        double diffY = Math.abs(newY - y);

        if ((diffX < precision && diffY < precision) || iterationCount > 50)
            return new AnswerXY(newX, newY, iterationCount);

        return calculate(system, precision, newX, newY, iterationCount + 1);
    }
}
