package GameState;

import java.util.ArrayList;
import java.util.Random;

/**
 * Classe responsável por inicialmente guardar todas as fases do jogo, e dar a
 * elas IDS randômicos
 * 
 * @author canoi Pattern: Singleton
 */
public class AllStates {

	/**
	 * Lista contendo as fases do jogo
	 */
	private ArrayList<GameState> states;
	/**
	 * Lista contendo os ids das fases do jogo
	 */
	private ArrayList<Integer> ids;

	/**
	 * Instância
	 */
	private static AllStates instance;

	private AllStates() {
		states = new ArrayList<GameState>();
		ids = new ArrayList<Integer>();

		for (int i = 0; i < 6; i++) {
			inserir(new LevelState(new Random().nextInt(3) + 1));
		}
	}

	/**
	 * Retorna a instância do objeto
	 * 
	 * @return AllStates - instance
	 */
	public static AllStates getInstance() {
		if (instance == null)
			instance = new AllStates();
		return instance;
	}

	/**
	 * Insere uma nova fase na lista de fases e dá um novo id para ela
	 * 
	 * @param state
	 */
	public void inserir(GameState state) {
		int id = new Random().nextInt(100);
		while (ids.contains(id)) {
			id = new Random().nextInt(100);
		}
		state.setID(id);
		ids.add(id);
		states.add(state);
	}

	/**
	 * Retorna a próxima fase da lista, e depois a remove
	 * 
	 * @return GameState
	 */
	public GameState getNext() {
		if (states.get(0) != null) {
			GameState newState = states.get(0);
			states.remove(0);
			return newState;
		}
		return null;
	}

	/**
	 * Testa se ainda existem fases na lista
	 * 
	 * @return boolen
	 */
	public boolean hasNext() {
		if (states.size() != 0) {
			return true;
		}
		return false;
	}

}
