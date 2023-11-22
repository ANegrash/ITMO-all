package work.story;

public class Story {
    public void doStory(){
        Creature ford = new Creature("Форд");
        Action assumption1 = new Action("Даже если предположить:");
        Civilization civilization = new Civilization("цивилизация", "когда-то");
        Action assumption2 = new Action("Даже если предположить ещё:");
        Things things = new Things(100, 0.01F);
        Riches riches = new Riches(500);
        Creature form = new Creature("форма");

        print(ford.doAction("подумал: \"Ерунда\""));
        print(assumption1.getAction());
        print(civilization.doAction("существовала"));
        civilization.setTime("теперь");
        print(civilization.doAction("превратилась в пыль"));
        print(assumption2.getAction());
        print(things.getThings());
        print(riches.doAction("не могли бы сохраниться"));
        print(form.doAction("не представляет интерес"));
        print(ford.doAction("пожал плечами"));
    }

    void print(String str){
        System.out.println(str);
    }
}
