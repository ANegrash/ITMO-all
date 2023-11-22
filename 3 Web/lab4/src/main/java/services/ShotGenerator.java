package services;

import beansLab.entities.Shot;

import java.time.LocalDateTime;

public class ShotGenerator {

    public static Shot generateShot(double xIn, double yIn, double rIn){
        LocalDateTime start = LocalDateTime.now();
        long scriptTime = System.nanoTime();
        boolean GR = check(xIn, yIn, rIn);
        scriptTime = System.nanoTime() - scriptTime;

        Shot shot = new Shot();
        shot.setX(xIn);
        shot.setY(yIn);
        shot.setR(rIn);
        shot.setRG(GR);
        shot.setStart(start);
        shot.setScriptTime(scriptTime);

        return shot;
    }

    private static boolean check(double x, double y, double r) {
        if ((y == 0 && ((x > 0 && x <= r) || ((-x) <= r/2))) || (x == 0 && (((y > 0) && (y <= r)) || ((-y) <= r/2)))) {
            return true;
        }
        if (y > 0) {
            if (x > 0) {
                return false;
            } else {
                return ((-x*2) + y <= r);
            }
        } else {
            if (x > 0) {
                return ((x <= r) && (-y*2 <= r));
            } else {
                return (x * x + y * y <= (r * r)/4);
            }
        }
    }
}
