public class PumpkinSpice extends CondimentDecorator {
    public PumpkinSpice(Beverage beverage) { this.beverage = beverage; }

    public  String getDescription () { return beverage.getDescription() + ", PumpkinSpice"; }

    public double cost() { return .5 + beverage.cost(); }
}