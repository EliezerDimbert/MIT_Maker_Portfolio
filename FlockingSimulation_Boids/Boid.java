package BoidsFinal;

import java.awt.Color;
import java.awt.Graphics2D;

public class Boid {
    public static double VIEW_RADIUS = 2000;
    public static final double MAX_SPEED = 15;

    Vector2D position;
    Vector2D velocity;

    public Boid() {
        position = new Vector2D(
                Math.random() * BoidsSimulation.WINDOW_WIDTH,
                Math.random() * BoidsSimulation.WINDOW_HEIGHT);
        double angle = Math.random() * 2 * Math.PI;
        velocity = new Vector2D(
                Math.cos(angle) * MAX_SPEED,
                Math.sin(angle) * MAX_SPEED);
    }
    public void apply(Vector2D force) {
        // System.out.print("Force: " + force);
        velocity.x += force.x + Math.random() * 0.1;
        velocity.y += force.y + Math.random() * 0.1;
        if (velocity.getLength() > MAX_SPEED) {
            velocity.normalize();
            velocity.x *= MAX_SPEED;
            velocity.y *= MAX_SPEED;
        }
        // System.out.println("Velocity: " + velocity);
    }
    public void move() {
        //  System.out.println("Boid Moved!");
        // System.out.print("OldPos: " + position);
        position.x += velocity.x;
        position.y += velocity.y;
        // System.out.println(" NewPos: " + position);
        // System.out.println(" Velocity: " +  velocity);
        // Bounce off left or right walls
        if (position.x > BoidsSimulation.WINDOW_WIDTH) {
            position.x = 0;
        } else if (position.x < 0) {
            position.x = BoidsSimulation.WINDOW_WIDTH;
        }
        if (position.y > BoidsSimulation.WINDOW_HEIGHT) {
            position.y = 0;
        } else if (position.y < 0) {
            position.y = BoidsSimulation.WINDOW_HEIGHT;
        }
        
        }
    public void draw(Graphics2D g2d) {
        // Calculate the angle of the velocity vector
        double angle = Math.atan2(velocity.y, velocity.x);

        // Define the triangle's points relative to the boid's position
        int[] xPoints = {
                (int) (position.x + 15 * Math.cos(angle)), // Tip of the triangle
                (int) (position.x - 10 * Math.cos(angle) + 5 * Math.sin(angle)), // Left base
                (int) (position.x - 10 * Math.cos(angle) - 5 * Math.sin(angle)) // Right base
        };
        int[] yPoints = {
                (int) (position.y + 15 * Math.sin(angle)), // Tip of the triangle
                (int) (position.y - 10 * Math.sin(angle) - 5 * Math.cos(angle)), // Left base
                (int) (position.y - 10 * Math.sin(angle) + 5 * Math.cos(angle)) // Right base
        };

        // Set the color and draw the triangle
        g2d.setColor(Color.WHITE);
        g2d.fillPolygon(xPoints, yPoints, 3);
    }
}
