package beansLab.entities;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

@Entity
@Table(name = "shots")

public class Shot implements Serializable {

    @Id
    @GeneratedValue(strategy= GenerationType.SEQUENCE, generator = "id_Sequence")
    @SequenceGenerator(name = "id_Sequence", sequenceName = "SEQ_SHOT", allocationSize = 1)
    @Column(name = "shot_id")
    private long id;

    @Column(name = "x")
    private double x;
    @Column(name = "y")
    private double y;
    @Column(name = "r")
    private double r;
    @Column(name = "rg")
    private boolean RG;
    @Column(name = "start_time")
    private String start;


    @Column(name = "script_time")
    private long scriptTime;

    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "user_id")
    private User user;

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public long getId() {
        return id;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setR(double r) {
        this.r = r;
    }

    public void setRG(boolean RG) {
        this.RG = RG;
    }

    public void setStart(LocalDateTime start) {
        String str = start.format(DateTimeFormatter.ofPattern("dd-MM-yyyy;HH:mm:ss"));
        this.start = str;
    }

    //.format(DateTimeFormatter.ofPattern("dd-MM-yyyy;hh:mm:ss"))

    public void setScriptTime(long scriptTime) {
        this.scriptTime = scriptTime;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getR() {
        return r;
    }

    public boolean isRG() {
        return RG;
    }

    public LocalDateTime getStart() {

        return LocalDateTime.parse(start,DateTimeFormatter.ofPattern("dd-MM-yyyy;HH:mm:ss"));
    }

    public long getScriptTime() {
        return scriptTime;
    }

    public Shot(){}

    @Override
    public String toString() {
        return "Shot:" + id + " " +
                "X: " + x + " " +
        "Y: " + y + " " +
        "R: " + r + " " +
        "GR: " + RG + " " +
        "Start time: " + start + " " +
        "Script time: " + scriptTime;
    }
}
