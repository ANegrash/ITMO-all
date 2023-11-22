package servlets;

import beansLab.entities.Shot;
import beansLab.entities.User;
import resources.UserManager;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

@WebServlet("/faces/checkShot")
public class AreaCheckServlet extends HttpServlet {

    private static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(CheckUserServlet.class);

    @EJB
    private UserManager ejb;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        int shotsSize = request.getIntHeader("rows");
        User user = (User) request.getSession().getAttribute("User");
        List<Shot> shots = user.getShots();

        if(shotsSize == -2){
            ejb.clearUser(user);
        }

        log.info("Rows code: " + shotsSize);
        log.info("User: " + user.getLogin());
        log.info("Rows: " + shots.size());

        if (shotsSize > -1) {

            log.info("Add one shot");

            String xStr = request.getParameter("coord_x");
            String yStr = request.getParameter("coord_y");
            String rStr = request.getParameter("coord_r");

            log.info("X: " + xStr);
            log.info("Y: " + yStr);
            log.info("R: " + rStr);

            double x = Double.parseDouble(xStr);
            double y = Double.parseDouble(yStr);
            double r = Double.parseDouble(rStr);

            Shot shot = addShot(x, y, r, user);

            if (shotsSize != 0) {
                log.info("Write just one");
                String string = formSCV(shot);
                response.getWriter().println(string);
            }

        }

        response.setIntHeader("rows", shots.size());

        if (shotsSize == 0 || shotsSize == -1) { //how many str-s has the user
            log.info("Write them all");
            for (int i = shots.size() - 1; i >= 0; i--) {
                String string = formSCV(shots.get(i));
                response.getWriter().println(string);
            }
        }

        response.getWriter().flush();

        log.info("Response written");

    }

    private Shot addShot(double x, double y, double r, User user) {

        long m = System.nanoTime();

        LocalDateTime start = LocalDateTime.now();

        boolean res = check(x, y, r);

        long time = System.nanoTime() - m;

        Shot shot = new Shot();
        shot.setX(x);
        shot.setY(y);
        shot.setR(r);
        shot.setRG(res);
        shot.setStart(start);
        shot.setScriptTime(time);

        ejb.addShotToUser(user, shot);

        return shot;
    }

    private String formSCV(Shot shot) {
        return cut(shot.getX()) + " " + cut(shot.getY()) + " " + cut(shot.getR()) + " " + shot.isRG() + " " + shot.getStart().format(DateTimeFormatter.ofPattern("dd-MM-yyyy;HH:mm:ss")) + " " + ((shot.getScriptTime()) / 1000);
    }

    private String cut(double num) {
        String result;
        if (num >= 0) {
            if (String.valueOf(num).length() > 7) {
                result = (String.valueOf(num)).substring(0, 6);
            } else {
                result = String.valueOf(num);
            }
        } else {
            if (String.valueOf(num).length() > 8) {
                result = (String.valueOf(num)).substring(0, 7);
            } else {
                result = String.valueOf(num);
            }
        }
        return result;
    }

    //Previously checked initialization and intervals
    public boolean check(double x, double y, double r) {
        if ((y == 0 && ((x > 0 && x <= r) || ((-x) <= r / 2))) || (x == 0 && (((y > 0) && (y <= r)) || ((-y) <= r / 2)))) {
            return true;
        }
        if (y > 0) {
            if (x > 0) {
                return false;
            } else {
                return ((-x * 2) + y <= r);
            }
        } else {
            if (x > 0) {
                return ((x <= r) && (-y * 2 <= r));
            } else {
                return (x * x + y * y <= (r * r) / 4);
            }
        }
    }
}
