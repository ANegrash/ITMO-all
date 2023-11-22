package resources;

import beansLab.entities.Shot;
import beansLab.entities.User;
import dao.UserDao;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpSession;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Stream;

@Startup
@Singleton
public class UserManager {

    private static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(UserManager.class);

    private ReentrantLock rLock;

    private UserDao usersDao;

    private List<User> users;

    private HashMap<String, UserInf> goingSessions = new HashMap<>(); //Session id + userInf

    public UserManager() {

    }

    @PostConstruct
    public void init(){
        usersDao = new UserDao();
        users = usersDao.findAllUsers();
        users.stream().forEachOrdered(user -> {
            log.info("UserInformFor " + user.getLogin() + " ------");
        });
        log.info("Initialised user manager: " + users.size());
        rLock = new ReentrantLock();
    }

    public int checkUser(String login, String password) throws Exception {
        //password is a HASH of real str of password
        rLock.lock();
        Stream<User> logined = users.stream().filter(user -> (user.getLogin().equals(login)));
        if (logined.count() == 0) {
            return 1;
        }
        long matches = users.stream().filter(user -> (user.getLogin().equals(login))).filter(user -> user.getPassword().equals(password)).count();
        if (matches == 1) {
            rLock.unlock();
            return 0;
        } else if (matches == 0) {
            rLock.unlock();
            return 2;
        } else {
            rLock.unlock();
            throw new Exception("There are identical users");
        }
    }

    public UserInf loginUser(String login, String password, HttpSession session) {
        rLock.lock();
        try {
            User user = getUser(login, password);
            session.setAttribute("User", user);
            UserInf userInf = new UserInf(user, session.getId());
            goingSessions.put(session.getId(), userInf);
            rLock.unlock();
            return userInf;
        } catch (Exception e) {
            log.warn(e.getMessage());
        }
        rLock.unlock();
        return null;
    }

    public void endSession(HttpSession session){
        rLock.lock();
        goingSessions.remove(session.getId());
        session.removeAttribute("User");
        log.info("There are " + goingSessions.size() + " sessions");
        rLock.unlock();
    }

    private User getUser(String login, String password) throws Exception {
        rLock.lock();
        Stream<User> logined = users.stream().filter(user -> (user.getLogin().equals(login) && user.getPassword().equals(password)));
        if (logined.count() > 0) {
            User use = users.stream().filter(user -> (user.getLogin().equals(login) && user.getPassword().equals(password))).findFirst().get();
            rLock.unlock();
            return use;
        } else {
            rLock.unlock();
            throw new Exception("Didn't find that");
        }

    }

    public boolean addUser(User user) {
        rLock.lock();
        if(users.contains(user)){
            rLock.unlock();
            return false;
        }else {
            users.add(user);
            usersDao.saveUser(user);
            rLock.unlock();
            return true;
        }

    }

    public void addShotToUser(User user, Shot shot) {
        rLock.lock();
        user.addShot(shot);
        usersDao.updateUser(user);
        rLock.unlock();
    }

    public boolean hasSession(HttpSession session, Cookie tokenCookie){
        rLock.lock();
        boolean b = false;
        if(goingSessions.containsKey(session.getId())){
            UserInf userInf = goingSessions.get(session.getId());
            int token = userInf.getToken();
            String cookieToken = tokenCookie.getValue();
            try {
                b = token == Integer.parseInt(cookieToken);
            }catch (NumberFormatException e){
                e.printStackTrace();
            }
        }
        rLock.unlock();
        return b;
    }

    public void clearUser(User user){
        rLock.lock();
        usersDao.deleteShots(user);
        log.info("User: " + user.getLogin() + " cleared NUM of Shots: " + user.getShots().size());
        rLock.unlock();
    }

//
//    @PreDestroy
//    private void close(){
//        rLock.lock();
//        usersDao.close();
//        rLock.unlock();
//    }
}