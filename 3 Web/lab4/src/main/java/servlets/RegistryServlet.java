package servlets;

import beansLab.entities.User;
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


@WebServlet("/register")
public class RegistryServlet extends HttpServlet {

    private static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(CheckUserServlet.class);

    @EJB
    private UserManager ejb;

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        log.info("Got request");

        String login = req.getParameter("login");
        String password = req.getParameter("password");

        log.info("Login: " + login + " Password: " + password);

        boolean res = ejb.addUser(new User(login, password));

        log.info("Result of registration: " + res);
        if(res){
            resp.setIntHeader("StatusOfRegistration", 1);
        }else {
            resp.setIntHeader("StatusOfRegistration", 0);
        }
    }
}
