import org.junit.Test;
import static org.junit.Assert.*;

public class TipCalculatorTest {

    @Test
    public void testCalculateTip20Percent() {
        TipCalculator calculator = new TipCalculator();
        double result = calculator.calculateTip(100.00, 20);
        assertEquals("20% Tip Calculation Error", 20.00, result, 0.01);
    }

    @Test
    public void testCalculateTip1Percent() {
        TipCalculator calculator = new TipCalculator();
        double result = calculator.calculateTip(1, 1);
        assertEquals("1% Tip Calculation Error", 0.01, result, 0.01);
    }
}
