public class Main {
    public static void main(String[] args) {
        ChocolateBoiler controller1 = ChocolateBoiler.getInstance();

        controller1.fill();
        controller1.boil();
        controller1.drain();
        controller1.drain();

        //ChocolateBoiler controller2 = new ChocolateBoiler();
        ChocolateBoiler controller2 = ChocolateBoiler.getInstance();

        controller1.fill();
        System.out.println("Testing Controller 2...");
        controller2.fill();
        controller2.boil();
        controller2.drain();
    }
}
