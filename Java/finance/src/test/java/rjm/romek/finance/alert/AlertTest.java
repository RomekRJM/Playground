package rjm.romek.finance.alert;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Collections;
import java.util.Date;
import java.util.LinkedHashMap;
import java.util.Map;
import javax.money.MonetaryAmount;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.DateUtil;
import rjm.romek.finance.MonetaryUtil;
import rjm.romek.finance.rule.PriceAboveRule;

class AlertTest {

  @Test
  public void shouldTrigger() {
    Alert alert = new Alert(new PriceAboveRule(MonetaryUtil.getDollars(10)), 2);
    Map<Date, MonetaryAmount> map = Map.of(
        DateUtil.createDate(10, 10, 10), MonetaryUtil.getDollars(10).getMonetaryAmount(),
        DateUtil.createDate(10, 10, 11), MonetaryUtil.getDollars(11).getMonetaryAmount(),
        DateUtil.createDate(10, 10, 12), MonetaryUtil.getDollars(12).getMonetaryAmount()
    );

    Map<Date, MonetaryAmount> twoActionableEventsAtTheEnd = new LinkedHashMap(map);
    assertTrue(alert.checkTrigger(twoActionableEventsAtTheEnd));
  }

  @Test
  public void shouldNotTriggerOnPastEvents() {
    Alert alert = new Alert(new PriceAboveRule(MonetaryUtil.getDollars(10)), 2);
    Map<Date, MonetaryAmount> map = Map.of(
        DateUtil.createDate(10, 10, 10), MonetaryUtil.getDollars(11).getMonetaryAmount(),
        DateUtil.createDate(10, 10, 11), MonetaryUtil.getDollars(12).getMonetaryAmount(),
        DateUtil.createDate(10, 10, 12), MonetaryUtil.getDollars(10).getMonetaryAmount()
    );

    Map<Date, MonetaryAmount> twoActionableEventsAtTheEnd = new LinkedHashMap(map);
    assertFalse(alert.checkTrigger(twoActionableEventsAtTheEnd));
  }

  @Test
  public void shoulNotTrigger() {
    assertFalse(new Alert().checkTrigger(Collections.emptyMap()));
  }
}