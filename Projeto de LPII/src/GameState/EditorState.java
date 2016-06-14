package GameState;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;

import Camera.Camera;
import GameObject.Enemy;
import GameObject.Slime;
import GameObject.Zombie;
import Map.Background;
import Aplicacao.GamePanel;

/**
 * Classe que representa o editor de fases
 * 
 * @author canoi
 *
 */
public class EditorState extends GameState {

	/**
	 * Lista de chãos
	 */
	private ArrayList<Rectangle> ground;
	/**
	 * Lista de portas
	 */
	private ArrayList<Rectangle> door;
	/**
	 * Lista de inimigos
	 */
	private ArrayList<Enemy> enemy;
	/**
	 * Variável de teste, caso seja true, adiciona um novo objeto no mapa
	 */
	private boolean adicionar = false;
	/**
	 * Variável responsável por dizer se estamos no modo de edição ou não
	 */
	private boolean editar = false;
	/**
	 * Objeto que está sendo editado atualmente
	 */
	private Rectangle editRect;

	/**
	 * Background da fase
	 */
	private Background bg;

	/**
	 * Inimigo que está sendo atualmente adicionado no mapa 0 = slime / 1 =
	 * zombie
	 */
	private int inimigoAtual = 0;
	/**
	 * Level atual que estamos a editar
	 */
	private int lvlAtual = 2;

	/**
	 * Tamanho do tile
	 */
	private int tileSize = 8;
	/**
	 * Largura da fase
	 */
	private int WIDTH = 1024;
	/**
	 * Altura da fase
	 */
	private int HEIGHT = 320;

	/**
	 * Arquivo TXT que guarda as posições dos chãos da fase
	 */
	private String levelTxt = "level" + lvlAtual + ".txt";

	/**
	 * Arquivo que carrega a imagem da fase atual
	 */
	private String levelImg = "level" + lvlAtual + ".png";
	/**
	 * Arquivo txt que guarda as posições das portas da fase
	 */
	private String doorsTxt = "doors" + lvlAtual + ".txt";
	/**
	 * Arquivo txt que guarda as posições dos inimigos da fase
	 */
	private String enemyTxt = "enemy" + lvlAtual + ".txt";

	/**
	 * Tipo de objeto que está sendo adicionado/editado atualmente
	 *  0 = chão
	 *  1 = porta 
	 *  2 = inimigo
	 */
	private int objsAtual = 0;

	/**
	 *  Booleanos responsável por controlar a posição da câmera
	 */
	private boolean left;
	private boolean right;
	private boolean up;
	private boolean down;

	/**
	 * Variável responsável por dizer se vamos alterar a posição de um objeto
	 */
	private boolean editPos;
	/**
	 * Variável responsável por dizer se vamos alterar o tamanho de um objeto
	 */
	private boolean editSize;

	public EditorState() {
		init();
	}

	/**
	 * Calcula a distância entre dois pontos
	 * 
	 * @param x1
	 *            - X do primeiro ponto
	 * @param y1
	 *            - Y do primeiro ponto
	 * @param x2
	 *            - X do segundo ponto
	 * @param y2
	 *            - Y do segundo ponto
	 * @return float - distância
	 */
	public float distance(float x1, float y1, float x2, float y2) {

		float dx = x1 - x2;
		float dy = y1 - y2;

		return (float) Math.sqrt((dx * dx) + (dy * dy));
	}

