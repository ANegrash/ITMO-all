package work.story;

public class Things {
    private final int quantity;
    private final float probability;

    public Things(int quantity, float probability) {
        this.quantity = quantity;
        this.probability = probability;
    }

    public String getThings(){
        return (quantity > 5 ? "много " : quantity + " ") + (probability < 1 ? "маловероятных вещей" : "вещей с вероятностью " + probability);
    }
}
