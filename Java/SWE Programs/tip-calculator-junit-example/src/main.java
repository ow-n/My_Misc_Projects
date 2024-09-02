public class main {

    public static void main(String[] args) {
        //MyClass mc1 = MyClass.getInstance();

        // No Longer works bc private now:
        //DatabaseConnection db1 = new DatabaseConnection("Oracle Connection");
        //DatabaseConnection db2 = new DatabaseConnection("MySQL Connection");

        DatabaseConnection db1 = DatabaseConnection.getInstance("Oracle Connection");
        DatabaseConnection db2 = DatabaseConnection.getInstance("MySql Connection");

        System.out.println("db1: " + db1);
        System.out.println("db2: " + db2);
    }
}
