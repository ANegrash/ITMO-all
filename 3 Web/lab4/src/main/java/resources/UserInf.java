package resources;

import beansLab.entities.User;

import java.util.HashMap;
import java.util.List;

public class UserInf {

    private User user;
    private int token;
    private String sessionId;

    public User getUser() {
        return user;
    }

    public String getSessionId() {
        return sessionId;
    }

    public int getToken(){
        return token;
    }

    public UserInf(User userIn, String sessionIdIn){
        user = userIn;
        sessionId = sessionIdIn;
        token = (sessionIdIn + user.getId()).hashCode();
    }

}
