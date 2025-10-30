package MIT_Maker_Portfolio.FlockingSimulation_Boids;

import javax.swing.JPanel;


import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Scanner;

public class SimulationCanvas extends JPanel {
    public static BoidManager boidManager;
    public static double x = -1;
    public static double y = -1;
    public SimulationCanvas() {
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                x = e.getX();
                y = e.getY();
            }
            @Override
            public void mouseReleased(MouseEvent e) {
                x = -1;
                y = -1;
            }
        });

        addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                x = e.getX();
                y = e.getY();
            }
        });

        // setPreferredSize(new Dimension(BoidsSimulation.WINDOW_HEIGHT, BoidsSimulation.WINDOW_WIDTH));
        setBackground(Color.DARK_GRAY); // Set a default background color
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the number of boids:");
        int boidCount = scanner.nextInt();
        scanner.close();
        boidManager = new BoidManager(boidCount); // Example: Create a BoidManager with 100 boids
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); // IMPORTANT: Clears the panel before drawing
        Graphics2D g2d = (Graphics2D) g; // Cast to Graphics2D for more features
        
        boidManager.update(g2d, getWidth(), getHeight()); // Update and draw the boids
    }
    
    @Override
    public Dimension getSize() {
        return super.getSize();
    }

}