	/**
	 * Carrega todos os dados da fase de seus respectivos txt's
	 * 
	 * @param s
	 *            - caminho do txt que gurada posições dos chãos
	 * @param s1
	 *            - caminho do txt que gurada posições das portas
	 * @param s2
	 *            - caminho do txt que gurada posições dos inimigos
	 */
	public void loadMap(String s, String s1, String s2) {
		InputStream in = getClass().getResourceAsStream(s);
		BufferedReader input = new BufferedReader(new InputStreamReader(in));
		String line;
		String rect[] = new String[4];
		try {
			while ((line = input.readLine()) != null) {
				rect = line.split(" ");
				ground.add(new Rectangle(Integer.parseInt(rect[0]), Integer.parseInt(rect[1]),
						Integer.parseInt(rect[2]), Integer.parseInt(rect[3])));
			}
			in.close();
			in = getClass().getResourceAsStream(s1);
			input = new BufferedReader(new InputStreamReader(in));
			while ((line = input.readLine()) != null) {
				rect = line.split(" ");
				door.add(new Rectangle(Integer.parseInt(rect[0]), Integer.parseInt(rect[1]), Integer.parseInt(rect[2]),
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
	 * Configura os dados iniciais
	 */
	public void init() {
		ground = new ArrayList<Rectangle>();
		door = new ArrayList<Rectangle>();
		enemy = new ArrayList<Enemy>();
		loadMap("/Map/" + levelTxt, "/Map/" + doorsTxt, "/Map/" + enemyTxt);
		Camera.getInstance().setCameraX(0);
		bg = new Background("/Background/" + levelImg);
	}

	/**
	 * Atualiza a posição da câmera
	 */
	public void update() {

		if (left)
			Camera.getInstance().setCameraX(Camera.getInstance().getCameraX() - 2);
		if (right)
			Camera.getInstance().setCameraX(Camera.getInstance().getCameraX() + 2);

		if (up)
			Camera.getInstance().setCameraY(Camera.getInstance().getCameraY() - 2);
		if (down)
			Camera.getInstance().setCameraY(Camera.getInstance().getCameraY() + 2);
	}

	/**
	 * Desenha o mapa na tela
	 */
	public void draw(Graphics2D g) {
		g.setColor(Color.WHITE);
		g.fill(new Rectangle(0, 0, WIDTH, HEIGHT));
		bg.draw(g);
		g.setColor(Color.BLACK);
		for (Rectangle rect : ground) {
			g.draw(rect);
			if (rect == editRect) {
				g.fillOval(rect.x - 6, rect.y - 6, 12, 12);
				g.fillOval(rect.x + rect.width - 6, rect.y + rect.height - 6, 12, 12);
			}
		}
		for (Rectangle rect : door) {
			g.draw(rect);
			if (rect == editRect) {
				g.fillOval(rect.x - 6, rect.y - 6, 12, 12);
				g.fillOval(rect.x + rect.width - 6, rect.y + rect.height - 6, 12, 12);
			}
		}
		for (Enemy rect : enemy) {
			g.draw(rect.position);
			rect.draw(g);
			if (rect.position == editRect) {
				g.fillOval(rect.position.x - 6, rect.position.y - 6, 12, 12);
				g.fillOval(rect.position.x + rect.position.width - 6, rect.position.y + rect.position.height - 6, 12,
						12);
			}
		}
		g.drawString("" + objsAtual, Camera.getInstance().getCameraX() + 10, Camera.getInstance().getCameraY() + 20);
		if (objsAtual == 2)
			g.drawString(inimigoAtual + "", Camera.getInstance().getCameraX() + 30,
					Camera.getInstance().getCameraY() + 20);
	}

	/**
	 * Método responsável por salvar todos os dados de volta no TXT
	 */
	public void salvar() {
		try {
			PrintWriter out = new PrintWriter("Resources/Map/" + levelTxt);
			for (Rectangle rect : ground) {
				out.println(rect.x + " " + rect.y + " " + rect.width + " " + rect.height);
			}
			out.close();
			out = new PrintWriter("Resources/Map/" + doorsTxt);
			for (Rectangle rect : door) {
				out.println(rect.x + " " + rect.y + " " + rect.width + " " + rect.height);
			}
			out.close();
			out = new PrintWriter("Resources/Map/" + enemyTxt);
			for (Enemy rect : enemy) {
				out.println(rect.getType() + " " + rect.position.x + " " + rect.position.y + " " + rect.position.width
						+ " " + rect.position.height);
			}
			out.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void keyPressed(int k) {
		if (k == KeyEvent.VK_LEFT)
			left = true;
		if (k == KeyEvent.VK_RIGHT)
			right = true;

		if (k == KeyEvent.VK_BACK_SPACE) {
			if (objsAtual == 0) {
				ground.remove(ground.get(ground.size() - 1));
			}
			if (objsAtual == 1) {
				door.remove(door.get(ground.size() - 1));
			}
			if (objsAtual == 2) {
				enemy.remove(enemy.get(enemy.size() - 1));
			}
		}

		if (k == KeyEvent.VK_A)
			inimigoAtual--;
		if (k == KeyEvent.VK_D)
			inimigoAtual++;

		if (k == KeyEvent.VK_0)
			objsAtual = 0;
		if (k == KeyEvent.VK_1)
			objsAtual = 1;
		if (k == KeyEvent.VK_2)
			objsAtual = 2;

		if (k == KeyEvent.VK_UP)
			up = true;
		if (k == KeyEvent.VK_DOWN)
			down = true;

		if (k == KeyEvent.VK_S) {
			salvar();
		}
	}

	public void keyReleased(int k) {
		if (k == KeyEvent.VK_LEFT)
			left = false;
		if (k == KeyEvent.VK_RIGHT)
			right = false;

		if (k == KeyEvent.VK_UP)
			up = false;
		if (k == KeyEvent.VK_DOWN)
			down = false;
	}

	public void mouseClicked(MouseEvent btn) {
		adicionar = true;
		if (btn.getButton() == MouseEvent.BUTTON1) {
			if (objsAtual == 0) {
				for (Rectangle rect : ground) {
					if ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() > rect.x
							&& (btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() < rect.x + rect.width
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() > rect.y
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() < rect.y + rect.height
							&& !editar) {
						adicionar = false;
						editRect = rect;
						editar = true;
						break;
					}
				}
			} else if (objsAtual == 1) {
				for (Rectangle rect : door) {
					if ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() > rect.x
							&& (btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() < rect.x + rect.width
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() > rect.y
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() < rect.y + rect.height
							&& !editar) {
						adicionar = false;
						editRect = rect;
						editar = true;
						break;
					}
				}
			} else if (objsAtual == 2) {
				for (Enemy rect : enemy) {
					if ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() > rect.position.x
							&& (btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() < rect.position.x
									+ rect.position.width
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() > rect.position.y
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() < rect.position.y
									+ rect.position.height
							&& !editar) {
						adicionar = false;
						editRect = rect.position;
						editar = true;
						break;
					}
				}
			}
			if (adicionar && !editar && objsAtual == 0) {
				ground.add(new Rectangle(
						((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX()) / tileSize * tileSize,
						((btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY()) / tileSize * tileSize, 32,
						32));
			}
			if (adicionar && !editar && objsAtual == 1) {
				door.add(new Rectangle(
						((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX()) / tileSize * tileSize,
						((btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY()) / tileSize * tileSize, 32,
						32));
			}
			if (adicionar && !editar && objsAtual == 2) {
				if (inimigoAtual == 0) {
					enemy.add(new Slime(
							(((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX()) / tileSize)
									* tileSize,
							(((btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY()) / tileSize)
									* tileSize,
							16, 16));
				}
				if (inimigoAtual == 1) {
					enemy.add(new Zombie(
							(((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX()) / tileSize)
									* tileSize,
							(((btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY()) / tileSize)
									* tileSize,
							16, 16));
				}
			}
			if (adicionar && editar) {
				editRect = null;
				editar = false;
			}
		}
	}

	public void mousePressed(MouseEvent btn) {
		if (btn.getButton() == MouseEvent.BUTTON1 && editRect != null) {
			if (distance((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX(),
					(btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY(), editRect.x - 6,
					editRect.y - 6) <= 12) {
				editPos = true;
			}
			if (distance((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX(),
					(btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY(), editRect.x + editRect.width - 6,
					editRect.y + editRect.height - 6) <= 12) {
				editSize = true;

			}
		}
		if (btn.getButton() == MouseEvent.BUTTON3) {
			editRect = null;
			if (objsAtual == 0) {
				for (Rectangle rect : ground) {
					if ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() > rect.x
							&& (btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() < rect.x + rect.width
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() > rect.y
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() < rect.y
									+ rect.height) {
						ground.remove(rect);
					}
				}
			} else if (objsAtual == 1) {
				for (Rectangle rect : door) {
					if ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() > rect.x
							&& (btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() < rect.x + rect.width
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() > rect.y
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() < rect.y
									+ rect.height) {
						door.remove(rect);
					}
				}
			} else if (objsAtual == 2) {
				for (Enemy rect : enemy) {
					if ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() > rect.position.x
							&& (btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX() < rect.position.x
									+ rect.position.width
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() > rect.position.y
							&& (btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY() < rect.position.y
									+ rect.position.height) {
						enemy.remove(rect);
					}
				}
			}
		}
	}

	@Override
	public void mouseReleased(MouseEvent btn) {
		// TODO Auto-generated method stub
		if (btn.getButton() == MouseEvent.BUTTON1) {
			editPos = false;
			editSize = false;
		}

	}

	public void mouseDragged(MouseEvent btn) {
		if (editPos) {
			editRect.x = ((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX()) / tileSize * tileSize;
			editRect.y = ((btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY()) / tileSize * tileSize;
		}
		if (editSize) {
			editRect.width = (((btn.getX() / GamePanel.SCALE) + Camera.getInstance().getCameraX()) - editRect.x)
					/ tileSize * tileSize;
			editRect.height = (((btn.getY() / GamePanel.SCALE) + Camera.getInstance().getCameraY()) - editRect.y)
					/ tileSize * tileSize;
		}
	}

	public void mouseMoved(MouseEvent e) {
	}

}
