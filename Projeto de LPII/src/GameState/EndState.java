package GameState;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;

import Aplicacao.GamePanel;
import Camera.Camera;

/**
 * Classe que representa a tela de final do jogo
 * @author canoi
 *
 */
public class EndState extends GameState {

	@Override
	public void init() {
		// TODO Auto-generated method stub
		Camera.getInstance().setCameraX(0);
		Camera.getInstance().setCameraY(0);
	}

	@Override
	public void update() {
		// TODO Auto-generated method stub
		Camera.getInstance().setCameraX(0);
		Camera.getInstance().setCameraY(0);
	}

	@Override
	/**
	 * Desenha os gráficos na tela
	 */
	public void draw(Graphics2D g) {
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, GamePanel.WIDTH * GamePanel.SCALE, GamePanel.HEIGHT * GamePanel.SCALE);
		g.setColor(Color.BLACK);
		g.drawString("Você ganhou! Parabéns!", 0, 90);
	}

	@Override
	public void keyPressed(int k) {

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
