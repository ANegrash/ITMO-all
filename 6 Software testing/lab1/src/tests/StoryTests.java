package tests;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeAll;
import work.story.*;

public class StoryTests {
    static Creature creature;
    static Action assumption;
    static Civilization civilization;
    static Things notManyThingsOften, notManyThingsNever, manyThingsNever, manyThingsOften;
    static Riches riches;

    @BeforeAll
    public static void createAll() {
        creature = new Creature("Тестовое создание 1");
        assumption = new Action("Тестовое предположение");
        civilization = new Civilization("Тестовая цивилизация", "тестовое позавчера");
        notManyThingsOften = new Things(2, 15);
        notManyThingsNever = new Things(3, 0);
        manyThingsNever = new Things(6, 0.8F);
        manyThingsOften = new Things(22, 25);
        riches = new Riches(3);
    }

    @Test
    public void actionsCheck() {
        Assertions.assertEquals(creature.doAction("действие 1"), "Тестовое создание 1 действие 1");
        Assertions.assertEquals(civilization.doAction("действие для цивилизации"), "Тестовая цивилизация действие для цивилизации тестовое позавчера");
        Assertions.assertEquals(assumption.getAction(), "Тестовое предположение");
    }

    @Test
    public void thingsParametersCheck() {
        Assertions.assertEquals(notManyThingsOften.getThings(), "2 вещей с вероятностью 15.0");
        Assertions.assertEquals(notManyThingsNever.getThings(), "3 маловероятных вещей");
        Assertions.assertEquals(manyThingsNever.getThings(), "много маловероятных вещей");
        Assertions.assertEquals(manyThingsOften.getThings(), "много вещей с вероятностью 25.0");
    }

    @Test
    public void richesQuantityCheck() {
        Assertions.assertEquals(riches.doAction("загробастать за тестирование"), "маленькие богатства загробастать за тестирование");
        riches.setQuantity(20);
        Assertions.assertEquals(riches.doAction("забрать за тестирование"), "средние богатства забрать за тестирование");
        riches.setQuantity(99);
        Assertions.assertEquals(riches.doAction("получить за тестирование"), "большие богатства получить за тестирование");
        riches.setQuantity(111);
        Assertions.assertEquals(riches.doAction("всё ещё получить за тестирование"), "большие богатства всё ещё получить за тестирование");
        riches.setQuantity(222);
        Assertions.assertEquals(riches.doAction("украсть за тестирование"), "огромные богатства украсть за тестирование");
    }

    @Test
    public void civilizationTimeCheck() {
        Assertions.assertEquals(civilization.doAction("захватить планету"), "Тестовая цивилизация захватить планету тестовое позавчера");
        civilization.setTime("завтра");
        Assertions.assertEquals(civilization.doAction("отменить пары на Земле для всех студентов"), "Тестовая цивилизация отменить пары на Земле для всех студентов завтра");
    }
}