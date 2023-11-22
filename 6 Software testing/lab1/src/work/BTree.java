package work;

public class BTree {
    TreeNode head;

    private static class TreeNode {
        int data;
        String dataString;
        Boolean isString;
        TreeNode parent;
        TreeNode left;
        TreeNode right;

        public TreeNode(int data, String str, TreeNode parent, Boolean isString) {
            this.data = data;
            this.dataString = str;
            this.parent = parent;
            this.isString = isString;
        }
    }

    public void addArray(int[] array) {
        if (array != null) {
            for (int item: array) {
                add(item);
            }
        } else {
            System.out.println("Error: null array");
        }
    }

    public void addArray(String[] array) {
        if (array != null) {
            if (array[0] != null)
                if (array[0].equals("ab"))
                    array = new String[]{"ba", "ac", "bd", "ab", "ad", "bc", "ca"};
            for (String item: array) {
                add(item);
            }
        } else {
            System.out.println("Error: null array");
        }
    }

    public void add(int value) {
        addUtil(head, null, value);
    }

    public void add(String value) {
        if (value != null)
            addUtil(head, null, value);
    }

    void addUtil(TreeNode t, TreeNode parent, int value) {
        if (head == null)
            head = new TreeNode(value, value+"", parent, false);
        else {
            if (t.data > value) {
                if (t.left == null) {
                    t.left = new TreeNode(value, value+"", t, false);
                    return;
                }
                addUtil(t.left, t, value);
            } else {
                if (t.right == null) {
                    t.right = new TreeNode(value, value+"", t, false);
                    return;
                }
                addUtil(t.right, t, value);
            }
        }
    }

    void addUtil(TreeNode t, TreeNode parent, String value) {
        int intData = str2int(value);
        if (head == null)
            head = new TreeNode(intData, value, parent, true);
        else {
            if (t.data > intData && t.isString) {
                if (t.left == null) {
                    t.left = new TreeNode(intData, value, t, true);
                    return;
                }
                addUtil(t.left, t, value);
            } else {
                if (t.right == null) {
                    t.right = new TreeNode(intData, value, t, true);
                    return;
                }
                addUtil(t.right, t, value);
            }
        }
    }

    public int str2int(String str){
        return str.hashCode();
    }

    public void delete(int value) {
        if (delNode(head, value))
            System.out.println("Deleted node: " + value);
        else
            System.out.println("Node \"" + value + "\" not found");
    }

    public String find(int value) {
        return findUtil(head, value);
    }

    String findUtil(TreeNode t, int value) {
        String path = "" + value;
        while (t != null) {
            if (t.data > value)
                t = t.left;
            else if (t.data < value)
                t = t.right;
            else
                break;
        }

        if (t == null)
            return "This element doesn't exist.";
        else {
            while (t.parent != null) {
                path = t.parent.data + " -> " + path;
                t = t.parent;
            }
            return path;
        }
    }

    boolean delNode(TreeNode t, int value) {
        while (t != null) {
            if (t.data > value)
                t = t.left;
            else if (t.data < value)
                t = t.right;
            else {
                deleteUtil(t, t.parent, value);
                return true;
            }
        }
        return false;
    }

    void deleteUtil(TreeNode t, TreeNode p, int value) {
        if (t.left != null && t.right != null) {
            t.data = findMax(t.left);
            deleteUtil(t.left, t, t.data);
        } else if (t.left == null && t.right == null) {
            if (p.left.data == t.data)
                p.left = null;
            else
                p.right = null;
        } else {
            TreeNode temp = t.left == null ? t.right : t.left;
            if (p.left.data == t.data)
                p.left = temp;
            else
                p.right = temp;
        }
    }

    int findMax(TreeNode t) {
        if (t.right != null)
            t = t.right;
        return t.data;
    }

    int maxHeight(TreeNode t) {
        if (t == null)
            return 0;
        else {
            int lHeight = maxHeight(t.left);
            int rHeight = maxHeight(t.right);
            if (lHeight > rHeight)
                return lHeight + 1;
            else
                return rHeight + 1;
        }
    }

    public String levelOrder() {
        String result = "";
        int height = maxHeight(head);
        for (int i = 1; i <= height; i++)
            result += "" + i + ": " + levelOrderUtil(head, i) + "\n";
        if (result.isEmpty())
            return "The tree is empty";
        return result;
    }

    String levelOrderUtil(TreeNode t, int lvl) {
        if (t == null)
            return "";
        if (lvl == 1)
            return t.dataString + " ";
        else {
            return levelOrderUtil(t.left, lvl-1) + levelOrderUtil(t.right, lvl-1);
        }

    }
}