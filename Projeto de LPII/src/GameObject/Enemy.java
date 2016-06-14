package GameObject;

import java.util.Random;

import GameState.GameStateManager;

/**
 * Classe que representa um inimigo no jogo
 * 
 * @author canoi
 *
 */
public class Enemy extends GameObject {
	/**
	 *  Tipo do inimigo (útil somente para ler e salvar no txt)
	 */
	protected String type;
	
	/**
	 * Variável necessária para destruir o inimigo
	 */
	private boolean destroy;

	public Enemy(int x, int y, int width, int height) {
		super(x, y, width, height);
		// TODO Auto-generated constructor stub
		int test = new Random().nextInt(10);

		if (test > 5) {
			right = true;
		} else {
			left = true;
		}
	}

	public void facingToPlayer(Player p) {
	}

	public void collisionTop(GameObject B) {
		super.collisionTop(B);
		if (B instanceof Player) {
			destroy = true;
		}
	}

	/**
	 * Este método é chamado quando houve colisão à esquerda do inimigo
	 */
	public void collisionLeft(GameObject B) {
		if(!(B instanceof Player)){
			right = false;
			left = true;
		}
	}

	/**
	 * Método chamado se houve colisão à direita do inimigo
	 */
	public void collisionRight(GameObject B) {
		if(!(B instanceof Player)){
			right = true;
			left = false;
		}
	}

	public void init() {
	}

	/**
	 * Atualiza o posição do inimigo, animação e testa colisões
	 */
	public void update() {
		if (position.y < GameStateManager.getInstance().getCurrentState().getValue().getRoomHeight()
				- colBox.getHeight()) {
			vspeed += (gravity * 0.01);
			position.y += vspeed * 0.01;
		}
		runAnimation();
		for (GameObject obj : GameStateManager.getInstance().getCurrentState().getValue().getMap().getGrounds()) {
			if (Collision(obj)) {
				if (colBox.x + colBox.width >= obj.colBox.x + obj.colBox.width
						&& colBox.x + colBox.width <= obj.colBox.x + obj.colBox.width + 5) {
					left = true;
					right = false;
				}
				if (colBox.x <= obj.colBox.x && colBox.x >= obj.colBox.x - 5) {
					right = true;
					left = false;
				}
			}
		}
		if (position.x <= 0) {
			right = true;
			left = false;
		}
		if (position.x + position.width >= GameStateManager.getInstance().getCurrentState().getValue().getRoomWidth()) {
			left = true;
			right = false;
		}

		if (left) {
			position.x -= hspeed;
			facingRight = false;
			facingLeft = true;
			flip = -1;
		} else if (right) {
			position.x += hspeed;
			facingLeft = false;
			facingRight = true;
			flip = 1;
		}
		Collision(GameStateManager.getInstance().getCurrentState().getValue().getPlayer());
		colBox.x = (int) position.x + colBoxValues[0];
		colBox.y = (int) position.y + colBoxValues[1];

	}

	/**
	 * Desenha a imagem do inimigo na tela
	 */
	public void draw(java.awt.Graphics2D g) {
		super.draw(g);
	}

	/**
	 * Seta o tipo do inimigo
	 * 
	 * @param type
	 */
	public void setType(String type) {
		this.type = type;
	}

	/**
	 * Retorna o tipo do inimigo
	 * 
	 * @return
	 */
	public String getType() {
		return type;
	}

	public boolean getDestroy() {
		return destroy;
	}

	public void keyPressed(int k) {
	}

	public void keyReleases(int k) {
	}

}
