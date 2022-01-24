import java.awt.*;
import javax.swing.*;
import javax.swing.JFrame;
import javax.swing.event.MouseInputListener;
import java.awt.Point;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Queue;
import java.util.Random;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.util.PriorityQueue;

class Grid extends JComponent {

    public void paint(Graphics g) {
        int z = 0;
        int x = 250;
        int y = 30;
       
        for (int i = 0; i < 67; i++)
        {
            for (int j = 0; j < 110; j++) 
            {
                g.drawRect(x+z, y, 15, 15);
                if (myGrid.grid[i][j] == 1) { 
                    g.setColor(Color.black);
                    g.fillRect(x+z, y, 15, 15);
                } 
                z+=15;
            }
            z = 0;
            y += 15;
        } 

       

       // System.out.println(Arrays.toString(myGrid.shortest.toArray()));

        z = 0;
        x = 250;
        y = 30;
       
       // System.out.println(Arrays.toString(myGrid.tagged.toArray()));
        if (myGrid.temp == true) {
            for (int i = 0; i < 67; i++)
            {
                for (int j = 0; j < 110; j++) 
                {
                    g.drawRect(x+z, y, 15, 15);
                    if (myGrid.shortest.contains(new Point(i,j)) ) { 
                        g.setColor(Color.BLUE);
                        g.fillRect(x+z, y, 15, 15);
                        g.setColor(Color.BLACK);
                    } 
                    z+=15;
                }
               // g.setColor(Color.BLACK);
                z = 0;
                y += 15;
            } 
        }
        
    }
}

public class maze {
    public static JButton bfs = new JButton("BFS"); 
    public static JButton dfs = new JButton("DFS"); 
    //public static JButton startover = new JButton("Start Over");
    public static boolean terminate = false; // terminates actionlistener, buttons can only be pressed once

    public static boolean[][] mygrid = new boolean[67][110];

