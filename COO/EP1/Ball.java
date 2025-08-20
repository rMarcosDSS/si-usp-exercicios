import java.awt.*;

/**
	Esta classe representa a bola usada no jogo. A classe princial do jogo (Pong)
	instancia um objeto deste tipo quando a execução é iniciada.
*/

public class Ball {

	/**
	 Construtor da classe Ball. Observe que quem invoca o construtor desta classe define a velocidade da bola 
	 (em pixels por millisegundo), mas não define a direção deste movimento. A direção do movimento é determinada 
	 aleatóriamente pelo construtor.
	 
	 @param cx coordenada x da posição inicial da bola (centro do retangulo que a representa).
	 @param cy coordenada y da posição inicial da bola (centro do retangulo que a representa).
	 @param width largura do retangulo que representa a bola.
	 @param height altura do retangulo que representa a bola.
	 @param color cor da bola.
	 @param speed velocidade da bola (em pixels por millisegundo).
	 */
	
	private double cx, cy;
	private double width, height;
	private Color color;
	private double speed;
	private double dx, dy;

	public Ball(double cx, double cy, double width, double height, Color color, double speed){
		this.cx = cx;
        this.cy = cy;
        this.width = width;
        this.height = height;
        this.color = color;
        this.speed = speed;
        setRandomDirection();
	}

	private void setRandomDirection() {
        double angle;
        do {
            angle = Math.random() * Math.PI / 3 - Math.PI / 6; 
        } while (Math.abs(angle) < 0.1); 

        if (Math.random() < 0.5) {
            angle = Math.PI - angle;
        }

        this.dx = speed * Math.cos(angle);
        this.dy = speed * Math.sin(angle);
    }



	/**
		Método chamado sempre que a bola precisa ser (re)desenhada.
	*/

	public void draw(){

		GameLib.setColor(color);
        GameLib.fillRect(cx - width / 2, cy - height / 2, width, height);
		
	}

	/**
		Método chamado quando o estado (posição) da bola precisa ser atualizado.
		
		@param delta quantidade de millisegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/

	public void update(long delta){
		cx += dx * delta;
        cy += dy * delta;
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com um jogador.
	
		@param playerId uma string cujo conteúdo identifica um dos jogadores.
	*/

	public void onPlayerCollision(String playerId){
		dx = -dx;
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com uma parede.

		@param wallId uma string cujo conteúdo identifica uma das paredes da quadra.
	*/

	public void onWallCollision(String wallId){
		if ((wallId.contains("Top")) || (wallId.contains("Bottom"))) {
			dy = -dy;
		} else {
			cx = 400; 
			cy = 300; 
			setRandomDirection();
		}
	}

	/**
		Método que verifica se houve colisão da bola com uma parede.

		@param wall referência para uma instância de Wall contra a qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/
	
	public boolean checkCollision(Wall wall){
		if (cx - width / 2 < wall.getCx() + wall.getWidth() / 2 &&
                cx + width / 2 > wall.getCx() - wall.getWidth() / 2 &&
                cy - height / 2 < wall.getCy() + wall.getHeight() / 2 &&
                cy + height / 2 > wall.getCy() - wall.getHeight() / 2) {
            return true;
        }
        return false;
	}

	/**
		Método que verifica se houve colisão da bola com um jogador.

		@param player referência para uma instância de Player contra o qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/	

	public boolean checkCollision(Player player){
		double ballLeft = cx - width / 2;
		double ballRight = cx + width / 2;
		double ballTop = cy - height / 2;
		double ballBottom = cy + height / 2;

		double playerLeft = player.getCx() - player.getWidth() / 2;
		double playerRight = player.getCx() + player.getWidth() / 2;
		double playerTop = player.getCy() - player.getHeight() / 2;
		double playerBottom = player.getCy() + player.getHeight() / 2;

		if (ballRight > playerLeft && ballLeft < playerRight &&
			ballBottom > playerTop && ballTop < playerBottom) {
			return true;
		}

		return false;
	}

	/**
		Método que devolve a coordenada x do centro do retângulo que representa a bola.
		@return o valor double da coordenada x.
	*/
	
	public double getCx(){

		return cx;
	}

	/**
		Método que devolve a coordenada y do centro do retângulo que representa a bola.
		@return o valor double da coordenada y.
	*/

	public double getCy(){

		return cy;
	}

	/**
		Método que devolve a velocidade da bola.
		@return o valor double da velocidade.

	*/

	public double getSpeed(){

		return speed;
	}

}
