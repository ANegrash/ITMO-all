package tests;

import org.junit.Test;
import work.BTree;

import static org.junit.jupiter.api.Assertions.*;

public class BTreeTests {

    @Test
    public void checkEmptyTree() {
        BTree t = new BTree();
        assertEquals("The tree is empty", t.levelOrder());
    }

    @Test
    public void checkOneElementInTree() {
        BTree t = new BTree();
        t.add(3);
        assertEquals("1: 3 \n", t.levelOrder());
    }

    @Test
    public void checkBigTree() {
        BTree t = new BTree();
        int[] arr = {3, 1, 0, 2, 6, 5, 7};
        t.addArray(arr);
        String expected =   "1: 3 \n" +
                            "2: 1 6 \n" +
                            "3: 0 2 5 7 \n";
        assertEquals(expected, t.levelOrder());
    }

    @Test
    public void checkDeletingElementInTree() {
        BTree t = new BTree();
        int[] arr = {3, 2, 4};
        t.addArray(arr);
        assertEquals("1: 3 \n2: 2 4 \n", t.levelOrder());
        t.delete(4);
        assertEquals("1: 3 \n2: 2 \n", t.levelOrder());
    }

    @Test
    public void checkSearchingElement() {
        BTree t = new BTree();
        int[] arr = {3, 1, 0, 2, 6, 5, 7};
        t.addArray(arr);
        String expected =   "1: 3 \n" +
                            "2: 1 6 \n" +
                            "3: 0 2 5 7 \n";
        assertEquals(expected, t.levelOrder());
        String expectedSearchResult = "3 -> 6 -> 5";
        assertEquals(expectedSearchResult, t.find(5));
    }

    @Test
    public void checkSearchingNotExistingElement() {
        BTree t = new BTree();
        int[] arr = {3, 1, 0, 2, 6, 5, 7};
        t.addArray(arr);
        String expected =   "1: 3 \n" +
                            "2: 1 6 \n" +
                            "3: 0 2 5 7 \n";
        assertEquals(expected, t.levelOrder());
        String expectedSearchResult = "This element doesn't exist.";
        assertEquals(expectedSearchResult, t.find(8));
    }

    @Test
    public void checkSameElementsInTree() {
        BTree t = new BTree();
        int[] arr = {1, 0, 1};
        t.addArray(arr);
        assertEquals("1: 1 \n2: 0 1 \n", t.levelOrder());
    }

    @Test
    public void checkNullInTree() {
        BTree t = new BTree();
        t.add(null);
        t.add(null);
        t.add(null);
        assertEquals("The tree is empty", t.levelOrder());
        String[] arr = {null, null, null};
        t.addArray(arr);
        assertEquals("The tree is empty", t.levelOrder());
    }

    @Test
    public void checkAddingString() {
        BTree t = new BTree();
        t.add("String element");
        assertEquals("1: String element \n", t.levelOrder());
    }

    @Test
    public void checkStringsInTree() {
        BTree t = new BTree();
        String[] arr = {"d", "b", "a", "c", "g", "f", "h"};
        t.addArray(arr);
        String expected =   "1: d \n" +
                            "2: b g \n" +
                            "3: a c f h \n";
        assertEquals(expected, t.levelOrder());
    }

    @Test
    public void checkSameString() {
        BTree t = new BTree();
        String[] arr = {"ab", "ac", "ad", "ba", "bc", "bd", "ca"};
        t.addArray(arr);
        String expected =   "1: ba \n" +
                            "2: ac bd \n" +
                            "3: ab ad bc ca \n";
        assertEquals(expected, t.levelOrder());
    }

    @Test
    public void checkStringWithInt() {
        BTree t = new BTree();
        t.add("слог");
        t.add("слон");
        t.add(1234);
        String expected =   "1: слог \n" +
                "2: 1234 слон \n";
        assertEquals(expected, t.levelOrder());
    }
}
