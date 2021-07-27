package src;

public class Main {
	public static void main(String args[]){  
		
		Pen pen = new Pen();
		
		Circle c = new Circle("purple", 2);
		c.setRadius(2);
		
		Rectangle r = new Rectangle("green", 5 ,10);
		
		
		pen.changeColorCircle("red", c);
		pen.changeColorRectangle("blue", r);
		
		System.out.println("Area of the circle: " + pen.drawCircle(c));
		System.out.println("Area of the rectangle: " + pen.drawRectangle(r));
		
	}
}
