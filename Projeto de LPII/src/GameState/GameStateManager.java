package GameState;

import java.awt.Graphics2D;
import java.awt.event.MouseEvent;

import Exception.ValorNuloException;

/**
 * Classe responsável por gerenciar as telas do jogo
 * 
 * @author canoi Pattern: Singleton
 */
public class GameStateManager {

	/**
	 * Nó raiz
	 */
	public Node raiz = null;

	/**
	 * Instância
	 */
	private static GameStateManager instance;
	/**
	 * Nó contendo fase atual
	 */
	private Node currentState;

	private GameStateManager() {
		currentState = new Node(new MenuState());
		currentState.setLeft(new Node(new EditorState()));

	}

	/**
	 * Retorna a instância do objeto
	 * 
	 * @return GameStateManager - instance
	 */
	public static GameStateManager getInstance() {
		if (instance == null)
			instance = new GameStateManager();
		return instance;
	}

	/**
	 * Retorna a raiz
	 * 
	 * @return Node - raiz
	 */
	public Node getRaiz() {
		return raiz;
	}

	public void inserir(GameState valor) throws ValorNuloException {
		if (valor == null) {
			throw new ValorNuloException("O valor colocado é inválido");
		} else {
			inserir(raiz, valor);
		}
	}

	/**
	 * Insere uma nova fase na árvore de fases
	 * 
	 * @param node
	 *            - Nó atual que estamos navegando
	 * @param valor
	 *            - Fase atual que desejamos adicionar na árvore
	 */
	private Node inserir(Node node, GameState valor) {
		if (raiz == null) {
			Node n = new Node(valor);
			raiz = n;
			raiz.getValue().node = n;
			return node;
		} else {
			if (valor.getID() < node.getValue().getID()) {
				if (node.getLeft() != null) {
					inserir(node.getLeft(), valor);
				} else {
					node.setLeft(new Node(valor));
					node.getLeft().setPai(node);
					node.getLeft().getValue().node = node.getLeft();
					System.out.println(node.getValue().getID() + " -> " + node.getLeft().getValue().getID());
					System.out.println(node.getLeft().getValue().getID() + " <- " + node.getLeft().getPai().getValue().getID());
				}
			} else if (valor.getID() > node.getValue().getID()) {
				if (node.getRight() != null) {
					inserir(node.getRight(), valor);
				} else {
					node.setRight(new Node(valor));
					node.getRight().setPai(node);
					node.getRight().getValue().node = node.getRight();
					System.out.println(node.getValue().getID() + " -> " + node.getRight().getValue().getID());
					System.out.println(node.getRight().getValue().getID() + " <- " + node.getRight().getPai().getValue().getID());
				}
			}
		}
		// node = balance(node);
		return node;
	}

	/**
	 * Retorna a altura do nó
	 * 
	 * @param t
	 *            - Nó que queremos pegar a altura
	 * @return int - altura
	 */
	private int height(Node t) {
		return t == null ? -1 : t.getHeight();
	}

	/**
	 * Retorna o maior entre dois valorea
	 * 
	 * @param lh
	 *            - Valor 1
	 * @param rh
	 *            - Valor 2
	 * @return inr
	 */
	private int max(int lh, int rh) {
		return lh > rh ? lh : rh;
	}

	/**
	 * Retorna o fator de balanceamento de um nó
	 * 
	 * @param node
	 *            - Nó que queremos pegar o fator de balanceamento
	 * @return int
	 */
	private int getFactor(Node node) {
		return height(node.getLeft()) - height(node.getRight());
	}

	/**
	 * Método que faz o balanceamento do nó
	 * 
	 * @param node
	 *            - Nó que queremos balancear
	 * @return Node - node
	 */
	private Node balance(Node node) {
		if (getFactor(node) == 2) {
			if (getFactor(node.getLeft()) > 0)
				node = rightRotation(node);
			else
				node = doubleRightRotation(node);
		} else if (getFactor(node) == -2) {
			if (getFactor(node.getRight()) < 0)
				node = leftRotation(node);
			else
				node = doubleLeftRotation(node);
		}
		node.setHeight(max(height(node.getLeft()), height(node.getRight())) + 1);
		return node;
	}

	/**
	 * Rotaciona a árvore para a direita
	 * 
	 * @param node
	 *            - Nó que queremos rotacionar
	 * @return
	 */
	private Node rightRotation(Node node) {
		Node aux = node.getLeft();
		node.setLeft(aux.getRight());
		// if (aux.getRight() != null)
		// aux.getRight().setPai(node);
		aux.setRight(node);
		// aux.setPai(node.getPai());
		// node.setPai(aux);
		node.setHeight(max(height(node.getLeft()), height(node.getRight())) + 1);
		aux.setHeight(max(height(aux.getLeft()), height(aux.getRight())) + 1);
		return aux;
	}

