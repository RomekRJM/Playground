package rjm.romek.finance.alert;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.MonetaryDateUtil;
import rjm.romek.finance.datapoint.model.DataPoint;
import rjm.romek.finance.rule.PriceAboveRule;

class AlertTest {

  @Test
  public void shouldTriggerOnLast2Elements() {
    Alert alert = new Alert(new PriceAboveRule(MonetaryDateUtil.getDollars(10)), 2);
    List<DataPoint> dataPoints = MonetaryDateUtil.createDataPoints("USD", 0, 0, 13, 13, 10, 11, 12);
    List<DataPoint> expected = new ArrayList<>();
    expected.add(dataPoints.get(4));
    expected.add(dataPoints.get(3));
    assertEquals(expected, alert.getRecentDataPointsTriggeringAlert(dataPoints));
  }

  @Test
  public void shouldNotTriggerWhenNotEnoughPoints() {
    Alert alert = new Alert(new PriceAboveRule(MonetaryDateUtil.getDollars(10)), 2);
    List<DataPoint> dataPoints = MonetaryDateUtil.createDataPoints("USD", 0, 0, 11, 12, 10);
    assertEquals(Collections.emptyList(), alert.getRecentDataPointsTriggeringAlert(dataPoints));
  }

  @Test
  public void shouldNotTriggerOnEmptyList() {
    assertEquals(Collections.emptyList(), new Alert().getRecentDataPointsTriggeringAlert(Collections.emptyList()));
  }
}