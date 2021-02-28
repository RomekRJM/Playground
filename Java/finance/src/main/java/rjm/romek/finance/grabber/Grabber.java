package rjm.romek.finance.grabber;

import java.util.Currency;
import java.util.Date;
import java.util.Map;

public interface Grabber {
    Map<Date, Currency> grabPrice();
}
