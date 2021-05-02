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
import rjm.romek.finance.datapoint.model.DataPoint;

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

  public static Date createDate(int hours, int minutes) {

    return new Calendar.Builder()
        .setDate(2045, 2, 12)
        .setTimeOfDay(hours, minutes, 0)
        .build().getTime();
  }

  public static SortedMap<Date, MonetaryAmount> createDateMonetaryUnits(String currencyCode,
      int startingHour, int startingMinute, Number... values) {
    SortedMap<Date, MonetaryAmount> map = new TreeMap<>();
    List<Date> dates = createDates(startingHour, startingMinute, values.length);

    for (int i = 0; i < values.length; ++i) {
      map.put(dates.get(i), getSimpleMonetaryAmount(currencyCode, values[i]).getMonetaryAmount());
    }

    return map;
  }

  private static List<Date> createDates(int startingHour, int startingMinute, int length) {
    int hour = startingHour;
    int minute = startingMinute;
    List<Date> dates = new ArrayList<>();

    for (int i = 0; i < length; ++i) {
      dates.add(createDate(hour, minute));

      ++minute;
      if (minute >= 60) {
        minute = 0;
        ++hour;
      }
    }

    return dates;
  }

  public static List<DataPoint> createDataPoints(String currencyCode,
      int startingHour, int startingMinute, Number... values) {
    List<DataPoint> dataPoints = new ArrayList<>();
    List<Date> dates = createDates(startingHour, startingMinute, values.length);

    for (int i = 0; i < values.length; ++i) {
      dataPoints.add(new DataPoint(
          (long) i,
          dates.get(i),
          ADVISOR,
          currencyCode,
          values[i].doubleValue()
      ));


    }

    return dataPoints;
  }
}
