package work.story;

public class Riches {
    private int quantity;

    public Riches(int quantity) {
        this.quantity = quantity;
    }

    public String doAction(String action) {
        Action act = new Action(action);
        return countRiches() + "богатства " + act.getAction();
    }

     public void setQuantity(int q) {
        this.quantity = q;
     }

    private String countRiches(){
        if (quantity < 10)
            return "маленькие ";
        else if (quantity < 50)
            return "средние ";
        else if (quantity < 150)
            return "большие ";
        else
            return "огромные ";
    }
}
