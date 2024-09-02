// User Profile Class
package userprofilelogger;

import java.util.Scanner;

public class UserProfileDriver {

public static void main(String[] args) { 
		
		//read input
		Scanner input = new Scanner(System.in);
		UserProfile[] everyoneInfo = new UserProfile[3];
		
		
		for (int i = 0; i < 3; i++) {	
			System.out.print("Enter Name: ");
			String name = input.nextLine();
			
			System.out.print("Enter Age (must be an integer): ");
			int age = input.nextInt();
			input.nextLine(); // Fixes newline error in formatting
			
			System.out.print("Enter Gender: ");
			String gender = input.nextLine();
			
			System.out.print("Enter Nationality: ");
			String nationality = input.nextLine();
			
			if (i < 2) { // Removes repeated third statement
			System.out.println("\nFill out next person's info.");
			}
			
			// Creates new UserProfile object for each everyoneInfo[i]
			everyoneInfo[i] = new UserProfile(name, age, gender, nationality);	
			
		}
	
		input.close();
			
		for (int i = 0; i < 3; i++) {
			System.out.println("\nPerson " + (i + 1) + "'s name is: "+ everyoneInfo[i].getName());
			System.out.println("Person " + (i + 1) + "'s age is: "+ everyoneInfo[i].getAge());
			System.out.println("Person " + (i + 1) + "'s gender is: "+ everyoneInfo[i].getGender());
			System.out.println("Person " + (i + 1) + "'s nationality is: "+ everyoneInfo[i].getNationality());
		}
			
	}

}
