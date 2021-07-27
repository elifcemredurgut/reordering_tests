package src;

public class Circle {
	private String color;
	private int radius;
	
	public Circle(){
		
	}
	
	public Circle(String color, int radius) {
		this.color = color;
		this.radius = radius;
	}
	
	void setColor(String color) {
		this.color = color;
	}
	
	String getColor() {
		return this.color;
	}
	
	int getRadius() {
		return this.radius;
	}
	
	void setRadius(int radius) {
		this.radius = radius;
	}
}
