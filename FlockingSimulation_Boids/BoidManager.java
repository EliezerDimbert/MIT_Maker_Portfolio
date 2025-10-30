package MIT_Maker_Portfolio.FlockingSimulation_Boids;

import java.awt.Graphics2D;
import java.util.*;
public class BoidManager {
    Boid[] boids;
    int boidCount;
    private static final double WALL_THRESHOLD = 150;
    private static final double WALL_FORCE = 1;
    public static double SEPARATION_MULT = 0.05;
    public static double ALIGNMENT_MULT = 0.4;
    public static double COHESION_MULT = 0.8;
    public BoidManager(int boidCount) {
        this.boidCount = boidCount;
        boids = new Boid[boidCount];
        for (int i = 0; i < boidCount; i++) {
            boids[i] = new Boid();
        }
    }
    public void update(Graphics2D g2d, int width, int height) {
        for (int i = 0; i < boidCount; i++) {
            ArrayList<Boid> surroundingBoids = getSurroundingBoids(boids[i]);
            // Vector2D wallForce = wallForce(boids[i]);
            // System.out.println("WallForce: " + wallForce);
            // boids[i].apply(wallForce);
            if (SimulationCanvas.x != -1 && SimulationCanvas.y != -1) {
                double dx = SimulationCanvas.x - boids[i].position.x;
                double dy = SimulationCanvas.y - boids[i].position.y;
                double distSq = dx * dx + dy * dy;
                if (distSq < 1)
                    distSq = 1; // Prevent division by zero
                double strength = 1000.0 / distSq; // Stronger when very close
                Vector2D force = new Vector2D(dx * strength, dy * strength);
                boids[i].apply(force);
            }
            Vector2D seperation = separation(boids[i], surroundingBoids).getMultiplied(SEPARATION_MULT);
            Vector2D alignment = alignment(boids[i], surroundingBoids).getMultiplied(ALIGNMENT_MULT);
            Vector2D cohesion = cohesion(boids[i], surroundingBoids).getMultiplied(COHESION_MULT);
            Vector2D wallForce = wallForce(boids[i], width, height).getMultiplied(WALL_FORCE);   
            // System.out.println("Separation: " + seperation);
            // System.out.println("Alignment: " + alignment);
            // System.out.println("Cohesion: " + cohesion);
            // System.out.println("WallForce: " + wallForce);
            Vector2D finalVector = Vector2D.add(seperation, alignment);
            finalVector = Vector2D.add(finalVector, cohesion);
            finalVector = Vector2D.add(finalVector, wallForce);
            finalVector.normalize();
            boids[i].apply(finalVector);
        }
        for (int i = 0; i < boidCount; i++) {
            boids[i].move();
            boids[i].draw(g2d);
        }
    }
    public ArrayList<Boid> getSurroundingBoids(Boid b) {
        ArrayList<Boid> surroundingBoids = new ArrayList<>();
        for (int i = 0; i < boidCount; i++) {
            if (boids[i] != b && boids[i].position.distanceSq(b.position) < Boid.VIEW_RADIUS) {
                surroundingBoids.add(boids[i]);
            }
        }
        return surroundingBoids;
    }

    public Vector2D separation(Boid b, ArrayList<Boid> neighbors) {
        Vector2D force = new Vector2D();
        for (Boid other : neighbors) {
            double dx = b.position.x - other.position.x;
            double dy = b.position.y - other.position.y;
            double distSq = dx * dx + dy * dy;
            if (distSq < 1)
                distSq = 1; // Prevent division by zero
            double strength = 1000.0 / distSq; // Stronger when very close
            force.x += dx * strength;
            force.y += dy * strength;
        }
        return force;
    }
    public Vector2D alignment(Boid b, ArrayList<Boid> surroundingBoids) {
        Vector2D result = new Vector2D();
        for (Boid other : surroundingBoids) {
            result.add(other.velocity);
        }
        if (surroundingBoids.isEmpty())
            return new Vector2D();
        result.x /= surroundingBoids.size();
        result.y /= surroundingBoids.size();
        result.normalize();
        return result;
    }
    public Vector2D cohesion(Boid b, ArrayList<Boid> surroundingBoids) {
        Vector2D result = new Vector2D();
        for (Boid other : surroundingBoids) {
            result.add(other.position);
        }
        if (surroundingBoids.isEmpty())
            return new Vector2D();
        result.x /= surroundingBoids.size();
        result.y /= surroundingBoids.size();
        Vector2D direction = new Vector2D(result.x - b.position.x, result.y - b.position.y);
        direction.normalize();
        return direction;
    }
    
    public Vector2D wallForce(Boid b, int w, int h) {
        Vector2D force = new Vector2D();
        double k = .3; // Tweak this for strength
        int e = 3; // Tweak this for strength

        // Left wall
        if (b.position.x < WALL_THRESHOLD) {
            double d = w - b.position.x;
            force.x += k * Math.pow(d, e);
        }
        // Right wall
        if (b.position.x > w - WALL_THRESHOLD) {
            double d = b.position.x - (w - WALL_THRESHOLD);
            force.x -= k * Math.pow(d, e);
        }
        // Top wall
        if (b.position.y < WALL_THRESHOLD) {
            double d = WALL_THRESHOLD - b.position.y;
            force.y += k * Math.pow(d, e);
        }
        // Bottom wall
        if (b.position.y > h - WALL_THRESHOLD) {
            double d = b.position.y - (h - WALL_THRESHOLD);
            force.y -= k * Math.pow(d, e);
        }
        return force;
    }
    /*
    public void wallForce(Boid b) {
        if (b.position.x > WALL_THRESHOLD || b.position.x < BoidsSimulation.WINDOW_WIDTH - WALL_THRESHOLD) {
            b.velocity.x = -b.velocity.x;
        }
        if (b.position.y > WALL_THRESHOLD || b.position.y < BoidsSimulation.WINDOW_HEIGHT - WALL_THRESHOLD) {
            b.velocity.y = -b.velocity.y;
        }
    }
    */
}
