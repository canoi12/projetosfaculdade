package GameState;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import Camera.Camera;
import GameObject.Chest;
import GameObject.Door;
import GameObject.Enemy;
import GameObject.Player;
import Map.Background;
import Map.Map;

/**
 * Classe que representa um level do jogo
 * 
 * @author canoi
 *
 */
public class LevelState extends GameState {

	/**
	 * Background
	 */
	Background bg;
	/**
	 * Cor do céu
	 */
	private Color color;
	/**
	 * Objeto baú
	 */
	private Chest chestObj;

	public LevelState(int level) {
		ROOMWIDTH = 1024;
		ROOMHEIGHT = 320;
		bg = new Background("/Background/level" + level + ".png");
		map = new Map("/Map/level" + level + ".txt", "/Map/doors" + level + ".txt", "/Map/enemy" + level + ".txt");
		player = new Player(10, (int) map.getDoors().get(0).getY(), 16, 16);
		doors = new Door[3];
		for (int i = 0; i < 3; i++) {
			if (map.getDoors().size() == 0)
				break;
			doors[i] = map.getDoors().get(i);
		}
		init();
	}

	/**
	 * Configura os dados iniciais
	 */
	@Override
	public void init(){
		// TODO Auto-generated method stub
		gsm = GameStateManager.getInstance();
		color = new Color(95, 205, 228);
		enemies = map.getEnemies();
	}

	/**
	 * Atualiza os dados
	 */
	@Override
	public void update() {
		// TODO Auto-generated method stub
		player.update();
		for (Enemy enemy : enemies) {
			if (enemy.getDestroy()) {
				enemies.remove(enemy);
				break;
			}
		}
		for (Enemy enemy : enemies) {
			enemy.update();
		}

	}

	/**
	 * Desenha o que estiver na fase na tela
	 */
	@Override
	public void draw(Graphics2D g) {
		// TODO Auto-generated method stub
		g.setColor(color);
		g.fillRect(0, 0, ROOMWIDTH, ROOMHEIGHT);
		bg.draw(g);
		g.setColor(Color.BLACK);
		g.drawString(""+id, Camera.getInstance().getCameraX(), Camera.getInstance().getCameraY() + 20);
		// map.draw(g);
		if(chest && chestObj == null){
			chestObj = new Chest((int) map.getDoors().get(2).getX(),(int) map.getDoors().get(2).getY()+8,16,16);
		}
		if (chest)
			chestObj.draw(g);
		if (gsm.getCurrentState().getPai() != null)
			doors[0].draw(g);
		if (gsm.getCurrentState().getRight() != null)
			doors[1].draw(g);
		if (gsm.getCurrentState().getLeft() != null)
			doors[2].draw(g);
		player.draw(g);
		for (Enemy enemy : enemies) {
			enemy.draw(g);
		}
	}
	
	public Chest getChestObj(){
		return chestObj;
	}

	@Override
	public void keyPressed(int k) {
		// TODO Auto-generated method stub
		player.keyPressed(k);
		if (k == KeyEvent.VK_SPACE) {
			if (player.collision2(getDoors()[0])) {
				GameStateManager.getInstance().goToPai();
			}
			else if (player.collision2(getDoors()[1])) {
				GameStateManager.getInstance().goToRight();
			}
			else if (player.collision2(getDoors()[2])) {
				GameStateManager.getInstance().goToLeft();
			}
			if(hasChest() && player.collision2(getChestObj())){
				GameStateManager.getInstance().setState(new Node(new EndState()));
			}
		}

	}

	@Override
	public void keyReleased(int k) {
		// TODO Auto-generated method stub
		player.keyReleased(k);

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
