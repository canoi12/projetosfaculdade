package GameObject;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Dictionary;
import java.util.HashMap;
import java.util.Map;

import javax.imageio.ImageIO;

import GameState.GameStateManager;

/**
 * Classe que representa qualquer objeto do jogo
 * 
 * @author canoi
 *
 */
public class GameObject {

	/**
	 * Posição do objeto (x, y, largura, altura)
	 */
	public Rectangle position;

	/**
	 * 1 se estiver virado para direita e -1 para a esquerda
	 */
	protected int flip = 1;

	/**
	 * Se está andando para a esquerda
	 */
	protected boolean left = false;
	/**
	 * Se está andando para a direita
	 */
	protected boolean right = false;
	/**
	 * Se está pulando
	 */
	protected boolean up = false;

	/**
	 * Se a imagem está virada para a esquerda
	 */
	protected boolean facingLeft = false;
	/**
	 * Se a imagem está virada para a direita
	 */
	protected boolean facingRight = true;

	/**
	 * Animação atual
	 */
	protected String currentAnimation = "";
	/**
	 * Tempo atual para muda o frame da animação
	 */
	protected float frameTime = 0.04f; 
	/**
	 * Tempo inicial para mudar o frame da animação
											 
 	*/
	protected float frameTimeInit = 0.04f;
	/**
	 * Frame atual da animação
	 */
	protected int actualFrame = 0;

	/**
	 * Gravidade
	 */
	protected int gravity = 1600;
	/**
	 * Velocidade vertical
	 */
	protected float vspeed = 1;
	
	/**
	 * Velocidade horizontal
	 */
	protected float hspeed = 0;

	/**
	 * Caixa de colisão
	 */
	public Rectangle colBox;
	/**
	 * Valores da caixa de colsão
	 */
	protected int[] colBoxValues = { 0, 0, 0, 0 };
	/**
	 * Game State Manager
	 */
	GameStateManager gsm;

	/**
	 * Imagem do objeto
	 */
	protected BufferedImage image;

	/**
	 * HashMap que guarda as animações
	 */
	protected Map<String, BufferedImage[]> animations = new HashMap<String, BufferedImage[]>();

	public GameObject() {

	}

	public GameObject(float x, float y, int w, int h) {
		position = new Rectangle((int) x, (int) y, w, h);
		colBox = new Rectangle((int) x, (int) y, w, h);
		// gsm = GameStateManager.getInstance();
	}

	private void init() {
	}

	/**
	 * Seta os valores da caixa de colisão
	 * 
	 * @param x
	 *            - valor X
	 * @param y
	 *            - valor Y
	 * @param w
	 *            - largura
	 * @param h
	 *            - altura
	 */
	public void setColBox(int x, int y, int w, int h) {
		colBoxValues[0] = x;
		colBoxValues[1] = y;
		colBoxValues[2] = w;
		colBoxValues[3] = h;
		colBox.setBounds((int) x + colBoxValues[0], (int) y + colBoxValues[1], colBoxValues[2], colBoxValues[3]);
	}

	/**
	 * Muda a posição do objeto
	 * 
	 * @param x
	 *            - X
	 * @param y
	 *            - Y
	 */
	public void setPosition(int x, int y) {
		position.x = x;
		position.y = y;
	}

	/**
	 * Retorna a largura
	 * 
	 * @return int - largura
	 */
	public int getWidth() {
		return position.width;
	}

	/**
	 * Retorna a altura
	 * 
	 * @return int - altura
	 */
	public int getHeight() {
		return position.height;
	}

	/**
	 * Retorna o valor da posição X do centro do objeto
	 * 
	 * @return float - centerX
	 */
	public float getCenterX() {
		return (float) position.getCenterX();
	}

	/**
	 * Retorna o valor da posição Y do centro do objeto
	 * 
	 * @return float - centerX
	 */
	public float getCenterY() {
		return (float) position.getCenterY();
	}

	/**
	 * Retorna o valor da posição X
	 * 
	 * @return float - X
	 */
	public float getX() {
		return position.x;
	}

	/**
	 * Retorna o valor da posição Y
	 * 
	 * @return int - Y
	 */
	public float getY() {
		return position.y;
	}

