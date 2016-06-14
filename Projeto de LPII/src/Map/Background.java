package Map;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import Aplicacao.GamePanel;

/**
 * Classe que representa um background
 * @author canoi
 *
 */
public class Background {

	/**
	 * Imagem do background
	 */
	private BufferedImage image;

	/**
	 * Valor X
	 */
	private double x;
	/**
	 * Valor Y
	 */
	private double y;
	/**
	 * Valor do deslocamento X
	 */
	private double dx;
	/**
	 * Valor do deslocamento Y
	 */
	private double dy;

	public Background(String s) {
		try {
			image = ImageIO.read(getClass().getResourceAsStream(s));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * Seta a posição X e Y do Background
	 * @param x - novo valor de X
	 * @param y - novo valor de Y
	 */
	public void setPosition(int x, int y) {
		this.x = x;
		this.y = y;
	}

	/**
	 * Muda o fator de deslocamento do Background
	 * @param dx
	 * @param dy
	 */
	public void setVector(int dx, int dy) {
		this.dx = dx;
		this.dy = dy;
	}

	/**
	 * Atualiza a posição
	 */
	public void update() {
		x += dx;
		y += dy;
		if (x < -GamePanel.WIDTH)
			x = 0;
	}

	/**
	 * Desenha na tela
	 * @param g
	 */
	public void draw(Graphics2D g) {
		g.drawImage(image, (int) x, (int) y, null);
	}

	/**
	 * Opção de desenho 2, caso o background se mova
	 * @param g
	 */
	public void draw2(Graphics2D g) {
		g.drawImage(image, (int) x, (int) y, null);
		g.drawImage(image, (int) x + GamePanel.WIDTH, (int) y, null);
	}
}
