package BoidsFinal;
import javax.swing.*;
import java.awt.BorderLayout; // For layout if needed
import java.awt.GridLayout;
import java.awt.FlowLayout;

public class BoidsSimulation {

    private JFrame frame;
    private SimulationCanvas canvas;
    public static int WINDOW_WIDTH = 1500;
    public static int WINDOW_HEIGHT = 960;
    public static double deltaTime = 0.0;

    public BoidsSimulation() {
        // 1. Create the main window (JFrame)
        frame = new JFrame("Boids Simulation");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Close program when window closes
        frame.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        frame.setLocationRelativeTo(null); // Center the window on the screen
        canvas = new SimulationCanvas();

        // --- Sliders panel ---
        JPanel slidersPanel = new JPanel();
        slidersPanel.setLayout(new GridLayout(4, 2)); // Adjust if needed

        JSlider separationSlider = new JSlider(0, 100, (int)(BoidManager.SEPARATION_MULT * (100/ BoidManager.SEPARATION_MULT))); // 0 to 0.01
        JSlider alignmentSlider = new JSlider(0, 100, (int)(BoidManager.ALIGNMENT_MULT * (100
                / BoidManager.ALIGNMENT_MULT)));    // 0 to 0.08
        JSlider cohesionSlider = new JSlider(0, 100, (int)(BoidManager.COHESION_MULT * (100 / BoidManager.COHESION_MULT)));       // 0 to 0.5
        JSlider VeiwSlider = new JSlider(100, 3000, 2000); // 100 to 3000

        slidersPanel.add(new JLabel("Separation"));
        slidersPanel.add(separationSlider);
        slidersPanel.add(new JLabel("Alignment"));
        slidersPanel.add(alignmentSlider);
        slidersPanel.add(new JLabel("Cohesion"));
        slidersPanel.add(cohesionSlider);
        slidersPanel.add(new JLabel("View Radius"));
        slidersPanel.add(VeiwSlider);

        // Listeners to update multipliers
        separationSlider.addChangeListener(e -> {
            BoidManager.SEPARATION_MULT = separationSlider.getValue() * 0.0001; // 0 to 0.01
        });
        alignmentSlider.addChangeListener(e -> {
            BoidManager.ALIGNMENT_MULT = alignmentSlider.getValue() * 0.0008;   // 0 to 0.08
        });
        cohesionSlider.addChangeListener(e -> {
            BoidManager.COHESION_MULT = cohesionSlider.getValue() * 0.005;      // 0 to 0.5
        });
        VeiwSlider.addChangeListener(e -> {
            Boid.VIEW_RADIUS = VeiwSlider.getValue(); // 100 to 3000
        });

        // Create a panel for the toggle button and dock it right
        JButton toggleSlidersButton = new JButton("Hide Sliders");
        JPanel bottomPanel = new JPanel(new BorderLayout());
        bottomPanel.add(slidersPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT, 10, 5));
        buttonPanel.add(toggleSlidersButton);
        bottomPanel.add(buttonPanel, BorderLayout.EAST);

        toggleSlidersButton.addActionListener(e -> {
            boolean currentlyVisible = slidersPanel.isVisible();
            slidersPanel.setVisible(!currentlyVisible);
            toggleSlidersButton.setText(currentlyVisible ? "Show Sliders" : "Hide Sliders");
        });

        frame.getContentPane().add(canvas, BorderLayout.CENTER);
        frame.getContentPane().add(bottomPanel, BorderLayout.SOUTH);

        // 3. Add the canvas to the frame's content pane
        frame.getContentPane().add(canvas, BorderLayout.CENTER);

        // 4. Set the frame to be visible
        frame.setVisible(true);
        startSimulationLoop();
        System.out.println("JFrame and Canvas initialized.");
    }


    private void startSimulationLoop() {
        Timer timer = new Timer(16, e -> { 
            // System.out.println("Frame tick");
            canvas.repaint(); // Tell the canvas to redraw itself
        });
        timer.start();
    }


    public static void main(String[] args) {
        // Swing GUI operations should be done on the Event Dispatch Thread (EDT)
        // SwingUtilities.invokeLater ensures this.
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new BoidsSimulation();
            }
        });
    }
}