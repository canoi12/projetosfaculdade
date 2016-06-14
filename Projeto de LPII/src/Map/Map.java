package Map;

import java.awt.Color;
import java.awt.Graphics2D;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import GameObject.Door;
import GameObject.Enemy;
import GameObject.GameObject;
import GameObject.Slime;
import GameObject.Zombie;

/**
 * Classe responsável por carregar os dados de cada fase dos seus respectivos
 * TXT
 * 
 * @author canoi
 *
 */
public class Map {

	/**
	 * Lista de chãos
	 */
	private ArrayList<GameObject> ground;
	/**
	 * Lista de portas
	 */
	private ArrayList<Door> door;
	/**
	 * Lista de inimigos
	 */
	private ArrayList<Enemy> enemy;

	public Map() {
		ground = new ArrayList<GameObject>();
	}

	public Map(String s, String s1, String s2) {
		ground = new ArrayList<GameObject>();
		door = new ArrayList<Door>();
		enemy = new ArrayList<Enemy>();
		loadMap(s, s1, s2);
	}

	/**
	 * Carrega as posições dos chãos, portas e inimigos, dos seus respectivos
	 * TXT
	 * 
	 * @param s
	 *            - caminho para o TXT de posições dos chãos
	 * @param s1
	 *            - caminho para o TXT de posições das portas
	 * @param s2
	 *            - caminho para o TXT de posições dos inimigos
	 */
	public void loadMap(String s, String s1, String s2) {
		InputStream in = getClass().getResourceAsStream(s);
		BufferedReader input = new BufferedReader(new InputStreamReader(in));
		String line;
		String rect[] = new String[4];
		try {
			while ((line = input.readLine()) != null) {
				rect = line.split(" ");
				ground.add(new GameObject(Integer.parseInt(rect[0]), Integer.parseInt(rect[1]),
						Integer.parseInt(rect[2]), Integer.parseInt(rect[3])));
			}
			in.close();
			in = getClass().getResourceAsStream(s1);
			input = new BufferedReader(new InputStreamReader(in));
			while ((line = input.readLine()) != null) {
				rect = line.split(" ");
				door.add(new Door(Integer.parseInt(rect[0]), Integer.parseInt(rect[1]), Integer.parseInt(rect[2]),
						Integer.parseInt(rect[3])));
			}
			in.close();
			in = getClass().getResourceAsStream(s2);
			input = new BufferedReader(new InputStreamReader(in));
			String[] en = new String[5];
			while ((line = input.readLine()) != null) {
				en = line.split(" ");
				if (en[0].contains("slime")) {
					enemy.add(new Slime(Integer.parseInt(en[1]), Integer.parseInt(en[2]), Integer.parseInt(en[3]),
							Integer.parseInt(en[4])));
				}
				if (en[0].contains("zombie")) {
					enemy.add(new Zombie(Integer.parseInt(en[1]), Integer.parseInt(en[2]), Integer.parseInt(en[3]),
							Integer.parseInt(en[4])));
				}
			}
			in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	/**
	 * Desenha o chão na tela
	 * 
	 * @param g
	 */
	public void draw(Graphics2D g) {
		g.setColor(Color.BLACK);
		for (GameObject go : ground)
			g.draw(go.colBox);
	}

	/**
	 * Retorna a lista de chãos
	 * 
	 * @return ArrayList - ground
	 */
	public ArrayList<GameObject> getGrounds() {
		return ground;
	}

	/**
	 * Retorna a lista de portas
	 * 
	 * @return ArrayList - door
	 */
	public ArrayList<Door> getDoors() {
		return door;
	}

	/**
	 * Retorna a lista de inimigos
	 * 
	 * @return ArrayList - enemy;
	 */
	public ArrayList<Enemy> getEnemies() {
		return enemy;
	}
}