	/**
	 * Rotaciona a árvore para a esquerda
	 * 
	 * @param node
	 *            - Nó que queremos rotacionar
	 * @return Node - node
	 */
	private Node leftRotation(Node node) {
		Node aux = node.getRight();
		node.setRight(aux.getLeft());
		// if (aux.getLeft() != null)
		// aux.getLeft().setPai(node);
		aux.setLeft(node);
		// aux.setPai(node.getPai());
		// node.setPai(aux);
		node.setHeight(max(height(node.getLeft()), height(node.getRight())) + 1);
		aux.setHeight(max(height(aux.getLeft()), height(aux.getRight())) + 1);
		return aux;
	}

	/**
	 * Faz uma rotação dupla para a direita
	 * 
	 * @param node
	 *            - Nó que queremos rotacionar
	 * @return Node - node
	 */
	private Node doubleRightRotation(Node node) {
		node.setLeft(leftRotation(node.getLeft()));
		return rightRotation(node);
	}

	/**
	 * Faz uma rotação dupla para a esquerda
	 * 
	 * @param node
	 *            - Nó que queremos rotacionar
	 * @return Node - node
	 */
	private Node doubleLeftRotation(Node node) {
		node.setRight(rightRotation(node.getRight()));
		return leftRotation(node);
	}

	public void preOrdem() {
		preOrdem(raiz);
	}

	public void preOrdem(Node node) {
		if (node != null) {
			System.out.println(node.getValue().getID());
			preOrdem(node.getLeft());
			preOrdem(node.getRight());
		}
	}

	/**
	 * Procura o nó da árvore que contém a fase que queremos achar
	 * 
	 * @param valor
	 *            - Fase que queremos encontrar na árvore
	 * @return Node
	 */
	public Node procurar(GameState valor) {
		return procurar(this.raiz, valor);
	}

	public Node procurar(Node node, GameState valor) {
		if (node.getValue().getID() == valor.getID())
			return node;
		else {
			if (valor.getID() < node.getValue().getID())
				return procurar(node.getLeft(), valor);
			else if (valor.getID() > node.getValue().getID())
				return procurar(node.getRight(), valor);
		}
		return null;
	}

	/**
	 * Muda a fase atual
	 * 
	 * @param state
	 */
	public void setState(Node state) {
		currentState = state;
		currentState.getValue().init();
	}

	/**
	 * Retorna a fase atual
	 * 
	 * @return Node - currentState
	 */
	public Node getCurrentState() {
		return currentState;
	}

	/**
	 * Muda a fase atual para a fase contida no nó direito dela
	 */
	public void goToRight() {
		if (currentState.getRight() == null) {

		} else {
			currentState = currentState.getRight();
			currentState.getValue().init();
		}

	}

	/**
	 * Muda a fase atual para a fase contida no nó esquerdo dela
	 */
	public void goToLeft() {
		if (currentState.getLeft() == null) {
		} else {
			currentState = currentState.getLeft();
			currentState.getValue().init();
		}
	}

	/**
	 * Muda a fase atual para a fase pai dela
	 */
	public void goToPai() {

		if (currentState.getPai() == null) {
		} else {
			currentState = currentState.getPai();
			currentState.getValue().init();
		}
	}

	/**
	 * Atualiza a fase atual
	 */
	public void update() {
		currentState.getValue().update();
	}

	/**
	 * Desenha tudo que estiver na fase atual
	 * 
	 * @param g
	 */
	public void draw(Graphics2D g) {
		currentState.getValue().draw(g);
	}

	public void keyPressed(int k) {
		currentState.getValue().keyPressed(k);
	}

	public void keyReleased(int k) {
		currentState.getValue().keyReleased(k);
	}

	public void mousePressed(MouseEvent btn) {
		currentState.getValue().mousePressed(btn);
	}

	public void mouseReleased(MouseEvent btn) {
		currentState.getValue().mouseReleased(btn);
	}

	public void mouseClicked(MouseEvent btn) {
		currentState.getValue().mouseClicked(btn);
	}

	public void mouseDragged(MouseEvent btn) {
		currentState.getValue().mouseDragged(btn);
	}

	public void mouseMoved(MouseEvent btn) {
		currentState.getValue().mouseMoved(btn);
	}
}
