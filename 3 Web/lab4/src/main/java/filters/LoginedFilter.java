package filters;

import resources.UserManager;
import servlets.CheckUserServlet;

import javax.ejb.EJB;
import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Optional;


@WebFilter(filterName = "SessionFilter")
public class LoginedFilter implements Filter {

    private static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LoginedFilter.class);

    @EJB
    private UserManager ejb;

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {

        log.info("Filter starts");

        ArrayList<Cookie> arrayList = new ArrayList<Cookie>(Arrays.asList(((HttpServletRequest) servletRequest).getCookies()));
        Cookie cookie = null;
        try {
            Optional<Cookie> cookieOptional = arrayList.stream().filter(cookie1 -> "token".equals(cookie1.getName())).findFirst();

            if(cookieOptional == null || cookieOptional.get() == null){
                log.info("Doesn't have cookie");
                cookie = null;
                String path = "/error";
                RequestDispatcher requestDispatcher = servletRequest.getRequestDispatcher(path);
                requestDispatcher.forward(servletRequest, servletResponse);
            }else {
                cookie = cookieOptional.get();
                log.info("Get cookie: " + cookie.getValue());
            }
        }catch (Exception e){
            e.printStackTrace();
        }

        if(cookie != null){
            log.info("Cookie exists");
            if (ejb.hasSession(((HttpServletRequest)servletRequest).getSession(), cookie)){
                log.info("Filtered and goes");
                filterChain.doFilter(servletRequest, servletResponse);
            }else {
                log.info("Goes to error");
                String path = "/error";
                RequestDispatcher requestDispatcher = servletRequest.getRequestDispatcher(path);
                requestDispatcher.forward(servletRequest, servletResponse);
            }
        }else {
            log.info("Goes to error");
            String path = "/error";
            RequestDispatcher requestDispatcher = servletRequest.getRequestDispatcher(path);
            requestDispatcher.forward(servletRequest, servletResponse);
        }
    }
}
