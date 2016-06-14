package GameState;

/**
 * Classe que representa um nó da fase
 * 
 * @author canoi
 *
 */
public class Node {

	/**
	 * Fase
	 */
	private GameState value;
	/**
	 * Nó pai
	 */
	private Node pai = null;
	/**
	 * Nó da esquerda
	 */
	private Node left = null;
	/**
	 * Nó da direita
	 */
	private Node right = null;

	/**
	 * Altura da árvore
	 */
	private int height;

	public Node() {
	}

	public Node(GameState value) {
		this.value = value;
		left = null;
		right = null;
		height = 0;
	}

	/**
	 * Retorna o valor da fase guardado no nó
	 * 
	 * @return GameState - value
	 */
	public GameState getValue() {
		return value;
	}

	/**
	 * Muda o valor da fase guardado no nó
	 * 
	 * @param value
	 *            - novo valor da fase
	 */
	public void setValue(GameState value) {
		this.value = value;
	}

	/**
	 * Testa se há nó na esquerda
	 * 
	 * @return boolean
	 */
	public boolean hasLeft() {
		if (left != null)
			return true;
		return false;
	}

	/**
	 * Testa se há nó na direita
	 * 
	 * @return boolean
	 */
	public boolean hasRight() {
		if (right != null)
			return true;
		return false;
	}

	public Node getPai() {
		return pai;
	}

	public Node getLeft() {
		return left;
	}

	public Node getRight() {
		return right;
	}

	public void setPai(Node pai) {
		this.pai = pai;
	}

	public void setRight(Node right) {
		this.right = right;
	}

	public void setLeft(Node left) {
		this.left = left;
	}
	
	public int getHeight(){
		return height;
	}
	
	public void setHeight(int height){
		this.height = height;
	}
}
