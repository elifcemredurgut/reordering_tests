package src;


public class Pen {
	
	public int drawRectangle(Rectangle r) {
		return r.getHeight() * r.getWidth();
	}
	
	public double drawCircle(Circle c) {
		return c.getRadius() * c.getRadius() * Math.PI; 
	}
	
	public void changeColorRectangle(String color, Rectangle r) {
		r.setColor(color);
		System.out.println("Rectangle color has been changed to " + color + ".");
	}
	
	public void changeColorCircle(String color, Circle c) {
		c.setColor(color);
		System.out.println("Circle color has been changed to " + color + ".");
	}
}
