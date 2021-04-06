package rjm.romek.finance.alert;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.TreeMap;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;
import rjm.romek.finance.rule.PriceAboveRule;

class AlertTest {

  @Test
  public void shouldTrigger() {
    Alert alert = new Alert(new PriceAboveRule(MonetaryDateUtil.getDollars(10)), 2);

    assertTrue(alert.checkTrigger(MonetaryDateUtil.createDataPoints("USD", 10, 11, 12)));
  }

  @Test
  public void shouldNotTriggerOnPastEvents() {
    Alert alert = new Alert(new PriceAboveRule(MonetaryDateUtil.getDollars(10)), 2);

    assertFalse(alert.checkTrigger(MonetaryDateUtil.createDataPoints("USD", 11, 12, 10)));
  }

  @Test
  public void shouldNotTrigger() {
    assertFalse(new Alert().checkTrigger(new TreeMap<>()));
  }
}