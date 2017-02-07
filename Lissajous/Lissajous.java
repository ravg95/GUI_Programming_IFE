/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lissajous;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.DecimalFormat;
import java.util.Objects;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.Document;
import javax.swing.text.JTextComponent;

/**
 *
 * @author rafal
 */
public class Lissajous extends JPanel {

    double[] values; // A1, w1, A2, w2, fi;
    boolean rad, animation;
    private final static String BAD_FORMAT_ERROR_MESSAGE = "<html>Incorrect number<br/>format!</html>";
    private static DecimalFormat df = new DecimalFormat("#.00");
    private Timer timer;

    public Lissajous() {
        JPanel optionsPanel = new JPanel();
        JFrame frame = new JFrame();
        frame.setTitle("Lissajous curve generator");
        frame.setSize(500, 400);
        setSize(400, 400);
        optionsPanel.setSize(100, 400);
        initValues();
        createOptionsView(optionsPanel);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(3);

        frame.add(optionsPanel, BorderLayout.EAST);
        frame.add(this);
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new Lissajous();
    }
    double[] prevX, prevY;
    double prevScale;

    @Override
    public void paint(Graphics g) {
        g.setPaintMode();
        g.setColor(Color.BLACK);
        if ((prevX == null && prevY == null) || !animation) {
            g.fillRect(0, 0, 400, 400);
        } else {
            for (int t = 0; t < prevX.length; t++) {
                g.fillOval(Center_X + new Double(prevScale * prevX[t]).intValue(), Center_Y + new Double(prevScale * prevY[t]).intValue(), LINE_WIDTH, LINE_WIDTH);
            }
        }

        double scale = (values[0] > values[1]) ? SCALE_CONST / values[0] : SCALE_CONST / values[1];
        double[] x = new double[200000], y = new double[200000];
        for (double t = -1000; t <= 1000; t += 0.01) {
            x[(int) ((t + 1000.0) * 100)] = x(t);
            y[(int) ((t + 1000.0) * 100)] = y(t);
        }
        for (int t = 0; t < x.length; t++) {
            g.setColor(getSineWaveColor(t));
            g.fillOval(Center_X + new Double(scale * x[t]).intValue(), Center_Y + new Double(scale * y[t]).intValue(), LINE_WIDTH, LINE_WIDTH);
        }
        prevX = x;
        prevY = y;
        prevScale = scale;
    }
    public static final int Center_X = 200;
    public static final int Center_Y = 180;
    public static final int LINE_WIDTH = 5;
    public static final int SCALE_CONST = 150;

    Color getSineWaveColor(int t) {
        int red, green, blue;
        double freq = 0.0003;
        red =  (int) (Math.sin(freq * t + 0) * 127 + 127);
        green =  (int) (Math.sin(freq * t + 2*Math.PI/3) * 127 + 127);
        blue =  (int) (Math.sin(freq * t + 4*Math.PI/3) * 127 + 127);

        return new Color((int)red, (int)green, (int)blue);
    }

