package userprofilelogger;

// Public User Profile Class
public class UserProfile{

	// 4 Parameters
	private String name;
	private int age;
	private String gender;
	private String nationality;
	

	// Constructor
	public UserProfile(String name, int age, String gender, String nationality) {
		this.name = name;
		this.age = age;
		this.nationality = nationality;
		this.gender = gender;
	}
	
	
	// Getter
	public String getName() {
		return name;
	}
	
	public int getAge() {
		return age;
	}
	
	public String getGender() {
		return gender;
	}
	
	
	public String getNationality() {
		return nationality;
	}
	
	
	// Setter
	public void setName(String name) {
		this.name = name;
	}
	
	public void setAge(int age) {
		this.age = age;
	}
	
	public void setGender(String gender) {
		this.gender = gender;
	}
	
	public void setNationality(String nationality) {
		this.nationality = nationality;
	}
	
	
}