    static class Action implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            
            if (e.getSource() == bfs && terminate == false) {
                //System.out.println("BFS pressed");
                myGrid.BFS = true;
                BFS();
                display();
                terminate = true;
            } else if (e.getSource() == dfs && terminate == false) {
                //System.out.println("DFS pressed");
                myGrid.DFS = true;
                DFS();
                display();
                terminate = true;
            }
        }
    }

    public static void display() 
    {
        JFrame frame = new JFrame("Maze");

        bfs.setBounds(50, 100, 150, 50);
        frame.add(bfs);
        bfs.addActionListener(new Action());
       
        dfs.setBounds(50, 150, 150, 50);
        frame.add(dfs);
        dfs.addActionListener(new Action());

        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
        frame.getContentPane().add(new Grid());
        frame.setVisible(true);

        return;
    }

    public static void populate() {
        for (int i = 0; i < 67; i++){
            for (int j = 0; j < 110; j++) {
                Random num = new Random();
                int randnum = num.nextInt(100);
                if (randnum % 5 == 0 ) { // change difficulty here for now
                    myGrid.grid[i][j] = 1; // if 1 then blockage
                } 
            }
        }
        myGrid.grid[0][0] = 0; // top left and bottom right should be white 
        myGrid.grid[66][109] = 0;


        // prints grid
        for (int i = 0; i < 67; i++){
            for (int j = 0; j < 110; j++) {
           //     System.out.print(myGrid.grid[i][j] + " ");
            }
           // System.out.println();
        }
    }

    public static void BFS() {
        Queue<Point> q = new ArrayDeque<>();
        Queue<Point> tagged = new ArrayDeque<>();

        Point prev[][] = new Point[67][110];

        q.add(new Point(0,0));
        tagged.add(new Point(0,0));

        boolean hasPath = false;

        while (!q.isEmpty()) 
        {
            Point cell = q.remove();
           // System.out.println(cell);

            if (cell.x == 66 && cell.y == 109 ) { hasPath = true; break; }

            if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                q.add(new Point(cell.x+1, cell.y) );
                myGrid.tagged.add(new Point(cell.x+1, cell.y) );

                prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
            }

            if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                q.add(new Point(cell.x-1, cell.y) );
                myGrid.tagged.add(new Point(cell.x-1, cell.y) );

                prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
            }

            if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                q.add(new Point(cell.x, cell.y+1) );
                myGrid.tagged.add(new Point(cell.x, cell.y+1) );

                prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
            }

            if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                q.add(new Point(cell.x, cell.y-1) );
                myGrid.tagged.add(new Point(cell.x, cell.y-1) );

                prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
            }
            
        }

        
        if ( hasPath == true) {
            System.out.println("Path Found");
            Point cell = prev[66][109];
            while (cell!= prev[0][0]) {
                myGrid.shortest.add(new Point(cell.x,cell.y));
                cell = prev[cell.x][cell.y];
            }
            myGrid.shortest.add(new Point(0,0));
            Collections.reverse(myGrid.shortest);
            myGrid.shortest.add(new Point(66,109));
            myGrid.temp = true;
            //prints path
           // System.out.println(Arrays.toString(myGrid.shortest.toArray()));

            myGrid.temp = true;
           // myGrid.checkTag = true;
        } else if (hasPath == false) {
            System.out.println("NO PATH FOUND");
        }

    }
    
    public static void DFS() {
        // Multiple if's because increasing randomnesss

        Stack<Point> q = new Stack<Point>();
        Queue<Point> tagged = new ArrayDeque<>();

        Point prev[][] = new Point[67][110];

        q.add(new Point(0,0));
        tagged.add(new Point(0,0));

        boolean hasPath = false;

        while (!q.isEmpty()) 
        {
            Point cell = q.pop();
            Random num = new Random();
            int randnum = num.nextInt(7);
           // System.out.println(cell);

            if (cell.x == 66 && cell.y == 109 ) { hasPath = true; break; }

            
            if (randnum == 0) {
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
            }

            if (randnum == 1) {
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                } 
            }

            if (randnum == 2) {
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
            }

            if (randnum == 3) {
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
            }

            if (randnum == 4) {
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                
            }

            if (randnum == 5) {
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
            }

            if (randnum == 6) {
                
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
                
            }

            if (randnum == 7) {          
                if (cell.y + 1 < 110 && myGrid.grid[cell.x][cell.y+1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y+1)) )  {
                    q.push(new Point(cell.x, cell.y+1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y+1) );
                    prev[cell.x][cell.y+1] = new Point(cell.x,cell.y);
                }
                if (cell.x - 1 >= 0 && myGrid.grid[cell.x-1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x-1, cell.y)))  {
                    q.push(new Point(cell.x-1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x-1, cell.y) );
                    prev[cell.x-1][cell.y] = new Point(cell.x,cell.y);
                }
                 if (cell.x + 1 < 67 && myGrid.grid[cell.x+1][cell.y] == 0 && !myGrid.tagged.contains(new Point(cell.x+1, cell.y)) )  {
                    q.push(new Point(cell.x+1, cell.y) );
                    myGrid.tagged.add(new Point(cell.x+1, cell.y) );
                    prev[cell.x+1][cell.y] = new Point(cell.x,cell.y);
                }
                if (cell.y - 1 >= 0 && myGrid.grid[cell.x][cell.y-1] == 0 && !myGrid.tagged.contains(new Point(cell.x, cell.y-1)))  {
                    q.push(new Point(cell.x, cell.y-1) );
                    myGrid.tagged.add(new Point(cell.x, cell.y-1) );
                    prev[cell.x][cell.y-1] = new Point(cell.x,cell.y);
                }
                
            }
            
        }

        
        if ( hasPath == true) {
            System.out.println("Path Found");
            Point cell = prev[66][109];
            while (cell!= prev[0][0]) {
                myGrid.shortest.add(new Point(cell.x,cell.y));
                cell = prev[cell.x][cell.y];
            }
            myGrid.shortest.add(new Point(0,0));
            Collections.reverse(myGrid.shortest);
            myGrid.shortest.add(new Point(66,109));
            myGrid.temp = true;
            //prints path
           // System.out.println(Arrays.toString(myGrid.shortest.toArray()));

            myGrid.temp = true;
           // myGrid.checkTag = true;
        } else if (hasPath == false) {
            System.out.println("NO PATH FOUND");
        }
    }
    public static void main (String[] args) {
        populate();
        display();  
        return;
    }


}