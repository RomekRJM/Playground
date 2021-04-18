package rjm.romek.finance;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.SortedMap;
import java.util.TreeMap;
import javax.money.Monetary;
import javax.money.MonetaryAmount;
import rjm.romek.finance.monetary.SimpleMonetaryAmount;
import rjm.romek.finance.persistency.DataPoint;

public class MonetaryDateUtil {

  private static final String CURRENCY = "USD";
  private static final String ADVISOR = "adv";

  public static SimpleMonetaryAmount getDollars(Number amount) {
    return getSimpleMonetaryAmount(CURRENCY, amount);
  }

  public static SimpleMonetaryAmount getSimpleMonetaryAmount(String currencyCode, Number amount) {
    return new SimpleMonetaryAmount(Monetary.getDefaultAmountFactory()
        .setCurrency(Monetary.getCurrency(currencyCode))
        .setNumber(amount)
        .create());
  }

  public static Date createDate(int hours, int minutes, int seconds) {
    return new Calendar.Builder()
        .setDate(2045, 2, 12)
        .setTimeOfDay(hours, minutes, seconds)
        .build().getTime();
  }

  public static SortedMap<Date, MonetaryAmount> createDateMonetaryUnits(String currencyCode,
      Number... values) {
    SortedMap<Date, MonetaryAmount> map = new TreeMap<>();

    for (int i = 0; i < values.length; ++i) {
      map.put(createDate(0, 0, i),
          getSimpleMonetaryAmount(currencyCode, values[i]).getMonetaryAmount());
    }

    return map;
  }

  public static List<DataPoint> createDataPoints(String currencyCode,
      Number... values) {
    List<DataPoint> dataPoints = new ArrayList<>();

    for (int i = 0; i < values.length; ++i) {
      dataPoints.add(new DataPoint(
          (long) i,
          createDate(0, 0, i),
          ADVISOR,
          currencyCode,
          values[i].doubleValue()
      ));
    }

    return dataPoints;
  }
}
