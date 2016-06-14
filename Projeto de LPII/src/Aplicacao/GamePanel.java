package Aplicacao;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.util.Random;

import javax.swing.JPanel;

import Camera.Camera;
import Exception.ValorNuloException;
import GameState.*;

/**
 * Classe que representa a tela do jogo, herda de JPanel
 * 
 * @author canoi
 *
 */
public class GamePanel extends JPanel implements Runnable, KeyListener, MouseListener, MouseMotionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * Dimensões
	 */
	public static final int WIDTH = 160;
	public static final int HEIGHT = 144;
	public static final int SCALE = 4;

	/**
	 * GameTime
	 */
	private Thread thread;
	private boolean running;
	private int FPS = 60;
	private long targetTime = 1000 / FPS;

	/**
	 * Images
	 */
	private BufferedImage image;
	private Graphics2D g;

	/**
	 * Game State Manager
	 */
	private GameStateManager gsm;

	public GamePanel() {
		super();

		setPreferredSize(new Dimension(WIDTH * SCALE, HEIGHT * SCALE));
		setFocusable(true);
		requestFocus();

	}

	public void addNotify() {
		super.addNotify();
		if (thread == null) {
			thread = new Thread(this);
			addKeyListener(this);
			addMouseListener(this);
			addMouseMotionListener(this);
			thread.start();
		}
	}

	/**
	 * Método que inicia as configurações iniciais necessárias do jogo
	 */
	public void init() {
		image = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
		g = (Graphics2D) image.getGraphics();

		running = true;
		gsm = GameStateManager.getInstance();
		AllStates as = AllStates.getInstance();
		
		gsm.raiz = null;
		while (AllStates.getInstance().hasNext()) {
			try {
				GameStateManager.getInstance().inserir(AllStates.getInstance().getNext());
			} catch (ValorNuloException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		Node node = gsm.getRaiz();
		while (node.hasLeft() || node.hasRight()) {
			int rand = new Random().nextInt(10);
			if (rand < 5 && node.hasLeft())
				node = node.getLeft();
			else if (rand >= 5 && node.hasRight())
				node = node.getRight();
		}
		node.getValue().setChest(true);

		gsm.preOrdem();
	}

	/**
	 * Método que atualiza posições e animações da tela atual Também atualiza a
	 * positção da câmera
	 */
	public void update() {
		gsm.update();
		Camera.getInstance().update();
	}

	/**
	 * Método que desenha a tela atual no JPanel
	 */
	public void draw() {
		// g.setColor(Color.WHITE);
		g.translate(-Camera.getInstance().getCameraX(), -Camera.getInstance().getCameraY());
		g.clearRect(0, 0, WIDTH, HEIGHT);
		gsm.draw(g);
		g.translate(Camera.getInstance().getCameraX(), Camera.getInstance().getCameraY());
	}

	/*
	 * Método para desenha tudo no tamanho certo
	 */
	public void drawToScreen() {
		Graphics g2 = getGraphics();
		g2.drawImage(image, 0, 0, WIDTH * SCALE, HEIGHT * SCALE, null);
		g2.dispose();
	}

	/**
	 * Game Loop, é esse método que faz o jogo rodar a 60 quadros por segundos,
	 * a partir do uso de Threads. Chama os métodos de init(),update, draw() e
	 * drawToScreen()
	 */
	public void run() {
		init();

		long start;
		long elapsed;
		long wait;

		while (running) {
			start = System.nanoTime();

			update();
			draw();
			drawToScreen();

			elapsed = System.nanoTime() - start;
			wait = targetTime - elapsed / 10000000;

			if (wait < 0) {
				wait = 5;
			}

			try {
				Thread.sleep(wait);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public void mouseDragged(MouseEvent arg0) {
		gsm.mouseDragged(arg0);
	}

	public void mouseMoved(MouseEvent arg0) {
		gsm.mouseMoved(arg0);
	}

	public void mouseClicked(MouseEvent arg0) {
		gsm.mouseClicked(arg0);
	}

	public void mouseEntered(MouseEvent arg0) {
	}

	public void mouseExited(MouseEvent arg0) {
	}

	public void mousePressed(MouseEvent arg0) {
		gsm.mousePressed(arg0);
	}

	public void mouseReleased(MouseEvent arg0) {
		gsm.mouseReleased(arg0);
	}

	public void keyPressed(KeyEvent arg0) {
		gsm.keyPressed(arg0.getKeyCode());
	}

	public void keyReleased(KeyEvent arg0) {
		gsm.keyReleased(arg0.getKeyCode());
	}

	public void keyTyped(KeyEvent arg0) {
	}

}
