package GameObject;

import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.io.IOException;

import javax.imageio.ImageIO;

import GameState.EndState;
import GameState.GameStateManager;
import GameState.LevelState;
import GameState.Node;
import Map.Map;
import Aplicacao.GamePanel;
import Camera.Camera;

/**
 * Classe que representa o personagem principal do jogo
 * @author canoi
 *
 */
public class Player extends GameObject {

	public Player(int x, int y, int width, int height) {
		super(x, y, width, height);
		// TODO Auto-generated constructor stub
		init();
	}

	/**
	 * Testa se há colisão, porém somente retorna true ou false, não chama os métodos de colisão para cada lado
	 * @param obj2
	 * @return
	 */
	public boolean collision2(GameObject obj2) {
		Rectangle A = this.colBox;
		Rectangle B = obj2.colBox;
		float w = (float) (0.5 * (A.getWidth() + B.getWidth()));
		float h = (float) (0.5 * (A.getHeight() + B.getHeight()));
		float vspeed = this.vspeed * 0.01f;
		float dx = (float) (A.getCenterX() - B.getCenterX());
		float dy = (float) (A.getCenterY() - B.getCenterY());

		if (Math.abs(dx) <= w && Math.abs(dy) <= h) {
			/* collision! */
			return true;
		}
		return false;
	}

	/**
	 * Caso haja colisão embaixo do player
	 */
	public void collisionBottom(GameObject B) {
		super.collisionBottom(B);
		up = false;
		if (!left && !right) {
			changeAnimation("idle");
		}
		if (B instanceof Enemy) {
			vspeed = -200;
			// ((Enemy)B).destroy = true;
		}
	}

	/**
	 * Caso haja colisão em cima do player
	 */
	public void collisionTop(GameObject B) {
		position.y = B.colBox.y + B.colBox.height;
		vspeed = 1;
	}

	/**
	 * Carrega as configurações iniciais, como imagem, cria as animações.
	 */
	public void init() {
		gsm = GameStateManager.getInstance();
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/Char/player.png"));
			addAnimation("walk", 0, 16, 16, 16, 10);
			addAnimation("idle", 0, 0, 16, 16, 3);
			addAnimation("jump", 0, 32, 16, 16, 1);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		frameTimeInit = 0.06f;

		setColBox(4, 3, 12, 12);
	}

	/**
	 * Atualiza os dados do jogador
	 */
	public void update() {

		position.x = (int) Math.max(0,
				Math.min(position.x, gsm.getCurrentState().getValue().getRoomWidth() - position.getWidth()));

		Camera.getInstance().setCameraX(position.x - (GamePanel.WIDTH / 2));
		Camera.getInstance().setCameraY(position.y - (GamePanel.HEIGHT / 2));

		if (left) {
			position.x -= 2;
		}
		if (right) {
			position.x += 2;
		}
		if ((left || right) && !up) {
			changeAnimation("walk");
		}

		if (position.y < gsm.getCurrentState().getValue().getRoomHeight() - colBox.getHeight()) {
			vspeed += (gravity * 0.01);
			position.y += vspeed * 0.01;
			up = true;
		} else {
			position.x = (int) gsm.getCurrentState().getValue().getMap().getDoors().get(0).getX();
			position.y = (int) gsm.getCurrentState().getValue().getMap().getDoors().get(0).getY();
		}

		colBox.x = position.x + colBoxValues[0];
		colBox.y = position.y + colBoxValues[1];

		for (GameObject rect : gsm.getCurrentState().getValue().getMap().getGrounds()) {
			Collision(rect);
		}

		for (Enemy enemy : gsm.getCurrentState().getValue().getEnemies()) {
			Collision(enemy);
		}
		runAnimation();
	}

	@Override
	public void keyPressed(int k) {
		super.keyPressed(k);
		if (k == KeyEvent.VK_LEFT) {
			left = true;
			flip = -1;
			facingLeft = true;
			facingRight = false;
		}
		if (k == KeyEvent.VK_RIGHT) {
			right = true;
			flip = 1;
			facingLeft = false;
			facingRight = true;
		}

		if (k == KeyEvent.VK_UP) {
			changeAnimation("jump");
			if (!up) {
				up = true;
				vspeed = -350;
				position.y -= 1;
			}
		}
	}

	@Override
	public void keyReleased(int k) {
		super.keyReleased(k);
		if (k == KeyEvent.VK_LEFT) {
			left = false;
		}
		if (k == KeyEvent.VK_RIGHT) {
			right = false;
		}
	}

}
