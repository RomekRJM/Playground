package rjm.romek.finance;

import java.util.Calendar;
import java.util.Date;

public class DateUtil {
  public static Date createDate(int hours, int minutes, int seconds) {
    return new Calendar.Builder()
        .setDate(2045, 2, 12)
        .setTimeOfDay(hours, minutes, seconds)
        .build().getTime();
  }
}
