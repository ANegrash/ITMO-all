import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/exception")
public class ExceptionServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        int attribute = (int) request.getAttribute("Except");

        switch (attribute) {
            case 0: {
                request.setAttribute("Content",
                        "<p>" + "Exception, not initialised: " + "</p>" +
                                "<p>" + "x = " + request.getParameter("answerX") + "</p>" +
                                "<p>" + "y = " + request.getParameter("answerY") + "</p>" +
                                "<p>" + "r = " + request.getParameter("answerR") + "</p>"
                );
            }
            case 1: {
                request.setAttribute("Content",
                        "<p>" + "Exception, wrong type: " + "</p>" +
                                "<p>" + "x = " + request.getParameter("answerX") + "</p>" +
                                "<p>" + "y = " + request.getParameter("answerY") + "</p>" +
                                "<p>" + "r = " + request.getParameter("answerR") + "</p>"
                );
            }
            case 2: {
                request.setAttribute("Content",
                        "<p>" + "Exception, not in range: " + "</p>" +
                                "<p>" + "Must: [-3;5] " + "x = " + request.getParameter("answerX") + "</p>" +
                                "<p>" + "Must: [-3;3] " + "y = " + request.getParameter("answerY") + "</p>" +
                                "<p>" + "Must: [2;5] " + "r = " + request.getParameter("answerR") + "</p>"
                );
            }
        }

        getServletContext().getRequestDispatcher("/pages/result.jsp").forward(request, response);

    }

}