	/**
	 * Testa a colisão entre o objeto atual, e um segundo objeto passado por
	 * parametro
	 * 
	 * @param obj2
	 *            - segundo objeto a ser testado
	 * @return boolean
	 */
	public boolean Collision(GameObject obj2) {
		Rectangle A = this.colBox;
		Rectangle B = obj2.colBox;
		float w = (float) (0.5 * (A.getWidth() + B.getWidth()));
		float h = (float) (0.5 * (A.getHeight() + B.getHeight()));
		float vspeed = this.vspeed * 0.01f;
		float dx = (float) (A.getCenterX() - B.getCenterX());
		float dy = (float) (A.getCenterY() - B.getCenterY());

		if (Math.abs(dx) <= w && Math.abs(dy) <= h) {
			/* collision! */
			dy = dy - vspeed;
			float wy = w * dy;
			float hx = h * dx;

			if (wy > hx) {
				if (wy > -hx) {
					collisionTop(obj2);
				} else {
					/* on the left */
					collisionLeft(obj2);
				}
			} else {
				if (wy > -hx) {
					/* on the right */
					collisionRight(obj2);
				} else {
					/* at the bottom */
					collisionBottom(obj2);
				}
			}
			return true;
		}
		return false;
	}

	/**
	 * Caso haja colisão acima do objeto
	 * 
	 * @param B
	 */
	public void collisionTop(GameObject B) {
	}

	/**
	 * Caso haja colisão embaixo do objeto
	 * 
	 * @param B
	 */
	public void collisionBottom(GameObject B) {
		position.y = (int) (B.colBox.getY() - (colBox.getHeight())) - colBoxValues[1];
		vspeed = 0;
	}

	/**
	 * Caso haja colisão a esquerda do objeto
	 * 
	 * @param B
	 */
	public void collisionLeft(GameObject B) {
		position.x = (int) (B.colBox.getX() - colBox.getWidth()) - colBoxValues[0];
	}

	/**
	 * Caso haja colisão a direita do objeto
	 * 
	 * @param B
	 */
	public void collisionRight(GameObject B) {
		position.x = (int) (B.colBox.getX() + B.colBox.getWidth()) - colBoxValues[0];
	}

	/**
	 * Adiciona uma nova animação no HashMap
	 * 
	 * @param name
	 *            - nome da nova animação
	 * @param xInit
	 *            - x inicial da animação na imagem principal
	 * @param yInit
	 *            - y inicial da animação na imagem principal
	 * @param frameWidth
	 *            - largura de cada frame da animação
	 * @param frameHeight
	 *            - altura de cada frame da animação
	 * @param numImages
	 *            - número de imagens que a animação irá conter
	 */
	public void addAnimation(String name, int xInit, int yInit, int frameWidth, int frameHeight, int numImages) {
		int index = 0;
		BufferedImage imgs[] = new BufferedImage[numImages];
		for (int i = (int) (xInit / frameWidth); i < (int) (xInit / frameWidth) + numImages; i++) {
			imgs[index] = image.getSubimage(i * frameWidth, yInit, frameWidth, frameHeight);
			index++;
		}
		animations.put(name, imgs);
		if (currentAnimation == "")
			currentAnimation = name;
	}

	/**
	 * Atualiza a animação
	 */
	public void runAnimation() {
		frameTime -= 0.01;
		if (frameTime <= 0) {
			frameTime = frameTimeInit;
			actualFrame++;
		}
		if (actualFrame > animations.get(currentAnimation).length - 1) {
			actualFrame = 0;
		}
	}

	/**
	 * Muda a animação atual
	 * 
	 * @param name
	 *            - nome da animação que será rodada
	 */
	public void changeAnimation(String name) {
		if (actualFrame > animations.get(name).length - 1)
			actualFrame = 0;
		currentAnimation = name;
	}

	/**
	 * Atualiza os dados do objeto
	 */
	public void update() {
	}

	/**
	 * Desenha o objeto na tela
	 * 
	 * @param g
	 */
	public void draw(Graphics2D g) {
		drawShape(g);
		if (facingRight)
			g.drawImage(animations.get(currentAnimation)[actualFrame], (int) position.x, (int) position.y,
					(flip) * position.width, position.height, null);
		else if (facingLeft)
			g.drawImage(animations.get(currentAnimation)[actualFrame], (int) position.x + position.width,
					(int) position.y, flip * position.width, position.height, null);

	}

	/**
	 * Desemja a caixa de colisão
	 * 
	 * @param g
	 */
	public void drawShape(Graphics2D g) {
		g.setColor(Color.BLACK);
		// g.draw(colBox);
	}

	public void keyPressed(int k) {
	}

	public void keyReleased(int k) {
	}
}
