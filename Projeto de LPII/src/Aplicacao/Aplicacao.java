package Aplicacao;

import javax.swing.JFrame;

public class Aplicacao {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		GamePanel gp = new GamePanel();
		
		JFrame window = new JFrame("Jogo");
        window.setContentPane(gp);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.pack();
        window.setVisible(true);

	}

}