    private void createOptionsView(JPanel optionsPanel) {
        final JTextField[] textField = new JTextField[]{
            new JTextField(Double.toString(values[0])),
            new JTextField(Double.toString(values[1])),
            new JTextField(Double.toString(values[2])),
            new JTextField(Double.toString(values[3])),
            new JTextField(df.format(values[4]))};

        final JButton animate = new JButton("Anim");
        timer = new Timer(100, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                values[4] += 16;
                if (values[4] - 360 > 0) {
                    values[4] -= 360;
                }
                if (!rad) {
                    textField[4].setText(Double.toString(values[4]));
                } else {
                    textField[4].setText(df.format(2 * Math.PI * values[4] / 360.0));
                }
                repaint();
            }
        });

        final JLabel aLabel = new JLabel("A1: "),
                bLabel = new JLabel("A2: "),
                w1Label = new JLabel("W1: "),
                w2Label = new JLabel("W2: "),
                fiLabel = new JLabel(String.valueOf((char) 966) + ": "),
                warningLabel = new JLabel();

        warningLabel.setForeground(Color.red);
        warningLabel.setFont(new Font("Helvetica", Font.PLAIN, 10));
        final JRadioButton radians = new JRadioButton("Radians");
        final JRadioButton degrees = new JRadioButton("Degrees");
        degrees.setSelected(true);
        for (int i = 0; i < 5; i++) {
            addChangeListener(textField[i], new ChangeAdapter(i) {
                @Override
                public void stateChanged(ChangeEvent e) {
                    double ret = values[index];
                    try {
                        ret = Double.parseDouble(textField[index].getText());
                        warningLabel.setText("");
                    } catch (NumberFormatException ex) {
                        warningLabel.setText(BAD_FORMAT_ERROR_MESSAGE);
                        animation=false;
                        timer.stop();
                    }
                    if (index == 4 && rad) {
                        values[index] = 360.0 * ret / (2 * Math.PI);
                    } else {
                        values[index] = ret;
                    }
                    repaint();
                }
            });
        }
        animate.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                animation = !animation;
                if (animation) {
                    timer.start();
                } else {
                    timer.stop();
                }

            }
        });
        degrees.addMouseListener(new MouseAdapter() {

            @Override
            public void mouseClicked(MouseEvent e) {
                radians.setSelected(false);
                rad = false;
                textField[4].setText(df.format(values[4]));
                repaint();
                degrees.setSelected(true);
            }
        });
        radians.addMouseListener(new MouseAdapter() {

            @Override
            public void mouseClicked(MouseEvent e) {
                degrees.setSelected(false);
                rad = true;

                textField[4].setText(df.format(2 * Math.PI * values[4] / 360.0));
                repaint();
                radians.setSelected(true);
            }
        });
        GroupLayout layout = new GroupLayout(optionsPanel);
        optionsPanel.setLayout(layout);
        layout.setAutoCreateGaps(true);
        layout.setAutoCreateContainerGaps(true);

        layout.setHorizontalGroup(layout.createParallelGroup()
                .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup()
                                .addComponent(aLabel)
                                .addComponent(bLabel)
                                .addComponent(w1Label)
                                .addComponent(w2Label)
                                .addComponent(fiLabel))
                        .addGroup(layout.createParallelGroup()
                                .addComponent(textField[0])
                                .addComponent(textField[1])
                                .addComponent(textField[2])
                                .addComponent(textField[3])
                                .addComponent(textField[4])))
                .addComponent(radians)
                .addComponent(degrees)
                .addComponent(animate)
                .addComponent(warningLabel)
        );

        layout.setVerticalGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup()
                        .addComponent(aLabel)
                        .addComponent(textField[0]))
                .addGroup(layout.createParallelGroup()
                        .addComponent(bLabel)
                        .addComponent(textField[1]))
                .addGroup(layout.createParallelGroup()
                        .addComponent(w1Label)
                        .addComponent(textField[2]))
                .addGroup(layout.createParallelGroup()
                        .addComponent(w2Label)
                        .addComponent(textField[3]))
                .addGroup(layout.createParallelGroup()
                        .addComponent(fiLabel)
                        .addComponent(textField[4]))
                .addComponent(radians)
                .addComponent(degrees)
                .addComponent(animate)
                .addComponent(warningLabel)
        );
        layout.linkSize(SwingConstants.VERTICAL, aLabel, textField[0]);
        layout.linkSize(SwingConstants.VERTICAL, bLabel, textField[1]);
        layout.linkSize(SwingConstants.VERTICAL, w1Label, textField[2]);
        layout.linkSize(SwingConstants.VERTICAL, w2Label, textField[3]);
        layout.linkSize(SwingConstants.VERTICAL, fiLabel, textField[4]);
        layout.linkSize(SwingConstants.HORIZONTAL, warningLabel, radians);
    }

    private double x(double t) {
        return values[0] * Math.cos(2 * Math.PI * (t * values[2] - values[4]) / 360.0);
    }

    private double y(double t) {
        return values[1] * Math.cos(2 * Math.PI * (t * values[3] - values[4]) / 360.0);
    }

    private void initValues() {
        values = new double[]{1, 1, 2, 3, 90};
        rad = false;
        animation = false;
    }

    public static void addChangeListener(final JTextComponent text, final ChangeListener changeListener) {
        Objects.requireNonNull(text);
        Objects.requireNonNull(changeListener);
        final DocumentListener dl;
        dl = new DocumentListener() {
            private int lastChange = 0, lastNotifiedChange = 0;

            @Override
            public void insertUpdate(DocumentEvent e) {
                changedUpdate(e);
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                changedUpdate(e);
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                lastChange++;
                SwingUtilities.invokeLater(new Runnable() {

                    @Override
                    public void run() {

                        if (lastNotifiedChange != lastChange) {
                            lastNotifiedChange = lastChange;
                            changeListener.stateChanged(new ChangeEvent(text));
                        }
                    }

                });
            }
        };
        text.addPropertyChangeListener("document", new PropertyChangeListener() {

            @Override
            public void propertyChange(PropertyChangeEvent e) {
                Document d1 = (Document) e.getOldValue();
                Document d2 = (Document) e.getNewValue();
                if (d1 != null) {
                    d1.removeDocumentListener(dl);
                }
                if (d2 != null) {
                    d2.addDocumentListener(dl);
                }
                dl.changedUpdate(null);
            }

        });
        Document d = text.getDocument();
        if (d != null) {
            d.addDocumentListener(dl);
        }
    }

    private class ChangeAdapter implements ChangeListener {

        public final int index;

        public ChangeAdapter(int index) {
            this.index = index;
        }

        @Override
        public void stateChanged(ChangeEvent e) {
            throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

    }
}
