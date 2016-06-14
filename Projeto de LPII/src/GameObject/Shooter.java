package GameObject;

import java.io.IOException;
import java.util.Random;

import javax.imageio.ImageIO;

public class Shooter extends Enemy {

	public Shooter(int x, int y, int width, int height) {
		super(x, y, width, height);
		// TODO Auto-generated constructor stub
		init();
	}

	public void init() {
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/Char/shooter.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		addAnimation("idle", 0, 0, 16, 16, 1);
		type = "shooter";

		setColBox(0, 2, 15, 11);
		hspeed = 0;

		frameTimeInit = 0.07f;

	}

	public void update() {

	}

	public void draw(java.awt.Graphics2D g) {
		super.draw(g);
	}

	public void keyPressed(int k) {
	}

	public void keyReleases(int k) {
	}

}
