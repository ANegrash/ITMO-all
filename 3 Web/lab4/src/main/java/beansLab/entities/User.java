package beansLab.entities;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table (name = "users")

public class User {

    @Id
    @GeneratedValue(strategy=GenerationType.SEQUENCE, generator = "id_Sequence")
    @SequenceGenerator(name = "id_Sequence", sequenceName = "SEQ_USER", allocationSize = 1)
    @Column(name = "user_id")
    private long id;
    @Column(name = "login")
    private String login;
    @Column(name = "password")
    private String password;

    @OneToMany(mappedBy = "user", cascade = CascadeType.ALL, orphanRemoval = true, fetch=FetchType.EAGER)
    private List<Shot> shots;

    public User() {
    }

    public User(String login, String password) {
        this.login = login;
        this.password = password;
        shots = new ArrayList<Shot>();
    }

    public void addShot(Shot shot) {
        shot.setUser(this);
        shots.add(shot);
    }

    public void removeShot(Shot shot) {
        shots.remove(shot);
    }

    public long getId() {
        return id;
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<Shot> getShots() {
        return shots;
    }

    public void setShots(List<Shot> shots) {
        this.shots = shots;
    }

    @Override
    public String toString() {
        return "models.User{" +
                "id=" + id +
                ", name='" + login + '\'' +
                '}';
    }
}