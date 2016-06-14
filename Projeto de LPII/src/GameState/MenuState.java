package GameState;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import Aplicacao.GamePanel;

/**
 * Classe que representa a tela de menu do jogo
 * @author canoi
 *
 */

public class MenuState extends GameState {

	private float i = 0;

	/**
	 * Opção atual
	 */
	private int currentChoice = 0;

	/**
	 * Opções do menu
	 */
	private String[] options = { "Start", "Editor", "Sair" };

	public MenuState() {
		init();
	}

	/**
	 * Carrega as configurações iniciais
	 */
	@Override
	public void init() {
		// TODO Auto-generated method stub
	}

	/**
	 * Atualiza os dados da fase
	 */
	@Override
	public void update() {
		// TODO Auto-generated method stub
		if(currentChoice < 0){
			currentChoice = 2;
		}
		else if(currentChoice > 2){
			currentChoice = 0;
		}
		i += 0.1;
		if(i % (Math.PI*2) == 0){
			i = 0;
		}
	}

	/**
	 * Desenha o bg e as opções na tela
	 */
	@Override
	public void draw(Graphics2D g) {
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, GamePanel.WIDTH * GamePanel.SCALE, GamePanel.HEIGHT * GamePanel.SCALE);
		//bg.draw(g);
		g.setColor(Color.BLACK);
		g.drawString("Labirinto", GamePanel.WIDTH/2-50, (int)(Math.sin(i)*5) + 30);
		for (int i = 0; i < options.length; i++) {
			if (i == currentChoice)
				g.setColor(Color.BLUE);
			else
				g.setColor(Color.BLACK);
			g.drawString(options[i], 70, 50 + (i * 20));

		}
	}

	/**
	 * Executa um comando dependendo da opção atual
	 */
	public void select() {
		switch (currentChoice) {
		case 0:
			GameStateManager.getInstance().setState(GameStateManager.getInstance().getRaiz());
			break;
		case 1:
			GameStateManager.getInstance().goToLeft();
			break;
		case 2:
			System.exit(0);
			break;
		}
	}

	@Override
	public void keyPressed(int k) {
		if (k == KeyEvent.VK_ENTER)
			select();
		if (k == KeyEvent.VK_UP) {
			currentChoice--;
		}
		if (k == KeyEvent.VK_DOWN) {
			currentChoice++;
		}

	}

	@Override
	public void keyReleased(int k) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseClicked(MouseEvent btn) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent btn) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseReleased(MouseEvent btn) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseDragged(MouseEvent btn) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseMoved(MouseEvent btn) {
		// TODO Auto-generated method stub

	}

}
