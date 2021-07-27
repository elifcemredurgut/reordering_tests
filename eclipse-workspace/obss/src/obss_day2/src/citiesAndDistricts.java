package src;
import java.util.Scanner;

public class citiesAndDistricts {
	public static void main(String args[]) {
		
		Scanner input = new Scanner(System.in);
		System.out.print("Enter the number of cities: ");
		int num = input.nextInt();
		String[][] list = new String[num][4];
		
		for(int i = 0; i < num; i++) {
			System.out.print("Enter the city name: ");
			String city = input.next();
			list[i][0] = city;
			
			System.out.print("Enter 3 districts: ");
			String districtInput = input.next();

	        districtInput += input.nextLine();
			String[] districts = districtInput.split(" ");
			
			for(int j = 0; j < 3; j++) {
				list[i][j+1] = districts[j];
			}
		}
		
		for(int i = 0; i < num; i++) {
			System.out.print(list[i][0] + ": ");
			for(int j = 0; j < 3; j++ ) {
				System.out.print(list[i][j+1] + " ");
			}
			System.out.print("\n");
		}
		
		input.close();
	}
	
}
