public class MyClass {

    // Create a private static variable to reference ourt one-and-only
    // instnace of MyClass
    private static MyClass uniqueInstance;

    // static getInstance() method
    public static MyClass getInstance() {
        // If uniqueInstance is null, go ahead and create a new MyClass instance
        // Otherwise, it means we already have a MyClass instance,
        // so do not create any more!!
        return new MyClass();
    }

    // Constructor Method
    private MyClass(){

    }
}
