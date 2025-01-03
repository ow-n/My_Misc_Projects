public class DatabaseConnection {
    private String connectionName;

    private static DatabaseConnection uniqueInstance; // unique instance of this class

    public static DatabaseConnection getInstance(String inConnectionName) { // static so can call without object
        // Is there already a database connection?
        if (uniqueInstance == null) {
            uniqueInstance = new DatabaseConnection(inConnectionName);
        }
        // return 1 and only database connection  that exists
        return uniqueInstance;
    }

    // Constructor
    private DatabaseConnection(String inConnectionName) {
        connectionName = inConnectionName;
        System.out.println("New Database Connection Created");
    }

    public String toString() {
        return connectionName;
    }

}

// Standard Approach
/*    private String connectionName;
    public  DatabaseConnection(String inConnectionName) {
        connectionName = inConnectionName;
        System.out.println("New Database Connection Created");
    }

    public String toString() {
        return connectionName;
    } */