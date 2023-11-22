package work.story;

public class Creature {
    private final String name;

    public Creature(String name) {
        this.name = name;
    }

    public String doAction(String action) {
        Action act = new Action(action);
        return name + " " + act.getAction();
    }
}
