import Resources.SessionShotsBean;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/control")
public class ControllerServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        HttpSession hSession = request.getSession();
        Object shots = hSession.getAttribute("shots");
        if (shots == null) {
            shots = new SessionShotsBean();
            hSession.setAttribute("shots", shots);
        }

        String xS = request.getParameter("answerX");
        String yS = request.getParameter("answerY");
        String rS = request.getParameter("answerR");

        ServletContext servletContext = getServletContext();
        RequestDispatcher requestDispatcher = null;
        String path = null;
        if (xS != null && yS != null && rS != null) {
            try {
                double x = Double.parseDouble(xS);
                double y = Double.parseDouble(yS);
                double r = Double.parseDouble(rS);
                if ((x >= -3 && x <= 5) && (y >= -3 && y <= 3) && (r >= 2 && r <= 5)) {
                    path = "/check";
                    requestDispatcher = servletContext.getRequestDispatcher(path);
                    requestDispatcher.forward(request, response);
                    return;
                }else {
                    request.setAttribute("Except", 2);
                }
            } catch (Exception e) {
                request.setAttribute("Except", 1);
            }
        } else {
            request.setAttribute("Except", 0);
        }
        path = "/exception";
        requestDispatcher = servletContext.getRequestDispatcher(path);
        requestDispatcher.forward(request, response);

    }

}
