
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
 * @brief Cette classe représente une interface graphique pour une application de recherche et de lecture de médias.
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
    static Client client; 
    String message;
    JTextField textField;
    String emptyMessage = "Le champ de texte ne peut pas être vide";
    String instructions = "Fonctionnalités disponibles : \"Rechercher média\", \"Rechercher groupe\", \"Jouer\", \"Finaliser\" et \"Lister\".\n\n" +
    "Pour utiliser ces fonctionnalités, saisissez le média ou groupe que vous souhaitez jouer/rechercher ou rechercher. \n\n" + 
    "Ensuite, appuyez sur le bouton correspondant à l'action que vous souhaitez effectuer : \"Rechercher groupe/média\" ou \"Jouer\".\n\n" +
    "Pour consulter la liste des éléments présents dans la base de données, appuyez sur le bouton \"Lister\".\n\n" +
    "Pour finaliser, appuyez sur le bouton \"Finaliser\".";

  
    /**
     * @brief Cette classe représente l'action du bouton "Rechercher média".
     */
    class Button1Action extends AbstractAction {
        public Button1Action() {
            super("Rechercher média");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            if (textField.getText().trim().isEmpty()) {
                JOptionPane.showMessageDialog(null, emptyMessage, "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                message = "search multimedia " + textField.getText(); 
                textField.setText(""); 
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
     * @brief Cette classe représente l'action du bouton "Jouer".
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
     * @brief Cette classe représente l'action du bouton "Finaliser".
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
     * @brief Cette classe représente l'action du bouton "Lister".
     */
    class Button4Action extends AbstractAction {
        public Button4Action() {
            super("Lister");
        }

        @Override
        public void actionPerformed(ActionEvent e) {

            message = "list"; 
            textField.setText(""); 
            try {
                String response = client.send(message);
                textArea.append(formatResponse(response) + "\n");
            } catch (IOException ex) {
                textArea.append("Error: " + ex.getMessage() + "\n");
            }

        }
    }

       /**
     * @brief Cette classe représente l'action du bouton "Rechercher groupe".
     */
    class Button5Action extends AbstractAction {
        public Button5Action() {
            super("Rechercher groupe");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
            if (textField.getText().trim().isEmpty()) {
                JOptionPane.showMessageDialog(null, emptyMessage, "Error", JOptionPane.ERROR_MESSAGE);
            } else {
                message = "search group " + textField.getText(); 
                textField.setText(""); 
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
     * @brief Cette classe représente l'action du bouton "Instructions".
     */
    class ButtonInstructionsAction extends AbstractAction {
        public ButtonInstructionsAction() {
            super("Instructions");
        }

        @Override
        public void actionPerformed(ActionEvent e) {
             
            JOptionPane.showMessageDialog(null, instructions, "Instructions", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    /**
     * @brief Réinitialise le champ de texte.
     */
    void resetTextField() {
        textField.setText(""); 
    }

    /**
     * Formate la réponse reçue du serveur.
     *
     * @param response la réponse du serveur
     * @return la réponse formatée
     */
    String formatResponse(String response) {
        String[] responseParts = response.split("::");
        return String.join("\n", responseParts) + "\n";
    }

    /**
     * @brief Constructeur de la classe GUI.
     */
    public GUI() {

        try {
            client = new Client("localhost", 3331); 
        } catch (Exception e) {
            System.err.println("Couldn't connect to the server");
            System.exit(1);
        }

        setLayout(new BorderLayout());

        // Create the menu bar
        textField = new JTextField(50); 

        menuBar = new JMenuBar();
        menu = new JMenu("Menu");
        menuBar.add(menu);
        menuBar.add(textField); 
        setJMenuBar(menuBar); 

     
        toolBar = new JToolBar();
        add(toolBar, BorderLayout.NORTH); 

        textArea = new JTextArea("", 30, 30);
        scrollPane = new JScrollPane(textArea);
        add(scrollPane, BorderLayout.CENTER);

        panel = new JPanel(new FlowLayout());

        
        Action action1 = new Button1Action();
        Action action2 = new Button2Action();
        Action action3 = new Button3Action();
        Action action4 = new Button4Action();
        Action action5 = new Button5Action();
        Action actionInstructions = new ButtonInstructionsAction();

       
        menu.add(new JMenuItem(action1));
        menu.add(new JMenuItem(action5));
        menu.add(new JMenuItem(action2));
        menu.add(new JMenuItem(action4));
        menu.add(new JMenuItem(action3));
        menu.add(new JMenuItem(actionInstructions));

        toolBar.add(new JButton(action1));
        toolBar.add(new JButton(action5));
        toolBar.add(new JButton(action2));
        toolBar.add(new JButton(action4));
        toolBar.add(new JButton(action3));
        toolBar.add(new JButton(actionInstructions));
        ;

        add(panel, BorderLayout.SOUTH);

        setSize(500, 500);
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