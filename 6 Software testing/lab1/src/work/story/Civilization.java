package work.story;

public class Civilization {
    private String name;
    private String time;

    public Civilization(String name, String time) {
        this.name = name;
        this.time = time;
    }

    public void setTime(String newTime) {
        this.time = newTime;
    }

    public String doAction(String action) {
        Action act = new Action(action);
        return name + " " + act.getAction() + " " + time;
    }
}
