package src;

public class Rectangle {
	private int width, height;
	private String color;
	
	public Rectangle() {
		
	}
	
	public Rectangle(String color, int height, int width) {
		this.color = color;
		this.height = height;
		this.width = width;
	}
	
	void setColor(String color) {
		this.color = color;
	}
	
	String getColor() {
		return this.color;
	}
	
	int getWidth() {
		return this.width;
	}
	
	int getHeight() {
		return this.height;
	}
	
	void setHeight(int h) {
		this.height = h;
	}
	
	void setWidth(int w) {
		this.width = w;
	}
}
