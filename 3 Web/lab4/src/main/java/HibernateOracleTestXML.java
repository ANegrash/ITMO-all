import beansLab.entities.Shot;
import beansLab.entities.User;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.Query;
import org.hibernate.type.StandardBasicTypes;
import resources.UserInf;
import resources.UserManager;
import services.ShotGenerator;
import utils.HibernateSessionFactoryUtil;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionContext;
import java.math.BigInteger;
import java.util.Enumeration;
import java.util.Random;

public class HibernateOracleTestXML {

    public static void main(String[] args) {

        putShot();

    }

    static void getVal(){
        Session session = HibernateSessionFactoryUtil.getSessionFactory().openSession();
        Transaction tx1 = session.beginTransaction();
        Query query =
                session.createSQLQuery("select SEQ_SHOT.nextval as num from dual")
                        .addScalar("num", StandardBasicTypes.BIG_INTEGER);
        long result = ((BigInteger) query.uniqueResult()).longValue();

        System.out.println(result);
        tx1.commit();
        session.close();
    }

    static void  putShot(){
        UserManager userManager = new UserManager();
        userManager.init();

        HttpSession httpSession = new HttpSession() {
            @Override
            public long getCreationTime() {
                return 0;

            }

            @Override
            public String getId() {
                return "null";
            }

            @Override
            public long getLastAccessedTime() {
                return 0;
            }

            @Override
            public ServletContext getServletContext() {
                return null;
            }

            @Override
            public void setMaxInactiveInterval(int interval) {

            }

            @Override
            public int getMaxInactiveInterval() {
                return 0;
            }

            @Override
            public HttpSessionContext getSessionContext() {
                return null;
            }

            @Override
            public Object getAttribute(String name) {
                return null;
            }

            @Override
            public Object getValue(String name) {
                return null;
            }

            @Override
            public Enumeration<String> getAttributeNames() {
                return null;
            }

            @Override
            public String[] getValueNames() {
                return new String[0];
            }

            @Override
            public void setAttribute(String name, Object value) {

            }

            @Override
            public void putValue(String name, Object value) {

            }

            @Override
            public void removeAttribute(String name) {

            }

            @Override
            public void removeValue(String name) {

            }

            @Override
            public void invalidate() {

            }

            @Override
            public boolean isNew() {
                return false;
            }
        };

        UserInf userInf = userManager.loginUser("Somebody@somewhere", "a6b46dd0d1ae5e86cbc8f37e75ceeb6760230c1ca4ffbcb0c97b96dd7d9c464b", httpSession);

        User workUser = userInf.getUser();

        userManager.addUser(workUser);

        Random random = new Random();

        try{
            Shot shot = ShotGenerator.generateShot((random.nextDouble() % 5), (random.nextDouble() % 5), 2);
            userManager.addShotToUser(workUser, shot);
        }catch (Exception e){
            e.printStackTrace();
        }

        userManager.endSession(httpSession);
    }
}