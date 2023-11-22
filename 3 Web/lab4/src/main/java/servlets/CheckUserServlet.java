package servlets;

import resources.UserInf;
import resources.UserManager;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/checkUser")
public class CheckUserServlet extends HttpServlet {

    private static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(CheckUserServlet.class);

    @EJB
    private UserManager ejb;

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        log.info("StartChecking");
        String login = req.getParameter("login");
        String password = req.getParameter("password");
        log.info("Login: " + login + " Password: " + password);
        try {
            int result = ejb.checkUser(login, password);
            log.info("Checked " + result);
            switch (result) {
                case 0: { //successful login
                    resp.setIntHeader("StatusOfLogIn", 0);
                    UserInf userInf = ejb.loginUser(login, password, req.getSession());
                    log.info((String.valueOf(userInf.getToken())));
                    Cookie cookie = new Cookie("token", String.valueOf(userInf.getToken()));
                    cookie.setMaxAge(-1);
                    resp.addCookie(cookie);
                    log.info("Completed");
                    break;
                }
                case 1: { //wrong login
                    resp.setIntHeader("StatusOfLogIn", 1);
                    log.info("Wrong login");
                    break;
                }
                case 2: { //wrong password
                    resp.setIntHeader("StatusOfLogIn", 2);
                    log.info("Wrong password");
                    break;
                }
            }
        } catch (Exception e) {
            log.warn(e.getMessage());
        }

    }
}
