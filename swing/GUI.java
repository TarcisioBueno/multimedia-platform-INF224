/**
 * @file GUI.java
 * @brief Ce fichier contient la classe GUI, qui représente une interface graphique pour une application Swing.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * Cette classe représente une interface graphique pour une application de recherche et de lecture de médias.
 */


public class GUI extends JFrame {

    private static final long serialVersionUID = 1L;

    JTextArea textArea;
    JScrollPane scrollPane;
    JButton button1, button2, button3, button4;
    JPanel panel;
    JMenuBar menuBar;
    JMenu menu;
    JToolBar toolBar;
    static Client client; // add a Client instance
    String message;
    JTextField textField;
    String emptyMessage = "Le champ de texte ne peut pas être vide";

    // Define actions as subclasses of AbstractAction

    /**
     * Cette classe représente l'action du bouton "Rechercher".
     */
    class Button1Action extends AbstractAction {
        public Button1Action() {
            super("Rechercher");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            if (textField.getText().trim().isEmpty()) {
                JOptionPane.showMessageDialog(null, emptyMessage, "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                message = "search multimedia " + textField.getText(); // get the text from the JTextField
                textField.setText(""); // clear the JTextField
                try {
                    String response = client.send(message);
                    textArea.append(formatResponse(response) + "\n");
                } catch (IOException ex) {
                    textArea.append("Error: " + ex.getMessage() + "\n");
                }
            }
        }
    }

    /**
     * Cette classe représente l'action du bouton "Jouer".
     */
    class Button2Action extends AbstractAction {
        public Button2Action() {
            super("Jouer");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            if (textField.getText().trim().isEmpty()) {
                JOptionPane.showMessageDialog(null, emptyMessage, "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                message = "play " + textField.getText();
                resetTextField();
                try {
                    String response = client.send(message);
                    textArea.append(formatResponse(response) + "\n");
                } catch (IOException ex) {
                    textArea.append("Error: " + ex.getMessage() + "\n");
                }
            }
        }
    }

    /**
     * Cette classe représente l'action du bouton "Finaliser".
     */
    class Button3Action extends AbstractAction {
        public Button3Action() {
            super("Finaliser");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }

    /**
     * Cette classe représente l'action du bouton "Lister".
     */
    class Button4Action extends AbstractAction {
        public Button4Action() {
            super("Lister");
        }

        @Override
        public void actionPerformed(ActionEvent e) {

            message = "list"; // get the text from the JTextField
            textField.setText(""); // clear the JTextField
            try {
                String response = client.send(message);
                textArea.append(formatResponse(response) + "\n");
            } catch (IOException ex) {
                textArea.append("Error: " + ex.getMessage() + "\n");
            }

        }
    }

    /**
     * Réinitialise le champ de texte.
     */
    void resetTextField() {
        textField.setText(""); // set initial text
    }

    /**
     * Formate la réponse reçue du serveur.
     *
     * @param response la réponse du serveur
     * @return la réponse formatée
     */
    String formatResponse(String response) {
        String[] responseParts = response.split("::");
        return String.join("\n", responseParts) + "\n------------------------------------------------------------";
    }

    /**
     * Constructeur de la classe GUI.
     */
    public GUI() {

        try {
            client = new Client("localhost", 3331); // Initialize the Client instance
        } catch (Exception e) {
            System.err.println("Couldn't connect to the server");
            System.exit(1);
        }

        setLayout(new BorderLayout());

        // Create the menu bar
        textField = new JTextField(20); // initialize the JTextField instance

        menuBar = new JMenuBar();
        menu = new JMenu("Menu");
        menuBar.add(menu);
        menuBar.add(textField); // add the JTextField to the menuBar
        setJMenuBar(menuBar); // Add the menu bar to the JFrame

        // Create the tool bar
        toolBar = new JToolBar();
        add(toolBar, BorderLayout.NORTH); // Add the tool bar to the top (north) of the JFrame

        textArea = new JTextArea("", 10, 30);
        scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        panel = new JPanel(new FlowLayout());

        // Create the actions
        Action action1 = new Button1Action();
        Action action2 = new Button2Action();
        Action action3 = new Button3Action();
        Action action4 = new Button4Action();

        // Add the actions to the menu and the tool bar
        menu.add(new JMenuItem(action1));
        menu.add(new JMenuItem(action2));
        menu.add(new JMenuItem(action3));
        menu.add(new JMenuItem(action4));

        toolBar.add(new JButton(action1));
        toolBar.add(new JButton(action2));
        toolBar.add(new JButton(action3));
        toolBar.add(new JButton(action4));

        add(panel, BorderLayout.SOUTH);

        setSize(300, 300);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    /**
     * Méthode principale pour exécuter l'application.
     *
     * @param args les arguments de la ligne de commande
     */
    public static void main(String[] args) {

        new GUI();

    }

}