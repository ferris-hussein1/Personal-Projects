import java.awt.Point;
import java.util.ArrayList;
import java.util.ArrayDeque;
import java.util.Queue;

public class myGrid {
    public static int[][] grid = new int[67][110];
    public static boolean temp = false;
    public static boolean BFS= false;
    public static boolean DFS= false;
    public static int difficulty = 0;
    public static ArrayList<Point> shortest = new ArrayList<>();
    public static Queue<Point> tagged = new ArrayDeque<>();
}