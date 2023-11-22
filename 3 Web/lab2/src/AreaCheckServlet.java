import Resources.SessionShotsBean;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

@WebServlet("/check")
public class AreaCheckServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        long m = System.nanoTime();
        String start = LocalDateTime.now().format(DateTimeFormatter.ofPattern("dd-MM-yyyy(hh:mm:ss)"));

        double x = Double.parseDouble(request.getParameter("answerX"));
        double y = Double.parseDouble(request.getParameter("answerY"));
        double r = Double.parseDouble(request.getParameter("answerR"));

        boolean res = check(x, y, r);

        SessionShotsBean shots = (SessionShotsBean) request.getSession().getAttribute("shots");

        long time = System.nanoTime() - m;

        String str = x + " " + y + " " + r + " " + res + " " + start + " " + ((time) / 1000);

        shots.addFirst(str);

        getServletContext().getRequestDispatcher("/pages/result.jsp").forward(request, response);
    }


    //Previously checked initialization and intervals
    public boolean check(double x, double y, double r) {
        if (y >= 0) {
            if (x > 0) {
                return ((x + 2 * y) <= r);
            } else {
                return ((-x <= r) && (y <= r / 2));
            }
        } else {
            if (x > 0) {
                return false;
            } else {
                return (x * x + y * y <= r * r);
            }
        }
    }

}
