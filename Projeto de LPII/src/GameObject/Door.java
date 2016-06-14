package GameObject;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * Classe que representa uma porta no jogo
 * @author canoi
 *
 */
public class Door extends GameObject {

	public Door(float x, float y, int w, int h) {
		position = new Rectangle((int) x, (int) y, w, h);
		colBox = new Rectangle((int) x, (int) y, w, h);
		// gsm = GameStateManager.getInstance();
		init();
	}

	/**
	 * Inicia a variável image da porta
	 */
	public void init() {
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/Background/door.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * Chama o método drawImage que desenha a imagem do objeto na tela
	 */
	public void draw(Graphics2D g) {
		g.drawImage(image, position.x, position.y, null);
	}

}
