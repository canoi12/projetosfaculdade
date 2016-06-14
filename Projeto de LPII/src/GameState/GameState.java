package GameState;

import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

import GameObject.Enemy;
import GameObject.GameObject;
import GameObject.Player;
import Map.Map;

/**
 * Classe que representa uma fase do jogo
 * @author canoi
 *
 */
public abstract class GameState {

	/**
	 * Game State Manager
	 */
	protected GameStateManager gsm;
	public Node node;

	/**
	 * Jogador
	 */
	protected Player player;
	/**
	 * Lista de inimigos
	 */
	protected ArrayList<Enemy> enemies;
	/**
	 * Mapa a ser carregado
	 */
	protected Map map; // 

	/**
	 * Se tem o baú ou não
	 */
	protected boolean chest = false;

	/**
	 * ID da fase
	 */
	protected int id = 0; 

	/**
	 *  Lista de portas
	 */
	protected GameObject[] doors;

	/**
	 * Dimensões da fase
	 */
	protected static int ROOMWIDTH;
	protected static int ROOMHEIGHT;

	/**
	 * Retorna o ID da fase
	 * @return int - id
	 */
	public int getID() {
		return id;
	}

	/**
	 * Modifica o ID da fase
	 * @param id
	 */
	public void setID(int id) {
		this.id = id;
	}

	/**
	 * Retorna a lista de inimigos
	 * @return ArrayList - enemies
	 */
	public ArrayList<Enemy> getEnemies() {
		return enemies;
	}

	/**
	 * Retorna a lista de portas
	 * @return ArrayList - doors
	 */
	public GameObject[] getDoors() {
		return doors;
	}

	/**
	 * Modifica a variável chest
	 * @param chest - Novo valor de chest
	 */
	public void setChest(boolean chest) {
		this.chest = chest;
	}
	
	/**
	 * Retorna o valor do boolean chest
	 * @return boolean - chest
	 */
	public boolean hasChest(){
		return chest;
	}
	
	/**
	 * Retorna o player
	 * @return Player - player
	 */
	public Player getPlayer(){
		return player;
	}

	/**
	 * Inicia os dados
	 */
	public abstract void init();

	/**
	 * Atualiza os dados
	 */
	public abstract void update();

	/**
	 * Desenha tudo que está na fase na tela
	 * @param g
	 */
	public abstract void draw(Graphics2D g);

	/**
	 * Retorna a largura da tela
	 * @return int - ROOMWIDTH
	 */
	public static int getRoomWidth() {
		return ROOMWIDTH;
	}

	/**
	 * Retorna a altura da tela
	 * @return int - ROOMHEIGHT
	 */
	public static int getRoomHeight() {
		return ROOMHEIGHT;
	}

	/**
	 * Retorna o mapa
	 * @return Mapa - map
	 */
	public Map getMap() {
		return map;
	}

	public abstract void keyPressed(int k);

	public abstract void keyReleased(int k);

	public abstract void mouseClicked(MouseEvent btn);

	public abstract void mousePressed(MouseEvent btn);

	public abstract void mouseReleased(MouseEvent btn);

	public abstract void mouseDragged(MouseEvent btn);

	public abstract void mouseMoved(MouseEvent btn);

}
