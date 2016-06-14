package Camera;

import Aplicacao.GamePanel;
import GameState.GameStateManager;

/**
 * Classe que representa a câmera do jogo
 * Pattern: Singleton
 * @author canoi
 */
public class Camera {

	/**
	 *  Posições X e Y da câmera
	 */
	private static int cameraX;
	private static int cameraY;
	
	/**
	 *  Instância da câmera
	 */
	private static Camera instance;
	
	private Camera(){}
	
	/**
	 * Pega  a instância da câmera
	 * Caso esteja nula, cria uma nova
	 * @return Camera - instance
	 */
	public static Camera getInstance()
	{
		if(instance == null)
			instance = new Camera();
		
		return instance;
	}
	
	/**
	 * Retorna a posição X da câmera
	 * @return int - X
	 */
	public int getCameraX()
	{
		return cameraX;
	}
	
	/**
	 * Retorna a posição Y da câmera
	 * @return int - Y
	 */
	public int getCameraY()
	{
		return cameraY;
	}
	
	/**
	 * Método responsável por atualizar a posição da camêra, a fazendo ficar no limite da tela
	 */
	public void update()
	{
		cameraX = Math.max(0, Math.min(cameraX, GameStateManager.getInstance().getCurrentState().getValue().getRoomWidth() - GamePanel.WIDTH));
		cameraY = Math.max(0,Math.min(cameraY, GameStateManager.getInstance().getCurrentState().getValue().getRoomHeight() - GamePanel.HEIGHT));
	}
	
	/**
	 * Muda a posição X da câmera
	 * @param cameraX - novo valor X
	 */
	public void setCameraX(int cameraX)
	{
		this.cameraX =  cameraX;
	}
	
	/**
	 * Muda posição Y da câmera
	 * @param cameraY
	 */
	public void setCameraY(int cameraY)
	{
		this.cameraY =  cameraY;
	}

}
