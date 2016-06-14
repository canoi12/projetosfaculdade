package GameObject;

import java.io.IOException;
import java.util.Random;

import javax.imageio.ImageIO;

/**
 * Classe que representa um inimigo do tipo Zombie
 * 
 * @author canoi
 *
 */

public class Zombie extends Enemy {

	public Zombie(int x, int y, int width, int height) {
		super(x, y, width, height);
		// TODO Auto-generated constructor stub
		init();
	}

	/**
	 * Configura os dados iniciais
	 */
	public void init() {
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/Char/zombie.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		addAnimation("idle", 0, 16, 16, 16, 3);
		type = "zombie";

		setColBox(0, 2, 15, 11);
		hspeed = 1;

		frameTimeInit = 0.07f;

	}

	/**
	 * Desenha o inimigo na tela
	 */
	public void draw(java.awt.Graphics2D g) {
		super.draw(g);
	}

	public void keyPressed(int k) {
	}

	public void keyReleases(int k) {
	}

}
